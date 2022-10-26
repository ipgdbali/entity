#ifndef CABSCUSTOMTYPE_HPP
#define CABSCUSTOMTYPE_HPP

#include "ICustomType.hpp"
#include "CEntityFacade.hpp"

namespace ipgdlib::entity
{

template <typename TSize>
class CAbsCustomType :
    virtual public ICustomType<TSize>
{

public:

protected:
    virtual void setPtr(void* ptr) override
    {
        this->_setPtr(ptr);
    }

    virtual void _setPtr(void *ptr) = 0;

    template <typename TFields>
    friend class CEntityFacade<TFields>::Base;
};

};

#endif