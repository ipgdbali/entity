#ifndef CENTITY_ARRAY_CURSOR_HPP
#define CENTITY_ARRAY_CURSOR_HPP

#include "CEntityArray.hpp"

namespace ipgdlib::entity
{

template <typename TFields>
template <typename TRowIndex>
class CEntityFacade<TFields>::Array<TRowIndex>::Cursor :
    virtual public IEntities<TRowIndex,TFields,CEntityFacade<TFields>::Array<TRowIndex>::iface::enum_wrapper_fields>::ICursor
{

    public:

        Cursor(Array& eArray)
            : m_EntityArray(eArray),m_RowPos(0),m_EntityShared(eArray.getFields(),eArray.m_arrPEntityData[0])
        {
        }

        Cursor &setRowPos(TRowIndex rowPos) override
        {
            this->m_RowPos = rowPos;
            this->m_EntityShared.setEntityPtr(this->m_EntityArray.m_arrPEntityData[rowPos]);
            return *this;
        }

        TRowIndex getRowPos() const noexcept override
        {
            return this->m_RowPos;
        }

        const typename CEntityFacade<TFields>::Shared &getEntity() const override
        {
            return this->m_EntityShared;
        }

        typename CEntityFacade<TFields>::Shared &getEntity() override
        {
            return this->m_EntityShared;
        }

    protected:

    private:
        Array &m_EntityArray;
        TRowIndex m_RowPos;
        typename CEntityFacade<TFields>::Shared m_EntityShared;

};

};

#endif