#ifndef CENTITIES_HPP
#define CENTITIES_HPP

#include "IEntities.hpp"
#include "CEntityShared.hpp"

namespace ipgdlib::entity
{

template <typename TCount, typename TFields>
class CEntities : public IEntities<TCount, TFields, ewConstPointer>
{
    using TWFields = TFields const *;

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

    CEntities(TWFields entityInfo, TCount entityCount) 
        : m_pFields(entityInfo), m_EntityCount(entityCount)
    {
        this->m_arrPEntityData = new char *[m_EntityCount];
        for (TCount li = 0; li < m_EntityCount; li++)
            m_arrPEntityData[li] = new char[m_pFields->size()];
    }

    TWFields getFields() const override
    {
        return this->m_pFields;
    }

    TCount count() const noexcept override
    {
        return this->m_EntityCount;
    }

    CEntityShared<TFields> getEntity(TCount rowPos) override
    {
        return {this->m_pFields,this->m_arrPEntityData[rowPos]}
    }

    class CEntitiesCursor :
        public virtual IEntitiesCursor
    {
        public:
            CEntitiesCursor(CEntities & entities)
                : m_arrPEntityDaya(entities.m_arrPEntityData),m_RowPos(0),m_EntityShared(m_pFields,m_arrPEntityData[0])
            {
            }

            void setRowPos(TCount rowPos) override
            {
                this->m_RowPos = rowPos;
                this->m_EntityShared.set(m_pArrPEntityDaya[rowPos]);
            }

            TCount getRowPos() const noexcept override
            {
                return this->m_RowPos;
            }

            CEntityShared<TFields> &getEntity() override
            {
                return this->m_EntityShared;
            }

        protected:
        private:
            char **m_pArrPEntityDaya
            TCount m_RowPos;
            CEntityShared m_EntityShared;
    }

protected:
private:
    TWFields m_pFields;
    TCount m_EntityCount;
    char **m_arrPEntityData;
};

};

#endif
