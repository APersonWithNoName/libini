#ifndef __LIBINI__ERROR_H__
#define __LIBINI__ERROR_H__

#include <iostream>
#include <string>

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

namespace libini{

    class Error
{
    private:
        INI_ERR _errcode;
        int _linenum;
    public:
        Error(const INI_ERR ErrCode, const int LineNum);
        INI_ERR get_errcode();
        std::string getErrorInfo(const INI_ERR ErrCode);
        INI_ERR throwError();
};

}

#endif /*__LIBINI_ERROR_H__*/