#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "CEntityBase.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityFacade<TFields>::Shared :
    public CEntityFacade<TFields>::Base,
    virtual public IEntity<TFields,CEntityFacade<TFields>::Base::enum_wrapper_fields>::IShared
{
    template <typename TRowIndex>
    friend class CEntityFacade<TFields>::Array;

    public:

        using Base = CEntityFacade<TFields>::Base;
        using TWFields = typename Base::TWFields;
        
        Shared() = delete;
        Shared(const Shared &ref) = delete;
        Shared &operator = (const Shared &ref) = delete;
        Shared(CEntityFacade<TFields>::Base &&) = delete;
        Shared& operator = (CEntityFacade<TFields>::Base &&) = delete;

        /**
         * Copy Constructor
        */
        Shared(const CEntityFacade<TFields>::Base &ref) :
            CEntityFacade<TFields>::Base(ref)
        {
        }

        /**
         * Copy Operator
        */
        Shared& operator = (const CEntityFacade<TFields>::Base& ref)
        {
            CEntityFacade<TFields>::Base::set(ref.m_Fields,ref.m_pEntityPtr);
            return *this;
        }

        /**
         * Move Constructor
        */
        Shared(Shared &&ref) :
            Base::Base(std::move(ref))
        {
        }
        
        /**
         * Move Operator
        */
        Shared& operator = (Shared&& ref)
        {
            Base::operator=(std::move(ref));
            return *this;
        }

    protected:
        Shared(TWFields fields,char *pData) : 
            CEntityFacade<TFields>::Base(fields,pData)
        {
        }

        Shared(TWFields fields) :
            CEntityFacade<TFields>::Base(fields)
        {
        }

};

};

#endif