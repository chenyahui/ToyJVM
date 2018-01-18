#include <jvm/rtdata/runtime_const_pool.h>
#include <string>
#include <jvm/rtdata/symbol_ref.h>

using namespace cyh;
#define ADD_VAL(CONSTINFO, TYPE)                                   \
    auto info = dynamic_cast<Constant##CONSTINFO##Info*>(cp_info); \
    PutVal<TYPE>(i, info->val());

#define ADD_REF(CINFO, REF)                                              \
    auto info = dynamic_cast<Constant##CINFO##Info*>(cp_info); \
    auto ref_info = new REF(this, info); \
    PutRef<REF>(i, ref_info);

RuntimeConstPool::RuntimeConstPool(JClass* jclass, ConstantPool* const_pool)
    : jclass_(jclass)
{
    auto& infos = const_pool->cpinfos();

    auto info_len = infos.size();
    const_vars_.resize(info_len);
    var_types_.resize(info_len);

    for (size_t i = 1; i < info_len; ++i) {
	auto cp_info = infos[i];
	auto tag = cp_info->tag();

	var_types_[i] = tag;

	switch (cp_info->tag()) {
	case Integer: {
	    ADD_VAL(Integer, int)
	    break;
	}
	case Float: {
	    ADD_VAL(Integer, float)
	    break;
	}
	case Double: {
	    ADD_VAL(Double, double)
	    i++;
	    break;
	}
	case Long: {
	    ADD_VAL(Long, long)
	    i++;
	    break;
	}
	case String: {
	    ADD_VAL(String, std::string)
	    break;
	}
	case Klass: {
	    ADD_REF(Klass, ClassRef)
	    break;
	}
	case Fieldref: {
	    ADD_REF(FieldRef, FieldRef)
	    break;
	}
	case Methodref: {
	    ADD_REF(MethodRef, MethodRef)
	    break;
	}
	case InterfaceMethodref: {
	    ADD_REF(InterfaceMethodRef, InterfaceMethodRef)
	    break;
	}
	}
    }
}

RuntimeConstPool::~RuntimeConstPool()
{
    for (auto item : const_vars_) {
	delete item;
    }
}
