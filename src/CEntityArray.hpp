#ifndef CENTITY_ARRAY_HPP
#define CENTITY_ARRAY_HPP

#include "CEntity.hpp"

namespace ipgdlib::entity
{

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>    
    CEntity<FieldsT>::Array<CountT,EntitySharedT>::~Array()
    {
        if (this->m_arrPEntityData != nullptr)
        {
            for(TRowIndex li = 0;li < this->m_EntityCount;li++)
                delete this->m_arrPEntityData[li];
            delete[] m_arrPEntityData;
        }
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>    
    CEntity<FieldsT>::Array<CountT,EntitySharedT>::Array(const CEntity<FieldsT>::TFields &fields,TRowIndex entityCount) :
        m_Fields(&fields),m_EntityCount(entityCount)
    {
        this->m_arrPEntityData = new char *[m_EntityCount];
        for (TRowIndex li = 0; li < m_EntityCount; li++)
            m_arrPEntityData[li] = new char[m_Fields->size()];
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>    
    const FieldsT &CEntity<FieldsT>::Array<CountT,EntitySharedT>::getFields() const
    {
        return *this->m_Fields;
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>    
    CountT CEntity<FieldsT>::Array<CountT,EntitySharedT>::count() const noexcept
    {
        return this->m_EntityCount;
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>    
    typename CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor CEntity<FieldsT>::Array<CountT,EntitySharedT>::createCursor(TRowIndex iStart) const
    {
        return {*this,iStart};
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>    
    CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor::Cursor(const CEntity<FieldsT>::Array<CountT,EntitySharedT>& array,CountT iStart) :
        m_EntityArray(&array),m_RowPos(iStart),m_EntityShared(array.getFields(),array.m_arrPEntityData[iStart])
    {

    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>
    typename CEntity<FieldsT>::Array<CountT,EntitySharedT>::TRowIndex CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor::getRowPos() const noexcept
    {
        return this->m_RowPos;
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>
    typename CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor& CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor::setRowPos(CEntity<FieldsT>::Array<CountT,EntitySharedT>::TRowIndex rowPos)
    {
        this->m_RowPos = rowPos;
        this->m_EntityShared.setEntityPtr(this->m_EntityArray.m_arrPEntityData[rowPos]);
        return *this;
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>
    const typename CEntity<FieldsT>::Array<CountT,EntitySharedT>::TShared& CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor::getEntity() const
    {
        return this->m_EntityShared;
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>
    typename CEntity<FieldsT>::Array<CountT,EntitySharedT>::TShared& CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor::getEntity()
    {
        return this->m_EntityShared;
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>
    const EntitySharedT& CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor::operator[](CountT rowPos) const
    {
        this->setRowPos(rowPos);
        return this->m_EntityShared;
    }

    template <typename FieldsT>
    template <typename CountT,typename EntitySharedT>
    EntitySharedT& CEntity<FieldsT>::Array<CountT,EntitySharedT>::Cursor::operator[](CountT rowPos)
    {
        this->setRowPos(rowPos);
        return this->m_EntityShared;
    }

};

#endif