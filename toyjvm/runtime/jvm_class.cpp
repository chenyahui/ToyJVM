//
// Created by cyhone on 18-4-17.
//
#include <toyjvm/runtime/jvm_class.h>
#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/utilities/javautils.h>
#include <toyjvm/runtime/jvm_reference.h>

namespace jvm {
    const std::vector<std::shared_ptr<JvmClass>> &JvmBaseClass::interfaces() const
    {
        return interfaces_;
    }

    const std::shared_ptr<JvmClass> &JvmBaseClass::superClass() const
    {
        return super_class_;
    }

    const AccessFlags &JvmBaseClass::accessFlags() const
    {
        return access_flags_;
    }

    JvmArrayClass::JvmArrayClass(const std::string &class_name)
            : JvmBaseClass(true, class_name, AccessFlags::PUBLIC)
    {
        super_class_ = Loader::instance()->loadClass("java/lang/Object");
        interfaces_.push_back(Loader::instance()->loadClass("java/lang/Cloneable"));
        interfaces_.push_back(Loader::instance()->loadClass("java/io/Serializable"));
    }

    std::shared_ptr<JvmBaseArray> JvmArrayClass::arrayFactory(jvm::u4 count)
    {
        if (class_name_ == "[Z") {
            return std::make_shared<JvmArray<jbool>>(count, shared_from_this());
        }
        if (class_name_ == "[B") {
            return std::make_shared<JvmArray<jbyte>>(count, shared_from_this());
        }
        if (class_name_ == "[C") {
            return std::make_shared<JvmArray<jchar>>(count, shared_from_this());
        }
        if (class_name_ == "[S") {
            return std::make_shared<JvmArray<jshort>>(count, shared_from_this());
        }
        if (class_name_ == "[I") {
            return std::make_shared<JvmArray<jint>>(count, shared_from_this());
        }
        if (class_name_ == "[J") {
            return std::make_shared<JvmArray<jlong>>(count, shared_from_this());
        }
        if (class_name_ == "[F") {
            return std::make_shared<JvmArray<jfloat>>(count, shared_from_this());
        }
        if (class_name_ == "[D") {
            return std::make_shared<JvmArray<jdouble>>(count, shared_from_this());
        }

        std::make_shared<JvmArray<JvmRef>>(count, shared_from_this());
    }

    // 不能在构造函数中使用shared_from_this
    JvmClass::JvmClass(jvm::ClassFile *class_file)
            : JvmBaseClass(true, class_file->className(), class_file->access_flags_),
              instance_slots_count_(0),
              static_slots_count_(0),
              runtime_const_pool_(class_file->const_pool_, shared_from_this())
    {
        if (isNotJavaLangObject()) {
            // 解析super class
            super_class_ = Loader::instance()->loadClass(
                    class_file->const_pool_.classNameOf(class_file->super_class_)
            );
            // 解析interfaces
            for (auto item: class_file->interfaces_) {
                interfaces_.push_back(Loader::instance()->loadClass(
                        class_file->const_pool_.classNameOf(item)
                ));
            }
        }

        // 解析fields和methods
        auto this_ptr = shared_from_this();
        for (auto &field_info : class_file->fields_) {
            fields_.push_back(std::make_shared<JvmField>(this_ptr, field_info.get()));
        }

        for (auto &method_info: class_file->methods_) {
            methods_.push_back(std::make_shared<JvmMethod>(this_ptr, method_info.get()));
        }
    }

    bool JvmClass::isNotJavaLangObject()
    {
        return class_name_ != "java/lang/Object";
    }

    bool JvmClass::isSubClassOf(jvm::JvmClass *klass) const
    {
        for (auto c = super_class_; c != nullptr; c = c->super_class_) {
            if (c == klass) {
                return true;
            }
        }
        return false;
    }
}
