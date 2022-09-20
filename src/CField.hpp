#ifndef CFIELD_HPP
#define CFIELD_HPP

#include "IField.hpp"
#include <utility>

namespace ipgdlib::entity
{

template <
    typename TName,
    typename TSize
>
class CField :
    public IField<TName,TSize,ewConstReference,ewConstReference>
{
public:

    using iface = IField<TName,TSize,ewConstReference,ewConstReference>;

    template <typename T>
    static CField<TName,TSize> create(TName const &name)
    {
	    return {name,sizeof(T)};
    }

    template <typename T>
    static CField<TName,TSize> *alloc(TName const &name)
    {
	    return new CField(name,sizeof(T));
    }

    template <TSize size>
    static CField<TName,TSize> *alloc(TName const &name)
    {
	    return new CField(name,size);
    }

    CField() = delete;
    CField(const CField &ref) = delete;
    CField<TName,TSize> &operator = (const CField &ref) = delete;
    CField(CField &&ref) = delete;
    CField &operator = (CField &&ref) = delete;

    CField(const TName &name,const TSize &size) :
    	m_Name(name),m_Size(size)
    {
    }

    const TName &name() const noexcept override
    {
	    return this->m_Name;
    }

    const TSize &size() const noexcept override
    {
	    return this->m_Size;
    }

private:
    TName m_Name;
    TSize m_Size;

};


};

#endif
