#include "CEntityInfo.hpp"
#include "CAttrInfo.hpp"
#include <string>
#include <cassert>
#include <iostream>


using CAttrInfo = ipgdlib::entity::CAttrInfo<std::string,size_t>;
using CEntityInfo = ipgdlib::entity::CEntityInfo<std::string,size_t,size_t,size_t>;

int main(int argc,char * argv[])
{
    CEntityInfo eInfo({
	CAttrInfo::fromTypeToHeap<unsigned int>("id"),
	CAttrInfo::fromTypeToHeap<void*>("fullname"),
	CAttrInfo::fromTypeToHeap<void*>("shortname"),
	CAttrInfo::fromTypeToHeap<unsigned int>("price_sell_unit"),
	CAttrInfo::fromTypeToHeap<unsigned int>("price_buy_pcs"),
	CAttrInfo::fromTypeToHeap<unsigned char>("pcs_per_unit"),
	CAttrInfo::fromTypeToHeap<unsigned char>("min_sale_unit"),
	});

    assert(eInfo.getAttrCount() == 7);

    for(size_t li = 0; li< eInfo.getAttrCount();li++)
	std::cout << eInfo.getAttrInfo(li)->getName() << "(" << eInfo.getAttrInfo(li)->getSize() << ')'
	    << "offset" << eInfo.getAttrOffset(li) << std::endl;

    std::cout << "Success" << std::endl;


    return 0;
}
