#ifndef CFIELDS_HPP
#define CFIELDS_HPP

#include "IFields.hpp"
#include "CField.hpp"
#include <vector>
#include <map>

namespace ipgdlib::entity
{

template <
	typename CountT,
	typename TotalSizeT,
	typename FieldT
>
class CFields :
    public IFields<CountT,TotalSizeT,const FieldT&,typename FieldT::iface::TFieldName>
{

    // TODO
    //static_assert(std::is_base_of<IField<typename FieldT::TFieldName,typename FieldT::TFieldSize>,FieldT>::value);

    public:

        using iface 			            = IFields<CountT,TotalSizeT,const FieldT&,typename FieldT::iface::TFieldName>;

        using TCount                        = CountT;
        using TTotalSize                    = TotalSizeT;
        using TField                        = FieldT;

        ~CFields()
        {
            if(m_RunningSum)
                delete [] this->m_RunningSum;
        }

        CFields() = delete;

        CFields(const CFields<TCount,TTotalSize,TField> &ref) = delete;
        CFields<TCount,TTotalSize,TField> &operator = (const CFields<TCount,TTotalSize,TField> &ref) = delete;

        // TODO define
        CFields(CFields<TCount,TTotalSize,TField> && ref) = delete;    
        CFields<TCount,TTotalSize,TField> &operator = (CFields<TCount,TTotalSize,TField> && ref) = delete;

        CFields(std::vector<TField> vField) : 
            m_vFields(std::move(vField))
        {
            TTotalSize sum					= 0;
            typename iface::TFieldIndex li 	= 0;
            this->m_FieldCount 				= m_vFields.size();
            this->m_RunningSum				= new TTotalSize[this->m_FieldCount];
            for(auto field : m_vFields)
            {
                this->m_RunningSum[li] 		= field.size() + sum;
                sum 						= this->m_RunningSum[li];
                m_Mapper[field.name()] 	    = li;
                li++;
            }
        }

        TCount count() const noexcept override
        {
            return this->m_FieldCount;
        }

        TTotalSize sum(typename iface::TFieldIndex index) const override
        {
            return this->m_RunningSum[index];
        }

        TTotalSize offset(typename iface::TFieldIndex index) const override
        {
            if(index == 0)
                return 0;
            else
                return this->m_RunningSum[index - 1];
        }

        TTotalSize size() const noexcept override
        {
            return this->m_RunningSum[this->m_FieldCount - 1];
        }

        typename iface::TField getField(typename iface::TFieldIndex index) const override
        {
            return this->m_vFields[index];
        }

        typename iface::TField operator[] (typename iface::TFieldIndex index) const
        {
            return this->m_vFields[index];
        }

        bool hasName(typename iface::TFieldName fieldName) const noexcept override
        {
            return this->m_Mapper.count(fieldName) == 1;
        }

        typename iface::TFieldIndex indexOf(typename iface::TFieldName fieldName) const override
        {
            return this->m_Mapper.at(fieldName);
        }

    private:
        TCount					                                            m_FieldCount;
        std::vector<TField>                                                 m_vFields;
        TTotalSize*					                                        m_RunningSum;
        std::map<typename TField::TFieldName,typename iface::TFieldIndex>   m_Mapper;

    };

};
#endif
