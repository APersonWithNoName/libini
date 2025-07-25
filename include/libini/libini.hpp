#ifndef __LIBINI_CPP_H__
#define __LIBINI_CPP_H__

#include "libini/Error.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cstdlib>


/*
 * 库声明从此开始
 */
namespace libini
{
    struct _Node
    {
        std::string _value;
        int _linenum;
    };

    class _Section
    {
    private:
        std::string _name;
        std::map<std::string, _Node> _data;
    public:
        _Section() = default;
        _Section(const std::string& sec_name);
        bool is_node_exist(const std::string& nod_key);
        INI_ERR add_node(const std::string& nod_key, const std::string& nod_value);
        void set_node(const std::string& nod_key, const std::string& nod_value);
        void append_section(_Section& sec);
        void rename(const std::string& new_name);
        INI_ERR remame_node(const std::string& old_key_name, const std::string& new_key_name);
        std::string get_name(void);
        std::string get_value(const std::string& nod_key);
        std::vector<std::string> get_all_keys(void);
        INI_ERR remove(const std::string& nod_key);
        void clear(void);
        std::string to_string(const std::string& node_format = "%s = %s", const std::string& title_format = "[%s]");
    };

    class _IniMgr
    {
    private:
        std::fstream _inifile;
        size_t _linenum;
        bool file_filter(const std::string& input);
        std::string line_filter(const std::string& input);
    public:
        std::string _file_name;
        std::map<std::string, _Section> _data;
        _IniMgr(void) = default;
        _IniMgr(const std::string file_name);
        ~_IniMgr(void);
        _IniMgr &operator=(const _IniMgr &ini_mgr);
        Error parse_file(void);
        Error to_string(void);
    };

    class ini
    {
    private:
        std::string _file_name;
        std::map<std::string, _Section> _data;
        _IniMgr _ini_mgr;
    public:
        ini(const std::string& file_name);
        INI_ERR load_file(const std::string& file_name);
        bool is_section_exist(const std::string& sec_name);
        void add_section(_Section& sec);
        INI_ERR add_section(const std::string& sec_name);
        INI_ERR add(const std::string& sec_name, const std::string& nod_key, const std::string& nod_value);
        INI_ERR add(const std::string& nod_key, const std::string& nod_value);
        void set(const std::string& sec_name, const std::string& nod_key, const std::string& nod_value);
        void set(const std::string& nod_key, const std::string& nod_value);
        void append(ini& iniIn);
        void append_section(_Section& sec);
        _Section* get_section(const std::string& sec_name);
        std::string get_value(const std::string& sec_name, const std::string& nod_key);
        std::string get_value(const std::string& nod_key);
        std::vector<std::string> get_all_section(void);
        INI_ERR remove_node(const std::string& sec_name, const std::string& nod_key);
        INI_ERR remove_node(const std::string& nod_key);
        INI_ERR remove_sec(const std::string& sec_name);
        void clear(void);
        std::string to_string(const std::string& file_format = "%s\n", const std::string& node_format = "%s = %s", const std::string& title_format = "[%s]");
        INI_ERR write(const std::string& file_name = "", const std::string& file_format = "%s\n", const std::string& node_format = "%s = %s", const std::string& title_format = "[%s]");
    };

};

#endif /*__LIBINI_CPP_H__*/
