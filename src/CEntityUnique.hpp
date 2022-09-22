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

public:
    using parent    = CEntityAbs<TFields>;
    using TWFields  = typename parent::TWFields;

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


    CEntityUnique(TWFields fields) 
        : CEntityAbs<TFields>(fields,new char[fields.size()])
    {
    }

};

};

#endif
