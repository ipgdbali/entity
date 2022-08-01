#include "CFields.hpp"
#include "CField.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include "CustomType/CCTStaticPrimitive.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>

using CField = ipgdlib::entity::CField<std::string,unsigned char>;
using CFields = ipgdlib::entity::CFields<size_t,size_t,CField>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CFields>;
using CEntityShared = ipgdlib::entity::CEntityShared<CFields>;

int main(int argc,char * argv[])
{
    CFields fieldProduct({
	CField::alloc<unsigned int>("id"),
	CField::alloc<const char*>("name"),
	CField::alloc<unsigned int>("price_sell_unit"),
	CField::alloc<unsigned int>("price_buy_pcs"),
	CField::alloc<unsigned char>("pcs_per_unit"),
	});

    assert(fieldProduct.count() == 5);

    CEntityUnique eProduct;
    eProduct.createFrom(fieldProduct);
    eProduct.as<unsigned int>("id") = 10;
    eProduct.as<const char *>("name") = "Resistor 10K Ohm";
    eProduct.as<unsigned int>("price_sell_unit") = 2500;
    eProduct.as<unsigned int>("price_buy_pcs") = 200;
    eProduct.as<unsigned char>("pcs_per_unit") = 10;

    assert(eProduct.as<unsigned int>(0) == 10); // ijj
    assert(strcmp(eProduct.as<const char *>(1),"Resistor 10K Ohm") == 0); // id
    assert(eProduct.as<unsigned int>(2) == 2500); // id
    assert(eProduct.as<unsigned int>(3) == 200); // id
    assert(eProduct.as<unsigned char>(4) == 10); // id

    CEntityShared eSharedProduct;
    eProduct.shareTo(eSharedProduct);
    assert(eSharedProduct.as<unsigned int>(0) == 10); // ijj
    assert(strcmp(eSharedProduct.as<const char *>(1),"Resistor 10K Ohm") == 0); // id
    assert(eSharedProduct.as<unsigned int>(2) == 2500); // id
    assert(eSharedProduct.as<unsigned int>(3) == 200); // id
    assert(eSharedProduct.as<unsigned char>(4) == 10); // id
						       //
    eSharedProduct.as<unsigned int>("id")		= 20;
    eSharedProduct.as<const char *>("name")		= "Resistor 20K Ohm";
    eSharedProduct.as<unsigned int>("price_sell_unit")	= 3000;
    eSharedProduct.as<unsigned int>("price_buy_pcs")	= 250;
    eSharedProduct.as<unsigned char>("pcs_per_unit")	= 20;

    assert(eProduct.as<unsigned int>(0) == 20); // ijj
    assert(strcmp(eProduct.as<const char *>(1),"Resistor 20K Ohm") == 0); // id
    assert(eProduct.as<unsigned int>(2) == 3000); // id
    assert(eProduct.as<unsigned int>(3) == 250); // id
    assert(eProduct.as<unsigned char>(4) == 20); // id
						 //
    return 0;
}
