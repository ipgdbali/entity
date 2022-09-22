#ifndef CFIELD_HPP
#define CFIELD_HPP

#include "IField.hpp"
#include <utility>
#include <type_traits>

namespace ipgdlib::entity
{

template <typename TName,typename TSize,bool isPointer>
class CField
{
};


template <typename TName,typename TSize>
class CFieldFactory
{
    public:
        using type_size = TSize;
        using type_name = TName;

        class CFieldAbs :
            public virtual IField<TName,TSize,ewConstReference,ewNoChange>
        {
        public:
            using iface = IField<TName,TSize,ewConstReference,ewNoChange>;

            const TName &name() const noexcept override
            {
                return this->m_Name;
            }

            CFieldAbs(const TName &name) :
                m_Name(name)
            {
            }

        private:
            TName m_Name;
        };

        template <bool isPointer>
        class CField : 
            public ipgdlib::entity::CField<TName,TSize,isPointer>
        {
            public:
                template <bool bPtr = isPointer,typename std::enable_if<bPtr,bool>::type = true>
                CField(const TName &name) :
                    ipgdlib::entity::CField<TName,TSize,true>(name)
                {
                }

                template <bool bPtr = isPointer,typename std::enable_if<!bPtr,bool>::type = true>
                CField(const TName &name,const TSize &size) : 
                    ipgdlib::entity::CField<TName,TSize,false>(name,size)
                {
                }

        };

        template <typename T,typename std::enable_if<std::is_pointer<T>::value,bool>::type = true>
        static CFieldAbs *alloc(const TName &name)
        {
            return new CField<true>(name);
        }

        template <typename T,typename std::enable_if<!std::is_pointer<T>::value,bool>::type = true>
        static CFieldAbs *alloc(const TName &name)
        {
            return new CField<false>(name,sizeof(T));
        }

        template <TSize size,typename std::enable_if<size == sizeof(void *),bool>::type = true>
        static CFieldAbs *alloc(const TName &name)
        {
            return new CField<true>(name);
        }

        template <TSize size,typename std::enable_if<size != sizeof(void *),bool>::type = true>
        static CFieldAbs *alloc(const TName &name)
        {
            return new CField<false>(name,size);
        }
};


template <typename TName,typename TSize>
class CField<TName,TSize,false> :
    public CFieldFactory<TName,TSize>::CFieldAbs
{
public:

    using iface         = IField<TName,TSize,ewConstReference,ewNoChange>;
    using parent        = typename CFieldFactory<TName,TSize>::CFieldAbs;

    CField()                                                    = delete;
    CField(const CField &ref)                                   = delete;
    CField<TName,TSize,false> &operator = (const CField &ref)   = delete;
    CField(CField &&ref)                                        = delete;
    CField<TName,TSize,false> &operator = (CField &&ref)        = delete;

    CField(const TName &name,const TSize &size) :
        CFieldFactory<TName,TSize>::CFieldAbs(name),m_Size(size)
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

template <typename TName,typename TSize>
class CField<TName,TSize,true> : 
    public CFieldFactory<TName,TSize>::CFieldAbs
{
public:
    using iface         = IField<TName,TSize,ewConstReference,ewConstReference>;
    using parent        = typename CFieldFactory<TName,TSize>::CFieldAbs;

    CField()                                        = delete;
    CField(const CField &ref)                       = delete;
    CField<TName,TSize,true> &operator = (const CField &ref)    = delete;
    CField(CField &&ref)                            = delete;
    CField<TName,TSize,true> &operator = (CField &&ref)         = delete;

    CField(const TName &name) :
        CFieldFactory<TName,TSize>::CFieldAbs(name)
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

};

#endif
