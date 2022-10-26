#include "entity.hpp"
#include <cassert>
#include <iostream>

using CField    = ipgdlib::entity::CField<unsigned char>;
using CFields   = ipgdlib::entity::CFields<unsigned char, unsigned char,CField>;
using CEntity   = ipgdlib::entity::CEntityFacade<CFields>;

int main(int argc,char * argv[])
{

    CFields fCustomer(
        {
            {"id",sizeof(unsigned int)},
            {"name",sizeof(char*)},
            {"sex",sizeof(char)},
            {"age",sizeof(unsigned char)}
        });

    assert(fCustomer.count() == 4);

    // Create Unique Entity
    CEntity::Unique eCustomer(fCustomer);

    // Create Shared Entity
    CEntity::Shared eSharedCustomer(eCustomer);

    // Access

    // - Using Copy Memory
    unsigned int id;

    id = 20;
    eCustomer.copyAttrFrom(0,&id);

    id = 0;
    eCustomer.copyAttrTo("id",&id);
    assert(id == 20);

    id = 30;
    eCustomer.copyAttrFrom("id",&id);

    id = 0;
    eCustomer.copyAttrTo(0,&id);
    assert(id == 30);

    // - Using As Method

    eCustomer.as<char>(2) = 'F';
    assert(eCustomer.as<char>("sex") == 'F');

    eCustomer.as<char>("sex") = 'M';
    assert(eCustomer.as<char>(2) == 'M');

    /*

    // - Using Custom Type
    CCTPrimitive<unsigned char> ctAge;

    eCustomer.toCustomType(3,ctAge);
    ctAge = 20;
    assert((ctAge == 20));
    assert((eCustomer.as<unsigned char>("age") == 20));

    eCustomer.toCustomType("age",ctAge);
    ctAge = 30;
    assert((ctAge == 30));
    assert((eCustomer.as<unsigned char>(3) == 30));

    */

    return 0;
}
