#include "entity.hpp"
#include <cassert>
#include <iostream>

using CField        = ipgdlib::entity::CField<size_t>;
using CFields       = ipgdlib::entity::CFields<unsigned char, size_t,CField>;
using CEntity       = ipgdlib::entity::CEntity<CFields>;

int main(int argc,char *argv[])
{
    CFields fCustomer(
        {
            {"id",sizeof(int)},
            {"name",sizeof(char*)},
            {"addr",sizeof(char*)},
            {"sex",sizeof(char)}
        }
    );

    assert(fCustomer.count() == 4);

    assert(fCustomer[0].name() == "id");
    assert(fCustomer[0].size() == sizeof(int));

    assert(fCustomer[1].name() == "name");
    assert(fCustomer[1].size() == sizeof(char*));

    assert(fCustomer[2].name() == "addr");
    assert(fCustomer[2].size() == sizeof(char*));

    CEntity::Unique eCustomer(fCustomer);

    eCustomer.as<unsigned int>("id") = 10;
    assert(eCustomer.as<unsigned int>("id") == 10);

    CEntity::Shared eShared(eCustomer);

    eShared.as<unsigned int>("id") = 30;
    assert(eShared.as<unsigned int>("id") == 30);
    assert(eCustomer.as<unsigned int>("id") == 30);

    CEntity::Array<unsigned char> eArray(fCustomer,10);
    assert(eArray.count() == 10);

    auto cursor = eArray.createCursor();

    for(int li = 0;li < 10;li ++)
        cursor[li].as<int>(0) = (li + 1) * 10;
    
    for(int li = 0;li < 10;li ++)
        assert(cursor[li].as<int>(0) == (li + 1) * 10);
        
    return 0;
}