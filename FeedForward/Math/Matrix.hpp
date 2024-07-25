#pragma once

#include <Math/Vector.hpp>

namespace Math
{
    template <typename Type> class Matrix
    {
        private:
        
        // Matrix size

        size_t rows = 0;
        size_t cols = 0;

        public:

        // Matrix elements

        Type *data = nullptr;

        // Constructors

        Matrix(size_t rows, size_t cols)
        { this->Resize(rows, cols); }

        Matrix(size_t rows, size_t cols, const Type *data)
        { this->Resize(rows, cols); this->Assign(data); }

        Matrix(size_t rows, size_t cols, Type diagonal)
        { this->Resize(rows, cols); this->Assign(diagonal); }

        Matrix(const Vector<Type> &vec)
        { this->Resize(vec.Size(), 1), this->Assign(vec.data); }

        // Destructor

        ~Matrix()
        {
            if (this->data != nullptr)
                delete[] this->data;
        }

        // Assignment

        void Assign(const Type *data)
        { std::memcpy(this->data, data, sizeof(Type) * this->rows * this->cols); }

        void Assign(Type diagonal)
        {
            size_t i = 0;
            for (size_t row = 0; row < this->rows; row++)
            {
                for (size_t col = 0; col < this->cols; col++)
                {
                    if (row == col)
                        this->data[i] = diagonal;
                    else
                        this->data[i] = 0;
                    i++;
                }
            }
        }

        // Dimensions

        size_t Rows() const { return this->rows; }
        size_t Cols() const { return this->cols; }

        void Resize(size_t rows, size_t cols)
        {
            if (rows == 0 || cols == 0)
                throw std::runtime_error("Matrix dimensions may not be 0.");

            if (this->rows == rows && this->cols == cols)
                return;

            if (this->data != nullptr)
                delete[] this->data;

            this->rows = rows;
            this->cols = cols;

            this->data = new Type[rows * cols];
        }

        // Copy constructor/assignment operator

        Matrix(const Matrix<Type> &mat)
        { this->Resize(mat.rows, mat.cols); this->Assign(mat.data); }

        Matrix<Type> &operator=(const Matrix<Type> &mat)
        { this->Resize(mat.rows, mat.cols); this->Assign(mat.data); }

        // Move constructor/assignment operator

        Matrix(Matrix<Type> &&mat) : rows(mat.rows), cols(mat.cols), data(mat.data)
        { mat.data = nullptr; }

        Matrix<Type> &operator=(Matrix<Type> &&mat)
        {
            if (this->data != nullptr)
                delete[] this->data;

            this->rows = mat.rows;
            this->cols = mat.cols;
            this->data = mat.data;

            mat.data = nullptr;

            return *this;
        }

        // Indexing

        Type &At(size_t index)
        {
            if (index >= this->rows * this->cols)
                throw std::out_of_range("Specified index out of bounds of matrix.");
            return this->data[index];
        }

        const Type &At(size_t index) const
        {
            if (index >= this->rows * this->cols)
                throw std::out_of_range("Specified index out of bounds of matrix.");
            return this->data[index];
        }

        inline Type &At(size_t row, size_t col) { return this->At(col * this->rows + row); }
        inline const Type &At(size_t row, size_t col) const { return this->At(col * this->rows + row); }

        // Index operators

        inline Type &operator[](size_t index) { return this->data[index]; }
        inline const Type &operator[](size_t index) const { return this->data[index]; }

        // Vector conversion

        Vector<Type> AsVector() const
        {
            if (this->cols != 1)
                throw std::runtime_error("Only matrices with 1 column may be interpreted as a vector.");
            return Vector<Type>(this->rows, this->data);
        }

        // Matrix properties

        Matrix<Type> Transpose() const
        {
            Matrix<Type> newMat(this->cols, this->rows);

            for (size_t row = 0; row < this->rows; row++)
            {
                for (size_t col = 0; col < this->cols; col++)
                    newMat.At(col, row) = this->At(row, col);
            }

            return newMat;
        }

        void TransposeInPlace()
        {
            Matrix<Type> newMat(this->cols, this->rows);

            for (size_t row = 0; row < this->rows; row++)
            {
                for (size_t col = 0; col < this->cols; col++)
                    newMat.At(col, row) = this->At(row, col);
            }

            this->rows = newMat.rows;
            this->cols = newMat.cols;

            delete[] this->data;
            this->data = newMat.data;
            newMat.data = nullptr;
        }

        // Scalar arithmetic

        Matrix<Type> Add(Type scalar) const
        {
            Matrix<Type> mat(this->rows, this->cols, this->data);

            for (size_t i = 0; i < this->rows * this->cols; i++)
                mat.data[i] += scalar;
                
            return mat;
        }

        Matrix<Type> Subtract(Type scalar) const
        {
            Matrix<Type> mat(this->rows, this->cols, this->data);

            for (size_t i = 0; i < this->rows * this->cols; i++)
                mat.data[i] -= scalar;
                
            return mat;
        }

        Matrix<Type> Scale(Type scalar) const
        {
            Matrix<Type> mat(this->rows, this->cols, this->data);

            for (size_t i = 0; i < this->rows * this->cols; i++)
                mat.data[i] *= scalar;
                
            return mat;
        }

        // In-place scalar arithmetic

        Matrix<Type> AddInPlace(Type scalar) const
        {
            for (size_t i = 0; i < this->rows * this->cols; i++)
            this->data[i] += scalar;
        }

        Matrix<Type> SubtractInPlace(Type scalar) const
        {
            for (size_t i = 0; i < this->rows * this->cols; i++)
            this->data[i] -= scalar;
        }

        Matrix<Type> ScaleInPlace(Type scalar) const
        {
            for (size_t i = 0; i < this->rows * this->cols; i++)
            this->data[i] *= scalar;
        }

        // Matrix arithmetic

        Matrix<Type> Add(const Matrix<Type> &mat) const
        {
            Matrix<Type> newMat(this->rows, this->cols, this->data);

            for (size_t i = 0; i < this->rows * this->cols; i++)
                newMat.data[i] += mat.data[i];

            return newMat;
        }

        Matrix<Type> Subtract(const Matrix<Type> &mat) const
        {
            Matrix<Type> newMat(this->rows, this->cols, this->data);

            for (size_t i = 0; i < this->rows * this->cols; i++)
                newMat.data[i] -= mat.data[i];

            return newMat;
        }

        Matrix<Type> Multiply(const Matrix<Type> &mat) const
        {
            if (this->cols != mat.rows)
                throw std::runtime_error("Matrix dimensions are incompatible for multiplication.");

            Matrix<Type> newMat(this->rows, mat.cols);

            for (size_t row = 0; row < this->rows; row++)
            {
                for (size_t col = 0; col < mat.cols; col++)
                {
                    Type dot = 0;

                    for (size_t m = 0; m < mat.rows; m++)
                        dot += this->At(row, m) * mat.At(m, col);

                    newMat.At(row, col) = dot;
                }
            }
            
            return newMat;
        }

        Vector<Type> Multiply(const Vector<Type> &vec) const
        {
            size_t vecSize = vec.Size();
            if (this->cols != vecSize)
                throw std::runtime_error("Matrix and vector dimensions are imcompatible for multiplic.");

            Vector<Type> newVec(this->rows);

            for (size_t row = 0; row < this->rows; row++)
            {
                Type dot = 0;
                
                for (size_t col = 0; col < this->cols; col++)
                    dot += this->At(row, col) * vec.data[col];

                newVec.data[row] = dot;
            }

            return newVec;
        }

        // In-place matrix arithmetic

        void AddInPlace(const Matrix<Type> &mat)
        {
            for (size_t i = 0; i < this->rows * this->cols; i++)
                this->data[i] = this->data[i] + mat.data[i];
        }

        void SubtractInPlace(const Matrix<Type> &mat)
        {
            for (size_t i = 0; i < this->rows * this->cols; i++)
                this->data[i] = this->data[i] - mat.data[i];
        }

        void MultiplyInPlace(const Matrix<Type> &mat)
        {
            if (this->cols != mat.rows)
                throw std::runtime_error("Matrix dimensions are incompatible for multiplication.");

            Matrix<Type> newMat(this->rows, mat.cols);

            for (size_t row = 0; row < this->rows; row++)
            {
                for (size_t col = 0; col < mat.cols; col++)
                {
                    Type dot = 0;

                    for (size_t m = 0; m < mat.rows; m++)
                        dot += this->At(row, m) * mat.At(m, col);

                    newMat.At(row, col) = dot;
                }
            }

            this->rows = newMat.rows;
            this->cols = newMat.cols;
            
            delete[] this->data;
            this->data = newMat.data;
            newMat.data = nullptr;
        }

        // Scalar arithmetic operators

        inline Matrix<Type> operator+(Type s) const { return Add(s); }
        inline Matrix<Type> operator-(Type s) const { return Subtract(s); }
        inline Matrix<Type> operator*(Type s) const { return Scale(s); }
        inline Matrix<Type> operator/(Type s) const { return Scale(1 / s); }

        inline void operator+=(Type s) { this->AddInPlace(s); }
        inline void operator-=(Type s) { this->SubtractInPlace(s); }
        inline void operator*=(Type s) { this->ScaleInPlace(s); }
        inline void operator/=(Type s) { this->ScaleInPlace(1 / s); }

        // Matrix arithmetic operators

        inline Matrix<Type> operator+(const Matrix<Type> &mat) const { return Add(mat); }
        inline Matrix<Type> operator-(const Matrix<Type> &mat) const { return Subtract(mat); }
        inline Matrix<Type> operator*(const Matrix<Type> &mat) const { return Multiply(mat); }
        inline Vector<Type> operator*(const Vector<Type> &vec) const { return Multiply(vec); }

        inline void operator+=(const Matrix<Type> &mat) { this->AddInPlace(mat); }
        inline void operator-=(const Matrix<Type> &mat) { this->SubtractInPlace(mat); }
        inline void operator*=(const Matrix<Type> &mat) { this->MultiplyInPlace(mat); }
        inline void operator*=(const Vector<Type> &vec) { this->MultiplyInPlace(vec); }

        // Identity matrix

        static Matrix<Type> Identity(size_t size)
        { return Matrix<Type>(size, size, 1); }
    };
}