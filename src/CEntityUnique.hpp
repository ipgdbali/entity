#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "CEntityBase.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityFacade<TFields>::Unique :
    public CEntityFacade<TFields>::Base,
    virtual public IEntity<TFields,CEntityFacade<TFields>::Base::enum_wrapper_fields>::IUnique
{
    public:
        using Base      = CEntityFacade<TFields>::Base;
        using TWFields  = typename Base::TWFields;

        virtual ~Unique()
        {
            delete []this->getEntityPtr();
        }

        Unique() = delete;

        Unique(const Unique &ref) = delete;
        Unique &operator = (const Unique &ref) = delete;


        Unique(TWFields fields) : 
            Base::Base(fields)
        {
            Base::setEntityPtr(std::malloc(fields.size()));
            if(Base::getEntityPtr() == nullptr)
                throw std::bad_alloc();
        }

        /**
         * Copy Constructor
        */
        Unique(const CEntityFacade<TFields>::Base &ref) :
            Unique(ref.getFields())
        {
            std::memcpy(Base::getEntityPtr(),ref.getEntityPtr());
        }

        /**
         * Copy Operator
        */
        Unique &operator = (Unique &ref)
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
            Base::operator=(std::move(ref));
            return *this;
        }

    protected:
};

};

#endif