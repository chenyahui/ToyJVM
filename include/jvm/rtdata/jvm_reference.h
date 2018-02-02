#ifndef TOYJVM_RTDATA_JVM_REFERENCE_H
#define TOYJVM_RTDATA_JVM_REFERENCE_H
#include <jvm/utils/types.h>
#include <vector>

namespace cyh {
class JClass;
class LocalVarRefs;

class JReference {
public:
    JReference(JClass* jclass)
	: jclass_(jclass)
    {
    }
    inline JClass* jclass()
    {
	return jclass_;
    }
    virtual ~JReference() {}
protected:
    JClass* jclass_;
};

class JObject : public JReference {
public:
    JObject(JClass* jclass);
    inline LocalVarRefs* fields()
    {
	return fields_;
    }

    bool IsInstanceOf(JClass*);
    ~JObject() {}
private:
    LocalVarRefs* fields_;
};

class JBaseArray : public JReference {
public:
    JBaseArray(u4 count, JClass* jclass)
	: JReference(jclass)
	, count_(count)
    {
    }

    virtual int array_length()
    {
	return count_;
    }
    ~JBaseArray()
    {
    }

protected:
    u4 count_;
};
template <typename T>
class JArray : public JBaseArray {
public:
    JArray(u4 count, JClass* jclass)
	: JBaseArray(count, jclass)
	, raw_data_(count)
    {
    }

    std::vector<T>& raw_data()
    {
	return raw_data_;
    }
    inline T& operator[](int index)
    {
	assert(index < raw_data_.size());
	return raw_data_[index];
    }

private:
    std::vector<T> raw_data_;
};
}

#endif /* end of include guard: TOYJVM_RTDATA_JVM_REFERENCE_H */
