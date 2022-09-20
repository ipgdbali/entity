#include "CFields.hpp"
#include "CField.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include "CustomType/CCTPrimitive.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>

using CField            = ipgdlib::entity::CField<std::string,unsigned char>;
using CFields           = ipgdlib::entity::CFields<size_t,size_t,CField>;
using CEntityUnique     = ipgdlib::entity::CEntityUnique<CFields>;
using CEntityShared     = ipgdlib::entity::CEntityShared<CFields>;
template <typename T>
using CCTPrimitive      = ipgdlib::entity::CCTPrimitive<T,size_t>;

int main(int argc,char * argv[])
{

    CFields fCustomer({
        CField::alloc<unsigned int>("id"),              // index - 0
        CField::alloc<sizeof(char*)>("name"),           // index - 1
        CField::alloc<char>("sex"),                      // index - 2
        CField::alloc<sizeof(unsigned char)>("age")    // index - 3
    });
    assert(fCustomer.count() == 4);

    // Create Entity
    CEntityUnique eCustomer(&fCustomer);    

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
    
    return 0;
}
