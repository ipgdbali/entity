#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "CEntityBase.hpp"

namespace ipgdlib::entity
{

template <typename FieldsT>
class CEntity<FieldsT>::Shared :
    public CEntity<FieldsT>::Base,
    virtual public IEntity<const FieldsT&,typename FieldsT::iface::TFieldName,typename FieldsT::iface::TFieldIndex>::IShared
{

    public:
        using TFields   = FieldsT;
        using Base      = CEntity<TFields>::Base;
        
        Shared() = delete;
        Shared(const Shared &ref) = delete;
        Shared &operator = (const Shared &ref) = delete;
        Shared(CEntity<TFields>::Base &&) = delete;
        Shared& operator = (CEntity<TFields>::Base &&) = delete;

        /**
         * Copy Constructor
        */
        Shared(const CEntity<TFields>::Base &ref) :
            Base::Base(ref)
        {
        }

        /**
         * Copy Operator
        */
        Shared& operator = (const CEntity<TFields>::Base& ref)
        {
            CEntity<TFields>::Base::set(ref.m_Fields,ref.m_pEntityPtr);
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

        Shared(typename TFields::iface::TFields fields,char *pData) : 
            Base::Base(fields,pData)
        {
        }

    protected:

};

};

#endif