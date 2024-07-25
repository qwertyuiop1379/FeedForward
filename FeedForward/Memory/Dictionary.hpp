#pragma once

#include <map>

namespace Memory
{
    class Dictionary : public Object
    {
        private:
            std::map<String *, Object *> map;

        public:
            Dictionary() = default;
            ~Dictionary();

            // Copy
            void Copy(const Dictionary *other);

            // Check if dictionary contains a key
            bool Contains(const char *key) const;
            bool Contains(const String *key) const;

            // Assign entry
            void SetObject(const char *key, Object *value);
            void SetObject(String *key, Object *value);

            // Assign primitive entry
            template <typename T> void SetPrimitive(const char *key, const T &value)
            {
                String *str = new String(key);
                this->SetPrimitive(str, value);
                str->Release();
            }

            template <typename T> void SetPrimitive(String *key, const T &value)
            {
                Number *number = new Number(value);
                this->SetObject(key, number);
                number->Release();
            }

            // Retrieve entry
            Object *GetObject(const char *key) const;
            Object *GetObject(const String *key) const;

            Object *GetObjectIfPresent(const char *key) const;
            Object *GetObjectIfPresent(const String *key) const;

            template <class T> T *GetObject(const char *key) const
            {
                Object *object = this->GetObject(key);
                return static_cast<T *>(object);
            }

            template <class T> T *GetObject(const String *key) const
            {
                Object *object = this->GetObject(key);
                return static_cast<T *>(object);
            }

            template <class T> T *GetObjectIfPresent(const char *key) const
            {
                Object *object = this->GetObjectIfPresent(key);
                return static_cast<T *>(object);
            }

            template <class T> T *GetObjectIfPresent(const String *key) const
            {
                Object *object = this->GetObjectIfPresent(key);
                return static_cast<T *>(object);
            }

            // Retrieve primitive entry
            template <typename T> T GetPrimitive(const char *key) const
            {
                String *str = new String(key);
                T value = this->GetPrimitive<T>(str);
                str->Release();

                return value;
            }

            template <typename T> T GetPrimitive(const String *key) const
            {
                return this->GetObject<Number>(key)->GetValue<T>();
            }

            template <typename T> T GetPrimitiveIfPresent(const char *key, T fallback = 0) const
            {
                if (this->Contains(key))
                    return this->GetPrimitive<T>(key);
                return fallback;
            }

            template <typename T> T GetPrimitiveIfPresent(const String *key, T fallback = 0) const
            {
                if (this->Contains(key))
                    return this->GetPrimitive<T>(key);
                return fallback;
            }

            // Remove entry
            void Remove(const char *key);
            void Remove(String *keyToRemove);

            // Clear dictionary
            void Clear();
    };
}