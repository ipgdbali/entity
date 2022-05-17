#ifndef CENTITIES_CURSOR_HPP
#define CENTITIES_CURSOR_HPP

#include "IEntitiesCursor.hpp"
#include "CEntityShared.hpp"

namespace ipgdlib::entity
{

template <typename TEntities>
class CEntitiesCursor :
    public IEntitiesCursor<TEntities,TEntities*,CEntityShared<typename TEntities::iface::type_entity_info>>
{
public:
    using iface = IEntitiesCursor<TEntities,TEntities*,CEntityShared<typename TEntities::iface::type_entity_info>>;

private:

using TEntityCount = typename iface::type_entity_count;
using TEntitiesWrapper = typename iface::type_entities_wrapper;
using TEntitiesShared = typename iface::type_entities_shared;

public:
    void createFrom(TEntitiesWrapper entities) override
    {
	this->m_pEntities = entities;
	this->m_RowPosition = 0;
	this->m_ActiveRow.set(entities->getEntityInfo(),entities->getPData(0));
    }

    TEntitiesWrapper getEntities()
    {
	return this->m_pEntities;
    }

    void setRowPosition(TEntityCount rowPos) override
    {
	this->m_RowPosition = rowPos;
	this->m_ActiveRow.assignFrom(this->m_pEntities->getPData(rowPos));
    }

    TEntityCount getRowPosition() const noexcept override
    {
	return this->m_RowPosition;
    }

    TEntitiesShared &getActiveRow() override
    {
	return this->m_ActiveRow;
    }

    TEntitiesShared &getRow(TEntityCount rowPos)
    {
	this->m_RowPosition = rowPos;
	this->m_ActiveRow.assignFrom(this->m_pEntities->getPData(rowPos));
	return this->m_ActiveRow;
    }

private:
    TEntityCount m_RowPosition;
    TEntitiesShared m_ActiveRow;
    TEntities *m_pEntities;
};

};

#endif
