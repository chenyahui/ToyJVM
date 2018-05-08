//
// Created by cyhone on 18-4-22.
//

#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/classfile/classfile.h>
#include <toyjvm/runtime/jvm_class.h>
#include <toyjvm/runtime/jvm_member.h>

#include <glog/logging.h>
#include "string_pool.h"

namespace jvm {
    void ClassLoader::detailInfo()
    {
        DLOG(INFO) << "non array class 共有: " << non_array_class_map_.size() << " 个";
        for (auto &kv: non_array_class_map_) {
            DLOG(INFO) << "==> " << kv.first;
        }
    }

    void ClassLoader::initBasicClasses()
    {
        auto jl_class = loadNonArrayClass("java/lang/Class");
        for (auto &kv : non_array_class_map_) {
            if (kv.second->meta_class_ != nullptr) {
                kv.second->meta_class_ = new JvmRef(kv.second);
            }
        }
    }

    static const std::unordered_map<std::string, std::string> primitiveTypes = {
            {"void",    "V"},
            {"boolean", "Z"},
            {"byte",    "B"},
            {"short",   "S"},
            {"int",     "I"},
            {"long",    "J"},
            {"char",    "C"},
            {"float",   "F"},
            {"double",  "D"}
    };

    void ClassLoader::initPrimitiveClasses()
    {
        for (auto &kv : primitiveTypes) {
            auto primitive_class = new JvmPrimitiveClass(kv.first);
            auto jlc_obj = new JvmRef(non_array_class_map_["java/lang/Class"]);
            primitive_class->meta_class_ = jlc_obj;

            primitive_class_map[kv.first] = primitive_class;
        }
    }

    JvmBaseClass *ClassLoader::loadClass(const std::string &class_name)
    {
        if (class_name[0] == '[') {
            return loadArrayClass(class_name);
        } else if (primitive_class_map.find(class_name) != primitive_class_map.end()) {
            return primitive_class_map[class_name];
        } else {
            return loadNonArrayClass(class_name);
        }
    }

    JvmArrayClass *ClassLoader::loadArrayClass(const std::string &class_name)
    {
        if (array_class_map_.find(class_name) == array_class_map_.end()) {
            array_class_map_[class_name] = new JvmArrayClass(class_name);

            for (auto &kv : array_class_map_) {
                if (kv.second->meta_class_ == nullptr) {
                    kv.second->meta_class_ = new JvmRef(kv.second);
                }
            }
        }
        return array_class_map_[class_name];
    }

    JvmClass *ClassLoader::loadNonArrayClass(const std::string &class_name)
    {
        if (non_array_class_map_.find(class_name) == non_array_class_map_.end()) {

            auto class_bytes = class_path_->readClass(class_name);
            auto klass = defineClass(std::move(class_bytes));
            prepareClass(klass);

            non_array_class_map_[class_name] = klass;

            for (auto &kv : non_array_class_map_) {
                if (kv.second->meta_class_ != nullptr) {
                    kv.second->meta_class_ = new JvmRef(kv.second);
                }
            }
        }


        return non_array_class_map_[class_name];
    }

    JvmClass *ClassLoader::defineClass(jvm::bytes class_bytes)
    {
        std::unique_ptr<ClassFile> classfile(new ClassFile(std::move(class_bytes)));
        classfile->parse();

        return new JvmClass(classfile.get());
    }

    static void calcInstanceFieldSlotIds(JvmClass *klass);

    static void calcStaticFieldSlotIds(JvmClass *klass);

    static void allocAndInitStaticVars(JvmClass *klass);

    void prepareClass(JvmClass *klass)
    {
        calcInstanceFieldSlotIds(klass);
        calcStaticFieldSlotIds(klass);
        allocAndInitStaticVars(klass);
    }

    void calcInstanceFieldSlotIds(JvmClass *klass)
    {
        auto super_class = klass->superClass();
        auto slot_num = super_class != nullptr ? super_class->instanceSlotsCount() : 0;

        for (auto field : klass->fields()) {
            if (!field->accessFlags().isStatic()) {
                field->setSlotIndex(slot_num++);
                if (field->isLongOrDouble()) {
                    slot_num++;
                }
            }
        }

        klass->setInstanceSlotsCount(slot_num);
    }

    void calcStaticFieldSlotIds(JvmClass *klass)
    {
        size_t slot_num = 0;
        for (auto field : klass->fields()) {
            if (field->accessFlags().isStatic()) {
                field->setSlotIndex(slot_num++);

                if (field->isLongOrDouble()) {
                    slot_num++;
                }
            }
        }

        klass->allocStaticSlots(slot_num);
    }

    void allocAndInitStaticVars(JvmClass *klass)
    {
        auto static_slots = klass->staticFields();
        auto &const_pool = klass->runtimeConstPool();

#define CopySlot(Type) \
static_slots->set<Type>(slot_index, const_pool.at<Type>(const_value_index));

        for (auto field : klass->fields()) {
            if (field->accessFlags().isStatic()
                && field->accessFlags().isFinal()
                && field->constValueIndex() > 0) {
                auto const_value_index = field->constValueIndex();
                auto slot_index = field->slotIndex();
                auto &descriptor = field->descriptor();
                if (descriptor == "Z" ||
                    descriptor == "B" ||
                    descriptor == "C" ||
                    descriptor == "S" ||
                    descriptor == "I") {
                    CopySlot(jint)
                } else if (descriptor == "J") {
                    CopySlot(jlong)
                } else if (descriptor == "F") {
                    CopySlot(jfloat)
                } else if (descriptor == "D") {
                    CopySlot(jdouble)
                } else if (descriptor == "Ljava/lang/String;") {
                    auto modified_utf8 = const_pool.at<ModifiedUTF8>(const_value_index);
                    static_slots->set<jobj>(slot_index, StringPool::get(modified_utf8));
                } else {
                    // TODO object
                    // todo array
                }
            }

        }
#undef CopySlot
    }

}