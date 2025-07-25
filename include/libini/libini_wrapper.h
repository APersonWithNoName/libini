#ifndef __LIBINI__WRAPPER_H__
#define __LIBINI__WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define INI_ERR int

#define NO_ERRORS 0
#define CANNOT_OPEN_FILE 1
#define MISS_BRACKETS 211
#define MISS_EQUAL 212
#define MISS_KEY 213
#define MISS_VALUE 214
#define EXTRA_TEXT 221
#define NODE_EXIST 311
#define NODE_NOT_EXIST 312
#define SECTION_EXIST 321
#define SECTION_NOT_EXIST 322

struct INI_ERROR;
INI_ERR INIERR_get_errcode(struct INI_ERROR *err);
char *INIERR_get_errinfo(struct INI_ERROR *err, INI_ERR err_code);

struct INI;
struct INI *INI_create(const char *file_name);
INI_ERR INI_load_file(struct INI *ini, const char *file_name);
bool INI_is_section_exist(struct INI *ini, const char *sec_name);
INI_ERR INI_add(struct INI *ini, const char *sec_name, const char *nod_key, const char *nod_value);
void INI_set(struct INI *ini, const char *sec_name, const char *nod_key, const char *nod_value);
char *INI_get_value(struct INI *ini, const char *sec_name, const char *nod_key);
INI_ERR INI_remode_node(struct INI *ini, const char *sec_name, const char *nod_key);
INI_ERR INI_remode_sec(struct INI *ini, const char *sec_name);
void INI_clear(struct INI *ini);
char *INI_to_string(struct INI *ini, const char *file_name);
INI_ERR INI_write(struct INI *ini, const char *file_name);

#ifdef __cplusplus
}
#endif

#endif
