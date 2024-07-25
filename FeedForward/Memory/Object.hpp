#pragma once

namespace Memory
{
    class Object
    {
        private:
            unsigned int referenceCount;

        public:
            // Constructor
            Object() : referenceCount(1) {}

            // Destructor
            virtual ~Object() = default;

            // Disable moving/copying/assigning
            Object(const Object &) = delete;
            Object(Object &&) = delete;
            void operator=(const Object &) = delete;

            // Reference counting
            void Retain();
            void Release();
    };
}