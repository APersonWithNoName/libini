#include "libini/libini.hpp"
#include <cstddef>
#include <cstdio>

libini::_Section::_Section(const std::string &sec_name)
{
    this->_name = sec_name;
}

bool libini::_Section::is_node_exist(const std::string &nod_key)
{
    if (nod_key == this->_data.end()->first) {
        return true;
    }
    else {
        if (this->_data.find(nod_key) == this->_data.end())
            return false;
        else
            return true;
    }
}

INI_ERR libini::_Section::add_node(const std::string &nod_key,
                                const std::string &nod_value)
{
    if (this->is_node_exist(nod_key)) 
        return NODE_EXIST;
    
    this->_data[nod_key]._value = nod_value;
    return NO_ERRORS;
}

void libini::_Section::append_section(_Section &sec)
{
    this->_data.insert(sec._data.begin(), sec._data.end());
}

void libini::_Section::set_node(const std::string &nod_key, const std::string &nod_value)
{
    if (this->is_node_exist(nod_key))
        this->_data[nod_key]._value = nod_value;
    else
        this->add_node(nod_key, nod_value);
}

void libini::_Section::rename(const std::string &new_name)
{
    this->_name = new_name;
}

INI_ERR libini::_Section::remame_node(const std::string& old_key_name, const std::string& new_key_name) 
{
    if (this->is_node_exist(old_key_name))
        return NODE_NOT_EXIST;
    
    this->_data[new_key_name] = this->_data[old_key_name];
    this->remove(old_key_name);
    return NO_ERRORS;
}

std::string libini::_Section::get_name(void)
{
    return this->_name;
}

std::string libini::_Section::get_value(const std::string &nod_key)
{
    if (this->is_node_exist(nod_key))
        return this->_data.at(nod_key)._value;

    return "";
}

std::vector<std::string> libini::_Section::get_all_keys(void)
{
    std::vector<std::string> result;

    for (std::map<std::string, libini::_Node>::iterator i = this->_data.begin();
         i != this->_data.end(); i++)
    {
        result.push_back(i->first);
    }

    return result;
}

INI_ERR libini::_Section::remove(const std::string &nod_key)
{
    if (this->is_node_exist(nod_key)) {
        this->_data.erase(nod_key);
        return NO_ERRORS;
    }
    
    return NODE_NOT_EXIST;
}

void libini::_Section::clear(void)
{
    this->_data.clear();
}

std::string libini::_Section::to_string(const std::string& node_format, const std::string& title_format)
{
    char *result;

    if (this->_name != "")
        std::snprintf(result, sizeof(result), title_format.c_str(), this->_name.c_str());
    else
        result = {};
    for (std::map<std::string, libini::_Node>::iterator i = this->_data.begin(); i != this->_data.end(); i++) {
        std::snprintf(result, sizeof(result), (node_format + '\n').c_str(), i->first.c_str(), i->second._value.c_str());
    }

    return std::string(result, sizeof(result));
}

/*
std::string libini::_Section::to_string(void)
{
    std::string result;

    if (this->_name == "")
        result = "";
    else
        result = "[" + this->_name + "]\n";

    for (std::map<std::string, libini::_Node>::iterator i = this->_data.begin();
         i != this->_data.end(); i++)
        result += i->first + "=" + i->second._value + "\n";
    return result;
}
    */