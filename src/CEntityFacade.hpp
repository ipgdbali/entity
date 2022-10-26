#ifndef CENTITY_FACADE_HPP
#define CENTITY_FACADE_HPP

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityFacade
{
    protected:
        // Base class for Unique and Shared
        class Base;

    public:
        class Unique;
        class Shared;

        class Array;
};



};

#endif
