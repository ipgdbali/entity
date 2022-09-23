#include "CFields.hpp"
#include "CField.hpp"
#include "CEntity.hpp"
#include "CustomType/CCTPrimitive.hpp"
#include <cassert>
#include <vector>

using CFieldFactory     = ipgdlib::entity::CFieldFactory<std::string,size_t>;
using CFields           = ipgdlib::entity::CFields<size_t,size_t,CFieldFactory::CFieldAbs>;
using CEntityUnique     = ipgdlib::entity::CEntity<CFields>::Unique;
using CEntityShared     = ipgdlib::entity::CEntity<CFields>::Shared;

template <typename T>
using CCTPrimitive      = ipgdlib::entity::CCTPrimitive<T,CFieldFactory::type_size>;

int main(int argc,char * argv[])
{

    std::vector<CFields::TWField> fields;
    fields.push_back(CFieldFactory::alloc<unsigned int>("id"));
    fields.push_back(CFieldFactory::alloc<sizeof(char*)>("name"));
    fields.push_back(CFieldFactory::alloc<char>("sex"));
    fields.push_back(CFieldFactory::alloc<sizeof(unsigned char)>("age"));

    CFields fCustomer(fields);
    assert(fCustomer.count() == 4);

    // Create Unique Entity
    CEntityUnique eCustomer(fCustomer);

    // Create Shared Entity
    CEntityShared eSharedCustomer(eCustomer);

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
