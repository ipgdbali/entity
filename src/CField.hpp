#ifndef CFIELD_HPP
#define CFIELD_HPP

#include "IField.hpp"
#include <utility>

namespace ipgdlib::entity
{

template <
    typename TAttrName,
    typename TAttrSize
>
class CField :
    public IField<TAttrName,TAttrSize>
{
public:

    using iface = IField<TAttrName,TAttrSize>;

    template <typename T>
    static CField<TAttrName,TAttrSize> create(TAttrName const &name)
    {
	return {name,sizeof(T)};
    }

    template <typename T>
    static CField<TAttrName,TAttrSize> *alloc(TAttrName const &name)
    {
	return new CField(name,sizeof(T));
    }

    CField() = delete;

    CField(const CField &ref) :
	m_Name(ref.m_Name),m_Size(ref.m_Size)
    {
    }

    CField<TAttrName,TAttrSize> &operator = (const CField &ref)
    {
	this->m_Name = ref.m_Name;
	this->m_Size = ref.m_Size;
	return *this;
    }

    CField(CField &&ref) :
	m_Name(std::move(ref.m_Name)),m_Size(ref.m_Size)
    {
	ref.m_Size = 0;
    }

    CField &operator = (CField &&ref)
    {
	this->m_Name = std::move(ref.m_Name);
	this->m_Size = ref.m_Size;
	ref.m_Size = 0;
	return *this;
    }

    CField(const TAttrName &name,const TAttrSize &size) :
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
