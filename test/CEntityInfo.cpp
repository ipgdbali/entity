#include "CEntityInfo.hpp"
#include "CFieldInfo.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>


using CFieldInfo	    = ipgdlib::entity::CFieldInfo<std::string,unsigned char>;
using CEntityInfo   = ipgdlib::entity::CEntityInfo<size_t,size_t,CFieldInfo>;

int main(int argc,char * argv[])
{
    CEntityInfo eInfo({
	CFieldInfo::alloc<unsigned int>("id"),
	CFieldInfo::alloc<void*>("fullname"),
	CFieldInfo::alloc<void*>("shortname"),
	CFieldInfo::alloc<unsigned int>("price_sell_unit"),
	CFieldInfo::alloc<unsigned int>("price_buy_pcs"),
	CFieldInfo::alloc<unsigned char>("pcs_per_unit"),
	CFieldInfo::alloc<unsigned char>("min_sale_unit"),
	CFieldInfo::alloc<unsigned short>("stock_outlet"),
	CFieldInfo::alloc<unsigned short>("stock_warehouse")
	});

    assert(eInfo.getAttrCount() == 9);

    return 0;
}
