#ifndef SHARED_HPP
#define SHARED_HPP

#include "BaseEntity.hpp"

namespace ipgdlib::entity
{

template <typename FieldsT>
CEntity<FieldsT>::Shared::Shared(const BaseEntity& ref) :
    CEntity<FieldsT>::BaseEntity(ref)
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
    CEntity<FieldsT>::BaseEntity(fields,pData)
{
}

template <typename FieldsT>
typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Shared::operator = (const CEntity<TFields>::BaseEntity& ref)
{
    CEntity<TFields>::BaseEntity::set(ref.m_Fields,ref.m_pEntityPtr);
    return *this;
}

template <typename FieldsT>
typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Shared::operator = (CEntity<TFields>::Shared&& ref)
{
    CEntity<TFields>::BaseEntity::set(ref.m_Fields,ref.m_pEntityPtr);
    return *this;
};

};

#endif