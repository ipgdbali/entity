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

    CEntityUnique(TFields const &entityInfo)
    {
	this->setFields(&entityInfo);
	this->setEntityPtr(new char [this->getFields()->size()]);
    }

    CEntityUnique(IEntity<TFields,ewConstPointer> const &entity)
    {
	this->setFields(entity.getFields());
	this->setEntityPtr(new char [this->getFields()->size()]);
	entity.copyTo(this->getEntityPtr());
    }

    void clear() override
    {
	if(this->getEntityPtr() != nullptr)
	{
	    delete []this->getEntityPtr();
	    this->setEntityPtr(nullptr);
	}
    }

};

};

#endif
