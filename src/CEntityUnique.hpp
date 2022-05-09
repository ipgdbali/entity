#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "IEntityUnique.hpp"
#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <
	typename TAttrIndex,			
	typename TAttrName,		
	typename TAttrSize,
	typename TAttrSizeTotal,
	typename TEntityInfo = CEntityInfo<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,
	    CAttrInfo<TAttrName,TAttrSize>;
>
class CEntityUnique :
    public CEntity<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,TEntityInfo>,
    public virtual IEntityUnique<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo,TEntityInfo const *>
{
public:
    virtual ~CEntityUnique()
    {
	this->clear();
    }

    bool createFrom(TEntityInfo const &entityInfo) override
    {
	this->clear();

	this->setEntityInfo(&EntityInfo);
	this->setEntityPtr(new char [this->getEntityInfo()->getEntitySize()]);
	return true;
    }

    bool createFrom(IEntity<TAttrIndex,TAttrName,TAttrSize,TAttrSizeTotal,TEntityInfo> const &entity) override
    {
	this->clear();
	this->setEntityInfo(entity.getEntityInfo());
	this->setEntityPtr(new char [this->getEntityInfo()->getEntitySize()]);
	return true;
    }

    void clear() override
    {
	if(this->getEntityPtr() != nullptr)
	{
	    delete []this->getEntityPtr();
	    this->setEntityPtr(nullptr);

	    // clear entity info
	    CEntity<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,TEntityInfo *>::clear();
	}
    }

    protected:
    private:
};

};

#endif
