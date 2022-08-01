#include "CField.hpp"
#include "CFields.hpp"
#include "CEntityUnique.hpp"
#include "CEntityShared.hpp"
#include "CEntities.hpp"
#include <cassert>

using CField = ipgdlib::entity::CField<std::string,unsigned char>;
using CFields = ipgdlib::entity::CFields<size_t,size_t,CField>;
using CEntityUnique = ipgdlib::entity::CEntityUnique<CFields>;
using CEntityShared = ipgdlib::entity::CEntityShared<CFields>;
using CEntities = ipgdlib::entity::CEntities<size_t,CFields>;

int main(int argc,char * argv[])
{
    CFields eInfo({
	CField::alloc<unsigned int>("id"),
	CField::alloc<const char*>("name"),
	CField::alloc<unsigned int>("price_sell_unit"),
	CField::alloc<unsigned int>("price_buy_pcs"),
	CField::alloc<unsigned char>("pcs_per_unit"),
	});

    CEntities entities(&eInfo,3);

    for(size_t li = 0;li < entities.count();li++)
	entities.assignFrom(li,new char [eInfo.size()]);

    CEntityShared eShared;
    entities.shareTo(eShared,0);
    eShared.as<unsigned int>("id") = 10;
    assert(eShared.as<unsigned int>("id") == 10);

    return 0;
}
