#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "IEntityUnique.hpp"
#include "CEntity.hpp"
#include "CEntityInfo.hpp"

namespace ipgdlib::entity
{

template <typename TEntityInfo>
class CEntityUnique :
    public CEntity<TEntityInfo>,
    public virtual IEntityUnique<TEntityInfo,TEntityInfo const *>
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

    bool createFrom(IEntity<TEntityInfo,TEntityInfoWrapper> const &entity) override
    {
	this->clear();
	this->setEntityInfo(entity.getEntityInfo());
	this->setEntityPtr(new char [this->getEntityInfo()->getEntitySize()]);
	entity.copyTo(this->getEntityPtr());
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
