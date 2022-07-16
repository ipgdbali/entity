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
    CFields eInfo({
	CField::alloc<unsigned int>("id"),
	CField::alloc<const char*>("fullname"),
	CField::alloc<const char *>("shortname"),
	CField::alloc<unsigned int>("price_sell_unit"),
	CField::alloc<unsigned int>("price_buy_pcs"),
	CField::alloc<unsigned char>("pcs_per_unit"),
	CField::alloc<unsigned char>("min_sale_unit"),
	CField::alloc<unsigned short>("stock_outlet"),
	CField::alloc<unsigned short>("stock_warehouse")
	});

    assert(eInfo.getFieldCount() == 9);

    CEntityUnique eProduct;
    eProduct.createFrom(eInfo);
    eProduct.getAs<unsigned int>("id") = 10;
    assert(eProduct.getAs<unsigned int>("id") == 10);
    eProduct.getAs<const char *>(1) = "Kucing";
    eProduct.getAs<const char *>(2) = "Kumbang";
    eProduct.getAs<unsigned int>(3) = 180000;
    eProduct.getAs<unsigned int>(4) = 100000;
    eProduct.getAs<unsigned char>("pcs_per_unit") = 20;
    eProduct.getAs<unsigned char>("min_sale_unit") = 1;
    eProduct.getAs<unsigned short>("stock_outlet") = 35;
    eProduct.getAs<unsigned short>("stock_warehouse") = 80;

    CEntityShared eSharedProduct;
    eProduct.shareTo(eSharedProduct);
    eSharedProduct.getAs<unsigned int>(0) = 30;
    assert(eProduct.getAs<unsigned int>(0) == 30);

    assert(eSharedProduct.getAs<unsigned int>(3) == 180000);
    assert(eProduct.getAs<unsigned int>(0) == 30);
    assert(strcmp(eProduct.getAs<const char*>(1),"Kucing") == 0);

    ipgdlib::entity::CCTStaticPrimitive<unsigned int,size_t> iPrice;
    eProduct.toCustomType(3,iPrice);

    iPrice = 200;

    assert(eProduct.getAs<unsigned int>(3) == 200);

    return 0;
}
