#include "CField.hpp"
#include "CFields.hpp"
#include <string>
#include <cassert>
#include <iostream>
#include <iomanip>

using CField	= ipgdlib::entity::CField<std::string,unsigned char>;
using CFields	= ipgdlib::entity::CFields<size_t,size_t,CField>;

int main(int argc,char * argv[])
{
    CFields fProduct({
	CField::alloc<unsigned int>("id"),
	CField::alloc<void*>("fullname"),
	CField::alloc<void*>("shortname"),
	CField::alloc<unsigned int>("price_sell_unit"),
	CField::alloc<unsigned int>("price_buy_pcs"),
	CField::alloc<unsigned char>("pcs_per_unit"),
	CField::alloc<unsigned char>("min_sale_unit"),
	CField::alloc<unsigned short>("stock_outlet"),
	CField::alloc<unsigned short>("stock_warehouse")
	});

    assert(fProduct.count() == 9);

    return 0;
}
