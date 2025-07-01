# libini : 使用 C++ 的 INI 解析器

* * * 

## 简介
使用 C++11 标准的 INI 配置文件解析器。

## 构建
### 第三方依赖
* __暂无__
### 编译
__确认 `cmake` 可用__
* __Unix-like__
``` shell
git clone https://github.com/APersonWithNoName/libini.git
cd libini
mkdir build # 创建 build 为可选
cd build    #
cmake ..
make -j
# 安装
make install
```
* __Windows__
``` shell
git clone https://github.com/APersonWithNoName/libini.git
cd libini
cmake .. -A "<your_arch>" -G "Visual Studio <version>"
```
* __其他__  
请参见 `cmake` 文档。

## 接口
* __参见 `doc/apis.md` 。__