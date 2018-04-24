//
// Created by cyhone on 18-4-22.
//

#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/classfile/classfile.h>
#include <toyjvm/runtime/jvm_class.h>
#include <toyjvm/runtime/jvm_member.h>

namespace jvm {
    std::shared_ptr<JvmClass> ClassLoader::loadClass(const std::string &class_name)
    {
        if (class_map_.find(class_name) != class_map_.end()) {
            return class_map_[class_name];
        }
        auto klass = loadNonArrayClass(class_name);
        class_map_[class_name] = klass;

        return klass;
    }

    std::shared_ptr<JvmClass> ClassLoader::loadNonArrayClass(const std::string &class_name)
    {
        auto class_bytes = class_path_->readClass(class_name);
        auto klass = defineClass(std::move(class_bytes));

        prepareClass(klass.get());
    }

    std::shared_ptr<JvmClass> ClassLoader::defineClass(jvm::bytes class_bytes)
    {
        std::unique_ptr<ClassFile> classfile(new ClassFile(std::move(class_bytes)));
        classfile->parse();

        return std::make_shared<JvmClass>(classfile.get());
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
        auto &rt_const_pool = klass->runtimeConstPool();

#define CopySlot(Type) \
static_slots->set<Type>(slot_index, rt_const_pool.at<Type>(const_value_index));

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
                } else {
                    // TODO string
                    // TODO object
                    // todo array
                }
            }

        }
#undef CopySlot
    }

}