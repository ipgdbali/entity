#include <iostream>
#include <cassert>
#include "CAttrInfo.hpp"


using namespace ipgdlib::entity;

using CFieldInfo = CAttrInfo<std::string,size_t>;

int main(int argc,char * argv[])
{
    CFieldInfo a("id",sizeof(unsigned int));
    CFieldInfo b("price",sizeof(unsigned int));

    assert(a.size() == sizeof(unsigned int));
    assert(b.size() == sizeof(unsigned int));

    assert(a.name() == "id");
    assert(b.name() == "price");

    b = std::move(a);
    assert(a.size() == 0);
    assert(a.name() == "");
    return 0;
}
