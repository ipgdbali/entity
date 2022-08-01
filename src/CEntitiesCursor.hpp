#ifndef CENTITIES_CURSOR_HPP
#define CENTITIES_CURSOR_HPP

#include "IEntitiesCursor.hpp"
#include "CEntityShared.hpp"

namespace ipgdlib::entity
{

template <typename TEntities>
class CEntitiesCursor :
    public IEntitiesCursor<TEntities,ewPointer,CEntityShared<typename TEntities::iface::type_fields>>
{
public:
    using iface = IEntitiesCursor<TEntities,ewPointer,CEntityShared<typename TEntities::iface::type_fields>>;

private:

using TCount = typename TEntities::iface::type_count;
using TEntitiesWrapper = typename ipgdlib::wrap<TEntities,ewPointer>::value;
using TEntityShared = typename iface::type_entity_shared;

public:
    void createFrom(TEntitiesWrapper entities) override
    {
	this->m_pEntities = entities;
	this->m_ActivePosition = 0;
	this->m_ActiveEntity.set(entities->getFields(),entities->getPData(0));
    }

    TEntitiesWrapper getEntities()
    {
	return this->m_pEntities;
    }

    void setActivePosition(TCount rowPos) override
    {
	this->m_ActivePosition = rowPos;
	this->m_ActiveEntity.assignFrom(this->m_pEntities->getPData(rowPos));
    }

    TCount getActivePosition() const noexcept override
    {
	return this->m_ActivePosition;
    }

    TEntityShared &getActiveEntity() override
    {
	return this->m_ActiveEntity;
    }

    TEntityShared &getRow(TCount rowPos)
    {
	this->m_ActivePosition = rowPos;
	this->m_ActiveEntity.assignFrom(this->m_pEntities->getPData(rowPos));
	return this->m_ActiveEntity;
    }

private:
    TCount m_ActivePosition;
    TEntityShared m_ActiveEntity;
    TEntities *m_pEntities;
};

};

#endif
