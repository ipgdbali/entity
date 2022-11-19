#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "CEntityBase.hpp"

namespace ipgdlib::entity
{

template <typename FieldsT>
CEntity<FieldsT>::Shared::Shared(const Base& ref) :
    CEntity<FieldsT>::Base(ref)
{
}

// Move Constructor 
template <typename FieldsT>
CEntity<FieldsT>::Shared::Shared(Shared&& ref) :
    CEntity<FieldsT>::Shared(ref.m_Fields,ref.m_pEntityPtr)
{
}

template <typename FieldsT>
CEntity<FieldsT>::Shared::Shared(const TFields& fields,void* pData) :
    CEntity<FieldsT>::Base(fields,pData)
{
}

template <typename FieldsT>
typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Shared::operator = (const CEntity<TFields>::Base& ref)
{
    CEntity<TFields>::Base::set(ref.m_Fields,ref.m_pEntityPtr);
    return *this;
}

template <typename FieldsT>
typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Shared::operator = (CEntity<TFields>::Shared&& ref)
{
    CEntity<TFields>::Base::set(ref.m_Fields,ref.m_pEntityPtr);
    return *this;
};

};

#endif