#include "CFields.hpp"
#include "CField.hpp"
#include "CEntity.hpp"
#include "CustomType/CCTPrimitive.hpp"
#include <cassert>
#include <vector>

using CFieldFactory     = ipgdlib::entity::CFieldFactory<std::string,size_t>;
using CFields           = ipgdlib::entity::CFields<size_t,size_t,CFieldFactory::CFieldAbs>;
using CEntity           = ipgdlib::entity::CEntity<CFields>;

template <typename T>
using CCTPrimitive      = ipgdlib::entity::CCTPrimitive<T,CFieldFactory::type_size>;

int main(int argc,char * argv[])
{

    CFields fCustomer({
        CFieldFactory::alloc<int>("id"),
        CFieldFactory::alloc<sizeof(char*)>("name"),
        CFieldFactory::alloc<char>("sex"),
        CFieldFactory::alloc<sizeof(unsigned char)>("age")
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
