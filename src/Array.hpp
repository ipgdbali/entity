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
        this->deAlloc(this->m_CountAlloc);
        free(this->m_arrPEntityData);
    }
}

template <typename FieldsT>
template <typename RowCountT>    
CEntity<FieldsT>::Array<RowCountT>::Array(const CEntity<FieldsT>::TFields& fields,TRowIndex reserved) :
    CEntity<FieldsT>::BaseEntities<RowCountT>(fields),m_CountReserved(reserved),m_CountAlloc(0)
{
    this->m_arrPEntityData = static_cast<char**>(calloc(reserved,sizeof(char*)));
    for(RowCountT li = 0;li < reserved;li++)
        this->m_arrPEntityData[li] = nullptr;
}

template <typename FieldsT>
template <typename RowCountT>    
RowCountT CEntity<FieldsT>::Array<RowCountT>::count() const noexcept
{
    return this->m_CountAlloc;
}

template <typename FieldsT>
template <typename RowCountT>    
RowCountT CEntity<FieldsT>::Array<RowCountT>::reserved() const noexcept
{
    return this->m_CountReserved;
}

template <typename FieldsT>
template <typename RowCountT>    
RowCountT CEntity<FieldsT>::Array<RowCountT>::alloc(TRowCount count)
{
    if(this->reserved() - this->count() >= count)
    {
        for(RowCountT li = 0;li < count;li++)
        {
            this->m_arrPEntityData[this->m_CountAlloc + li] = static_cast<char*>(malloc(this->getFields().size()));
            if(this->m_arrPEntityData[this->m_CountAlloc + li] == nullptr)
            {
                this->m_CountAlloc += li;
                return li;
            }
        }
        this->m_CountAlloc += count;
        return count;
    }
    else
        return 0;
}

template <typename FieldsT>
template <typename RowCountT>    
RowCountT CEntity<FieldsT>::Array<RowCountT>::deAlloc(TRowCount count)
{
    if(this->m_CountAlloc >= count)
    {
        for(RowCountT li = 1;li <= count;li++)
        {
            free(this->m_arrPEntityData[this->m_CountAlloc - li]);
            this->m_arrPEntityData[this->m_CountAlloc - li] = nullptr;
        }
        this->m_CountAlloc -= count;
        return count;
    }
    else
        return 0;
}

template <typename FieldsT>
template <typename RowCountT>    
bool CEntity<FieldsT>::Array<RowCountT>::remRow(TRowIndex idxRow)
{
    if(idxRow < this->m_CountAlloc)
    {
        free(this->m_arrPEntityData[idxRow]);
        for(TRowIndex li = idxRow;li < this->m_CountAlloc - 1;li++)
            this->m_arrPEntityData[li] = this->m_arrPEntityData[li+1];
        this->m_CountAlloc--;
        this->m_arrPEntityData[this->m_CountAlloc] = nullptr;
        return true;
    }
    else
        return false;
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

template <typename FieldsT>
template <typename RowCountT>    
void CEntity<FieldsT>::Array<RowCountT>::setEntityPtr(TRowIndex index,char* entityPtr)
{
    this->m_arrPEntityData[index] = entityPtr;
}

};

#endif