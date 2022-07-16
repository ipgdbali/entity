#include <iostream>
#include <cassert>
#include "CField.hpp"



using CField = ipgdlib::entity::CField<std::string,size_t>;

int main(int argc,char * argv[])
{
    CField a("id",sizeof(unsigned int));
    CField b("price",sizeof(unsigned int));

    assert(a.size() == sizeof(unsigned int));
    assert(b.size() == sizeof(unsigned int));

    assert(a.name() == "id");
    assert(b.name() == "price");

    b = std::move(a);
    assert(a.size() == 0);
    assert(a.name() == "");
    return 0;
}
