#ifndef CENTITY_HPP
#define CENTITY_HPP

namespace ipgdlib::entity
{

template <typename FieldsT>
class CEntity
{
    public:
        using TFields           = FieldsT;
        using TFieldIndex       = typename TFields::TFieldIndex;
        using TFieldName        = typename TFields::TFieldName;

        /**
         * CEntity::Base
        */
        class Base
        {
            public:

                inline const TFields& getFields() const noexcept;

                bool copyAttrTo(TFieldIndex fieldIndex, void *pDst) const;
                bool copyAttrTo(TFieldName fieldName, void *pDst) const;

                bool copyAttrFrom(TFieldIndex fieldIndex, const void *pSrc);
                bool copyAttrFrom(TFieldName fieldName, const void *pSrc);

                template <typename T>
                const T& as(TFieldIndex fieldIndex) const;
                template <typename T>
                T& as(TFieldIndex fieldIndex);
                
                template <typename T>
                const T& as(TFieldName fieldName) const;
                template <typename T>
                T& as(TFieldName fieldName);

            protected:
                Base() = delete;
                Base(const Base& ref);                          //Copy Constructor
                Base(Base&& ref);                               //Move Constructor
                Base(const TFields& fields,void* pData);        //Constructor

                Base& operator = (const Base& ref);
                Base& operator = (Base&& ref);

                const char* getEntityAttrPtr(TFieldIndex fieldIndex) const;
                char* getEntityAttrPtr(TFieldIndex fieldIndex);

                const char* getEntityPtr() const; 
                char* getEntityPtr();

                void setEntityPtr(void* pEntityPtr);
                void set(const TFields& fields,char* pEntityPtr);

            private:
                const TFields*      m_Fields;
                char*               m_pEntityPtr;

        };

        /**
         * 
         *  CEntity::Unique
         * 
        */
        class Unique :
            public Base
        {
            public:
                virtual ~Unique();
                Unique() = delete;

                Unique(const Unique& ref) = delete;                 // Copy Constructor
                Unique(const Base &ref);                            // Copy Constructor

                Unique(Base &&ref) = delete;                        // Move Constructor
                Unique(Unique &&ref);                               // Move Constructor
                
                Unique(const TFields& fields);   

                Unique& operator = (const Unique& ref) = delete;    // Copy Operator
                Unique& operator = (const Base& ref);               // Copy Operator

                Unique& operator = (Base&& ref) = delete;           // Move Operator
                Unique& operator = (Unique&& ref);                  // Move Operator
                
        };

        /**
         * 
         *  CEntity::Shared
         * 
        */
        class Shared :
            public Base
        {
            public:
                Shared() = delete;

                Shared(const Shared& ref) = delete;                 // Copy Constructor
                Shared(const Base& ref);                            // Copy Constructor

                Shared(Base&&) = delete;                            // Move Constructor
                Shared(Shared&& ref);                               // Move Constructor

                Shared(const TFields& fields,void* pData);          // Constructor

                Shared& operator = (const Shared&) = delete;        // Copy Operator
                Shared& operator = (const Base& ref);               // Copy Operator

                Shared& operator = (Base &&) = delete;              // Move Operator
                Shared& operator = (Shared&& ref);                  // Move Operator

                // TODO : do not set public, let only Array can access
                using Base::setEntityPtr;

        };

        /**
         * 
         *  CEntity::Array Class
         * 
        */
        template <
            typename RowCountT
        >
        class Array
        {
            public:
                using TRowCount         = RowCountT;
                using TRowIndex         = RowCountT;

                ~Array();

                Array(const Array& ref) = delete;
                Array(Array&& ref) = delete;

                Array(const TFields &fields,TRowIndex entityCount);

                Array& operator = (const Array& ref) = delete;
                Array& operator = (Array& ref) = delete;

                const TFields &getFields() const;
                TRowCount count() const noexcept;

                /**
                 * 
                 * CEntity::Array::Cursor Class
                 * 
                */
                class Cursor
                {
                    public:
                        Cursor(const Array &array,TRowIndex iStart);
                        TRowIndex getRowPos() const noexcept;
                        Cursor& setRowPos(TRowIndex rowPos);
                        const Shared& getEntity() const;
                        Shared &getEntity();

                        const Shared& operator[](TRowIndex rowPos) const;
                        Shared& operator[](TRowIndex rowPos);

                    private:
                        const Array*    m_EntityArray;
                        TRowIndex       m_RowPos;
                        Shared         m_EntityShared;
                };
                Cursor createCursor(TRowIndex iStart = 0) const;

            private:
                const TFields*      m_Fields;
                TRowCount           m_EntityCount;
                char**              m_arrPEntityData;
        };

};

};

#endif
