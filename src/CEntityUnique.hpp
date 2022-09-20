#ifndef CENTITY_UNIQUE_HPP
#define CENTITY_UNIQUE_HPP

#include "IEntityUnique.hpp"
#include "CEntityAbs.hpp"
#include "CFields.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityUnique :
    public CEntityAbs<TFields>,
    public virtual IEntityUnique<TFields,ewConstPointer>
{
using TFieldsWrapper = TFields const *;
public:

    virtual ~CEntityUnique()
    {
        if(this->getEntityPtr() != nullptr)
            delete []this->getEntityPtr();
    }

    CEntityUnique(TFields const &entityInfo) :
        CEntityAbs<TFields>(entityInfo,new char[entityInfo.size()])
    {
    }

};

};

#endif
