#include "libini.hpp"
#include <iostream>
int main(){
    libini::_Section sec1("test_sec1");
    sec1.addNode("nod1", "vnod1");
    //sec1.addNode("nod1", "vnod1");
    //sec1.removeNode("nod1");
    std::cout << sec1.toString() << std::endl;

    libini::ini ini1("test_ini1");
    ini1.parser("test.ini");
    std::cout << ini1.toString() << std::endl;
    return 0;
}