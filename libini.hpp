#ifndef __LIBINI_CPP_H__
#define __LIBINI_CPP_H__

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>

/*
 * 通过是否定义以下宏控制接口的启用
 * 定义则启用
 */
// 库调试
#define __LIBINI_DEBUG__
// 库错误处理
#define __LIBINI_ERROR__



#ifdef __LIBINI_ERROR__

#define INI_ERROR(INFO) std::cerr << INFO << std::endl;

#else /*__LIBINI__ERROR__*/

#define INI_ERROR(Type)

#endif /*__LIBINI__ERROR__*/



#ifdef __LIBINI_DEBUG__

#define DEBUG_INFO "At File:     " << __FILE__ << "\n"                        \
                                   << "   Function: " << __FUNCTION__ << "\n" \
                                   << "   Line:     " << __LINE__ << "\n"
#define DEBUG(Info) std::cout << "LIBINI:\n" \
                              << DEBUG_INFO << Info << "\n";

#else /*__LIBINI_DEBUG__*/

#define DEBUG(x)

#endif /*__LIBINI_DEBUG__*/

/*
 * 库声明从此开始
 */
namespace libini
{

    struct _Node
    {
        std::string _Value;
        int _LineNum;
    };

    class _Section
    {
    private:
        std::string _Name;
        std::map<std::string, _Node> _Data;
    public:
        _Section(const std::string& secName);
        bool isNodeExist(const std::string& nodKey);
        bool addNode(const std::string& nodKey, const std::string& nodValue);
        void appendSection(_Section& sec);
        void setNode(const std::string& nodKey, const std::string& nodValue);
        void rename(const std::string& newName);
        std::string getName(void);
        std::string getValue(const std::string& nodKey);
        std::vector<std::string> getAllKeys(void);
        bool removeNode(const std::string& nodKey);
        void clear(void);
        std::string toString(void);
    };

    class ini
    {
    private:
        std::string _FileName;
        std::map<std::string, _Section> _Data;
        bool filter(const std::string& input);
        std::string LineFilter(const std::string& input);
    public:
        ini();
        ini(const std::string& FileName);
        bool isSectionExist(const std::string& secName);
        void addSection(_Section &sec);
        void add(const std::string& secName, const std::string& nodKey, const std::string& nodValue);
        void add(const std::string& nodKey, const std::string& nodValue);
        void set(const std::string& secName, const std::string& nodKey, const std::string& nodValue);
        void set(const std::string& nodKey, const std::string& nodValue);
        void append(ini& iniIn);
        void appendSection(_Section& sec);
        _Section* getSection(const std::string& secName);
        std::string getValue(const std::string& secName, const std::string& nodKey);
        std::string getValue(const std::string& nodKey);
        std::vector<std::string> getAllSection(void);
        bool removeNode(const std::string& secName, const std::string& nodKey);
        bool removeNode(const std::string& nodKey);
        bool removeSection(const std::string& secName);
        void clear(void);
        int parser(const std::string& FileName);
        std::string toString(void);
        bool write(const std::string& FileName = "");
    };

};

#endif /*__LIBINI_CPP_H__*/
