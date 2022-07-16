#ifndef CFIELD_INFO_HPP
#define CFIELD_INFO_HPP

#include "IFieldInfo.hpp"
#include <utility>

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class CFieldInfo :
    public IFieldInfo<TAttrName,TAttrSize>
{
public:

    using iface = IFieldInfo<TAttrName,TAttrSize>;

    template <typename T>
    static CFieldInfo<TAttrName,TAttrSize> create(TAttrName const &name)
    {
	return {name,sizeof(T)};
    }

    template <typename T>
    static CFieldInfo<TAttrName,TAttrSize> *alloc(TAttrName const &name)
    {
	return new CFieldInfo(name,sizeof(T));
    }

    CFieldInfo() = delete;

    CFieldInfo(const CFieldInfo &ref) :
	m_Name(ref.m_Name),m_Size(ref.m_Size)
    {
    }

    CFieldInfo<TAttrName,TAttrSize> &operator = (const CFieldInfo &ref)
    {
	this->m_Name = ref.m_Name;
	this->m_Size = ref.m_Size;
	return *this;
    }

    CFieldInfo(CFieldInfo &&ref) :
	m_Name(std::move(ref.m_Name)),m_Size(ref.m_Size)
    {
	ref.m_Size = 0;
    }

    CFieldInfo &operator = (CFieldInfo &&ref)
    {
	this->m_Name = std::move(ref.m_Name);
	this->m_Size = ref.m_Size;
	ref.m_Size = 0;
	return *this;
    }

    CFieldInfo(const TAttrName &name,const TAttrSize &size) :
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
