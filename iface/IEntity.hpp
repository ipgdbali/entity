#ifndef IENTITY_HPP
#define IENTITY_HPP

#include "wrapper.hpp"
#include "IField.hpp"
#include "IFields.hpp"
#include "ICustomType.hpp"

namespace ipgdlib::entity
{

template <
    typename TFields,
    eWrapper ewFields
>
class IEntity
{
    
    public:
        using type_fields = TFields;
        constexpr static eWrapper enum_wrapper_fields = ewFields;

        using TFieldIndex				= typename TFields::iface::type_count;
        using TFieldName				= typename TFields::iface::type_field::type_name;
        using TFieldSize				= typename TFields::iface::type_field::type_size;
        using TWFields				    = typename ipgdlib::wrap<TFields,ewFields>::value;

        virtual ~IEntity() {};

        virtual TWFields getFields() const noexcept = 0;

        virtual bool copyAttrTo(const TFieldIndex &fieldIndex,void *pDst) const = 0;
        virtual bool copyAttrTo(const TFieldName &fieldName,void *pDst) const = 0;

        virtual bool copyAttrFrom(const TFieldIndex &fieldIndex,const void *pSrc) = 0;
        virtual bool copyAttrFrom(const TFieldName &fieldName,const void *pSrc) = 0;
        
        /*
        CCustomTypeBase<8> toCustomType(const TFieldIndex &fieldIndex)
        {
            return {this-> getPtr()}
        }
        

        virtual bool toCustomType(TFieldIndex const &fieldIndex, ICustomType<TFieldSize> &ref) = 0;
        virtual bool toCustomType(TFieldName const &fieldName, ICustomType<TFieldSize> &ref) = 0;
        */

        class IUnique;
        class IShared;
};


template <
    typename TFields,
    eWrapper ewFields
>
class IEntity<TFields,ewFields>::IUnique :
    public virtual IEntity<TFields,ewFields>
{

};

template <
    typename TFields,
    eWrapper ewFields
>
class IEntity<TFields,ewFields>::IShared : 
    public virtual IEntity<TFields,ewFields>
{
    virtual void set(void *pSrc) = 0;
    virtual bool isNull() const noexcept = 0;
    virtual void clear() noexcept = 0;
};


};

#endif
