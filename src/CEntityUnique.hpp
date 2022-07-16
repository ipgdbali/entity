#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "IEntityUnique.hpp"
#include "CEntity.hpp"
#include "CFields.hpp"

namespace ipgdlib::entity
{

template <typename TEntityInfo>
class CEntityUnique :
    public CEntity<TEntityInfo>,
    public virtual IEntityUnique<TEntityInfo,ewConstPointer>
{
using TEntityInfoWrapper = TEntityInfo const *;
public:

    virtual ~CEntityUnique()
    {
	this->clear();
    }

    bool createFrom(TEntityInfo const &entityInfo) override
    {
	this->clear();

	this->setEntityInfo(&entityInfo);
	this->setEntityPtr(new char [this->getEntityInfo()->getEntitySize()]);
	return true;
    }

    bool createFrom(IEntity<TEntityInfo,ewConstPointer> const &entity) override
    {
	this->clear();
	this->setEntityInfo(entity.getEntityInfo());
	this->setEntityPtr(new char [this->getEntityInfo()->getEntitySize()]);
	entity.copyAttrsTo(this->getEntityPtr());
	return true;
    }

    void clear() override
    {
	if(this->getEntityPtr() != nullptr)
	{
	    delete []this->getEntityPtr();
	    this->setEntityPtr(nullptr);
	    this->setEntityInfo(nullptr);
	}
    }

};

};

#endif
