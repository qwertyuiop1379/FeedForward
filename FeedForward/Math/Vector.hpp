#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>

#define __VEC_FOREACH(i) for (size_t i = 0; i < this->size; i++)

namespace Math
{
    template <typename Type> class Vector
    {
        private:

        // Vector size

        size_t size = 0;

        public:

        // Vector elements
        
        Type *data = nullptr;

        // Constructors

        explicit Vector(size_t size)
        { this->Resize(size); };

        Vector(size_t size, Type value)
        { this->Resize(size); this->Assign(value); }

        Vector(size_t size, const Type *values)
        { this->Resize(size); this->Assign(values); }
        Vector(const std::vector<Type> &values)
        { this->Assign(values); }

        // Destructor

        ~Vector()
        {
            if (this->data != nullptr)
                delete[] this->data;
        }

        // Size 

        size_t Size() const { return this->size; }

        void Resize(size_t size)
        {
            if (size == 0)
                throw Error::Create("Vector", "Reize", "Vector size may not be 0.");

            if (this->size == size)
                return;

            if (this->data != nullptr)
                delete[] this->data;

            this->size = size;
            this->data = new Type[size];
        }

        // Assignment

        void Assign(Type value)
        { __VEC_FOREACH(i) this->data[i] = value; }

        void Assign(const Vector<Type> &vec)
        {
            this->Resize(vec.size);
            std::memcpy(this->data, vec.data, sizeof(Type) * vec.size);
        }

        void Assign(const Type *values)
        { std::memcpy(this->data, values, sizeof(Type) * this->size); }

        void Assign(const std::vector<Type> &values)
        {
            this->Resize(values.size());
            std::memcpy(this->data, &values[0], sizeof(Type) * this->size);
        }

        // Copy constructor/assignment operator

        Vector(const Vector<Type> &vec)
        { this->Assign(vec); }

        Vector<Type> &operator=(const Vector<Type> &vec)
        { this->Assign(vec); }

        // Move constructor/assignment operator

        Vector(Vector<Type> &&vec) : size(vec.size), data(vec.data)
        { vec.data = nullptr; }

        Vector<Type> &operator=(Vector<Type> &&vec)
        {
            if (this->data != nullptr)
                delete[] this->data;

            this->size = vec.size;
            this->data = vec.data;

            vec.size = 0;
            vec.data = nullptr;
            
            return *this;
        }

        // Indexing

        Type &At(size_t index)
        {
            if (index >= this->size)
                throw Error::IndexError("Vector", "At", index, this->size);
            return this->data[index];
        }

        const Type &At(size_t index) const
        {
            if (index >= this->size)
                throw Error::IndexError("Vector", "At", index, this->size);
            return this->data[index];
        }

        // Index operator

        inline Type &operator[](size_t index) { return this->data[index]; }
        inline const Type &operator[](size_t index) const { return this->data[index]; }

        // Range-based iteration

        Type *begin()
        { return this->data; }
        Type *end()
        { return this->data + this->size; }

        const Type *begin() const
        { return this->data; }
        const Type *end() const
        { return this->data + this->size; }

        // Vector properties

        Type Sum() const
        {
            Type sum = 0;
            __VEC_FOREACH(i) sum += this->data[i];
            return sum;
        }

        double Magnitude() const
        {
            Type sum = 0;

            __VEC_FOREACH(i)
            {
                const Type &element = this->data[i];
                sum += element * element;
            }

            return sqrt(sum);
        }

        double Distance(const Vector<Type> &vec) const
        {
            Type sum = 0;

            __VEC_FOREACH(i)
            {
                Type delta = this->data[i] - vec->data[i];
                sum += delta * delta;
            }

            return sqrt(sum);
        }

        Type Dot(const Vector<Type> &vec) const
        {
            Type product = 0;
            __VEC_FOREACH(i) product += this->data[i] * vec.data[i];
            return product;
        }

        // Normalization

        Vector<Type> Normalize() const
        { return this->Scale(1 / this->Magnitude()); }

        void NormalizeInPlace()
        { this->ScaleInPlace(1 / this->Magnitude()); }

        // Scalar arithmetic

        Vector<Type> Add(Type scalar) const
        {
            Vector<Type> vec(this->size, this->data);
            __VEC_FOREACH(i) vec.data[i] += scalar;
            return vec;
        }

        Vector<Type> Subtract(Type scalar) const
        {
            Vector<Type> vec(this->size, this->data);
            __VEC_FOREACH(i) vec.data[i] -= scalar;
            return vec;
        }

        Vector<Type> Scale(Type scalar) const
        {
            Vector<Type> vec(this->size, this->data);
            __VEC_FOREACH(i) vec.data[i] *= scalar;
            return vec;
        }

        // In-place scalar arithmetic

        void AddInPlace(Type scalar)
        { __VEC_FOREACH(i) this->data[i] += scalar; }

        void SubtractInPlace(Type scalar)
        { __VEC_FOREACH(i) this->data[i] -= scalar; }

        void ScaleInPlace(Type scalar)
        { __VEC_FOREACH(i) this->data[i] *= scalar; }

        // Vector arithmetic

        Vector<Type> Add(const Vector<Type> &vec) const
        {
            Vector<Type> newVec(this->size, this->data);
            __VEC_FOREACH(i) newVec.data[i] += vec.data[i];
            return newVec;
        }

        Vector<Type> Subtract(const Vector<Type> &vec) const
        {
            Vector<Type> newVec(this->size, this->data);
            __VEC_FOREACH(i) newVec.data[i] -= vec.data[i];
            return newVec;
        }

        Vector<Type> Multiply(const Vector<Type> &vec) const
        {
            Vector<Type> newVec(this->size, this->data);
            __VEC_FOREACH(i) newVec.data[i] *= vec.data[i];
            return newVec;
        }

        // In-place vector arithmetic

        void AddInPlace(const Vector<Type> &vec)
        { __VEC_FOREACH(i) this->data[i] += vec.data[i]; }

        void SubtractInPlace(const Vector<Type> &vec)
        { __VEC_FOREACH(i) this->data[i] -= vec.data[i]; }

        void MultiplyInPlace(const Vector<Type> &vec)
        { __VEC_FOREACH(i) this->data[i] *= vec.data[i]; }

        // Scalar arithmetic operators

        inline Vector<Type> operator+(Type s) const { return Add(s); }
        inline Vector<Type> operator-(Type s) const { return Subtract(s); }
        inline Vector<Type> operator*(Type s) const { return Scale(s); }
        inline Vector<Type> operator/(Type s) const { return Scale(1 / s); }

        inline void operator+=(Type s) { this->AddInPlace(s); }
        inline void operator-=(Type s) { this->SubtractInPlace(s); }
        inline void operator*=(Type s) { this->ScaleInPlace(s); }
        inline void operator/=(Type s) { this->ScaleInPlace(1 / s); }

        // Vector arithmetic operators

        inline Vector<Type> operator+(const Vector<Type> &vec) const { return Add(vec); }
        inline Vector<Type> operator-(const Vector<Type> &vec) const { return Subtract(vec); }
        inline Vector<Type> operator*(const Vector<Type> &vec) const { return Multiply(vec); }

        inline void operator+=(const Vector<Type> &vec) { this->AddInPlace(vec); }
        inline void operator-=(const Vector<Type> &vec) { this->SubtractInPlace(vec); }
        inline void operator*=(const Vector<Type> &vec) { this->MultiplyInPlace(vec); }
    };
    
    // Floating-point vector aliases

    typedef Vector<float> FVector;
    typedef Vector<double> DVector;

    // Signed integer vector aliases

    typedef Vector<int8_t> I8Vector;
    typedef Vector<int16_t> I16Vector;
    typedef Vector<int32_t> I32Vector;
    typedef Vector<int64_t> I64Vector;

    // Unsigned integer vector aliases

    typedef Vector<uint8_t> U8Vector;
    typedef Vector<uint16_t> U16Vector;
    typedef Vector<uint32_t> U32Vector;
    typedef Vector<uint64_t> U64Vector;
}

#undef __VEC_FOREACH