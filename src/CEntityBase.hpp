#ifndef CENTITY_BASE_HPP
#define CENTITY_BASE_HPP

#include "CEntity.hpp"
#include <cstring>

namespace ipgdlib::entity
{

template <typename FieldsT>
const FieldsT& CEntity<FieldsT>::Base::getFields() const noexcept
{
    return *this->m_Fields;
}

template <typename FieldsT>
bool CEntity<FieldsT>::Base::copyAttrTo(TFieldIndex fieldIndex, void *pDst) const
{
    return 
        std::memcpy(
            pDst,
            &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
            this->m_Fields->getField(fieldIndex).size()) != nullptr;
}

template <typename FieldsT>
bool CEntity<FieldsT>::Base::copyAttrTo(TFieldName fieldName, void *pDst) const
{
    return copyAttrTo(
        this->m_Fields->indexOf(fieldName),
        pDst);
}

template <typename FieldsT>
bool CEntity<FieldsT>::Base::copyAttrFrom(TFieldIndex fieldIndex, const void *pSrc)
{
    std::memcpy(
        &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
        pSrc,
        this->m_Fields->getField(fieldIndex).size());
    return true;
}

template <typename FieldsT>
bool CEntity<FieldsT>::Base::copyAttrFrom(TFieldName fieldName, const void *pSrc)
{
    return copyAttrFrom(
        this->m_Fields->indexOf(fieldName),
        pSrc);
}

template <typename FieldsT>
template <typename T>
const T& CEntity<FieldsT>::Base::as(TFieldIndex fieldIndex) const
{
    return *reinterpret_cast<T *>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
}

template <typename FieldsT>
template <typename T>
T& CEntity<FieldsT>::Base::as(TFieldIndex fieldIndex)
{
    return *reinterpret_cast<T *>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
}

template <typename FieldsT>
template <typename T>
T& CEntity<FieldsT>::Base::as(TFieldName fieldName)
{
    return as<T>(this->m_Fields->indexOf(fieldName));
}

template <typename FieldsT>
template <typename T>
const T& CEntity<FieldsT>::Base::as(TFieldName fieldName) const
{
    return as<T>(this->m_Fields->indexOf(fieldName));
}

/* Copy Constructor */
template <typename FieldsT>
CEntity<FieldsT>::Base::Base(const Base& ref) :
    m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
{
}

/**
 * Move Construction
*/
template <typename FieldsT>
CEntity<FieldsT>::Base::Base(Base &&ref) :
    m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
{
    ref.m_Fields        = nullptr;
    ref.m_pEntityPtr    = nullptr;
}


template <typename FieldsT>
CEntity<FieldsT>::Base::Base(const TFields& fields,void* pData) : 
    m_Fields(&fields), m_pEntityPtr((char*)pData)
{
}

/**
 * Copy Operator, only for shared ptr
*/
template <typename FieldsT>
typename CEntity<FieldsT>::Base& CEntity<FieldsT>::Base::operator = (const Base &ref)
{
    this->m_Fields = ref.m_Fields;
    this->m_pEntityPtr = ref.m_pEntityPtr;
    return *this;
}

/**
 * Move Operator
*/
template <typename FieldsT>
typename CEntity<FieldsT>::Base& CEntity<FieldsT>::Base::operator = (Base &&ref)
{
    std::swap(this->m_Fields,ref.m_Fields);
    std::swap(this->m_pEntityPtr,ref.m_pEntityPtr);
    return *this;
}

template <typename FieldsT>
const char* CEntity<FieldsT>::Base::getEntityAttrPtr(TFieldIndex fieldIndex) const
{
    return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
}

template <typename FieldsT>
char* CEntity<FieldsT>::Base::getEntityAttrPtr(TFieldIndex fieldIndex)
{
    return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
}

template <typename FieldsT>
const char* CEntity<FieldsT>::Base::getEntityPtr() const
{
    return this->m_pEntityPtr;
}

template <typename FieldsT>
char* CEntity<FieldsT>::Base::getEntityPtr()
{
    return this->m_pEntityPtr;
}

template <typename FieldsT>
void CEntity<FieldsT>::Base::setEntityPtr(void *pEntityPtr)
{
    this->m_pEntityPtr = (char*)pEntityPtr;
}

template <typename FieldsT>
void CEntity<FieldsT>::Base::set(const TFields& fields,char* pEntityPtr)
{
    this->m_Fields      = fields;
    this->m_pEntityPtr  = pEntityPtr;
}

};

#endif