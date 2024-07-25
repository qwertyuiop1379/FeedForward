#include "Dictionary.hpp"

namespace Memory
{
    static void AssertValidKey(const String *key, const char *methodName)
    {
        if (key == nullptr)
            throw Error::NullError("Dictionary", methodName, "key");
        if (key->Empty())
            throw Error::EmptyError("Dictionary", methodName, "key");
    }

    Dictionary::~Dictionary()
    {
        this->Clear();
    }

    void Dictionary::Copy(const Dictionary *other)
    {
        this->map = other->map;

        for (const auto &pair : this->map)
        {
            pair.first->Retain();
            pair.second->Retain();
        }
    }

    bool Dictionary::Contains(const char *key) const
    {
        String *str = new String(key);
        bool result = this->Contains(str);
        str->Release();

        return result;
    }

    bool Dictionary::Contains(const String *key) const
    {
        AssertValidKey(key, "Contains");

        for (const auto &pair : this->map)
        {
            if (pair.first->IsEqual(key))
                return true;
        }

        return false;
    }

    void Dictionary::SetObject(const char *key, Object *value)
    {
        String *str = new String(key);
        this->SetObject(str, value);
        str->Release();
    }

    void Dictionary::SetObject(String *key, Object *value)
    {
        AssertValidKey(key, "SetObject");

        if (value == nullptr)
            throw Error::NullError("Dictionary", "SetObject", "value");

        key->Retain();
        value->Retain();

        this->Remove(key);
        this->map.insert_or_assign(key, value);
    }

    Object *Dictionary::GetObject(const char *key) const
    {
        String *str = new String(key);
        Object *value = this->GetObject(str);
        str->Release();

        return value;
    }

    Object *Dictionary::GetObject(const String *key) const
    {
        Object *object = this->GetObjectIfPresent(key);

        if (object == nullptr)
            throw Error::Create("Dictionary", "GetObject", "Dictionary does not contain specified key '%s'.", key->GetCString());

        return object;
    }

    Object *Dictionary::GetObjectIfPresent(const char *key) const
    {
        String *str = new String(key);
        Object *value = this->GetObjectIfPresent(str);
        str->Release();

        return value;
    }

    Object *Dictionary::GetObjectIfPresent(const String *key) const
    {
        AssertValidKey(key, "GetObjectIfPresent");

        for (const auto &pair : this->map)
        {
            if (pair.first->IsEqual(key))
                return pair.second;
        }

        return nullptr;
    }

    void Dictionary::Remove(const char *key)
    {
        String *str = new String(key);
        this->Remove(str);
        str->Release();
    }

    void Dictionary::Remove(String *keyToRemove)
    {
        AssertValidKey(keyToRemove, "Remove");

        for (auto it = this->map.begin(); it != this->map.end(); it++)
        {
            String *key = it->first;

            if (key->IsEqual(keyToRemove))
            {
                it->second->Release();
                this->map.erase(key);
                key->Release();

                return;
            }
        }
    }

    void Dictionary::Clear()
    {
        for (const auto &pair : this->map)
        {
            pair.first->Release();
            pair.second->Release();
        }

        this->map.clear();
    }
}