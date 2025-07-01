#include <iostream>

#include "libini/libini.hpp"
#include "libini/Error.hpp"

int main(int argc, char **argv)
{
    std::string file_name = "test.ini";

    // 创建 ini 对象
    libini::ini ini_file((std::string)file_name);
    // 使用 load_file 加载文件
    ini_file.load_file(file_name);
    // 打印一些值
    std::cout << ini_file.get_value("Section1", "key1.1") << std::endl;
    std::cout << ini_file.get_value("key0.1") << std::endl;
    // 创建新 section
    
    return 0;
}