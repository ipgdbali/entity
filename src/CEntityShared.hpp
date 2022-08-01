#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "IEntityShared.hpp"
#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityShared :
    public CEntity<TFields>,
    public virtual IEntityShared<TFields,ewConstPointer>
{
using TFieldsWrapper = TFields const *;

public:

    using CEntity<TFields>::setFields;

    /**
     *  Fields must be non null
     */
    void assignFrom(void *pSrc) override
    {
	this->setEntityPtr(static_cast<char*>(pSrc));
    }

    void assignTo(void *&pDest) const override
    {
	pDest = this->getEntityPtr();
    }

    void set(TFieldsWrapper pInfo,void *pSrc) override
    {
	this->setEntityPtr(static_cast<char*>(pSrc));
	this->setFields(pInfo);
    }

    void clear() override
    {
	this->setEntityPtr(nullptr);
	this->setFields(nullptr);
    }

};


};

#endif
