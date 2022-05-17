#include "CAttrInfo.hpp"
#include "CEntityInfo.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include "CEntities.hpp"
#include "CEntitiesCursor.hpp"
#include <cassert>

using CAttrInfo = ipgdlib::entity::CAttrInfo<std::string,unsigned char>;
using CEntityInfo = ipgdlib::entity::CEntityInfo<size_t,size_t,CAttrInfo>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CEntityInfo>;
using CEntityShared = ipgdlib::entity::CEntityShared<CEntityInfo>;
using CEntities = ipgdlib::entity::CEntities<size_t,CEntityInfo>;
using CEntitiesCursor = ipgdlib::entity::CEntitiesCursor<CEntities>;

int main(int argc,char * argv[])
{
    CEntityInfo eInfo({
	CAttrInfo::alloc<unsigned int>("id"),
	CAttrInfo::alloc<const char *>("fullname"),
	CAttrInfo::alloc<const char *>("shortname"),
	CAttrInfo::alloc<unsigned int>("price_sell_unit"),
	CAttrInfo::alloc<unsigned int>("price_buy_pcs"),
	CAttrInfo::alloc<unsigned char>("pcs_per_unit"),
	CAttrInfo::alloc<unsigned char>("min_sale_unit"),
	CAttrInfo::alloc<unsigned short>("stock_outlet"),
	CAttrInfo::alloc<unsigned short>("stock_warehouse")
	});

    CEntities entities(&eInfo,3);

    for(size_t li = 0;li < entities.getEntityCount();li++)
	entities.assignFrom(li,new char [eInfo.getEntitySize()]);

    CEntitiesCursor eCursor;
    eCursor.createFrom(&entities);
    for(size_t li = 0;li < entities.getEntityCount();li++)
	eCursor.getRow(li).getAs<unsigned int>("id") = (li + 1) * 10;

    for(size_t li = 0;li < entities.getEntityCount();li++)
	assert(eCursor.getRow(li).getAs<unsigned int>("id") == (li + 1) * 10);

    return 0;
}

