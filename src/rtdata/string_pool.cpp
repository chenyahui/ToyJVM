#include <jvm/rtdata/class_loader.h>
#include <jvm/rtdata/jvm_reference.h>
#include <jvm/rtdata/string_pool.h>
#include <map>
namespace cyh {

std::map<std::string, JObject*> g_innered_strs;
JObject* GetStringFromPool(ClassLoader* loader, std::string str)
{
    if (g_innered_strs.find(str) != g_innered_strs.end()) {
	return g_innered_strs[str];
    }

    auto char_array_class = loader->LoadClass("[C");
    auto jchar_arr = StringToUtf16Arr(str);
    auto char_array_obj = new JArray<j_char>(jchar_arr, char_array_class);

    auto string_class = loader->LoadClass("java/lang/String");

    auto str_obj = new JObject(string_class);
    std::string name = "value";
    std::string descriptor = "[C";
    str_obj->SetRefVar(name, descriptor, char_array_obj);

    g_innered_strs[str] = str_obj;

    return str_obj;
}

std::vector<j_char> StringToUtf16Arr(std::string& str)
{
    std::vector<j_char> result;
    for (size_t i = 0; i < str.size(); i++) {
	j_char item = str[i];
	result.push_back(item);
    }
    return result;
}

std::string TransJString(JObject* str_obj)
{
    assert(str_obj != NULL);
    std::string name = "value", descriptor = "[C";
    auto char_array_obj = dynamic_cast<JArray<j_char>*>(str_obj->GetRefVar(name, descriptor));
    auto& char_vec = char_array_obj->raw_data();

    return { char_vec.begin(), char_vec.end() };
}
}
