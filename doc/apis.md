# API 说明

## `Class Error` (`src/Error.cpp, include/libini/Error.hpp`)
* 宏定义，说明错误类型
``` cpp
/*      MARCO      CODE        */
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
```
* 类型`INI_ERR`  
```cpp
#define INI_ERR int
```
* `std::string getErrorInfo(const INI_ERR ErrCode)`
根据错误码输出信息。

## `Class _Section`（`src/Section.cpp`）
* `_Section(const std::string& sec_name)`  
构造函数，接受字符串作为名称。
* `bool is_node_exist(const std::string& nod_key)`  
判断节点是否存在，是则返回`true`，否则返回`falae`。
* `INI_ERR add_node(const std::string& nod_key, const std::string& nod_value)`  
向`Section`中添加`_Node`，并返回错误码。
* `void append_section(_Section& sec)`  
向当前节点内追加另一个节点。
* `void set_node(const std::string& nod_key, const std::string& nod_value)`  
若节点不存在则创建，若存在则重新赋值。
* `void rename(const std::string& new_name)`  
重命名当前`Section`。
* `void clear(void)`  
清除当前`Section`内容。
* `std::string to_string(const std::string& node_format = "%s = %s", const std::string& title_format = "[%s]")`  
将当前`Section`转为`std::string`，并接受格式参数。

## `Class _IniMgr` (`src/IniMgr.cpp`)
__注意__  此类仅供内部解析，不建议直接调用。具体请参阅源码。


## `Class ini`（`src/Ini.cpp`）
* `ini(const std::string& file_name)`  
构造时必须提供文件名。
* `bool is_section_exist(const std::string& sec_key)`  
判断节点是否存在，是则返回`true`，否则返回`falae`。
* `INI_ERR add(const std::string& sec_name, const std::string& nod_key, const std::string& nod_value)`  
添加节点，若存在则报错。
* `void set(const std::string& sec_name, const std::string& nod_key, const std::string& nod_value)`  
添加节点，若存在则覆盖。
* `INI_ERR write(const std::string& file_name = "", const std::string& file_format = "%s\n", const std::string& node_format = "%s = %s", const std::string& title_format = "[%s]");`  
将修改写入文件。