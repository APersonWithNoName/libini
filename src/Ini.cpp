#include "libini/Error.hpp"
#include "libini/libini.hpp"

libini::ini::ini(const std::string &file_name)
{
    this->_file_name = file_name;
    //this->_ini_mgr = _IniMgr(this->_file_name);
    //this->_data = this->_ini_mgr._data;
}

libini::Error libini::ini::load_file(const std::string &file_name)
{
    /*this->_ini_mgr = _IniMgr(this->_file_name);
    INI_ERR status = this->_ini_mgr.parse_file().get_errcode();

    if (status == NO_ERRORS) {
        this->_data = this->_ini_mgr._data;
    }

    return status;-*/
  libini::Error err = this->_ini_mgr.parse_file();
  this->_data = this->_ini_mgr._data;
  return err;
}

bool libini::ini::is_section_exist(const std::string &sec_name)
{
    if (sec_name == this->_data.end()->first) {
        return true;
    }
    else {
        if (this->_data.find(sec_name) == this->_data.end())
            return false;
        else
            return true;
    }
}

void libini::ini::add_section(_Section &sec)
{
    this->_data.emplace(sec.get_name(), sec);
}

INI_ERR libini::ini::add_section(const std::string &sec_name)
{
    if (this->is_section_exist(sec_name))
        return SECTION_EXIST;

    this->_data.emplace(sec_name, _Section(sec_name));
 
    return NO_ERRORS;
}

INI_ERR libini::ini::add(const std::string &sec_name, const std::string &nod_key, const std::string &nod_value)
{
    if (!this->is_section_exist(sec_name))
        this->set(sec_name, nod_key, nod_value);
    else {
        if (!this->_data.at(sec_name).is_node_exist(nod_key))
            this->set(sec_name, nod_key, nod_value);
        else 
            return NODE_EXIST;
    }

    return NO_ERRORS;
}

INI_ERR libini::ini::add(const std::string &nod_key, const std::string &nod_value)
{
    return this->add("", nod_key, nod_value);
}

void libini::ini::set(const std::string &sec_name, const std::string &nod_key, const std::string &nod_value)
{
    if (!this->is_section_exist(sec_name))
    {
        _Section sec(sec_name);
        this->add_section(sec);
    }
    this->_data.at(sec_name).set_node(nod_key, nod_value);
}

void libini::ini::set(const std::string &nod_key, const std::string &nod_value)
{
    this->set("", nod_key, nod_value);
}

void libini::ini::append(ini &iniIn)
{
    this->_data.insert(iniIn._data.begin(), iniIn._data.end());
}

void libini::ini::append_section(_Section &sec)
{
    std::string sec_name = sec.get_name();

    if (this->is_section_exist(sec_name))
        this->_data.at(sec_name).append_section(sec);
    else
        this->add_section(sec);
}

libini::_Section *libini::ini::get_section(const std::string &sec_name)
{
    if (this->is_section_exist(sec_name))
        return &(this->_data.at(sec_name));
    
    return NULL;
}

std::string libini::ini::get_value(const std::string &sec_name,
                                   const std::string &nod_key)
{
    if (this->is_section_exist(sec_name))
        return this->_data.at(sec_name).get_value(nod_key);

    return "";
}

std::string libini::ini::get_value(const std::string &nod_key)
{
    return this->get_value("", nod_key);
}

std::vector<std::string> libini::ini::get_all_section(void)
{
    std::vector<std::string> result;

    for (std::map<std::string, libini::_Section>::iterator i =
             this->_data.begin();
         i != this->_data.end(); i++)
        result.push_back(i->first);

    return result;
}

INI_ERR libini::ini::remove_node(const std::string &sec_name, const std::string &nod_key)
{
    if (this->is_section_exist(sec_name))
        return this->_data.at(sec_name).remove(nod_key);

    return SECTION_NOT_EXIST;
}

INI_ERR libini::ini::remove_node(const std::string &nod_key)
{
    return this->remove_node("", nod_key);
}

INI_ERR libini::ini::remove_sec(const std::string &sec_name)
{
    if (this->is_section_exist(sec_name)) {
        this->_data.at(sec_name).clear();
        return NO_ERRORS;
    }
    else
        return SECTION_NOT_EXIST;
}

void libini::ini::clear(void)
{
    this->_data.clear();
}

std::string libini::ini::to_string(const std::string& file_format, const std::string& node_format, const std::string& title_format)
{
    char *result = {};

    for (std::map<std::string, libini::_Section>::iterator i = this->_data.begin(); i != this->_data.end(); i++) {
        snprintf(result, sizeof(result), (file_format + '\n').c_str(), i->second.to_string(node_format, title_format).c_str());
    }

    return std::string(result, sizeof(result));
}

INI_ERR libini::ini::write(const std::string& file_name, const std::string& file_format, const std::string& node_format, const std::string& title_format)
{
    std::string __file_name;
    if (file_name == "")
        __file_name = this->_file_name;
    else
        __file_name = file_name;

    std::fstream out_file;
    out_file.open(__file_name, std::fstream::in | std::fstream::out | std::fstream::app);

    if (!out_file.is_open())
        return CANNOT_OPEN_FILE;

    out_file << this->to_string(file_format, node_format, title_format);
    out_file.close();
    out_file.clear();

    return NO_ERRORS;
}
