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

class CProduct
{
public:
    static CEntityInfo eInfo;

    CProduct(
	unsigned int id,
	const char *fullname,
	const char *shortname,
	unsigned int price_sell_unit,
	unsigned int price_buy_pcs,
	unsigned char pcs_per_unit,
	unsigned char min_sale_unit,
	unsigned short stock_outlet,
	unsigned short stock_warehouse
    )
    {
	m_entity.createFrom(eInfo);

	this->id() = id;
	this->fullname() = fullname;
	this->shortname() = shortname;
	this->price_sell_unit() = price_sell_unit;
	this->price_buy_pcs() = price_buy_pcs;
	this->pcs_per_unit() = pcs_per_unit;
	this->min_sale_unit() = min_sale_unit;
	this->stock_outlet() = stock_outlet;
	this->stock_warehouse() = stock_warehouse;
    }

    unsigned int &id()
    {
	return this->m_entity.getAs<unsigned int>("id");
    }

    const char *&fullname()
    {
	return this->m_entity.getAs<const char*>("fullname");
    }

    const char *&shortname()
    {
	return this->m_entity.getAs<const char*>("shortname");
    }

    unsigned int &price_sell_unit()
    {
	return this->m_entity.getAs<unsigned int>("price_sell_unit");
    }

    unsigned int price_sell_unit() const
    {
	return this->m_entity.getAs<unsigned int>("price_sell_unit");
    }

    unsigned int &price_buy_pcs()
    {
	return this->m_entity.getAs<unsigned int>("price_buy_pcs");
    }

    unsigned int const &price_buy_pcs() const
    {
	return this->m_entity.getAs<unsigned int>("price_buy_pcs");
    }

    unsigned char &pcs_per_unit()
    {
	return this->m_entity.getAs<unsigned char>("pcs_per_unit");
    }

    unsigned char const &pcs_per_unit() const
    {
	return this->m_entity.getAs<unsigned char>("pcs_per_unit");
    }

    unsigned char &min_sale_unit()
    {
	return this->m_entity.getAs<unsigned char>("min_sale_unit");
    }

    unsigned short &stock_outlet()
    {
	return this->m_entity.getAs<unsigned short>("stock_outlet");
    }

    unsigned short const &stock_outlet() const
    {
	return this->m_entity.getAs<unsigned short>("stock_outlet");
    }

    unsigned short &stock_warehouse()
    {
	return this->m_entity.getAs<unsigned short>("stock_warehouse");
    }

    unsigned short const &stock_warehouse() const
    {
	return this->m_entity.getAs<unsigned short>("stock_warehouse");
    }

    unsigned int profit_per_unit() const
    {
	return this->price_sell_unit() - this->price_buy_pcs() * this->pcs_per_unit();
    }

    unsigned int stock_total() const
    {
	return this->stock_outlet() + this->stock_warehouse();
    }

private:
    CEntityUnique m_entity;
};

CEntityInfo CProduct::eInfo({
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

int main(int argc,char * argv[])
{
    CProduct product(12,"Arduino UNO R3","",3000,250,10,1,23,48);

    assert(product.profit_per_unit() == 500);
    return 0;
}
