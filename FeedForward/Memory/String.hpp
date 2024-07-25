#pragma once

using size_t = decltype(sizeof 1);

namespace Memory
{
    class String : public Object
    {
        private:
            char *data = nullptr;

        public:
            String();
            ~String();

            // Copy
            void Copy(const String *other);

            // Substring constructor
            explicit String(const String *string, size_t startIndex = 0);
            String(const String *string, size_t startIndex, size_t length);
            explicit String(const char *string, size_t startIndex = 0);
            String(const char *string, size_t startIndex, size_t length);

            // Length
            size_t GetLength() const;

            // Data access
            char &GetCharacter(size_t index);
            char * const GetCString() const;

            // Assignment
            void Assign(const String *source, size_t startIndex = 0);
            void Assign(const String *source, size_t startIndex, size_t length);
            void Assign(const char *source, size_t startIndex = 0);
            void Assign(const char *source, size_t startIndex, size_t length);

            // Format assignment
            void AssignFormat(const char *format, ...);

            // Evaluation
            bool Empty() const;
            bool IsEqual(const String *other) const;
            bool IsEqual(const char *other) const;
            int Compare(const String *other, size_t maxLength = 0) const;
            int Compare(const char *other, size_t maxLength = 0) const;
            bool StartsWith(const String *string) const;
            bool StartsWith(const char *string) const;
            bool EndsWith(const String *string) const;
            bool EndsWith(const char *string) const;

            // String manipulation
            void Clear();

            void Append(char c);
            void Append(const String *string);
            void Append(const char *string);
            void Append(const String *string, size_t count);
            void Append(const char *string, size_t count);
            void AppendFormat(const char *format, ...);
            
            void Insert(const String *string, size_t index);
            void Insert(const char *string, size_t index);
            void Insert(const String *string, size_t index, size_t count);
            void Insert(const char *string, size_t index, size_t count);

            void ConvertToUppercaseString();
            void ConvertToLowercaseString();
    };
}