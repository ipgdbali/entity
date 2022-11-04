#ifndef CENTITY_BASE_HPP
#define CENTITY_BASE_HPP

#include "IEntity.hpp"
#include "CField.hpp"
#include "CFields.hpp"
#include "CEntity.hpp"
#include <cstring>


namespace ipgdlib::entity
{
/**
 * 
 * 
 * * Disabled *
 *   - Default Constructor
 *   - Copy Construction
 *   - Copy Operator
 *   - Move Operator
 * 
 * * Feature *
 *  - Memory Copy Operation for Entity Attribute. From / To and By Index or Name
 *  - Templated Casting Type for attribute
 *  - Move Construction
 *  - Store CField as Pointer but public interface as const reference. 
 * 
*/
template <typename FieldsT>
class CEntity<FieldsT>::Base :
    virtual public IEntity<const FieldsT&,typename FieldsT::iface::TFieldName,typename FieldsT::iface::TFieldIndex>
{
    public:

        using TFields           = FieldsT;
        using iface             = IEntity<const FieldsT&,typename FieldsT::iface::TFieldName,typename FieldsT::iface::TFieldIndex>;
        
        Base() = delete;
        
        typename iface::TFields getFields() const noexcept override
        {
            return *this->m_Fields;
        }

        bool copyAttrTo(typename iface::TFieldIndex fieldIndex, void *pDst) const override
        {
            return 
                std::memcpy(
                    pDst,
                    &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
                    this->m_Fields->getField(fieldIndex).size()) != nullptr;
        }

        bool copyAttrTo(typename iface::TFieldName fieldName, void *pDst) const override
        {
            return copyAttrTo(
                this->m_Fields->indexOf(fieldName),
                pDst);
        }

        bool copyAttrFrom(typename iface::TFieldIndex fieldIndex, const void *pSrc) override
        {
            std::memcpy(
                &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)],
                pSrc,
                this->m_Fields->getField(fieldIndex).size());
            return true;
        }

        bool copyAttrFrom(typename iface::TFieldName fieldName, const void *pSrc) override
        {
            return copyAttrFrom(
                this->m_Fields->indexOf(fieldName),
                pSrc);
        }

        template <typename T>
        T &as(typename iface::TFieldIndex fieldIndex)
        {
            return *reinterpret_cast<T *>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
        }

        template <typename T>
        T const &as(typename iface::TFieldIndex fieldIndex) const
        {
            return *reinterpret_cast<T *>(&this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)]);
        }

        template <typename T>
        T &as(typename iface::TFieldName fieldName)
        {
            return as<T>(this->m_Fields->indexOf(fieldName));
        }

        template <typename T>
        T const &as(typename iface::TFieldName fieldName) const
        {
            return as<T>(this->m_Fields->indexOf(fieldName));
        }

    protected:
    
        /**
         * Copy Constructor
        */
        Base(const Base &ref) :
            m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
        {
        }

        /**
         * Move Construction
        */
        Base(Base &&ref) :
            m_Fields(ref.m_Fields),m_pEntityPtr(ref.m_pEntityPtr)
        {
            ref.m_Fields        = nullptr;
            ref.m_pEntityPtr    = nullptr;
        }

        Base(typename  iface::TFields fields) :
            m_Fields(&fields),m_pEntityPtr(nullptr)
        {
        }

        // Unique Entity & CShared Entity
        Base(typename  iface::TFields fields,char *pData) : 
            m_Fields(&fields), m_pEntityPtr(pData)
        {
        }

        /**
         * Copy Operator
        */
        Base &operator = (const Base &ref) = delete;

        /**
         * Move Operator
        */
        Base &operator = (Base &&ref)
        {
            std::swap(this->m_Fields,ref.m_Fields);
            std::swap(this->m_pEntityPtr,ref.m_pEntityPtr);
            return *this;
        }

        const char *getEntityAttrPtr(typename iface::TFieldIndex fieldIndex) const
        {
            return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
        }

        char *getEntityAttrPtr(typename iface::TFieldIndex fieldIndex)
        {
            return &this->m_pEntityPtr[this->m_Fields->offset(fieldIndex)];
        }

        const char* getConstEntityPtr() const
        {
            return this->m_pEntityPtr;
        }

        char *getEntityPtr()
        {
            return this->m_pEntityPtr;
        }

        void setEntityPtr(void *pEntityPtr)
        {
            this->m_pEntityPtr = (char*)pEntityPtr;
        }

        void set(typename iface::TFieldIndex fields,char* pEntityPtr)
        {
            this->m_Fields      = fields;
            this->m_pEntityPtr  = pEntityPtr;
        }

    private:
        const TFields*      m_Fields;
        char*               m_pEntityPtr;

};


};



#endif