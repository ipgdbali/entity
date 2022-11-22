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
         * CEntity::BaseEntity
        */
        class BaseEntity
        {
            public:

                inline const TFields& getFields() const noexcept;

                inline bool copyAttrTo(TFieldIndex fieldIndex, void *pDst) const;
                inline bool copyAttrTo(TFieldName fieldName, void *pDst) const;

                inline bool copyAttrFrom(TFieldIndex fieldIndex, const void *pSrc);
                inline bool copyAttrFrom(TFieldName fieldName, const void *pSrc);

                template <typename T>
                inline const T& attrAs(TFieldIndex fieldIndex) const;
                template <typename T>
                inline T& attrAs(TFieldIndex fieldIndex);
                
                template <typename T>
                inline const T& attrAs(TFieldName fieldName) const;
                template <typename T>
                inline T& attrAs(TFieldName fieldName);

            protected:
                BaseEntity() = delete;
                inline BaseEntity(const BaseEntity& ref);                          //Copy Constructor
                inline BaseEntity(BaseEntity&& ref);                               //Move Constructor
                inline BaseEntity(const TFields& fields,void* pData);              //Constructor

                inline BaseEntity& operator = (const BaseEntity& ref);
                inline BaseEntity& operator = (BaseEntity&& ref);

                inline const char* getEntityAttrPtr(TFieldIndex fieldIndex) const;
                inline char* getEntityAttrPtr(TFieldIndex fieldIndex);

                inline const char* getEntityPtr() const; 
                inline char* getEntityPtr();

                inline void setEntityPtr(void* pEntityPtr);
                inline void set(const TFields& fields,void* pEntityPtr);

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
            public BaseEntity
        {
            public:
                inline virtual ~Unique();
                Unique() = delete;

                Unique(const Unique& ref) = delete;                        // Copy Constructor
                inline Unique(const BaseEntity &ref);                      // Copy Constructor

                Unique(BaseEntity &&ref) = delete;                         // Move Constructor
                inline Unique(Unique &&ref);                               // Move Constructor
                
                inline Unique(const TFields& fields);   

                inline Unique& operator = (const Unique& ref) = delete;    // Copy Operator
                inline Unique& operator = (const BaseEntity& ref);         // Copy Operator

                inline Unique& operator = (BaseEntity&& ref) = delete;     // Move Operator
                inline Unique& operator = (Unique&& ref);                  // Move Operator
                
        };

        /**
         * 
         *  CEntity::Shared
         * 
        */
        class Shared :
            public BaseEntity
        {
            public:
                Shared() = delete;

                Shared(const Shared& ref) = delete;                         // deleted SharedCopy Constructor
                inline Shared(const BaseEntity& ref);                      // Copy Constructor from Parent

                Shared(BaseEntity&&) = delete;                              // deleted Move Constructor from Parent
                inline Shared(Shared&& ref);                               // Move Constructor

                inline Shared(const TFields& fields,void* pData);          // Constructor

                inline Shared& operator = (const Shared&) = delete;        // deleted Shared Copy Operator
                inline Shared& operator = (const BaseEntity& ref);         // Copy Operator

                inline Shared& operator = (BaseEntity &&) = delete;        // Move Operator
                inline Shared& operator = (Shared&& ref);                  // Move Operator

                // TODO : do not set public, let only Array access
                using BaseEntity::setEntityPtr;

        };

        template <
            typename RowCountT
        >
        class BaseEntities
        {
            public:
                using TRowCount         = RowCountT;
                using TRowIndex         = RowCountT;

                virtual ~BaseEntities();

                inline const TFields &getFields() const;

                virtual TRowCount count() const noexcept = 0;           // Count Entity that usable

                virtual TRowCount alloc(TRowCount count = 1) = 0;
                virtual TRowCount deAlloc(TRowCount count = 1) = 0;

                virtual bool remRow(TRowIndex idxRow) = 0;                    // Dealloc Specific Row and shift

                inline bool copyAttrTo(TRowIndex idxRow,TFieldIndex fieldIndex, void *pDst) const;
                inline bool copyAttrTo(TRowIndex idxRow,TFieldName fieldName, void *pDst) const;

                inline bool copyAttrFrom(TRowIndex idxRow,TFieldIndex fieldIndex, const void *pSrc);
                inline bool copyAttrFrom(TRowIndex idxRow,TFieldName fieldName, const void *pSrc);

                template <typename T>
                inline const T& attrAs(TRowIndex idxRow,TFieldIndex fieldIndex) const;
                template <typename T>
                inline T& attrAs(TRowIndex idxRow,TFieldIndex fieldIndex);

                template <typename T>
                inline const T& attrAs(TRowIndex idxRow,TFieldName fieldName) const;
                template <typename T>
                inline T& attrAs(TRowIndex idxRow,TFieldName fieldName);

                inline void swap(TRowIndex idxRowA,TRowIndex idxRowB);
                inline void rotate(TRowIndex idxFrom,TRowIndex idxTo);

                /**
                 * 
                 * CEntity::BaseEntities::Cursor Class
                 * 
                */
                class Cursor
                {
                    public:
                        inline Cursor(BaseEntities& entities,TRowIndex iStart = 0);

                        inline const BaseEntities& getEntities() const;
                        inline BaseEntities& getEntities();
                        
                        inline TRowIndex getRowPos() const noexcept;
                        inline Cursor& setRowPos(TRowIndex rowPos);
                        inline bool isRowPosValid() const noexcept;

                        inline const Shared& getEntity() const;
                        inline Shared& getEntity();

                    private:
                        BaseEntities*           m_Entities;
                        TRowIndex               m_RowPos;
                        Shared                  m_EntityShared;
                };
                inline Cursor createCursor(TRowIndex iStart = 0);


            protected:
                inline BaseEntities(const TFields& fields);
                virtual const char* getEntityPtr(TRowIndex index) const = 0;
                virtual char* getEntityPtr(TRowIndex index) = 0;
                
                virtual void setEntityPtr(TRowIndex index,char* entityPtr) = 0;

            private:
                const TFields*      m_Fields;
        };

        /**
         * 
         *  CEntity::Array Class
         * 
        */
        template <
            typename RowCountT = size_t
        >
        class Array :
            public BaseEntities<RowCountT>
        {
            public:
                using TRowCount         = RowCountT;
                using TRowIndex         = RowCountT;

                inline ~Array() override;
                Array()                                 = delete;
                Array(const Array& ref)                 = delete;
                Array(Array&& ref)                      = delete;
                Array& operator = (const Array& ref)    = delete;
                Array& operator = (Array& ref)          = delete;

                inline Array(const TFields& fields,TRowIndex reserved);

                inline TRowCount count() const noexcept override;
                inline TRowCount reserved() const noexcept;
                
                inline TRowCount alloc(TRowCount count) override;
                inline TRowCount deAlloc(TRowCount count) override;

                inline bool remRow(TRowIndex idxRow) override;                    // Dealloc Specific Row and rotate

            protected:
                inline const char* getEntityPtr(TRowIndex index) const override;
                inline char* getEntityPtr(TRowIndex index) override;
                inline void setEntityPtr(TRowIndex index,char* entityPtr) override;
                
            private:
                TRowCount           m_CountReserved;
                TRowCount           m_CountAlloc;
                char**              m_arrPEntityData;
        };

        /*
        class Vector :
            public BaseEntities<size_t>
        {
                inline ~Vector() override;
                Vector()                                    = delete;
                Vector(const Vector& ref)                   = delete;
                Vector(Vector&& ref)                        = delete;
                Vector& operator = (const Vector& ref)      = delete;
                Vector& operator = (Vector&& ref)           = delete;

                inline Vector(const TFields& fields);
                inline size_t count() const noexcept override;

            protected:
                inline const char* getEntityPtr(size_t index) const override;
                inline char* getEntityPtr(size_t index) override;
                inline void setEntityPtr(size_t index,char* entityPtr) override;

            private:
                std::vector<char*>       m_vEntityData;

        };
        */

};

};

#endif
