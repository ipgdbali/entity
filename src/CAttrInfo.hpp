#ifndef CATTR_INFO_HPP
#define CATTR_INFO_HPP

#include "IAttrInfo.hpp"

namespace ipgdlib::entity
{

template <
    typename TAttrSize,
    typename TAttrName
>
class CAttrInfo :
    public IAttrInfo<TAttrSize,TAttrName>
{
public:
    CAttrInfo(TAttrSize const &size,TAttrName const &name) :
	m_Size(size),m_Name(name)
    {
    }

    TAttrSize const &getSize() const noexcept
    {
	return this->m_Size;
    }

    TAttrName const &getName() const noexcept
    {
	return this->m_Name;
    }

private:
    TAttrSize const m_Size;
    TAttrName const m_Name;

};

};

#endif
