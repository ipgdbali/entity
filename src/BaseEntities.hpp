#ifndef BASE_ENTITIES_HPP
#define BASE_ENTITIES_HPP

#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <typename FieldsT>
template <typename RowCountT>
const typename CEntity<FieldsT>::TFields& CEntity<FieldsT>::BaseEntities<RowCountT>::getFields() const
{
    return *this->m_Fields;
}

template <typename FieldsT>
template <typename RowCountT>
bool CEntity<FieldsT>::BaseEntities<RowCountT>::copyAttrTo(TRowIndex idxRow,TFieldIndex fieldIndex, void *pDst) const
{
    return std::memcpy(pDst,
        &this->getEntityPtr(idxRow)[this->m_Fields->offset(fieldIndex)],
        this->m_Fields->getField(fieldIndex).size) != nullptr;
}

template <typename FieldsT>
template <typename RowCountT>
bool CEntity<FieldsT>::BaseEntities<RowCountT>::copyAttrTo(TRowIndex idxRow,TFieldName fieldName, void *pDst) const
{
    return copyAttrTo(
        idxRow,
        this->m_Fields->indexOf(fieldName),
        pDst);
}

template <typename FieldsT>
template <typename RowCountT>
bool CEntity<FieldsT>::BaseEntities<RowCountT>::copyAttrFrom(TRowIndex idxRow,TFieldIndex fieldIndex, const void *pSrc)
{
    return std::memcpy(
        &this->getEntityPtr(idxRow)[this->m_Fields->offset(fieldIndex)],
        pSrc,
        this->m_Fields->getField(fieldIndex).size()) != nullptr;

}

template <typename FieldsT>
template <typename RowCountT>
bool CEntity<FieldsT>::BaseEntities<RowCountT>::copyAttrFrom(TRowIndex idxRow,TFieldName fieldName, const void *pSrc)
{
    return copyAttrFrom(
        idxRow,
        this->m_Fields->indexOf(fieldName),
        pSrc);
}

template <typename FieldsT>
template <typename RowCountT>
template <typename T>
const T& CEntity<FieldsT>::BaseEntities<RowCountT>::attrAs(TRowIndex idxRow,TFieldIndex fieldIndex) const
{
    return *reinterpret_cast<T*>(&this->getEntityPtr(idxRow)[this->m_Fields->offset(fieldIndex)]);
}

template <typename FieldsT>
template <typename RowCountT>
template <typename T>
T& CEntity<FieldsT>::BaseEntities<RowCountT>::attrAs(TRowIndex idxRow,TFieldIndex fieldIndex)
{
    return *reinterpret_cast<T*>(&this->getEntityPtr(idxRow)[this->m_Fields->offset(fieldIndex)]);
}

template <typename FieldsT>
template <typename RowCountT>
template <typename T>
const T& CEntity<FieldsT>::BaseEntities<RowCountT>::attrAs(TRowIndex idxRow,TFieldName fieldName) const
{
    return attrAs<T>(idxRow,this->m_Fields->indexOf(fieldName));
}

template <typename FieldsT>
template <typename RowCountT>
template <typename T>
T& CEntity<FieldsT>::BaseEntities<RowCountT>::attrAs(TRowIndex idxRow,TFieldName fieldName)
{
    return attrAs<T>(idxRow,this->m_Fields->indexOf(fieldName));
}


template <typename FieldsT>
template <typename RowCountT>    
CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor::Cursor(CEntity<FieldsT>::BaseEntities<RowCountT>& entities,TRowIndex iStart) :
    m_Entities(&entities),m_RowPos(iStart),m_EntityShared(entities.getFields(),entities.getEntityPtr(iStart))
{
}

template <typename FieldsT>
template <typename RowCountT>
typename CEntity<FieldsT>::BaseEntities<RowCountT>::TRowIndex CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor::getRowPos() const noexcept
{
    return this->m_RowPos;
}

template <typename FieldsT>
template <typename RowCountT>
typename CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor& CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor::setRowPos(CEntity<FieldsT>::BaseEntities<RowCountT>::TRowIndex rowPos)
{
    this->m_RowPos = rowPos;
    this->m_EntityShared.setEntityPtr(this->m_Entities->getEntityPtr(rowPos));
    return *this;
}

template <typename FieldsT>
template <typename RowCountT>
bool CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor::isRowPosValid() const noexcept
{
    if( this->getRowPos() >= 0 && this->getRowPos() < m_Entities->count())
        return true;
    else
        return false;
}

template <typename FieldsT>
template <typename RowCountT>
const typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor::getEntity() const
{
    return this->m_EntityShared;
}

template <typename FieldsT>
template <typename RowCountT>
typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor::getEntity()
{
    return this->m_EntityShared;
}

template <typename FieldsT>
template <typename RowCountT>    
typename CEntity<FieldsT>::BaseEntities<RowCountT>::Cursor CEntity<FieldsT>::BaseEntities<RowCountT>::createCursor(TRowIndex iStart)
{
    return {*this,iStart};
}

template <typename FieldsT>
template <typename RowCountT>
CEntity<FieldsT>::BaseEntities<RowCountT>::BaseEntities(const TFields& fields) :
    m_Fields(&fields)
{
}

};

#endif