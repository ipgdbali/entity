#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "IEntityUnique.hpp"
#include "CEntity.hpp"
#include "CFields.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityUnique :
    public CEntity<TFields>,
    public virtual IEntityUnique<TFields,ewConstPointer>
{
using TFieldsWrapper = TFields const *;
public:

    virtual ~CEntityUnique()
    {
	this->clear();
    }

    bool createFrom(TFields const &entityInfo) override
    {
	this->clear();

	this->setFields(&entityInfo);
	this->setEntityPtr(new char [this->getFields()->size()]);
	return true;
    }

    bool createFrom(IEntity<TFields,ewConstPointer> const &entity) override
    {
	this->clear();
	this->setFields(entity.getFields());
	this->setEntityPtr(new char [this->getFields()->size()]);
	entity.copyAttrsTo(this->getEntityPtr());
	return true;
    }

    void clear() override
    {
	if(this->getEntityPtr() != nullptr)
	{
	    delete []this->getEntityPtr();
	    this->setEntityPtr(nullptr);
	    this->setFields(nullptr);
	}
    }

};

};

#endif
