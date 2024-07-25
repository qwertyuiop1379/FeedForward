#include "Codable.hpp"

#include <cstring>

namespace Memory
{
    bool Codable::IsClass(const char *className) const
    {
        return strcmp(this->Class(), className) == 0;
    }
}