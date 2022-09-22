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

using TFieldName	= typename TField::iface::type_name;
using TFieldSize	= typename TField::iface::type_size;

public:
    using iface 		= IFields<TCount,TSizeTotal,TField,ewConstPointer>;
	using TWField		= typename ipgdlib::wrap<TField,ewConstPointer>::value;

    CFields() = delete;
    CFields(const CFields &ref) = delete;
    CFields &operator = (const CFields &ref) = delete;
    CFields(CFields && ref) = delete;
    CFields &operator = (CFields && ref) = delete;

	~CFields()
    {
		for(TCount li = 0;li < this->m_FieldCount;li++)
			delete this->m_arrFieldInfos[li];

		delete [] this->m_arrFieldInfos;
		delete [] this->m_RunningSum;
    }


    CFields(std::initializer_list<TWField> ltpFieldInfo)
    {
		this->create(ltpFieldInfo);
    }
	
	template <typename T>
	CFields(T &col)
	{
		this->create(col);
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
    TCount						m_FieldCount;
    TWField*					m_arrFieldInfos;
    TSizeTotal*					m_RunningSum;
    std::map<TFieldName,TCount> m_Mapper;

	template <typename T>
	void create(T &col)
	{
		this->m_FieldCount 				= col.size();
		this->m_arrFieldInfos			= new TWField[this->m_FieldCount];
		this->m_RunningSum				= new TSizeTotal[this->m_FieldCount];
		TSizeTotal sum					= 0;
		TCount li 						= 0;
		for(TWField field : col)
		{
			this->m_arrFieldInfos[li] 	= field;
			this->m_RunningSum[li] 		= field->size() + sum;
			sum 						= this->m_RunningSum[li];
			m_Mapper[field->name()] 	= li;

			li++;
		}
	}
};

};
#endif
