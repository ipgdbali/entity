#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "IEntityShared.hpp"
#include "CEntityAbs.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityShared :
    public CEntityAbs<TFields>,
    public virtual IEntityShared<TFields,ewConstPointer>
{
using TFieldsWrapper = TFields const *;

public:

    CEntityShared(const TFields& fields) :
        CEntityAbs<TFields>(fields,nullptr)
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
