#include "String.hpp"

#include <stdlib.h>

namespace Memory
{
    // Constructor

    String::String()
    {
        this->Assign("");
    }

    // Destructor

    String::~String()
    {
        if (this->data != nullptr)
            free(this->data);
    };

    // Copy

    void String::Copy(const String *other)
    {
        this->Assign(other);
    }

    // Substring constructor

    String::String(const String *str, size_t startIndex)
    { this->Assign(str->data, startIndex, strlen(str->data)); }
    String::String(const String *str, size_t startIndex, size_t length)
    { this->Assign(str->data, startIndex, length); }
    String::String(const char *str, size_t startIndex)
    { this->Assign(str, startIndex, strlen(str)); }
    String::String(const char *str, size_t startIndex, size_t length)
    { this->Assign(str, startIndex, length); }

    // Length

    size_t String::GetLength() const
    { return strlen(this->data); }

    // Data access

    char * const String::GetCString() const
    { return this->data; }

    char &String::GetCharacter(size_t index)
    {
        size_t length = strlen(this->data);
        if (index >= length)
            throw Error::IndexError("String", "GetCharacter", index, length);

        return this->data[index];
    }

    // Assignment

    void String::Assign(const String *source, size_t startIndex)
    { this->Assign(source->data, startIndex, strlen(source->data)); }
    void String::Assign(const String *source, size_t startIndex, size_t length)
    { this->Assign(source->data, startIndex, length); }
    void String::Assign(const char *source, size_t startIndex)
    { this->Assign(source, startIndex, strlen(source)); }
    
    void String::Assign(const char *source, size_t startIndex, size_t length)
    {
        size_t sourceLength = strlen(source + startIndex);
        if (sourceLength > length)
            sourceLength = length;

        size_t dataSize = sourceLength + 1;
        if (this->data == nullptr)
            this->data = (char *)malloc(dataSize + 1);
        else
            this->data = (char *)realloc(this->data, dataSize + 1);

        memcpy(this->data, source + startIndex, dataSize);
        this->data[sourceLength] = '\0';
    }

    // Format assigment

    void String::AssignFormat(const char *format, ...)
    {
        int final_n, n = ((int)strlen(format)) * 2;
        std::unique_ptr<char[]> formatted;
        va_list ap;

        while (true)
        {
            formatted.reset(new char[n]);
            strcpy(&formatted[0], format);

            va_start(ap, format);
            final_n = vsnprintf(&formatted[0], n, format, ap);
            va_end(ap);

            if (final_n < 0 || final_n >= n)
                n += abs(final_n - n + 1);
            else
                break;
        }

        this->Assign(formatted.get());
    }

    // Evaluation

    bool String::Empty() const
    { return strlen(this->data) == 0; }

    bool String::IsEqual(const String *other) const
    {
        if (this == other)
            return true;
        return this->IsEqual(other->data);
    }

    bool String::IsEqual(const char *other) const
    {
        size_t length = strlen(this->data);
        if (length != strlen(other))
            return false;

        return memcmp(this->data, other, length) == 0;
    }

    int String::Compare(const String *other, size_t maxLength) const
    { return this->Compare(other->GetCString(), maxLength); }

    int String::Compare(const char *other, size_t maxLength) const
    {
        if (other == nullptr)
            throw Error::NullError("String", "Compare", "string");
        if (maxLength == 0)
            maxLength = strlen(this->data) + 1;
        return strncmp(this->data, other, maxLength);
    }

    bool String::StartsWith(const String *str) const
    { return this->Compare(str, strlen(str->data)) == 0; }

    bool String::StartsWith(const char *str) const
    { return this->Compare(str, strlen(str)) == 0; }

    bool String::EndsWith(const String *str) const
    { return this->EndsWith(str->GetCString()); }

    bool String::EndsWith(const char *str) const
    {
        if (str == nullptr)
            throw Error::NullError("String", "EndsWith", "string");

        size_t length = strlen(str);
        if (length == 0)
            throw Error::Create("String", "EndsWith", "Specified string is empty.");

        if (length >= strlen(this->data))
            return false;
            
        return strncmp(this->data + strlen(this->data) - length, str, length) == 0;
    }

    // String manipulation

    void String::Clear()
    { this->Assign(""); }

    void String::Append(char c)
    { this->Insert(&c, strlen(this->data), 1); }
    void String::Append(const String *str)
    { this->Insert(str->data, strlen(this->data), strlen(str->data)); }
    void String::Append(const char *str)
    { this->Insert(str, strlen(this->data), strlen(str)); }
    void String::Append(const String *str, size_t count)
    { this->Insert(str->data, strlen(this->data), count); }
    void String::Append(const char *str, size_t count)
    { this->Insert(str, strlen(this->data), count); }

    void String::AppendFormat(const char *format, ...)
    {
        int final_n, n = ((int)strlen(format)) * 2;
        std::unique_ptr<char[]> formatted;
        va_list ap;

        while (true)
        {
            formatted.reset(new char[n]);
            strcpy(&formatted[0], format);

            va_start(ap, format);
            final_n = vsnprintf(&formatted[0], n, format, ap);
            va_end(ap);

            if (final_n < 0 || final_n >= n)
                n += abs(final_n - n + 1);
            else
                break;
        }

        this->Append(formatted.get());
    }

    void String::Insert(const String *str, size_t index)
    { this->Insert(str->data, index, strlen(str->data)); }
    void String::Insert(const char *str, size_t index)
    { this->Insert(str, index, strlen(str)); }
    void String::Insert(const String *str, size_t index, size_t count)
    { this->Insert(str->data, index, count); }

    void String::Insert(const char *str, size_t index, size_t count)
    {
        size_t length = strlen(this->data);
        if (index > length)
            throw Error::IndexError("String", "Insert", index, length);

        length += count;

        char *buffer = (char *)malloc(length + count + 1);
        memcpy(buffer, this->data, index);
        memcpy(buffer + index, str, count);
        strcpy(buffer + index + count, this->data + index);
        
        this->Assign(buffer);
        free(buffer);
    }


    void String::ConvertToUppercaseString()
    {
        size_t length = this->GetLength();
        for (int i = 0; i < length; i++)
        {
            char &c = this->GetCharacter(i);
            if (c >= 'a' && c <= 'z')
                c -= 0x20;
        }
    }

    void String::ConvertToLowercaseString()
    {
        size_t length = this->GetLength();
        for (int i = 0; i < length; i++)
        {
            char &c = this->GetCharacter(i);
            if (c >= 'A' && c <= 'Z')
                c += 0x20;
        }
    }
}