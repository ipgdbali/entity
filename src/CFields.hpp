#ifndef CFIELDS_HPP
#define CFIELDS_HPP

#include "wrapper.hpp"

#include "IFields.hpp"
#include "CField.hpp"
#include <initializer_list>
#include <map>

namespace ipgdlib::entity
{

template <
	typename TCount,
	typename TSizeTotal,
	typename TField
>
class CFields :
    public IFields<TCount,TSizeTotal,TField,ewConstPointer>
{

using TWField		= typename ipgdlib::wrap<TField,ewConstPointer>::value;
using TFieldName	= typename TField::iface::type_name;
using TFieldSize	= typename TField::iface::type_size;

public:
    using iface = IFields<TCount,TSizeTotal,TField,ewConstPointer>;

    CFields() = delete;
    CFields(const CFields &ref) = delete;
    CFields &operator = (const CFields &ref) = delete;
    CFields(CFields && ref) = delete;
    CFields &operator = (CFields && ref) = delete;

    CFields(std::initializer_list<TWField> ltpFieldInfo) :
	CFields(ltpFieldInfo.begin(),ltpFieldInfo.end(),ltpFieldInfo.size())
    {
    }

    template <typename TIt>
    CFields(TIt first,TIt last,TCount count = 0)
    {
	if(count == 0)
	{
	    m_FieldCount = 0;
	    for(auto it = first;it != last;++it)
		this->m_FieldCount++;
	}
	else
	    m_FieldCount = count;

	this->m_arrFieldInfos	= new TWField[this->m_FieldCount];
	this->m_RunningSum	= new TSizeTotal[this->m_FieldCount];

	TSizeTotal sum		= 0;

	auto it = first;
	TCount li = 0;
	while(li < m_FieldCount || it != last)
	{
	    if(this->hasName((*it)->name()))
		throw "Duplicate Name";

	    this->m_arrFieldInfos[li] = *it;
	    this->m_RunningSum[li] = (*it)->size() + sum;
	    sum = this->m_RunningSum[li];
	    m_Mapper[(*it)->name()] = li;

	    //forward
	    li++;
	    ++it;
	}
    }


    ~CFields()
    {
	for(TCount li = 0;li < this->m_FieldCount;li++)
	    delete this->m_arrFieldInfos[li];

	delete [] this->m_arrFieldInfos;
	delete [] this->m_RunningSum;
    }

    TCount count() const noexcept override
    {
	return this->m_FieldCount;
    }

    TWField getField(TCount index) const override
    {
	return this->m_arrFieldInfos[index];
    }

    TSizeTotal sum(TCount index) const override
    {
	return this->m_RunningSum[index];
    }

    TSizeTotal offset(TCount index) const override
    {
	if(index == 0)
	    return 0;
	else
	    return this->m_RunningSum[index - 1];
    }

    TSizeTotal size() const noexcept override
    {
	return this->m_RunningSum[this->m_FieldCount - 1];
    }

    bool hasName(TFieldName const &fieldName) const noexcept override
    {
	return this->m_Mapper.count(fieldName) == 1;
    }

    TCount indexOf(TFieldName const &fieldName) const override
    {
	return this->m_Mapper.at(fieldName);
    }

private:
    TCount m_FieldCount;
    TWField *m_arrFieldInfos;
    TSizeTotal *m_RunningSum;
    std::map<TFieldName,TCount> m_Mapper;
};

};
#endif
