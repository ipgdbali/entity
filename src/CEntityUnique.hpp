#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "CEntityBase.hpp"

namespace ipgdlib::entity
{

template <typename FieldsT>
CEntity<FieldsT>::Unique::~Unique()
{
    delete []this->getEntityPtr();
}

template <typename FieldsT>
CEntity<FieldsT>::Unique::Unique(const CEntity<FieldsT>::Base& ref) :
    CEntity<FieldsT>::Base(ref.getFields(),std::malloc(ref.getFields().size()))
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
    CEntity<FieldsT>::Base(std::move(ref))
{
}

template <typename FieldsT>
CEntity<FieldsT>::Unique::Unique(const TFields& fields) : 
    Base::Base(fields,std::malloc(fields.size()))
{
    if(Base::getEntityPtr() == nullptr)
        throw std::bad_alloc();
}


/**
 * Copy Operator
*/
template <typename FieldsT>
typename CEntity<FieldsT>::Unique& CEntity<FieldsT>::Unique::operator = (const CEntity<FieldsT>::Base& ref)
{
    delete []this->getEntityPtr();
    Base::setEntityPtr(std::malloc(ref.getField().size()));
    if(Base::getEntityPtr() == nullptr)
        throw std::bad_alloc();
    else
        std::memcpy(Base::getEntityPtr(),ref.getEntityPtr());
    return *this;
}

/**
 * Move Operator
*/
template <typename FieldsT>
typename CEntity<FieldsT>::Unique& CEntity<FieldsT>::Unique::operator = (CEntity<FieldsT>::Unique &&ref)
{
    delete []this->getEntityPtr();
    
    Base::operator=(std::move(ref));
    return *this;
}


};

#endif