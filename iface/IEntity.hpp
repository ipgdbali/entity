#ifndef IENTITY_HPP
#define IENTITY_HPP

#include "wrapper.hpp"
#include "IField.hpp"
#include "IFields.hpp"

namespace ipgdlib::entity
{

template <
    typename FieldsT,
    typename FieldNameT,
    typename FieldIndexT
>
class IEntity
{
    
    public:

        using TFields       = FieldsT;
        using TFieldName    = FieldNameT;
        using TFieldIndex   = FieldIndexT;
        
        virtual ~IEntity() {};

        virtual TFields getFields() const noexcept = 0;

        virtual bool copyAttrTo(TFieldIndex fieldIndex,void *pDst) const = 0;
        virtual bool copyAttrTo(TFieldName fieldName,void *pDst) const = 0;

        virtual bool copyAttrFrom(TFieldIndex fieldIndex,const void *pSrc) = 0;
        virtual bool copyAttrFrom(TFieldName fieldName,const void *pSrc) = 0;
        
        class IUnique {};
        class IShared {};
};

};

#endif
