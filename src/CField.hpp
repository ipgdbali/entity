#ifndef CFIELD_HPP
#define CFIELD_HPP

#include "IField.hpp"
#include <utility>
#include <string>

namespace ipgdlib::entity
{

template <
    typename TSize
>
class CField :
    public IField<std::string,TSize,ewConstReference,ewConstReference>
{

public:

    using iface = IField<std::string,TSize,ewConstReference,ewConstReference>;

    CField() = delete;

    CField(const CField &ref) 
        : m_Name(ref.m_Name),m_Size(ref.m_Size)
    {
    }

    CField<TSize> &operator = (const CField &ref) = delete;

    CField(CField &&ref) 
        : m_Name(std::move(ref.m_Name)),m_Size(ref.m_Size)
    {
	    ref.m_Size = 0;
    }

    CField<TSize> &operator = (CField &&ref) = delete;

    CField(const std::string &name,const TSize &size)
        : m_Name(name),m_Size(size)
    {
    }

    CField(std::string &&name,const TSize &size)
        : m_Name(std::move(name)),m_Size(size)
    {
    }

    const std::string &name() const noexcept override
    {
	    return this->m_Name;
    }

    const TSize &size() const noexcept override
    {
	    return this->m_Size;
    }

private:
    const std::string m_Name;
    const TSize m_Size;

};


};

#endif
