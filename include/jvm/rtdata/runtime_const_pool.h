#ifndef TOYJVM_RTDATA_RUNTIME_CONST_POOL_H
#define TOYJVM_RTDATA_RUNTIME_CONST_POOL_H

#include <jvm/classfile/constant_infos.h>
#include <jvm/classfile/constant_pool.h>
#include <jvm/rtdata/jvm_class.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/symbol_ref.h>

namespace cyh {

using ConstVar = char*;

class RuntimeConstPool {
public:
    RuntimeConstPool(JClass* jclass, ConstantPool* const_pool);
    ~RuntimeConstPool();

    template <typename T>
    T* GetRef(int i)
    {
	return (T*)(const_vars_[i]);
    }

    template <typename T>
    T GetVal(int i)
    {
	return *(T*)(const_vars_[i]);
    }

    inline u1 GetType(int i)
    {
	return var_types_[i];
    }
    inline JClass* jclass()
    {
	return jclass_;
    }

private:
    template <typename T>
    void PutVal(int index, T val)
    {
	const_vars_[index] = (ConstVar)(new T(val));
    }

    template <typename T>
    void PutRef(int index, T* ref)
    {
	const_vars_[index] = (ConstVar)(ref);
    }
    JClass* jclass_;
    std::vector<ConstVar> const_vars_;
    std::vector<u1> var_types_;
};
}

#endif /* end of include guard: TOYJVM_RTDATA_RUNTIME_CONST_POOL_H */
