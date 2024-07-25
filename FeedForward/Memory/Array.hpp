#pragma once

#include <vector>

namespace Memory
{
    class Array : public Object
    {
        private:
            std::vector<Object *> objects;

        public:
            // Initialize property
            static void InitializeProperty(Property<Array> &property);

            // Constructor
            Array() = default;
            
            // Destructor
            ~Array();

            // Copy
            void Copy(const Array *other);

            // Size
            size_t Size() const { return this->objects.size(); }

            // Indexing
            Object *ObjectAtIndex(size_t index) const;
            
            template <class T> T *ObjectAtIndex(size_t index) const
            {
                Object *object = this->ObjectAtIndex(index);
                return static_cast<T *>(object);
            }

            // Check if array contains object
            bool Contains(Object *obj, size_t *index = nullptr) const;

            // Add objects
            void AddObject(Object *obj);
            void AddObjects(const Array *array);

            // Remove objects
            void RemoveObjectAtIndex(size_t i);
            void RemoveObject(Object *obj);
            void RemoveAllObjects();
    };
}