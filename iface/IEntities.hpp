#ifndef IENTITIES_HPP
#define IENTITIES_HPP

#include "CEntity.hpp"

namespace ipgdlib::entity
{

template <
    typename TRowIndex,
    typename TFields,
    eWrapper ewFields
>
class IEntities
{
public:
    using type_row_index    = TRowIndex;
    using type_fields       = TFields;
    constexpr static eWrapper enum_wrapper_fields = ewFields;

    using TWFields          = typename ipgdlib::wrap<TFields,ewFields>::value;
    using TFieldName        = typename TFields::TFieldName;
    using TFieldIndex       = typename TFields::type_field_index;

    virtual ~IEntities() {};

    virtual TWFields getFields() const = 0;
    virtual TRowIndex count() const noexcept = 0;

    virtual bool copyAttrTo(TRowIndex rowPos,const TFieldIndex &fieldIndex,void *pDst) const = 0;
    virtual bool copyAttrTo(TRowIndex rowPos,const TFieldName &fieldName,void *pDst) const = 0;
    virtual bool copyAttrFrom(TRowIndex rowPos,const TFieldIndex &fieldIndex,const void *pSrc) = 0;
    virtual bool copyAttrFrom(TRowIndex rowPos,const TFieldName &fieldName,const void *pSrc) = 0;    

    class ICursor
    {
        public:
            virtual ~ICursor() {};

            virtual ICursor &setRowPos(TRowIndex rowPos) = 0;
            virtual TRowIndex getRowPos() const noexcept = 0;
    };

};

};

#endif
