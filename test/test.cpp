#include <cstddef>
#include <iostream>

#include "libini/libini.hpp"
#include "libini/Error.hpp"

int main(int argc, char **argv)
{
    std::string file_name = "test.ini";

    // 创建 ini 对象
    libini::ini ini_file((std::string)file_name);

    // 使用 load_file 加载文件
    INI_ERR status = ini_file.load_file(file_name);
    if (status != 0){
        std::cout << "Error!" << " " << status << " " << std::endl;
        return -1;
    }
        
    // 获取
    // 值
    std::cout << ini_file.get_value("Section1", "key1.1") << std::endl;
    std::cout << ini_file.get_value("key0.1") << std::endl;
    // 所有 section 名称
    auto sec_list = ini_file.get_all_section();
    for (size_t i = 0; i < sec_list.size(); i++) {
        std::cout << sec_list[i] << std::endl;
    }
    // 若不存在则返回空值
    std::cout << ini_file.get_value("Section5", "key5.1");

    // 删除
    // 键值对
    ini_file.remove_node("Section1", "key1.1");
    // 节
    ini_file.remove_sec("Section2");


    // set 系函数，不检查是否存在，直接覆盖或添加，是 add 系的底层实现
    // 覆盖
    ini_file.set("Section1", "key1.2", "value1.2.set");
    // 新建
    ini_file.set("Section1", "key1.3", "value1.3");

    // 创建新 section
    ini_file.add_section("sec4");
    // 向新 section 添加值
    ini_file.add("sec4", "key0", "value0");
    
    // 写入文件，使用默认格式
    ini_file.write("Test_out.ini");
    
    return 0;
}