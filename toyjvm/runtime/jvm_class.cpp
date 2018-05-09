//
// Created by cyhone on 18-4-17.
//
#include <toyjvm/runtime/jvm_class.h>
#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/utilities/javautils.h>
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/runtime/jvm_member.h>

namespace jvm {
    const std::string &JvmBaseClass::descriptor() const
    {
        if (class_descriptor_.empty()) {
            class_descriptor_ = classNameToDescriptor(class_name_);
        }

        return class_descriptor_;
    }

    const std::vector<JvmClass *> &JvmBaseClass::interfaces() const
    {
        return interfaces_;
    }

    const std::string &JvmBaseClass::name() const
    {
        return class_name_;
    }

    JvmClass *JvmBaseClass::superClass() const
    {
        return super_class_;
    }

    const AccessFlags &JvmBaseClass::accessFlags() const
    {
        return access_flags_;
    }

    bool JvmBaseClass::isSubClassOf(jvm::JvmBaseClass *klass) const
    {
        assert(!klass->isArray() && !klass->access_flags_.isInterface());
        auto t = dynamic_cast<JvmClass *>(klass);
        assert(t != nullptr);

        for (auto c = super_class_; c != nullptr; c = c->super_class_) {
            if (c == t) {
                return true;
            }
        }
        return false;
    }

    bool JvmBaseClass::isImplements(jvm::JvmBaseClass *iface) const
    {
        assert(iface->access_flags_.isInterface());
        auto t = dynamic_cast<JvmClass *>(iface);
        assert(t != nullptr);

        for (auto c = this; c != nullptr; c = c->super_class_) {
            for (const auto &inter : c->interfaces_) {
                if (inter == t || inter->isSubInterfaceOf(t)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool JvmBaseClass::isAssignableFrom(jvm::JvmBaseClass *t) const
    {
        assert(!t->isArray());
        if (this == t) return true;
        if (t->accessFlags().isInterface()) {
            return isImplements(t);
        } else {
            return isSubClassOf(t);
        }
    }

    JvmPrimitiveClass::JvmPrimitiveClass(const std::string &class_name)
            : JvmBaseClass(class_name, AccessFlags::PUBLIC),
              is_primitive_(true)
    {
    }

    JvmArrayClass::JvmArrayClass(const std::string &class_name)
            : JvmBaseClass(class_name, AccessFlags::PUBLIC),
              is_array_(true),
              component_name_(descriptorToClassName(class_name.substr(1)))
    {
        assert(class_name[0] == '[');

        super_class_ = Loader::instance()->loadNonArrayClass("java/lang/Object");
        interfaces_.push_back(Loader::instance()->loadNonArrayClass("java/lang/Cloneable"));
        interfaces_.push_back(Loader::instance()->loadNonArrayClass("java/io/Serializable"));
    }

    JvmBaseClass *JvmArrayClass::componentClass() const
    {
        return Loader::instance()->loadClass(component_name_);
    }

    bool JvmArrayClass::isAssignableFrom(jvm::JvmBaseClass *t) const
    {
        if (this == t) return true;
        if (!t->isArray()) {
            return JvmBaseClass::isAssignableFrom(t);
        }
        auto sc = componentClass();
        auto tc = dynamic_cast<JvmArrayClass *>(t)->componentClass();

        return sc->isAssignableFrom(tc);
    }

    JvmBaseArray *JvmArrayClass::arrayFactory(jvm::u4 count)
    {
        if (class_name_ == "[Z") {
            return new JvmArray<jbool>(count, this);
        }
        if (class_name_ == "[B") {
            return new JvmArray<jbyte>(count, this);
        }
        if (class_name_ == "[C") {
            return new JvmArray<jchar>(count, this);
        }
        if (class_name_ == "[S") {
            return new JvmArray<jshort>(count, this);
        }
        if (class_name_ == "[I") {
            return new JvmArray<jint>(count, this);
        }
        if (class_name_ == "[J") {
            return new JvmArray<jlong>(count, this);
        }
        if (class_name_ == "[F") {
            return new JvmArray<jfloat>(count, this);
        }
        if (class_name_ == "[D") {
            return new JvmArray<jdouble>(count, this);
        }
        return new JvmArray<JvmRef>(count, this);
    }

    // 不能在构造函数中使用shared_from_this
    JvmClass::JvmClass(jvm::ClassFile *class_file)
            : JvmBaseClass(true, class_file->className(), class_file->access_flags_),
              instance_slots_count_(0),
              static_slots_count_(0),
              runtime_const_pool_(class_file->const_pool_, this)
    {
        if (!isJavaLangObject()) {

            auto getClass = [class_file](u2 class_index) {
                return Loader::instance()->loadNonArrayClass(
                        class_file->const_pool_.classNameOf(class_index)
                );
            };
            // 解析super class
            super_class_ = getClass(class_file->super_class_);

            // 解析interfaces
            for (auto item: class_file->interfaces_) {
                interfaces_.push_back(getClass(item));
            }
        }

        for (auto field_info : class_file->fields_) {
            fields_.push_back(new JvmField(this, field_info));
        }

        for (auto method_info: class_file->methods_) {
            methods_.push_back(new JvmMethod(this, method_info));
        }
    }

    JvmMethod *JvmClass::getMainMethod()
    {
        return getStaticMethod("main", "([Ljava/lang/String;)V");
    }

    JvmMethod *JvmClass::getStaticMethod(const std::string &name, const std::string &descriptor)
    {
        for (auto method: methods_) {
            if (method->accessFlags().isStatic()
                && method->name() == name
                && method->descriptor() == descriptor) {
                return method;
            }
        }
        return nullptr;
    }

    bool JvmClass::isJavaLangObject()
    {
        return class_name_ == "java/lang/Object";
    }

    bool JvmClass::isSubInterfaceOf(jvm::JvmClass *inter) const
    {
        for (auto &super_inter:interfaces_) {
            if (super_inter == inter || super_inter->isSubInterfaceOf(inter)) {
                return true;
            }
        }

        return false;
    }

    JvmField *JvmClass::getField(const std::string &name, const std::string &descriptor, bool isStatic)
    {
        for (auto c = this; c != nullptr; c = c->super_class_) {
            for (auto field : c->fields_) {
                if (field->accessFlags().isStatic() == isStatic
                    && field->descriptor() == descriptor
                    && field->name() == name) {
                    return field;
                }
            }
        }

        return nullptr;
    }
}
