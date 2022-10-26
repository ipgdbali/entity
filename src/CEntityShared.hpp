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

    public:

        using parent = CEntityFacade<TFields>::Base;
        using TWFields = typename parent::TWFields;
        
        Shared() = delete;
        Shared(const Shared &ref) = delete;
        Shared &operator = (const Shared &ref) = delete;
        Shared(Shared &&ref) = delete;
        Shared &operator = (Shared &&ref) = delete;

        Shared(CEntityFacade<TFields>::Base &ref) :
            CEntityFacade<TFields>::Base(ref)
        {
        }

        Shared(TWFields fields,char *pData) :
            CEntityFacade<TFields>::Base(fields,pData)
        {
        }

        Shared(TWFields fields) :
            CEntityFacade<TFields>::Base(fields)
        {
        }

        void set(void *pSrc) override
        {
            this->setEntityPtr(static_cast<char*>(pSrc));
        }

        bool isNull() const noexcept override
        {
            return this->getEntityPtr() == nullptr;
        }

        void clear() noexcept override
        {
            this->setEntityPtr(nullptr);
        }

};

};

#endif