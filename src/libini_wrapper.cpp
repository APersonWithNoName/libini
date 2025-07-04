#include "libini/libini_wrapper.h"
#include "libini/libini.hpp"

struct INI_ERROR
{
    libini::Error _error;
};

INI_ERR INIERR_get_errcode(struct INI_ERROR *err)
{
    return err->_error.get_errcode();
}

char *INIERR_get_errinfo(struct INI_ERROR *err, INI_ERR err_code)
{
    char *result;
    strcpy(result, err->_error.getErrorInfo(err_code).c_str());
    return result;
}

struct INI
{
    libini::ini _ini;
};

struct INI *INI_create(const char *file_name)
{
    struct INI *ini = (struct INI*)malloc(sizeof(struct INI));
    ini->_ini = libini::ini(std::string(file_name));
    return ini;
}

INI_ERR INI_load_file(struct INI *ini, const char *file_name)
{
    return ini->_ini.load_file(std::string(file_name));
}

bool INI_is_section_exist(struct INI *ini, const char *sec_name)
{
    return ini->_ini.is_section_exist(std::string(sec_name));
}

INI_ERR INI_add(struct INI *ini, const char *sec_name, const char *nod_key, const char *nod_value)
{
    return ini->_ini.add(std::string(sec_name), std::string(nod_key), std::string(nod_value));
}

void INI_set(struct INI *ini, const char *sec_name, const char *nod_key, const char *nod_value)
{
    ini->_ini.set(std::string(sec_name), std::string(nod_key), std::string(nod_value));
}

char *INI_get_value(struct INI *ini, const char *sec_name, const char *nod_key)
{
    char *result;
    strcpy(result, ini->_ini.get_value(std::string(sec_name), std::string(nod_key)).c_str());
    return result;
}

INI_ERR INI_remode_node(struct INI *ini, const char *sec_name, const char *nod_key)
{
    return ini->_ini.remove_node(std::string(sec_name), std::string(nod_key));
}

INI_ERR INI_remode_sec(struct INI *ini, const char *sec_name)
{
    return ini->_ini.remove_sec(std::string(sec_name));
}

void INI_clear(struct INI *ini)
{
    ini->_ini.clear();
}

char *INI_to_string(struct INI *ini)
{
    char *result;
    strcpy(result, ini->_ini.to_string().c_str());
    return result;
}

INI_ERR INI_write(struct INI *ini, const char *file_name)
{
    return ini->_ini.write(std::string(file_name));
}

