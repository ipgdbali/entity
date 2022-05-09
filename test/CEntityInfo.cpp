#include "CEntityInfo.hpp"
#include "CAttrInfo.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>


using CAttrInfo = ipgdlib::entity::CAttrInfo<std::string,size_t>;
using CEntityInfo = ipgdlib::entity::CEntityInfo<std::string,size_t,size_t,size_t,CAttrInfo>;

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
	});

    assert(eInfo.getAttrCount() == 7);

    for(size_t li = 0; li< eInfo.getAttrCount();li++)
	std::cout << std::setw(2) << eInfo.getAttrOffset(li) << ' ' << eInfo.getAttrInfo(li)->getName() << "(" << eInfo.getAttrInfo(li)->getSize() << ')' << std::endl;

    std::cout << "Success" << std::endl;


    return 0;
}
