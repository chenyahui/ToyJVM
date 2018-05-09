//
// Created by cyhone on 18-5-7.
//
#include <toyjvm/runtime/string_pool.h>
#include <toyjvm/runtime/class_loader.h>

namespace jvm {
    jobj StringPool::intern(jvm::ModifiedUTF8 &&utf8_data)
    {
        if (inner_str_objects.find(utf8_data) != inner_str_objects.end()) {
            return inner_str_objects[utf8_data];
        }

        auto char_array_class = Loader::instance()->loadArrayClass("[C");
        auto char_arr = new JvmArray<jchar>(utf8_data.asJCharArr(), char_array_class);
        auto string_class = Loader::instance()->loadNonArrayClass("java/lang/String");

        auto str_obj = new JvmObject(string_class);
        str_obj->setRef("value", "[C", char_arr);

        inner_str_objects[utf8_data] = str_obj;
        return str_obj;
    }

    std::string javaLangStringAsString(jobj str_obj)
    {
        assert(str_obj);
        auto char_array_obj = dynamic_cast<JvmArray<jchar> *>(str_obj->getRef("value", "[C"));
        auto &char_vec = char_array_obj->rawData();

        std::string str;
        str.resize(char_vec.size());
        std::copy(char_vec.begin(), char_vec.end(), str.begin());
        return str;
    }
}
