#include "CEntityInfo.hpp"
#include "CAttrInfo.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>


using CAttrInfo	    = ipgdlib::entity::CAttrInfo<std::string,unsigned char>;
using CEntityInfo   = ipgdlib::entity::CEntityInfo<size_t,size_t,CAttrInfo>;

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

    return 0;
}
