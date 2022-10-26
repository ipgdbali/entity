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
        using parent    = CEntityFacade<TFields>::Base;
        using TWFields  = typename parent::TWFields;

        virtual ~Unique()
        {
            if(this->getEntityPtr() != nullptr)
                delete []this->getEntityPtr();
        }

        Unique() = delete;
        Unique(const Unique &ref) = delete;
        Unique &operator = (const Unique &ref) = delete;
        Unique(Unique &&ref) = delete;
        Unique &operator = (Unique &&ref) = delete;


        Unique(TWFields fields) 
            : CEntityFacade<TFields>::Base(fields,new char[fields.size()])
        {
        }

};

};

#endif