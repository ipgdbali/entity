#ifndef CFIELDS_HPP
#define CFIELDS_HPP

#include "wrapper.hpp"

#include "IFields.hpp"
#include "IField.hpp"
#include "CField.hpp"
#include <initializer_list>
#include <map>

namespace ipgdlib::entity
{

template <
	typename TFieldIndex,
	typename TFieldSizeTotal,
	typename TFieldInfo
>
class CFields :
    public IFields<TFieldIndex,TFieldSizeTotal,TFieldInfo,ewConstPointer>
{

using TFieldInfoWrapper = typename ipgdlib::wrap<TFieldInfo,ewConstPointer>::value;
using TFieldName = typename TFieldInfo::iface::type_field_name;
using TFieldSize = typename TFieldInfo::iface::type_field_size;

public:
    using iface = IFields<TFieldIndex,TFieldSizeTotal,TFieldInfo,ewConstPointer>;
    using type_field_name = TFieldName;
    using type_field_index = TFieldIndex;
    using type_field_size = TFieldSize;
    using type_field_size_total = TFieldSizeTotal;
    using type_field_info = TFieldInfo;
    using type_field_info_wrapper = TFieldInfoWrapper;

    CFields() = delete;
    CFields(const CFields &ref) = delete;
    CFields &operator = (const CFields &ref) = delete;
    CFields(CFields && ref) = delete;
    CFields &operator = (CFields && ref) = delete;

    CFields(std::initializer_list<TFieldInfoWrapper> ltpFieldInfo)
    {
	this->m_FieldCount = ltpFieldInfo.size();
	this->m_arrFieldInfos = new TFieldInfoWrapper[this->m_FieldCount];
	this->m_RunningSum = new TFieldSizeTotal[this->m_FieldCount];

	TFieldIndex idx = 0;
	TFieldSizeTotal sum = 0;

	for(auto it = ltpFieldInfo.begin();it != ltpFieldInfo.end();++it)
	{
	    if(this->hasName((*it)->name()))
		throw "Duplicate Name";

	    this->m_arrFieldInfos[idx] = *it;
	    this->m_RunningSum[idx] = (*it)->size() + sum;
	    sum = this->m_RunningSum[idx];
	    m_Mapper[(*it)->name()] = idx;
	    idx++;
	}
    }

    ~CFields()
    {
	for(TFieldIndex li = 0;li < this->m_FieldCount;li++)
	    delete this->m_arrFieldInfos[li];

	delete [] this->m_arrFieldInfos;
	delete [] this->m_RunningSum;
    }

    TFieldIndex getFieldCount() const noexcept override
    {
	return this->m_FieldCount;
    }

    TFieldInfoWrapper getField(TFieldIndex index) const override
    {
	return this->m_arrFieldInfos[index];
    }

    TFieldSizeTotal getRunningSum(TFieldIndex index) const override
    {
	return this->m_RunningSum[index];
    }

    TFieldSizeTotal getFieldOffset(TFieldIndex index) const noexcept override
    {
	if(index == 0)
	    return 0;
	else
	    return this->m_RunningSum[index - 1];
    }

    TFieldSizeTotal getFieldsSize() const noexcept override
    {
	return this->m_RunningSum[this->m_FieldCount - 1];
    }

    bool hasName(TFieldName const &fieldName) const noexcept override
    {
	return this->m_Mapper.count(fieldName) == 1;
    }

    TFieldIndex getIndex(TFieldName const &fieldName) const override
    {
	return this->m_Mapper.at(fieldName);
    }

    TFieldName const &getName(TFieldIndex index) const override
    {
	return this->m_arrFieldInfos[index]->name();
    }

private:
    TFieldIndex m_FieldCount;
    TFieldInfoWrapper *m_arrFieldInfos;
    TFieldSizeTotal *m_RunningSum;
    std::map<TFieldName,TFieldIndex> m_Mapper;
};

};
#endif
