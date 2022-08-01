#ifndef IENTITES_CURSOR_HPP
#define IENTITES_CURSOR_HPP

namespace ipgdlib::entity
{

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
    virtual void createFrom(TEntitiesWrapper entities) = 0;

    virtual void setActivePosition(TCount rowPos) = 0;
    virtual TCount getActivePosition() const noexcept = 0;

    virtual TEntityShared &getActiveEntity() = 0;

};

};

#endif
