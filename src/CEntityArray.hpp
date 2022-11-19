#ifndef CENTITY_ARRAY_HPP
#define CENTITY_ARRAY_HPP

#include "CEntity.hpp"

namespace ipgdlib::entity
{

    template <typename FieldsT>
    template <typename RowCountT>    
    CEntity<FieldsT>::Array<RowCountT>::~Array()
    {
        if (this->m_arrPEntityData != nullptr)
        {
            for(TRowIndex li = 0;li < this->m_EntityCount;li++)
                delete this->m_arrPEntityData[li];
            delete[] m_arrPEntityData;
        }
    }

    template <typename FieldsT>
    template <typename RowCountT>    
    CEntity<FieldsT>::Array<RowCountT>::Array(const CEntity<FieldsT>::TFields &fields,TRowIndex entityCount) :
        m_Fields(&fields),m_EntityCount(entityCount)
    {
        this->m_arrPEntityData = new char *[m_EntityCount];
        for (TRowIndex li = 0; li < m_EntityCount; li++)
            m_arrPEntityData[li] = new char[m_Fields->size()];
    }

    template <typename FieldsT>
    template <typename RowCountT>    
    const FieldsT &CEntity<FieldsT>::Array<RowCountT>::getFields() const
    {
        return *this->m_Fields;
    }

    template <typename FieldsT>
    template <typename RowCountT>    
    RowCountT CEntity<FieldsT>::Array<RowCountT>::count() const noexcept
    {
        return this->m_EntityCount;
    }

    template <typename FieldsT>
    template <typename RowCountT>    
    typename CEntity<FieldsT>::Array<RowCountT>::Cursor CEntity<FieldsT>::Array<RowCountT>::createCursor(TRowIndex iStart) const
    {
        return {*this,iStart};
    }

    template <typename FieldsT>
    template <typename RowCountT>    
    CEntity<FieldsT>::Array<RowCountT>::Cursor::Cursor(const CEntity<FieldsT>::Array<RowCountT>& array,RowCountT iStart) :
        m_EntityArray(&array),m_RowPos(iStart),m_EntityShared(array.getFields(),array.m_arrPEntityData[iStart])
    {

    }

    template <typename FieldsT>
    template <typename RowCountT>
    typename CEntity<FieldsT>::Array<RowCountT>::TRowIndex CEntity<FieldsT>::Array<RowCountT>::Cursor::getRowPos() const noexcept
    {
        return this->m_RowPos;
    }

    template <typename FieldsT>
    template <typename RowCountT>
    typename CEntity<FieldsT>::Array<RowCountT>::Cursor& CEntity<FieldsT>::Array<RowCountT>::Cursor::setRowPos(CEntity<FieldsT>::Array<RowCountT>::TRowIndex rowPos)
    {
        this->m_RowPos = rowPos;
        
        this->m_EntityShared.setEntityPtr(this->m_EntityArray->m_arrPEntityData[rowPos]);
        return *this;
    }

    template <typename FieldsT>
    template <typename RowCountT>
    const typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Array<RowCountT>::Cursor::getEntity() const
    {
        return this->m_EntityShared;
    }

    template <typename FieldsT>
    template <typename RowCountT>
    typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Array<RowCountT>::Cursor::getEntity()
    {
        return this->m_EntityShared;
    }

    template <typename FieldsT>
    template <typename RowCountT>
    const typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Array<RowCountT>::Cursor::operator[](RowCountT rowPos) const
    {
        this->setRowPos(rowPos);
        return this->m_EntityShared;
    }

    template <typename FieldsT>
    template <typename RowCountT>
    typename CEntity<FieldsT>::Shared& CEntity<FieldsT>::Array<RowCountT>::Cursor::operator[](RowCountT rowPos)
    {
        this->setRowPos(rowPos);
        return this->m_EntityShared;
    }

};

#endif