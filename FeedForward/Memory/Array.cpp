#include "Array.hpp"

namespace Memory
{
    void Array::InitializeProperty(Property<Array> &property)
    {
        Array *array = new Array();
        property.Set(array);
        array->Release();
    }

    Array::~Array()
    {
        this->RemoveAllObjects();
    }

    void Array::Copy(const Array *other)
    {
        this->RemoveAllObjects();
        
        this->objects = other->objects;
        for (Object *object : this->objects)
            object->Retain();
    }

    Object *Array::ObjectAtIndex(size_t index) const
    {
        if (index >= this->objects.size())
            throw Error::IndexError("Array", "ObjectAtIndex", index, this->objects.size());
            
        return this->objects[index];
    }
    
    bool Array::Contains(Object *obj, size_t *index) const
    {
        size_t size = this->objects.size();
        
        for (size_t i = 0; i < size; i++)
        {
            if (this->objects[i] == obj)
            {
                if (index != nullptr)
                    *index = i;

                return true;
            }
        }

        return false;
    }

    void Array::AddObject(Object *obj)
    {
        if (this->Contains(obj))
            return;

        obj->Retain();
        this->objects.push_back(obj);
    }

    void Array::AddObjects(const Array *array)
    {
        size_t size = array->objects.size();
        for (size_t i = 0; i < size; i++)
            this->AddObject(array->objects[i]);
    }

    void Array::RemoveObjectAtIndex(size_t i)
    {
        if (i >= this->objects.size())
            throw Error::IndexError("Array", "RemoveObjectAtIndex", i, this->objects.size());

        this->objects[i]->Release();
        this->objects.erase(this->objects.begin() + i);
    }

    void Array::RemoveObject(Object *obj)
    {
        size_t size = this->objects.size();
        for (size_t i = 0; i < size; i++) {

            Object *test = this->objects[i];
            if (test == obj) {
                test->Release();
                this->objects.erase(this->objects.begin() + i);
                break;
            }
        }
    }

    void Array::RemoveAllObjects()
    {
        for (Object *obj : this->objects)
            obj->Release();

        objects.clear();
    }
}