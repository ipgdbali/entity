#ifndef ICUSTOM_TYPE_DYNAMIC_HPP
#define ICUSTOM_TYPE_DYNAMIC_HPP

namespace ipgdlib::entity
{

template <typename TSize>
class ICustomTypeDynamic :
    public ICustomType<TSize>
{

public:
    virtual bool assignFrom(void *pSrc) = 0;
    virtual bool assignTo(void *&pDest) = 0;

    virtual bool clear() = 0; // set to Null
    virtual bool isNull() const noexcept = 0;

    ICustomType<TSize>::eCustomTypeKind getKind() const noexcept override
    {
	return ectkDynamic;
    }
};

};

#endif
