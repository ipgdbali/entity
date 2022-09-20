#ifndef CENTITY_SHARED_HPP
#define CENTITY_SHARED_HPP

#include "IEntityShared.hpp"
#include "CEntityAbs.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityShared :
    public CEntityAbs<TFields>
{
using TFieldsWrapper = TFields const *;

public:

    CEntityShared(CEntityAbs<TFields> &ref) :
        CEntityAbs<TFields>(ref)
    {
    }

};


};

#endif
