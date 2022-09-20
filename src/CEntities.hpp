#ifndef CENTITIES_HPP
#define CENTITIES_HPP

#include "IEntities.hpp"
#include "CEntityShared.hpp"

namespace ipgdlib::entity
{

template <typename TCount, typename TFields>
class CEntities : public IEntities<TCount, TFields, ewConstPointer>
{
    using TFieldsWrapper = TFields const *;

public:
    using iface = IEntities<TCount, TFields, ewConstPointer>;

    virtual ~CEntities()
    {
        if (this->m_arrPEntityData != nullptr)
        {
            delete[] m_arrPEntityData;
            this->m_arrPEntityData = nullptr;
        }
    }

    CEntities(TFieldsWrapper entityInfo, TCount entityCount) : m_pFields(entityInfo), m_EntityCount(entityCount)
    {
        this->m_arrPEntityData = new char *[m_EntityCount];
        for (TCount li = 0; li < m_EntityCount; li++)
            m_arrPEntityData[li] = new char[m_pFields->size()];
    }

    TFieldsWrapper getFields() const override
    {
        return this->m_pFields;
    }

    TCount count() const noexcept override
    {
        return this->m_EntityCount;
    }

    void *getPData(TCount rowPos) override
    {
        return this->m_arrPEntityData[rowPos];
    }

    void shareTo(TCount rowPos,IEntityShared<TFields, ewConstPointer> &eShared) const override
    {
        eShared.set(m_arrPEntityData[rowPos]);
    }

protected:
private:
    TFieldsWrapper m_pFields;
    TCount m_EntityCount;
    char **m_arrPEntityData;
};

};

#endif
