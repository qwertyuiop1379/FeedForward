#pragma once

namespace Memory
{
    class Codable
    {
        public:
            virtual ~Codable() = default;

            // Test class
            bool IsClass(const char *className) const;

            // Get class name
            virtual const char *Class() const = 0;

            // To/from dictionary
            virtual void FromDictionary(const Dictionary *data) = 0;
            virtual void ToDictionary(Dictionary *data) const = 0;
    };
}