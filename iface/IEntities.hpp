#ifndef IENTITIES_HPP
#define IENTITIES_HPP

#include "wrapper.hpp"
#include "CEntityFacade.hpp"

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

    virtual typename CEntityFacade<TFields>::Shared createEntity(TRowIndex rowPos) = 0;

    class ICursor
    {
        public:
            virtual ~ICursor() {};

            virtual ICursor &setRowPos(TRowIndex rowPos) = 0;
            virtual TRowIndex getRowPos() const noexcept = 0;

            virtual const typename CEntityFacade<TFields>::Shared &getEntity() const = 0;
            virtual typename CEntityFacade<TFields>::Shared &getEntity() = 0;

    };

};

};

#endif
