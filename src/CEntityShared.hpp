#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "IEntityShared.hpp"
#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <typename TEntityInfo>
class CEntityShared :
    public CEntity<TEntityInfo>,
    public virtual IEntityShared<TEntityInfo,ewConstPointer>
{
using TEntityInfoWrapper = TEntityInfo const *;

public:

    using CEntity<TEntityInfo>::setEntityInfo;

    /**
     *  EntityInfo must be non null
     */
    void assignFrom(void *pSrc) override
    {
	this->setEntityPtr(static_cast<char*>(pSrc));
    }

    void assignTo(void *&pDest) const override
    {
	pDest = this->getEntityPtr();
    }

    void set(TEntityInfoWrapper pInfo,void *pSrc) override
    {
	this->setEntityPtr(static_cast<char*>(pSrc));
	this->setEntityInfo(pInfo);
    }

    void clear() override
    {
	this->setEntityPtr(nullptr);
	this->setEntityInfo(nullptr);
    }

};


};

#endif
