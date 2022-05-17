#ifndef IENTITES_CURSOR_HPP
#define IENTITES_CURSOR_HPP

namespace ipgdlib::entity
{

template <typename TEntities,typename TEntitiesWrapper,typename TEntitiesShared>
class IEntitiesCursor
{
using TEntityCount = typename TEntities::iface::type_entity_count;

public:
    using type_entities = TEntities;
    using type_entities_wrapper = TEntitiesWrapper;
    using type_entities_shared = TEntitiesShared;
    using type_entity_count = TEntityCount;

    virtual ~IEntitiesCursor() {};
    virtual void createFrom(TEntitiesWrapper entities) = 0;

    virtual void setRowPosition(TEntityCount rowPos) = 0;
    virtual TEntityCount getRowPosition() const noexcept = 0;

    virtual TEntitiesShared &getActiveRow() = 0;

};

};

#endif
