#include <iostream>
#include <cassert>
#include "CAttrInfo.hpp"


using namespace ipgdlib::entity;

using CFieldInfo = CAttrInfo<std::string,size_t>;

int main(int argc,char * argv[])
{
    CFieldInfo a("id",sizeof(unsigned int));
    CFieldInfo b("price",sizeof(unsigned int));

    assert(a.getSize() == sizeof(unsigned int));
    assert(b.getSize() == sizeof(unsigned int));

    assert(a.getName() == "id");
    assert(b.getName() == "price");

    b = std::move(a);
    assert(a.getSize() == 0);
    assert(a.getName() == "");
    return 0;
}
