#ifndef CFIELD_HPP
#define CFIELD_HPP

#include "IField.hpp"
#include <utility>
#include <type_traits>

namespace ipgdlib::entity
{

template <
    typename TName,
    typename TSize
>
class CBaseField :
    public virtual IField<TName,TSize,ewConstReference,ewNoChange>
{
public:
    using iface = IField<TName,TSize,ewConstReference,ewNoChange>;

    const TName &name() const noexcept override
    {
	    return this->m_Name;
    }

    CBaseField(const TName &name) :
    	m_Name(name)
    {
    }

private:
    TName m_Name;
};

template <
    typename TName,
    typename TSize,
    bool bPointer
>
class CField
{
};

template <
    typename TName,
    typename TSize
>
class CField<TName,TSize,false> :
    public CBaseField<TName,TSize>
{
public:

    using iface = IField<TName,TSize,ewConstReference,ewNoChange>;

    CField() = delete;
    CField(const CField &ref) = delete;
    CField<TName,TSize,false> &operator = (const CField &ref) = delete;
    CField(CField &&ref) = delete;
    CField<TName,TSize,false> &operator = (CField &&ref) = delete;

    CField(const TName &name,const TSize &size) :
    	CBaseField<TName,TSize>(name),m_Size(size)
    {
    }

    TSize size() const noexcept override
    {
	    return this->m_Size;
    }

    bool isPointer() const noexcept override
    {
        return false;
    }

private:
    TSize   m_Size;

};

template <
    typename TName,
    typename TSize
>
class CField<TName,TSize,true> : 
    public CBaseField<TName,TSize>
{
public:
    using iface = IField<TName,TSize,ewConstReference,ewConstReference>;

    CField() = delete;
    CField(const CField &ref) = delete;
    CField<TName,TSize,true> &operator = (const CField &ref) = delete;
    CField(CField &&ref) = delete;
    CField<TName,TSize,true> &operator = (CField &&ref) = delete;

    CField(const TName &name) :
    	CBaseField<TName,TSize>(name)
    {
    }

    TSize size() const noexcept override
    {
	    return sizeof(void*);
    }

    bool isPointer() const noexcept override
    {
        return true;
    }

};

template <typename TName,typename TSize>
class CFieldFactory
{
    public:

        template <typename T,typename std::enable_if<std::is_pointer<T>::value,bool>::type = true>
        static CBaseField<TName,TSize> *alloc(const TName &name)
        {
            return new CField<TName,TSize,true>(name);
        }

        template <typename T,typename std::enable_if<!std::is_pointer<T>::value,bool>::type = true>
        static CBaseField<TName,TSize> *alloc(const TName &name)
        {
            return new CField<TName,TSize,false>(name,sizeof(T));
        }

        template <TSize size,typename std::enable_if<size == sizeof(void *),bool>::type = true>
        static CBaseField<TName,TSize> *alloc(const TName &name)
        {
            return new CField<TName,TSize,true>(name);
        }

        template <TSize size,typename std::enable_if<size != sizeof(void *),bool>::type = true>
        static CBaseField<TName,TSize> *alloc(const TName &name)
        {
            return new CField<TName,TSize,false>(name,size);
        }

};

};

#endif
