#ifndef BASE_ENTITY_HPP
#define BASE_ENTITY_HPP

#include "CEntity.hpp"
#include <cstring>

namespace ipgdlib::entity
{

template <typename FieldsT>
const FieldsT& CEntity<FieldsT>::BaseEntity::getFields() const noexcept
{
    return *this->m_Fields;
}

template <typename FieldsT>
bool CEntity<FieldsT>::BaseEntity::copyAttrTo(TFieldIndex fieldIndex, void *pDst) const
{
    return 
        std::memcpy(
            pDst,
            &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
            this->m_Fields->getField(fieldIndex).size()) != nullptr;
}

template <typename FieldsT>
bool CEntity<FieldsT>::BaseEntity::copyAttrTo(TFieldName fieldName, void *pDst) const
{
    return copyAttrTo(
        this->m_Fields->indexOf(fieldName),
        pDst);
}

template <typename FieldsT>
bool CEntity<FieldsT>::BaseEntity::copyAttrFrom(TFieldIndex fieldIndex, const void *pSrc)
{
    return std::memcpy(
        &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
        pSrc,
        this->m_Fields->getField(fieldIndex).size()) != nullptr;
}

template <typename FieldsT>
bool CEntity<FieldsT>::BaseEntity::copyAttrFrom(TFieldName fieldName, const void *pSrc)
{
    return copyAttrFrom(
        this->m_Fields->indexOf(fieldName),
        pSrc);
}

template <typename FieldsT>
template <typename T>
const T& CEntity<FieldsT>::BaseEntity::attrAs(TFieldIndex fieldIndex) const
{
    return *reinterpret_cast<T*>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
}

template <typename FieldsT>
template <typename T>
T& CEntity<FieldsT>::BaseEntity::attrAs(TFieldIndex fieldIndex)
{
    return *reinterpret_cast<T *>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
}

template <typename FieldsT>
template <typename T>
const T& CEntity<FieldsT>::BaseEntity::attrAs(TFieldName fieldName) const
{
    return attrAs<T>(this->m_Fields->indexOf(fieldName));
}

template <typename FieldsT>
template <typename T>
T& CEntity<FieldsT>::BaseEntity::attrAs(TFieldName fieldName)
{
    return attrAs<T>(this->m_Fields->indexOf(fieldName));
}

/* Copy Constructor */
template <typename FieldsT>
CEntity<FieldsT>::BaseEntity::BaseEntity(const BaseEntity& ref) :
    m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
{
}

/**
 * Move Construction
*/
template <typename FieldsT>
CEntity<FieldsT>::BaseEntity::BaseEntity(BaseEntity &&ref) :
    m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
{
    ref.m_Fields        = nullptr;
    ref.m_pEntityPtr    = nullptr;
}


template <typename FieldsT>
CEntity<FieldsT>::BaseEntity::BaseEntity(const TFields& fields,void* pData) : 
    m_Fields(&fields), m_pEntityPtr((char*)pData)
{
}

/**
 * Copy Operator, only for shared ptr
*/
template <typename FieldsT>
typename CEntity<FieldsT>::BaseEntity& CEntity<FieldsT>::BaseEntity::operator = (const BaseEntity &ref)
{
    this->m_Fields = ref.m_Fields;
    this->m_pEntityPtr = ref.m_pEntityPtr;
    return *this;
}

/**
 * Move Operator
*/
template <typename FieldsT>
typename CEntity<FieldsT>::BaseEntity& CEntity<FieldsT>::BaseEntity::operator = (BaseEntity &&ref)
{
    std::swap(this->m_Fields,ref.m_Fields);
    std::swap(this->m_pEntityPtr,ref.m_pEntityPtr);
    return *this;
}

template <typename FieldsT>
const char* CEntity<FieldsT>::BaseEntity::getEntityAttrPtr(TFieldIndex fieldIndex) const
{
    return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
}

template <typename FieldsT>
char* CEntity<FieldsT>::BaseEntity::getEntityAttrPtr(TFieldIndex fieldIndex)
{
    return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
}

template <typename FieldsT>
const char* CEntity<FieldsT>::BaseEntity::getEntityPtr() const
{
    return this->m_pEntityPtr;
}

template <typename FieldsT>
char* CEntity<FieldsT>::BaseEntity::getEntityPtr()
{
    return this->m_pEntityPtr;
}

template <typename FieldsT>
void CEntity<FieldsT>::BaseEntity::setEntityPtr(void *pEntityPtr)
{
    this->m_pEntityPtr = (char*)pEntityPtr;
}

template <typename FieldsT>
void CEntity<FieldsT>::BaseEntity::set(const TFields& fields,void* pEntityPtr)
{
    this->m_Fields      = fields;
    this->m_pEntityPtr  = pEntityPtr;
}

};

#endif