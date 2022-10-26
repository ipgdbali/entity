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

    CField<TSize> &operator = (const CField &ref)
    {
        this->m_Name = ref.m_Name;
        this->m_Size = ref.m_Size;
    }

    CField(CField &&ref) 
        : m_Name(std::move(ref.m_Name)),m_Size(ref.m_Size)
    {
	    ref.m_Size = 0;
    }

    CField<TSize> &operator = (CField &&ref)
    {
        std::swap(this->m_Name,ref.m_Name);
        std::swap(this->m_Size,ref.m_Size);
    }

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
    std::string m_Name;
    TSize m_Size;

};


};

#endif
