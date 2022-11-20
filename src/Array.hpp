#ifndef ARRAY_HPP
#define ARRAY_HPP

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
CEntity<FieldsT>::Array<RowCountT>::Array(const CEntity<FieldsT>::TFields& fields,TRowIndex entityCount) :
    CEntity<FieldsT>::BaseEntities<RowCountT>(fields),m_EntityCount(entityCount)
{
    this->m_arrPEntityData = new char *[m_EntityCount];
    for (TRowIndex li = 0; li < m_EntityCount; li++)
        m_arrPEntityData[li] = new char[this->getFields().size()];
}

template <typename FieldsT>
template <typename RowCountT>    
RowCountT CEntity<FieldsT>::Array<RowCountT>::count() const noexcept
{
    return this->m_EntityCount;
}

template <typename FieldsT>
template <typename RowCountT>    
const char* CEntity<FieldsT>::Array<RowCountT>::getEntityPtr(TRowIndex index) const
{
    return this->m_arrPEntityData[index];
}

template <typename FieldsT>
template <typename RowCountT>    
char* CEntity<FieldsT>::Array<RowCountT>::getEntityPtr(TRowIndex index)
{
    return this->m_arrPEntityData[index];
}

};

#endif