#ifndef CFIELD_HPP
#define CFIELD_HPP

#include "IField.hpp"
#include <string>
#include <utility>


namespace ipgdlib::entity
{

template <
    typename FieldSizeT
>
class CField :
    public IField<const std::string&,FieldSizeT>
{

public:

    using iface         = IField<const std::string&,FieldSizeT>;

    using TFieldSize    = FieldSizeT;
    using TFieldName    = std::string;
    
    CField() = delete;

    /**
     * Copy Constructor
    */
    CField(const CField<TFieldSize> &ref) 
        : m_Name(ref.m_Name),m_Size(ref.m_Size)
    {
    }

    /**
     * Copy Operator
    */
    CField<TFieldSize> &operator = (const CField<TFieldSize> &ref)
    {
        this->m_Name = ref.m_Name;
        this->m_Size = ref.m_Size;

        return *this;
    }

    /**
     * Move Constructor
    */
    CField(CField<TFieldSize> &&ref) 
    {
        std::swap(this->m_Name,ref.m_Name);
        std::swap(this->m_Size,ref.m_Size);
    }

    /**
     * Move Operator
    */
    CField<TFieldSize> &operator = (CField<TFieldSize> &&ref)
    {
        std::swap(this->m_Name,ref.m_Name);
        std::swap(this->m_Size,ref.m_Size);

        return *this;
    }

    /**
     * Raw Constructor
    */
    CField(typename iface::TFieldName name,typename iface::TFieldSize size = sizeof(void*))
        : m_Name(name),m_Size(size)
    {
    }

    /**
     * Raw Move Constructor
    */
    CField(std::string &&name,TFieldSize &&size)
        : m_Name(std::move(name)),m_Size(size)
    {
        size = 0;
    }

    typename iface::TFieldName name() const noexcept override
    {
	    return this->m_Name;
    }

    typename iface::TFieldSize size() const noexcept override
    {
	    return this->m_Size;
    }

private:
    TFieldName      m_Name;
    TFieldSize      m_Size;
};

};

#endif
