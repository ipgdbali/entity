#ifndef ICUSTOM_TYPE_HPP
#define ICUSTOM_TYPE_HPP

namespace ipgdlib::entity
{

template <typename TSize>
class ICustomType
{
public:
    virtual ~ICustomType() {};

    virtual TSize getTypeSize() const = 0;
    virtual bool set(void *ptr) = 0;
};

};

#endif
