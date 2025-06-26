#include "libini/libini.hpp"

libini::ini::ini(const std::string &file_name)
{
    this->_file_name = file_name;
    this->_ini_mgr = _IniMgr(this->_file_name);
    this->_data = this->_ini_mgr._data;
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

void libini::ini::addSection(_Section &sec)
{
    this->_data.emplace(sec.get_name(), sec);
}

void libini::ini::add(const std::string &sec_name, const std::string &nod_key,
                      const std::string &nod_value)
{
    if (!this->is_section_exist(sec_name)) {
        _Section sec(sec_name);
        this->addSection(sec);
    }
    this->_data.at(sec_name).add_node(nod_key, nod_value);
}

void libini::ini::add(const std::string &nod_key, const std::string &nod_value)
{
    this->add("", nod_key, nod_value);
}

void libini::ini::set(const std::string &sec_name, const std::string &nod_key, const std::string &nod_value)
{
    if (!this->is_section_exist(sec_name))
    {
        _Section sec(sec_name);
        this->addSection(sec);
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
        this->addSection(sec);
}

libini::_Section *libini::ini::getSection(const std::string &sec_name)
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

std::vector<std::string> libini::ini::getAllSection(void)
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

std::string libini::ini::to_string(void)
{
    std::string result;

    for (std::map<std::string, libini::_Section>::iterator i =
             this->_data.begin();
         i != this->_data.end(); i++)
        result += i->second.to_string() + "\n";

    return result;
}

INI_ERR libini::ini::write(const std::string &file_name)
{
    std::string _file_name = this->_file_name;

    if (file_name != "")
        _file_name = file_name;

    std::fstream out_file;
    out_file.open(_file_name,
                 std::ifstream::in | std::ifstream::out | std::fstream::app);

    if (!out_file.is_open())
        return CANNOT_OPEN_FILE;

    out_file << this->to_string() << std::endl;
    out_file.close();
    out_file.clear();

    return NO_ERRORS;
}

INI_ERR libini::ini::format(const std::string file_name)
{
    return this->write(file_name);
}