#include "libini/libini.hpp"
#include <string>


libini::_IniMgr::_IniMgr(const std::string file_name)
{
    this->_file_name = file_name;
    this->_inifile.open(file_name, std::ios::in | std::ios::out);
}

libini::_IniMgr::~_IniMgr()
{
    this->_inifile.close();
    this->_inifile.clear();
}

libini::Error libini::_IniMgr::parse_file()
{
    this->_linenum = 1;
    std::string line_data, sec_name, key, value;
    libini::_Section sec("");
    int line_length;

    if (!this->_inifile.is_open())
        return Error(CANNOT_OPEN_FILE, 0);

    while (std::getline(this->_inifile, line_data))
    {
        if (!file_filter(line_data))
        {
            this->_linenum++;
            continue;
        }

        line_data = this->line_filter(line_data);

        line_length = line_data.length();

        if (line_data.find('[') == 0)
        {
            this->_data[sec_name] = sec;

            sec_name.clear();
            sec.clear();

            size_t first = line_data.find('[');
            size_t last = line_data.find(']');

            if (last != line_length - 1)
                return Error(EXTRA_TEXT, this->_linenum);

            if (last == std::string::npos)
            {
                this->_linenum++;
                return Error(MISS_BRACKETS, this->_linenum);
            }

            sec_name = line_data.substr(first + 1, last - first - 1);
            sec.rename(sec_name);

            this->_data[sec_name] = sec;
        }
        else
        {
            std::string::size_type equal_pos;

            for (std::string::size_type i = 0; i < line_length; i++) {
                char c = line_data.at(i);
                if (c == '=') {
                    if (line_data.at(i - 1) == '\\')
                        continue;
                    equal_pos = i;
                }
                else
                    continue;
            }

            if (equal_pos == std::string::npos)
                return Error(MISS_EQUAL, this->_linenum);

            std::string::size_type key_first_pos, key_last_pos, value_first_pos, value_last_pos;

            for (std::string::size_type i = equal_pos; i >= 0; i--) {
                if (line_data[i] == ' ')
                    continue;
                else {
                    key_last_pos = i;
                    break;
                }
            }
            for (std::string::size_type i = 0; i < equal_pos; i++) {
                if (line_data[i] == ' ')
                    continue;
                else {
                    key_first_pos = i;
                    break;
                }
            }
            for (std::string::size_type i = equal_pos; i < line_length; i++) {
                if(line_data[i] == ' ')
                    continue;
                else {
                    value_first_pos = i;
                    break;
                }
            }
            for (std::string::size_type i = line_length - 1; i > equal_pos; i--) {
                if (line_data[i] == ' ')
                    continue;
                else {
                    value_last_pos = i;
                    break;
                }
            }

            key = line_data.substr(key_first_pos, key_last_pos - key_first_pos + 1);
            value = line_data.substr(value_first_pos, value_last_pos - value_first_pos + 1);

            if (key == "")
                return Error(MISS_KEY, _linenum);
            //if (value == "")
            //  return Error(MISS_VALUE, _linenum)

            sec.add_node(key, value);

            key.clear();
            value.clear();
        }

        line_data.clear();
        this->_linenum++;
    }

    return Error(NO_ERRORS, 0);
}

bool libini::_IniMgr::file_filter(const std::string &input)
{
    if (input.find(';') == 0 || input.find('#') == 0)
        return false;
    return true;
}

std::string libini::_IniMgr::line_filter(const std::string &input)
{
    for (std::string::size_type i = 0; i < input.length(); i++) {
        char c = input.at(i);
        if (i == ';' || i == '#') {
            if (input.at(i - 1) == '\\') 
                continue;
            return  input.substr(0, i + 1);
        }
        else
            continue;
    }

    return input;
}

libini::_IniMgr& libini::_IniMgr::operator=(const _IniMgr &ini_mgr) {
    this->_file_name.clear();
    this->_data.clear();
    this->_inifile.close();
    this->_inifile.clear();

    this->_file_name = ini_mgr._file_name;
    this->_data = ini_mgr._data;
    this->_inifile.open(this->_file_name, std::ios::in | std::ios::out);

    return *this;
}