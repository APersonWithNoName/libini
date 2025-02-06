# libini : 使用 C++ 的 INI 解析器

* * * 

## 使用
引入`libini.hpp`即可。
```c++
#include "libini.hpp"
```
+ 在`libini.hpp`中，定义了如下宏，若注释则不启用相关功能：

    `__LIBINI_DEBUG__` ： 输出调试数据（暂未使用）；

    `__LIBINI_ERROR__` ： 输出错误信息；

    `__LIBINI_IMPLEMENTATION__` ： 库函数实现，注释则仅包含声明。

