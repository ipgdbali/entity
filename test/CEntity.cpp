#include "CEntityInfo.hpp"
#include "CAttrInfo.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>


using CAttrInfo = ipgdlib::entity::CAttrInfo<std::string,unsigned char>;
using CEntityInfo = ipgdlib::entity::CEntityInfo<size_t,size_t,CAttrInfo>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CEntityInfo>;
using CEntityShared = ipgdlib::entity::CEntityShared<CEntityInfo>;

int main(int argc,char * argv[])
{
    CEntityInfo eInfo({
	CAttrInfo::alloc<unsigned int>("id"),
	CAttrInfo::alloc<void*>("fullname"),
	CAttrInfo::alloc<void*>("shortname"),
	CAttrInfo::alloc<unsigned int>("price_sell_unit"),
	CAttrInfo::alloc<unsigned int>("price_buy_pcs"),
	CAttrInfo::alloc<unsigned char>("pcs_per_unit"),
	CAttrInfo::alloc<unsigned char>("min_sale_unit"),
	CAttrInfo::alloc<unsigned short>("stock_outlet"),
	CAttrInfo::alloc<unsigned short>("stock_warehouse")
	});

    assert(eInfo.getAttrCount() == 9);

    for(size_t li = 0; li< eInfo.getAttrCount();li++)
	std::cout << std::setw(2) << eInfo.getAttrOffset(li) << ' ' << eInfo.getAttrInfo(li)->getName() << "(" << eInfo.getAttrInfo(li)->getSize() << ')' << std::endl;

    CEntityUnique eProduct;
    eProduct.createFrom(eInfo);
    eProduct.getAs<unsigned int>("id") = 10;
    assert(eProduct.getAs<unsigned int>("id") == 10);
    eProduct.getAs<char const*>(1) = "Arduino UNO R3";
    eProduct.getAs<unsigned char>("pcs_per_unit") = 20;
    assert(eProduct.getAs<unsigned char>("pcs_per_unit") == 20);

    CEntityShared eSharedProduct;
    eProduct.shareTo(eSharedProduct);

    assert(eSharedProduct.getAs<unsigned int>("id") == 10);
    eSharedProduct.getAs<unsigned int>("id") = 20;
    assert(eProduct.getAs<unsigned int>("id") == 20);

    return 0;
}
