//
// Created by cyhone on 18-4-19.
//

#ifndef TOYJVM_RUNTIME_CONST_POOL_H
#define TOYJVM_RUNTIME_CONST_POOL_H

#include <vector>
#include <boost/any.hpp>
#include <toyjvm/classfile/const_pool.h>
#include <tuple>
#include <toyjvm/classfile/const_infos.h>

namespace jvm {

    class JvmClass;

    class RuntimeConstPool : public boost::noncopyable {
    public:
        explicit RuntimeConstPool(const ConstPool &const_pool, std::shared_ptr<JvmClass> klass);

        template<typename T>
        const T at(size_t index) const
        {
            return boost::any_cast<T>(std::get<0>(pool_[index]));
        }

        // 其所属的class
        inline std::shared_ptr<JvmClass> ofClass() const
        {
            return klass_.lock();
        }

    private:
        template<typename ConstRefType, typename SymbolRefType>
        void addRef(int index, BaseConstInfo *item)
        {
            auto info = dynamic_cast<ConstRefType>(item);
            auto ref_info = std::make_shared<SymbolRefType>(*this, info);
            pool_[index] = std::make_tuple<boost::any, ConstType>(ref_info, item->tag());
        }

        template<typename ConstRefType>
        void addVal(int index, BaseConstInfo *item)
        {
            auto info = dynamic_cast<ConstRefType>(item);
            pool_[index] = std::make_tuple<boost::any, ConstType>(info->val(), item->tag());
        }

    private:
        using PoolItem = std::tuple<boost::any, ConstType>;
        std::vector<PoolItem> pool_;
        std::weak_ptr<JvmClass> klass_; // 该runtimePool所属的class
    };
}
#endif //TOYJVM_RUNTIME_CONST_POOL_H
