#ifndef MY_JVM_CLASSFILE_ATTRIBUTE_TABLE_H
#define MY_JVM_CLASSFILE_ATTRIBUTE_TABLE_H

#include <jvm/classfile/constant_pool.h>

namespace cyh{
	class AttributeInfo{
		public:
			virtual void ReadInfo(ClassReader&) = 0;
			virtual ~AttributeInfo(){}
	};

	class AttributeTable{
		public:
			void Read(ClassReader& reader,ConstantPool*);
		private:
			AttributeInfo* ReadAttributeInfo(ClassReader&,ConstantPool*);
			AttributeInfo* NewAttributeInfo(std::string attrname, ConstantPool*);
			std::vector<AttributeInfo*> attributes_infos_;
	};
}

#endif
