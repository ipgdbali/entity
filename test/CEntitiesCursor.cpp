#include "CField.hpp"
#include "CFields.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include "CEntities.hpp"
#include "CEntitiesCursor.hpp"
#include <cassert>

using CField = ipgdlib::entity::CField<std::string,unsigned char>;
using CFields = ipgdlib::entity::CFields<size_t,size_t,CField>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CFields>;
using CEntityShared = ipgdlib::entity::CEntityShared<CFields>;
using CEntities = ipgdlib::entity::CEntities<size_t,CFields>;
using CEntitiesCursor = ipgdlib::entity::CEntitiesCursor<CEntities>;

int main(int argc,char * argv[])
{
    CFields eInfo({
	CField::alloc<unsigned int>("id"),
	CField::alloc<const char *>("fullname"),
	CField::alloc<const char *>("shortname"),
	CField::alloc<unsigned int>("price_sell_unit"),
	CField::alloc<unsigned int>("price_buy_pcs"),
	CField::alloc<unsigned char>("pcs_per_unit"),
	CField::alloc<unsigned char>("min_sale_unit"),
	CField::alloc<unsigned short>("stock_outlet"),
	CField::alloc<unsigned short>("stock_warehouse")
	});

    CEntities entities(&eInfo,3);

    for(size_t li = 0;li < entities.getEntityCount();li++)
	entities.assignFrom(li,new char [eInfo.getFieldsSize()]);

    CEntitiesCursor eCursor;
    eCursor.createFrom(&entities);
    for(size_t li = 0;li < entities.getEntityCount();li++)
	eCursor.getRow(li).getAs<unsigned int>("id") = (li + 1) * 10;

    for(size_t li = 0;li < entities.getEntityCount();li++)
	assert(eCursor.getRow(li).getAs<unsigned int>("id") == (li + 1) * 10);

    return 0;
}

