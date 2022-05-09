#ifndef ICUSTOM_TYPE_HPP
#define ICUSTOM_TYPE_HPP

namespace ipgdlib::entity
{

template <
    typename TSize
>
class ICustomType
{
public:
    virtual ~ICustomType() {};
    virtual bool set(TSize size,void *ptr) = 0;
};

};

#endif
