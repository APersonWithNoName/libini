#ifndef __LIBINI_CPP_H__
#define __LIBINI_CPP_H__

#include "libini/Error.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include <cstddef>

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
        void append_section(_Section& sec);
        void set_node(const std::string& nod_key, const std::string& nod_value);
        void rename(const std::string& new_name);
        INI_ERR remame_node(const std::string& old_key_name, const std::string& new_key_name);
        std::string get_name(void);
        std::string get_value(const std::string& nod_key);
        std::vector<std::string> get_all_keys(void);
        INI_ERR remove(const std::string& nod_key);
        void clear(void);
        std::string to_string(void);
    };

    class _IniMgr
    {
    private:
        std::fstream _inifile;
        size_t _linenum;
        bool LineFilter(const std::string& input);
    public:
        std::string _file_name;
        std::map<std::string, _Section> _data;
        _IniMgr() = default;
        _IniMgr(const std::string file_name);
        ~_IniMgr();
        _IniMgr &operator=(const _IniMgr &ini_mgr);
        Error parse_file();
        Error to_string();
    };

    class ini
    {
    private:
        std::string _file_name;
        std::map<std::string, _Section> _data;
        _IniMgr _ini_mgr;
    public:
        ini(const std::string& file_name);
        bool is_section_exist(const std::string& sec_name);
        void addSection(_Section &sec);
        void add(const std::string& sec_name, const std::string& nod_key, const std::string& nod_value);
        void add(const std::string& nod_key, const std::string& nod_value);
        void set(const std::string& sec_name, const std::string& nod_key, const std::string& nod_value);
        void set(const std::string& nod_key, const std::string& nod_value);
        void append(ini& iniIn);
        void append_section(_Section& sec);
        _Section* getSection(const std::string& sec_name);
        std::string get_value(const std::string& sec_name, const std::string& nod_key);
        std::string get_value(const std::string& nod_key);
        std::vector<std::string> getAllSection(void);
        INI_ERR remove_node(const std::string& sec_name, const std::string& nod_key);
        INI_ERR remove_node(const std::string& nod_key);
        INI_ERR remove_sec(const std::string& sec_name);
        void clear(void);
        std::string to_string(void);
        INI_ERR write(const std::string& file_name = "");
        INI_ERR format(const std::string file_name = "");
    };

};

#endif /*__LIBINI_CPP_H__*/
