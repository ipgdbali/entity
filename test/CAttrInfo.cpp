#include <iostream>
#include "CAttrInfo.hpp"

using namespace ipgdlib::entity;

int main(int argc,char * argv[])
{
    CAttrInfo<size_t,std::string> id(sizeof(int),"id");
    std::cout << id.getSize() << id.getName() << std::endl;
    return 0;
}
