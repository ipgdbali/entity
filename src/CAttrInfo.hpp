#ifndef CATTR_INFO_HPP
#define CATTR_INFO_HPP

#include "IAttrInfo.hpp"
#include <utility>

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class CAttrInfo :
    public IAttrInfo<TAttrName,TAttrSize>
{
public:

    using iface = IAttrInfo<TAttrName,TAttrSize>;

    template <typename T>
    static CAttrInfo<TAttrName,TAttrSize> create(TAttrName const &name)
    {
	return {name,sizeof(T)};
    }

    template <typename T>
    static CAttrInfo<TAttrName,TAttrSize> *alloc(TAttrName const &name)
    {
	return new CAttrInfo(name,sizeof(T));
    }

    CAttrInfo() = delete;

    CAttrInfo(const CAttrInfo &ref) :
	m_Name(ref.m_Name),m_Size(ref.m_Size)
    {
    }

    CAttrInfo<TAttrName,TAttrSize> &operator = (const CAttrInfo &ref)
    {
	this->m_Name = ref.m_Name;
	this->m_Size = ref.m_Size;
	return *this;
    }

    CAttrInfo(CAttrInfo &&ref) :
	m_Name(std::move(ref.m_Name)),m_Size(ref.m_Size)
    {
	ref.m_Size = 0;
    }

    CAttrInfo &operator = (CAttrInfo &&ref)
    {
	this->m_Name = std::move(ref.m_Name);
	this->m_Size = ref.m_Size;
	ref.m_Size = 0;
	return *this;
    }

    CAttrInfo(const TAttrName &name,const TAttrSize &size) :
	m_Name(name),m_Size(size)
    {
    }

    const TAttrSize &size() const noexcept
    {
	return this->m_Size;
    }

    const TAttrName &name() const noexcept
    {
	return this->m_Name;
    }

private:
    TAttrName m_Name;
    TAttrSize m_Size;

};


};

#endif
