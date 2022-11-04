#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "CEntityBase.hpp"

namespace ipgdlib::entity
{

template <typename FieldsT>
class CEntity<FieldsT>::Unique :
    public CEntity<FieldsT>::Base,
    virtual public IEntity<const FieldsT&,typename FieldsT::iface::TFieldName,typename FieldsT::iface::TFieldIndex>::IUnique
{
    public:
        using TFields   = FieldsT;
        using Base      = CEntity<TFields>::Base;

        virtual ~Unique()
        {
            delete []this->getEntityPtr();
        }

        Unique() = delete;

        /**
         * Copy Constructor
        */
        Unique(const CEntity<TFields>::Base &ref) :
            Unique(ref.getFields())
        {
            std::memcpy(Base::getEntityPtr(),ref.getEntityPtr());
        }

        /**
         * Copy Operator
        */
        Unique &operator = (const Unique &ref)
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
         * Move Constructor
        */
        Unique(Unique &&ref) :
            Base::Base(std::move(ref))
        {
        }

        /**
         * Move Operator
        */
        Unique &operator = (Unique &&ref)
        {
            delete []this->getEntityPtr();
            Base::operator=(std::move(ref));
            return *this;
        }

        Unique(typename Base::iface::TFields fields) : 
            Base::Base(fields)
        {
            Base::setEntityPtr(std::malloc(fields.size()));
            if(Base::getEntityPtr() == nullptr)
                throw std::bad_alloc();
        }

};

};

#endif