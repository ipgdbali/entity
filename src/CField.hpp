#ifndef CFIELD_HPP
#define CFIELD_HPP

#include "IField.hpp"
#include <utility>

namespace ipgdlib::entity
{

template <
    typename TFieldName,
    typename TFieldSize
>
class CField :
    public IField<TFieldName,TFieldSize>
{
public:

    using iface = IField<TFieldName,TFieldSize>;

    template <typename T>
    static CField<TFieldName,TFieldSize> create(TFieldName const &name)
    {
	return {name,sizeof(T)};
    }

    template <typename T>
    static CField<TFieldName,TFieldSize> *alloc(TFieldName const &name)
    {
	return new CField(name,sizeof(T));
    }

    CField() = delete;

    CField(const CField &ref) :
	m_Name(ref.m_Name),m_Size(ref.m_Size)
    {
    }

    CField<TFieldName,TFieldSize> &operator = (const CField &ref)
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

    CField(const TFieldName &name,const TFieldSize &size) :
	m_Name(name),m_Size(size)
    {
    }

    const TFieldSize &size() const noexcept
    {
	return this->m_Size;
    }

    const TFieldName &name() const noexcept
    {
	return this->m_Name;
    }

private:
    TFieldName m_Name;
    TFieldSize m_Size;

};


};

#endif
