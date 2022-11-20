#ifndef UNIQUE_HPP
#define UNIQUE_HPP

#include "BaseEntity.hpp"

namespace ipgdlib::entity
{

template <typename FieldsT>
CEntity<FieldsT>::Unique::~Unique()
{
    free(this->getEntityPtr());
}

template <typename FieldsT>
CEntity<FieldsT>::Unique::Unique(const CEntity<FieldsT>::BaseEntity& ref) :
    CEntity<FieldsT>::BaseEntity(ref.getFields(),std::malloc(ref.getFields().size()))
{
    if(this->getEntityPtr() == nullptr)
        throw std::bad_alloc();
    else
        std::memcpy(this->getEntityPtr(),ref.getEntityPtr(),ref.getFields().size());
}

/**
 * Move Constructor
*/
template <typename FieldsT>
CEntity<FieldsT>::Unique::Unique(CEntity<FieldsT>::Unique&& ref) :
    CEntity<FieldsT>::BaseEntity(std::move(ref))
{
}

template <typename FieldsT>
CEntity<FieldsT>::Unique::Unique(const TFields& fields) : 
    BaseEntity::BaseEntity(fields,std::malloc(fields.size()))
{
    if(BaseEntity::getEntityPtr() == nullptr)
        throw std::bad_alloc();
}


/**
 * Copy Operator
*/
template <typename FieldsT>
typename CEntity<FieldsT>::Unique& CEntity<FieldsT>::Unique::operator = (const CEntity<FieldsT>::BaseEntity& ref)
{
    delete []this->getEntityPtr();
    BaseEntity::setEntityPtr(std::malloc(ref.getField().size()));
    if(BaseEntity::getEntityPtr() == nullptr)
        throw std::bad_alloc();
    else
        std::memcpy(BaseEntity::getEntityPtr(),ref.getEntityPtr());
    return *this;
}

/**
 * Move Operator
*/
template <typename FieldsT>
typename CEntity<FieldsT>::Unique& CEntity<FieldsT>::Unique::operator = (CEntity<FieldsT>::Unique &&ref)
{
    delete []this->getEntityPtr();
    
    BaseEntity::operator=(std::move(ref));
    return *this;
}


};

#endif