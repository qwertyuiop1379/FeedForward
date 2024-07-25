#pragma once

namespace Memory
{
    template<typename T>
    class Property
    {
        private:
            T *obj = nullptr;

        public:
            // Constructor
            Property() = default;

            // Destructor
            ~Property()
            {
                if (obj != nullptr)
                    obj->Release();
            }

            // Get/set
            inline T *Get() const { return this->obj; }
            void Set(T *newObj)
            {
                if (this->obj != nullptr)
                    this->obj->Release();

                if (newObj != nullptr)
                    newObj->Retain();

                this->obj = newObj;
            }

            // Operator overrides
            inline operator T *() const { return this->obj; }
            inline T *operator->() const { return this->obj; }
            inline T *operator=(T *newObj) { this->Set(newObj); return this->obj; }
    };
}