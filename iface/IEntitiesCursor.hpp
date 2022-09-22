#ifndef IENTITES_CURSOR_HPP
#define IENTITES_CURSOR_HPP

namespace ipgdlib::entity
{

template <typename TFields>
class CEntityShared;

template <
    typename TEntities,
    eWrapper ewEntities,
    typename TEntityShared>
class IEntitiesCursor
{
using TCount	= typename TEntities::iface::type_count;
using TEntitiesWrapper	= typename ipgdlib::wrap<TEntities,ewEntities>::value;

public:
    using type_entities = TEntities;
    static constexpr eWrapper enum_wrapper_entities = ewEntities;
    using type_entity_shared = TEntityShared;

    virtual ~IEntitiesCursor() {};

    virtual void setRowPos(TCount rowPos) = 0;
    virtual TCount getRowPos() const noexcept = 0;

    virtual CEntityShared<TFields> &getEntity() = 0;

};

};

#endif
