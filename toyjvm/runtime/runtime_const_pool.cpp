//
// Created by cyhone on 18-4-20.
//
#include <toyjvm/runtime/runtime_const_pool.h>
#include <toyjvm/runtime/symbol_ref.h>

namespace jvm {
    RuntimeConstPool::RuntimeConstPool(const ConstPool &const_pool,
                                       JvmClass *klass)
            : klass_(klass)
    {
        const auto &const_infos = const_pool.constInfos();
        pool_.resize(const_infos.size());

        for (int i = 1; i < const_infos.size(); i++) {
            auto item = const_infos[i];

            switch (item->tag()) {
                case ConstType::Integer: {
                    addVal<ConstIntegerInfo *>(i, item);
                    break;
                }
                case ConstType::Float: {
                    addVal<ConstFloatInfo *>(i, item);
                    break;
                }
                case ConstType::Double: {
                    addVal<ConstDoubleInfo *>(i, item);
                    i++;
                    break;
                }
                case ConstType::Long: {
                    addVal<ConstLongInfo *>(i, item);
                    i++;
                    break;
                }
                case ConstType::String: {
                    addVal<ConstStringInfo *>(i, item);
                    break;
                }

                case ConstType::Class: {
                    addRef<ConstClassInfo, ClassRef>(i, item);
                    break;
                }

                case ConstType::FieldRef: {
                    addRef<ConstFieldRefInfo, FieldRef>(i, item);
                    break;
                }
                case ConstType::MethodRef: {
                    addRef<ConstMethodRefInfo, MethodRef>(i, item);
                    break;
                }
                case ConstType::InterfaceMethodRef: {
                    addRef<ConstInterfaceMethodRefInfo, InterfaceMethodRef>(i, item);
                    break;
                }
            }
        }


    }
}
