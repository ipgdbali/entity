#include "CFieldInfo.hpp"
#include "CEntityInfo.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include "CEntities.hpp"
#include "CEntitiesCursor.hpp"
#include <cassert>

using CFieldInfo = ipgdlib::entity::CFieldInfo<std::string,unsigned char>;
using CEntityInfo = ipgdlib::entity::CEntityInfo<size_t,size_t,CFieldInfo>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CEntityInfo>;
using CEntityShared = ipgdlib::entity::CEntityShared<CEntityInfo>;
using CEntities = ipgdlib::entity::CEntities<size_t,CEntityInfo>;
using CEntitiesCursor = ipgdlib::entity::CEntitiesCursor<CEntities>;

int main(int argc,char * argv[])
{
    CEntityInfo eInfo({
	CFieldInfo::alloc<unsigned int>("id"),
	CFieldInfo::alloc<const char *>("fullname"),
	CFieldInfo::alloc<const char *>("shortname"),
	CFieldInfo::alloc<unsigned int>("price_sell_unit"),
	CFieldInfo::alloc<unsigned int>("price_buy_pcs"),
	CFieldInfo::alloc<unsigned char>("pcs_per_unit"),
	CFieldInfo::alloc<unsigned char>("min_sale_unit"),
	CFieldInfo::alloc<unsigned short>("stock_outlet"),
	CFieldInfo::alloc<unsigned short>("stock_warehouse")
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

