#ifndef CFIELDS_HPP
#define CFIELDS_HPP

#include "wrapper.hpp"

#include "IFields.hpp"
#include "CField.hpp"
#include <vector>
#include <map>

namespace ipgdlib::entity
{

template <
	typename TFieldIndex,
	typename TSizeTotal,
	typename TField
>
class CFields :
  public IFields<TFieldIndex,TSizeTotal,TField,ewConstReference>
{
public:
  using iface 			      = IFields<TFieldIndex,TSizeTotal,TField,ewConstReference>;

	using type_field_index	= TFieldIndex;
	using type_size_total	  = TSizeTotal;
	using type_field		    = TField;

	using TFieldName		    = typename TField::iface::type_name;
	using TFieldSize		    = typename TField::iface::type_size;
	using TWField			      = typename ipgdlib::wrap<TField,ewConstReference>::value;

  CFields() = delete;
  CFields(const CFields &ref) = delete;
  CFields &operator = (const CFields &ref) = delete;
  CFields(CFields && ref)
    : m_FieldCount(ref.m_FieldCount)
  {
    ref.m_FieldCount = 0;
  }

  CFields &operator = (CFields && ref) = delete;

  ~CFields()
  {
    if(m_RunningSum)
      delete [] this->m_RunningSum;
  }


  CFields(std::vector<TField> vField)
    : m_arrFields(std::move(vField))
  {
    this->m_FieldCount 				= m_arrFields.size();
    this->m_RunningSum				= new TSizeTotal[this->m_FieldCount];
    TSizeTotal sum					= 0;
    TFieldIndex li 					= 0;
    for(auto field : m_arrFields)
    {
      this->m_RunningSum[li] 		= field.size() + sum;
      sum 						= this->m_RunningSum[li];
      m_Mapper[field.name()] 	= li;
      li++;
    }
  }

  TFieldIndex count() const noexcept override
  {
    return this->m_FieldCount;
  }

  TWField getField(TFieldIndex index) const override
  {
    return this->m_arrFields[index];
  }

  TWField operator[] (TFieldIndex index) const
  {
    return this->m_arrFields[index];
  }

  TSizeTotal sum(TFieldIndex index) const override
  {
    return this->m_RunningSum[index];
  }

  TSizeTotal offset(TFieldIndex index) const override
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

  TFieldIndex indexOf(TFieldName const &fieldName) const override
  {
    return this->m_Mapper.at(fieldName);
  }

private:
    TFieldIndex					              m_FieldCount;
    std::vector<TField>		            m_arrFields;
    TSizeTotal*					              m_RunningSum;
    std::map<TFieldName,TFieldIndex>  m_Mapper;

};

};
#endif
