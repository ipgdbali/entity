#ifndef CENTITIES_HPP
#define CENTITIES_HPP

#include "IEntities.hpp"
#include "CEntityShared.hpp"

namespace ipgdlib::entity
{

template <typename TEntityCount,typename TEntityInfo>
class CEntities :
    public IEntities<TEntityCount,TEntityInfo,ewConstPointer>
{
using TEntityInfoWrapper = TEntityInfo const *;

public:
    using iface = IEntities<TEntityCount,TEntityInfo,ewConstPointer>;

    virtual ~CEntities()
    {
	if(this->m_arrPEntityData != nullptr)
	{
	    delete [] m_arrPEntityData;
	    this->m_arrPEntityData = nullptr;
	}
    }

    CEntities(TEntityInfoWrapper entityInfo,TEntityCount entityCount) :
	m_pEntityInfo(entityInfo),m_EntityCount(entityCount)
    {
	this->m_arrPEntityData = new char*[m_EntityCount];
	for(TEntityCount li = 0;li < m_EntityCount;li++)
	    m_arrPEntityData[li] = nullptr;
    }

    TEntityInfoWrapper getEntityInfo() const override
    {
	return this->m_pEntityInfo;
    }

    TEntityCount getEntityCount() const noexcept override
    {
	return this->m_EntityCount;
    }

    bool isNullEntities() const noexcept override
    {
	return this->m_arrPEntityData == nullptr;
    }

    bool isNullEntity(TEntityCount rowPos) const override
    {
	return this->m_arrPEntityData[rowPos] == nullptr;
    }

    void assignFrom(TEntityCount rowPos,void *pSrc) override
    {
	this->m_arrPEntityData[rowPos] = static_cast<char*>(pSrc);
    }

    void assignTo(TEntityCount rowPos,void *&pDest) const override
    {
	pDest = m_arrPEntityData[rowPos];
    }

    void *getPData(TEntityCount rowPos) override
    {
	return this->m_arrPEntityData[rowPos];
    }

    /**
     * Should not be null
     */
    void copyFrom(TEntityCount rowPos,const void *pSrc) override
    {
	std::memcpy(m_arrPEntityData[rowPos],pSrc,m_pEntityInfo->getFieldsSize());
    }

    /**
     * Should not be null
     */
    void copyTo(TEntityCount rowPos,void *pDest) const override
    {
	std::memcpy(pDest,m_arrPEntityData[rowPos],m_pEntityInfo->getFieldsSize());
    }

    void shareTo(TEntityCount rowPos,IEntityShared<TEntityInfo,ewConstPointer> &eShared) const override
    {
	eShared.set(m_pEntityInfo,m_arrPEntityData[rowPos]);
    }

protected:

private:
    TEntityInfoWrapper m_pEntityInfo;
    TEntityCount m_EntityCount;
    char* *m_arrPEntityData;
};

};

#endif
