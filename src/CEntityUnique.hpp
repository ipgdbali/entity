#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "IEntityUnique.hpp"
#include "CEntityAbs.hpp"
#include "CFields.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityUnique :
    public CEntityAbs<TFields>
{
using TFieldsWrapper = TFields const *;
public:

    virtual ~CEntityUnique()
    {
        if(this->getEntityPtr() != nullptr)
            delete []this->getEntityPtr();
    }

    CEntityUnique() = delete;
    CEntityUnique(const CEntityUnique &ref) = delete;
    CEntityUnique &operator = (const CEntityUnique &ref) = delete;
    CEntityUnique(CEntityUnique &&ref) = delete;
    CEntityUnique &operator = (CEntityUnique &&ref) = delete;


    CEntityUnique(TFieldsWrapper pEntityInfo) 
        : CEntityAbs<TFields>(pEntityInfo,new char[pEntityInfo->size()])
    {
    }

};

};

#endif
