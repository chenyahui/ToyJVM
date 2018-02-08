#ifndef TOYJVM_RTDATA_JVM_REFERENCE_H
#define TOYJVM_RTDATA_JVM_REFERENCE_H
#include <jvm/utils/types.h>
#include <string>
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
    bool IsInstanceOf(JClass*);
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

    void SetRefVar(std::string& name, std::string& descriptor, JReference* obj);
    JReference* GetRefVar(std::string& name, std::string& descriptor);
    ~JObject() {}
    inline void set_extra(char* extra)
    {
	extra_ = extra;
    }

    template <typename T>
    T ExtraTo()
    {
	return (T)(extra_);
    }

    inline bool has_extra()
    {
	return extra_ != NULL;
    }

private:
    LocalVarRefs* fields_;
    char* extra_ = NULL;
};

class JBaseArray : public JReference {
public:
    JBaseArray(JClass* jclass)
	: JReference(jclass)
    {
    }

    virtual int array_length() = 0;
    ~JBaseArray()
    {
    }
};
template <typename T>
class JArray : public JBaseArray {
public:
    JArray(u4 count, JClass* jclass)
	: JBaseArray(jclass)
	, raw_data_(count)
    {
    }

    JArray(std::vector<T>& raw_data, JClass* jclass)
	: JBaseArray(jclass)
	, raw_data_(raw_data)
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

    inline int array_length() override
    {
	return raw_data_.size();
    }

private:
    std::vector<T> raw_data_;
};
}

#endif /* end of include guard: TOYJVM_RTDATA_JVM_REFERENCE_H */
