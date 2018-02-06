#ifndef TOYJVM_RTDATA_JVM_CLASS_H
#define TOYJVM_RTDATA_JVM_CLASS_H

#include <jvm/classfile/classfile.h>
#include <jvm/rtdata/local_vars.h>
namespace cyh {
class JField;
class JMethod;
class RuntimeConstPool;
class ClassLoader;
class JReference;
class JBaseArray;

class JClass {
public:
    JClass(ClassFile* classfile, ClassLoader* class_loader);
    // for array class
    JClass(ClassLoader*, std::string name);
    bool IsPublic();
    bool IsAccessibleTo(JClass* other);
    bool IsInterface();
    bool IsAbstract();
    bool IsSuper();

    JClass* ComponentClass();
    std::string GetComponentName();
    void ResolveSuperClass();
    void ResolveInterfaces();
    std::string GetPackageName();
    std::string JavaName();

    bool IsAssignableFrom(JClass*);
    bool IsSubClassOf(JClass*);
    bool IsImplements(JClass*);
    bool IsSubInterfaceOf(JClass*);
    bool IsSuperClassOf(JClass*);

    bool IsPrimitive();
    bool IsJlObject();
    bool IsJlCloneable();
    bool IsJioSerializable();

    bool IsArray();
    JBaseArray* ArrayFactory(u4);
    JClass* ArrayClass();

    JField* GetField(std::string& name, std::string& descriptor, bool is_static);
    // getter setter
    inline std::string& name()
    {
	return name_;
    }
    inline JClass* super_class()
    {
	return super_class_;
    }
    inline void set_instance_slot_count(u4 instance_slot_count)
    {
	instance_slot_count_ = instance_slot_count;
    }
    inline void set_static_slot_count(u4 static_slot_count)
    {
	static_slot_count_ = static_slot_count;
	static_vars_ = new LocalVarRefs(static_slot_count);
    }
    inline u4 instance_slot_count()
    {
	return instance_slot_count_;
    }
    inline const std::vector<JField*>& fields()
    {
	return fields_;
    }
    inline const std::vector<JMethod*>& methods()
    {
	return methods_;
    }
    inline LocalVarRefs* static_vars()
    {
	return static_vars_;
    }
    inline RuntimeConstPool* rt_const_pool()
    {
	return rt_const_pool_;
    }
    inline void set_class_loader(ClassLoader* loader)
    {
	class_loader_ = loader;
    }
    inline ClassLoader* class_loader()
    {
	return class_loader_;
    }
    inline std::vector<JClass*>& interfaces()
    {
	return interfaces_;
    }

    inline bool init_started()
    {
	return init_started_;
    }

    inline void start_init()
    {
	init_started_ = true;
    }

    inline std::string source_file()
    {
	return source_file_;
    }

private:
    u2 access_flags_ = 0;
    std::string name_;
    std::string super_class_name_;
    std::vector<std::string> interface_names_;
    RuntimeConstPool* rt_const_pool_ = NULL;
    std::vector<JField*> fields_;
    std::vector<JMethod*> methods_;
    ClassLoader* class_loader_ = NULL;
    JClass* super_class_ = NULL;
    std::vector<JClass*> interfaces_;
    u4 instance_slot_count_ = 0;
    u4 static_slot_count_ = 0;
    LocalVarRefs* static_vars_ = NULL;
    bool init_started_ = false;
    std::string source_file_;
};
}

#endif /* end of include guard: TOYJVM_RTDATA_JVM_CLASS_H */
