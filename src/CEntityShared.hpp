#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "IEntityShared.hpp"
#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <typename TEntityInfo>
class CEntityShared :
    public CEntity<TEntityInfo>,
    public virtual IEntityShared<TEntityInfo,TEntityInfo const *>
{

public:

    using CEntity<TEntityInfo>::setEntityInfo;

    bool assignFrom(void *pSrc) override
    {
	this->setEntityPtr(static_cast<char*>(pSrc));
	return true;
    }

    bool assignTo(void *&pDest) const override
    {
	pDest = this->getEntityPtr();
	return true;
    }

    bool set(void *pSrc,TEntityInfo const *pInfo) override
    {
	this->setEntityPtr(static_cast<char*>(pSrc));
	this->setEntityInfo(pInfo);
	return true;
    }

    void clear() override
    {
	this->setEntityPtr(nullptr);
	this->setEntityInfo(nullptr);
    }

};


};

#endif
