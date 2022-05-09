#ifndef CENTITY_INFO_HPP
#define CENTITY_INFO_HPP

#include "IEntityInfo.hpp"
#include "IAttrInfo.hpp"
#include "CAttrInfo.hpp"
#include <initializer_list>
#include <map>

namespace ipgdlib::entity
{

template <
	typename TAttrName,
	typename TAttrIndex,
	typename TAttrSize,
	typename TAttrSizeTotal,
	typename TAttrInfo
>
class CEntityInfo :
    public IEntityInfo<TAttrName,TAttrIndex,TAttrSize,TAttrSizeTotal,TAttrInfo,TAttrInfo const *>
{
public:
    using type_attr_name = TAttrName;
    using type_attr_index = TAttrIndex;
    using type_attr_size = TAttrSize;
    using type_attr_size_total = TAttrSizeTotal;
    using type_attr_info = TAttrInfo;

    CEntityInfo(const CEntityInfo &ref) = delete;
    CEntityInfo &operator = (const CEntityInfo &ref) = delete;
    CEntityInfo(CEntityInfo && ref) = delete;
    CEntityInfo &operator = (CEntityInfo && ref) = delete;

    CEntityInfo(std::initializer_list<TAttrInfo const *> ltpAttrInfo)
    {
	this->m_AttrCount = ltpAttrInfo.size();
	this->m_arrAttrInfos = new TAttrInfo const*[this->m_AttrCount];
	this->m_RunningSum = new TAttrSizeTotal[this->m_AttrCount];

	TAttrIndex idx = 0;
	TAttrSizeTotal sum = 0;

	for(auto it = ltpAttrInfo.begin();it != ltpAttrInfo.end();++it)
	{
	    if(this->hasName((*it)->getName()))
		throw "Duplicate Name";

	    this->m_arrAttrInfos[idx] = *it;
	    this->m_RunningSum[idx] = (*it)->getSize() + sum;
	    sum = this->m_RunningSum[idx];
	    m_Mapper[(*it)->getName()] = idx;
	    idx++;
	}
    }

    ~CEntityInfo()
    {
	for(TAttrIndex li = 0;li < this->m_AttrCount;li++)
	    delete this->m_arrAttrInfos[li];

	delete [] this->m_arrAttrInfos;
	delete [] this->m_RunningSum;
    }

    TAttrIndex getAttrCount() const noexcept override
    {
	return this->m_AttrCount;
    }

    TAttrInfo const* getAttrInfo(TAttrIndex index) const override
    {
	return this->m_arrAttrInfos[index];
    }

    TAttrSizeTotal getRunningSum(TAttrIndex index) const override
    {
	return this->m_RunningSum[index];
    }

    TAttrSizeTotal getAttrOffset(TAttrIndex index) const noexcept override
    {
	if(index == 0)
	    return 0;
	else
	    return this->m_RunningSum[index - 1];
    }

    TAttrSizeTotal getEntitySize() const noexcept override
    {
	return this->m_RunningSum[this->m_AttrCount - 1];
    }

    bool hasName(TAttrName const &attrName) const noexcept override
    {
	return this->m_Mapper.count(attrName) == 1;
    }

    TAttrIndex getIndex(TAttrName const &attrName) const override
    {
	return this->m_Mapper.at(attrName);
    }

    TAttrName const &getName(TAttrIndex index) const override
    {
	return this->m_arrAttrInfos[index]->getName();
    }

private:
    TAttrIndex m_AttrCount;
    TAttrInfo const* *m_arrAttrInfos;
    TAttrSizeTotal *m_RunningSum;
    std::map<TAttrName,TAttrIndex> m_Mapper;
};

};
#endif
