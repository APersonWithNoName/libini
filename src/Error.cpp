#include "libini/Error.hpp"

libini::Error::Error(const INI_ERR ErrCode, const int LineNum)
{
    this->_errcode = ErrCode;
    this->_linenum = LineNum;
}

INI_ERR libini::Error::get_errcode()
{
    return this->_errcode;
}

std::string libini::Error::getErrorInfo(const INI_ERR errcode)
{
    std::string errinfo = "";

    switch (errcode) {
    case NO_ERRORS:
        errinfo = "No errors";
    case CANNOT_OPEN_FILE:
        errinfo = "Cannot open ini file.";
    case MISS_BRACKETS:
        errinfo = "Miss brackets";
    case MISS_EQUAL:
        errinfo = "Miss equal";
    case MISS_KEY:
        errinfo = "Miss key";
    case MISS_VALUE:
        errinfo = "Miss value";
    case EXTRA_TEXT:
        errinfo = "Extra text after brackets";
    case NODE_EXIST:
        errinfo = "Node exists";
    case NODE_NOT_EXIST:
        errinfo = "Node not exists";
    case SECTION_EXIST:
        errinfo = "Section exists";
    case SECTION_NOT_EXIST:
        errinfo = "Section not exists";
    default:
        throw "Illegal error code";
    }

    return errinfo;
}
