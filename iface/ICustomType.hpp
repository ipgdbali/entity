#ifndef ICUSTOM_TYPE_HPP
#define ICUSTOM_TYPE_HPP

#include <string>

namespace ipgdlib::entity
{

template <typename TSize>
class ICustomType
{
public:
    enum eCustomTypeKind {ectkStatic,ectkDynamic};

    virtual ~ICustomType() {};
    virtual TSize getTypeSize() const = 0;

    virtual eCustomTypeKind getKind() const noexcept = 0;

    virtual void setPtr(void *pSrc) = 0;

};

};

#endif
