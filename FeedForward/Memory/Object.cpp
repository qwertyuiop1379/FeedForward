#include "Object.hpp"

namespace Memory
{
    void Object::Retain()
    {
        this->referenceCount++;
    }

    void Object::Release()
    {
        if (--this->referenceCount == 0)
            delete this;
    }
}