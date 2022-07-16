#include "CEntityInfo.hpp"
#include "CFieldInfo.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include "CustomType/CCTStaticPrimitive.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>

using CFieldInfo = ipgdlib::entity::CFieldInfo<std::string,unsigned char>;
using CEntityInfo = ipgdlib::entity::CEntityInfo<size_t,size_t,CFieldInfo>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CEntityInfo>;
using CEntityShared = ipgdlib::entity::CEntityShared<CEntityInfo>;

int main(int argc,char * argv[])
{
    CEntityInfo eInfo({
	CFieldInfo::alloc<unsigned int>("id"),
	CFieldInfo::alloc<const char*>("fullname"),
	CFieldInfo::alloc<const char *>("shortname"),
	CFieldInfo::alloc<unsigned int>("price_sell_unit"),
	CFieldInfo::alloc<unsigned int>("price_buy_pcs"),
	CFieldInfo::alloc<unsigned char>("pcs_per_unit"),
	CFieldInfo::alloc<unsigned char>("min_sale_unit"),
	CFieldInfo::alloc<unsigned short>("stock_outlet"),
	CFieldInfo::alloc<unsigned short>("stock_warehouse")
	});

    assert(eInfo.getAttrCount() == 9);

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
