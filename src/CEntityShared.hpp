#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "IEntityShared.hpp"
#include "CEntityAbs.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityShared :
    public CEntityAbs<TFields>,
    virtual public IEntityShared<TFields,ewConstPointer>
{
using TFieldsWrapper = TFields const *;

public:

    CEntityShared() = delete;
    CEntityShared(const CEntityShared &ref) = delete;
    CEntityShared &operator = (const CEntityShared &ref) = delete;
    CEntityShared(CEntityShared &&ref) = delete;
    CEntityShared &operator = (CEntityShared &&ref) = delete;

    CEntityShared(CEntityAbs<TFields> &ref) :
        CEntityAbs<TFields>(ref)
    {
    }

    CEntityShared(TFieldsWrapper fields,char *pData) :
        CEntityAbs<TFields>(fields,pData)
    {
    }

    CEntityShared(TFieldsWrapper fields) :
        CEntityAbs<TFields>(fields)
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
