#ifndef CBASIC_ENTITY_HPP
#define CBASIC_ENTITY_HPP

#include "IEntity.hpp"

namespace ipgdlib:entity
{

template <
    typename TAttrSize,
    typename TAttrName
>
class CEntityAttrInfo :
    public IEntityAttrInfo<TAttrSize,TAttrName>
{
public:
    CEntityAttributeInfo(TAttrSize const &size,TAttrName const &name) :
	m_Size(size),m_Name(name)
    {
    }

    TAttrSize const &getSize() const noexcept
    {
	return this->m_Size;
    }

    TAttrName const &getName() const noexcept
    {
	return this->m_Name;
    }

private:
    TAttrSize const m_Size;
    TAttrName const m_Name;
};

template <
	typename TAttrIndex		
	typename TAttrName,
	typename TAttrSize,
	typename TAttrSizeTotal,
	typename TEntityAttrInfo = CEntityAttrInfo<TAttrSize,TAttrName> const *
>
class CEntityInfo :
    public IEntityInfo<TAttrIndex,TAttrName,TAttrSize,TAttrSize,TAttrSizeTotal,TEntityAttrInfo>
{

public:

    using type_attr_index = TAttrIndex;
    using type_attr_name = TAttrName;
    using type_attr_size = TAttrSize;
    using type_attr_size_total = TAttrSizeTotal;
    using type_entity_attr_info = TEntityAttrInfo;

    CEntityInfo(std::initializer_list<TEntityAttrInfo> ltpAttrInfo)
    {
	this->m_AttrCount = ltpAttrInfo.size();
	this->m_EntityAttrInfo = new TEntityAttrInfo[this->m_AttrCount];
	this->m_RunningSum = new TAttrSizeTotal[this->m_AttrCount];

	TAttrIndex idx = 0;
	TAttrSizeTotal = 0;
	for(auto it = ltpAttrInfo.begin();it != ltpAttrInfo.end();++it)
	{
	    this->m_EntityAttrInfo[idx] = *it;
	    this->m_RunningSum[idx] = it->getSize() + sum;
	    sum = this->m_RunningSum[idx];
	}
    }

    ~CEntityInfo()
    {
	for(size_t li = 0;li < this->m_AttrCount;li++)
	    delete this->m_EntityAttrInfo[li];

	delete [] this->m_EntityAttrInfo;
	delete [] this->m_RunningSum;
    }

    TAttrIndex const &getAttrCount() const noexcept override
    {
	return this->m_AttrCount;
    }

    TEntityAttrInfo getAttrInfo(TAttrIndex const &index) const override
    {
	return this->m_EntityAttrInfo[index];
    }

    TAttrSizeTotal const &getRunningSum(TAttrIndex const &index) const override
    {
	return this->m_RunningSum[index];
    }

    TAttrSizeTotal const &getEntitySize() const noexcept override
    {
	return this->m_RunningSum[this->m_AttrCount - 1];
    }

    bool hasName(TAttrName const &attrName) const noexcept override
    {
	return this->m_Mapper.count(attrName) == 1;
    }

    TAttrIndex const &getIndex(TAttrName const &attrName) const override
    {
	return this->m_Mapper[attrName];
    }


    TAttrName const &getName(TAttrIndex const &index) const override
    {
	return this->m_EntityAttrInfo[index]->getName();
    }

private:
    TAttrIndex m_AttrCount;
    TEntityAttrInfo *m_EntityAttrInfos;
    TAttrSizeTotal *m_RunningSum;
    std::map<TAttrName,TAttrIndex> m_Mapper;
};

template <
	typename TIndex,			
	typename TString,		
	typename TAttrSize,
	typename TAttrSizeTotal
	typename TEntityInfo
>
class CEntity :
    public IEntity // << LAST
{
public:

	IEntityInfo<TIndex,TString,TAttrSize,TAttrSizeTotal,IEntityAttrInfo<TAttrSize,TString>>
	const &getEntityInfo() const
	{
		return *this->m_pEntityInfo;
	}

	bool copyTo(TIndex const &idx,void *dst) const
	{
		if(idx >= 0 && idx < this->getAttrCount())
		{
			char *pSrc = this->getAttrPtr(idx);
			char *pDst = dst;
			for(size_t li = 0;li < this->getAttrSize();li++)
				pDst[li] = pSrc[li];
		}
		else
			return false;
	}

	bool copyTo(TString const &pName,void *dst) const
	{
		if(this->m_pEntityInfo->hasName(pName))
			return this->copyTo(this->m_pEntityInfo->getIndex(pName),dst);
		else
			return false;
	}

	bool copyFrom(TIndex const &idx,void *src)
	{
		if(idx >= 0 && idx < this->getAttrCount())
		{
			char *pSrc = src; 
			char *pDst = this->getAttrPtr(idx);
			for(size_t li = 0;li < this->getAttrSize();li++)
				pDst[li] = pSrc[li];
		}
		else
			return false;
	}

	bool copyFrom(TString const &pName,void *src)
	{
		if(this->m_pEntityInfo->hasName(pName))
			return this->copyFrom(this->m_pEntityInfo->getIndex(pName),dst);
		else
			return false;
	}

	template <typename T>
	T &as(TIndex const &idx)
	{
		if(idx >= 0 && idx < this->getAttrCount())
			return *reinterpret_cast<T*>(this->getAttrPtr(idx));
		else
			throw "error";
	}

	template <typename T>
	T &as(TString const &pName)
	{
		if(this->m_pEntityInfo->hasName(pName))
			return *reinterpret_cast<T*>(this->getAttrPtr(this->getIndex(pName)));
		else
			throw "error";
	}

	template <typename TCustomType>
	TCustomType asCustom(TIndex const &idx)
	{
		if(idx >= 0 && idx < this->getAttrCount())
			return {this->getAttrSize(idx),this->getAttrPtr(idx)};
		else
			throw "error";
	}
	template <typename TCustomType>
	TCustomType asCustom(TString const &pName)
	{
		if(this->hasName(pName))
			return {this->getAttrSize(this->getIndex(pName)),this->getAttrPtr(this->getIndex(pName))};
		else
			throw "Error";
	}


protected:
	char *getAttrPtr(TIndex idx) const
	{
		if(idx > 0 && idx < this->getAttrCount())
		{
			if(idx == 0)
				return this->m_pEntityData;
			else
				return &this->m_pEntityData[this->m_pEntityInfo->getRunningSum(idx - 1)];
		}
		else
			return nullptr;
	}

	TAttrSize getAttrSize(TIndex idx) const
	{
		if(idx < this->getAttrCount())
			return this->m_pEntityData->getAttrInfo(idx)->getSize();
	}
	bool hasName(TString const &pName) const
	{
		return this->m_pEntityInfo->hasName(pName);
	}

	TIndex getAttrCount() const
	{
		return this->m_pEntityInfo->getAttrCount();
	}

	TIndex getIndex(TString const &pName)
	{
		return this->m_pEntityInfo->getIndex(pName);
	}


private:
	IEntityInfo *m_pEntityInfo;
	char *m_pEntityData;

};
*/


};

#endif
