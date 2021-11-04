/**
 * @file vectors.hpp
 * @author Mit Bailey (mitbailey99@gmail.com)
 * @brief Vectors and things.
 * @version See Git tags for version information.
 * @date 2021.11.02
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <iostream>
#include <cmath>

namespace vec
{
    template <class T>
    class Vector3;
    template <class T>
    class Vector4;
    template <class T>
    class Matrix33;
    template <class T>
    class Matrix44;

    template <class T>
    class Matrix33
    {
        private:
        bool transposed;
    public:
        Matrix33()
        {
            // prevent creation of matrix of non-numbers
            double temp = data[0];
            for (int i = 0; i < 9; i++)
                data[i] = 0;
            transposed = false;
        }

        Matrix33(T in[3][3])
        {
            double temp = in[0][0];
            for (int i = 0; i < 9; i++)
            {
                int x = i / 3;
                int y = i % 3;
                data[i] = in[x][y];
                transposed = false;
            }
        }

        Matrix33(T in[9])
        {
            double temp = in[0];

            for (int i = 0; i < 9; i++)
            {
                data[i] = in[i];
                transposed = false;
            }
        }

        template <class U>
        Matrix33(const Matrix33<U> &in)
        {
            double temp = in(0, 0); // check that

            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    *this(x, y) = in(x, y);
            transposed = in.isTransposed();
        }

        T& operator()(int x, int y)
        {
            if (x < 0 || x > 3 || y < 0 || y > 3)
                throw std::out_of_range("Index out of range.");
            int idx;
            if (transposed)
                idx = 3 * y + x;
            else
                idx = 3 * x + y;
            return data[idx];
        }

        bool isTransposed()
        {
            return transposed;
        }

        Matrix33<T> transpose() const
        {
            Matrix33<T> temp(data);
            temp.transposed = !transposed;
            return temp;
        }

        // determinant
        T operator()()
        {

        }
        // out of place ops, scalar
        template <class U>
        Matrix33<T> operator*(const U in)
        {
            Matrix33<T> newMatrix(*this);
            double temp = in;
            for (int i = 0; i < 9; i++)
                newMatrix.data[i] *= temp;
            return newMatrix;
        }
        template <class U>
        Matrix33<T> operator/(const U in)
        {
            Matrix33<T> newMatrix(*this);
            double temp = in;
            for (int i = 0; i < 9; i++)
                newMatrix.data[i] /= temp;
            return newMatrix;
        }
        // in place ops, scalar
        template <class U>
        void operator*=(const U in)
        {
            double temp = in;
            for (int i = 0; i < 9; i++)
                data[i] *= temp;
        }
        template <class U>
        void operator/=(const U in)
        {
            double temp = in;
            for (int i = 0; i < 9; i++)
                data[i] /= temp;
        }
        // in place ops, vector
        template <class U>
        Vector3<T> operator*(const Vector3<U> in)
        {
            if (in.isrow())
                throw std::invalid_argument("Can not multiply: Matrix33 * Row Vector");
            Vector3<T> res;
            res.x = in.x * (*this)(0, 0) + in.y * (*this)(0, 1) + in.z * (*this)(0, 2);
            res.y = in.x * (*this)(1, 0) + in.y * (*this)(1, 1) + in.z * (*this)(2, 2);
            res.z = in.x * (*this)(2, 0) + in.y * (*this)(1, 1) + in.z * (*this)(2, 2);
            return res;
        }

        template <class U>
        friend Matrix33 operator/(const U &s, const Matrix33<T> &in)
        {
            double temp = s;
            // TODO: invert here
        }
        

        T data[9];
    };

    template <class T>
    class Vector3
    {
    public:
        /**
         * @brief Default constructor, all elements initialized to 0.
         * 
         */
        Vector3()
        {
            // Prohibits templates of types that cannot be cast to double.
            double temp = x;

            x = 0;
            y = 0;
            z = 0;
            row = false;
        }

        /**
         * @brief Constructor, all elements initialized to xyz.
         * 
         * @param xyz 
         */
        Vector3(const T xyz)
        {
            // Prohibits templates of types that cannot be cast to double.
            double temp = xyz;

            x = xyz;
            y = xyz;
            z = xyz;
            row = false;
        }

        /**
         * @brief Constructor, elements set individually.
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        Vector3(T x, T y, T z)
        {
            // Prohibits templates of types that cannot be cast to double.
            double temp = x;

            this->x = x;
            this->y = y;
            this->z = z;
            row = false;
        }

        /**
         * @brief Copy constructor.
         * 
         * @param obj 
         */
        Vector3(const Vector3 &obj)
        {
            x = obj.x;
            y = obj.y;
            z = obj.z;
            row = obj.isrow();
        }

        // TODO: set a quaternion into a vector here

        /*** SELF OPERATIONS ***/

        /**
         * @brief Returns the norm of this vector object.
         * 
         * Does not change the values of this vector object.
         * 
         * @return double 
         */
        double norm()
        {
            return sqrt(x * x + y * y + z * z);
        }

        /**
         * @brief Returns the transpose of this vector object.
         * 
         * Does not change the values of this vector object.
         * 
         * @return Vector3<T> 
         */
        Vector3<T> transpose()
        {
            Vector3<T> tmp(x, y, z);
            tmp.row = !row;
            return tmp;
        }

        /**
         * @brief Normalizes this vector object.
         * 
         * Changes the values of this vector object.
         * 
         */
        void normalize()
        {
            for (double n = this->norm(); n > 0; n = 0)
            {
                x /= n;
                y /= n;
                z /= n;
            }
        }
        
        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool isrow() const
        {
            return row;
        }

        // In Place Scalar Ops
        template <class U>
        void operator=(const U &val)
        {
            x = (T)val;
            y = (T)val;
            z = (T)val;
        }

        template <class U>
        void operator+=(const U &val)
        {
            x += (T)val;
            y += (T)val;
            z += (T)val;
        }

        template <class U>
        void operator-=(const U &val)
        {
            x -= (T)val;
            y -= (T)val;
            z -= (T)val;
        }

        template <class U>
        void operator*=(const U &val)
        {
            x *= (T)val;
            y *= (T)val;
            z *= (T)val;
        }

        template <class U>
        void operator/=(const U &val)
        {
            x /= (T)val;
            y /= (T)val;
            z /= (T)val;
        }

        // Out of place scalar ops
        template <class U>
        Vector3 operator+(const U &val)
        {
            return Vector3(x + val, y + val, z + val);
        }

        template <class U>
        Vector3 operator-(const U &val)
        {
            return Vector3(x - val, y - val, z - val);
        }

        template <class U>
        Vector3 operator*(const U &val)
        {
            return Vector3(x * val, y * val, z * val);
        }

        template <class U>
        Vector3 operator/(const U &val)
        {
            return Vector3(x / val, y / val, z / val);
        }

        // Vector operations in place
        template <class U>
        void operator+=(const Vector3<U> &vec)
        {
            if (row != vec.row)
                throw std::invalid_argument("Vectors are not of the same shape.");
            x += (T)vec.x;
            y += (T)vec.y;
            z += (T)vec.z;
        }

        template <class U>
        void operator-=(const Vector3<U> &vec)
        {
            if (row != vec.row)
                throw std::invalid_argument("Vectors are not of the same shape.");
            x -= (T)vec.x;
            y -= (T)vec.y;
            z -= (T)vec.z;
        }

        template <class U>
        void operator^=(const Vector3<U> &v) // in place cross product
        {
            if (row != v.row)
                throw std::invalid_argument("Vectors are not of the same shape.");
            T xx, yy, zz;
            zz = x * v.y - y * v.x;
            xx = y * v.z - z * v.y;
            yy = z * v.x - x * v.z;
            x = xx;
            y = yy;
            z = zz;
        }

        // Vector operations out of place
        template <class U>
        Vector3 operator+(const Vector3<U> &vec)
        {
            if (row != vec.row)
                throw std::invalid_argument("Vectors are not of the same shape.");
            return Vector3(x + vec.x, y + vec.y, z + vec.z);
        }

        template <class U>
        Vector3 operator-(const Vector3<U> &vec)
        {
            if (row != vec.row)
                throw std::invalid_argument("Vectors are not of the same shape.");
            return Vector3(x - vec.x, y - vec.y, z - vec.z);
        }

        template <class U>
        Vector3 operator^(const Vector3<U> &v) // cross product
        {
            if (row != v.row)
                throw std::invalid_argument("Vectors are not of the same shape.");
            T xx, yy, zz;
            zz = x * v.y - y * v.x;
            xx = y * v.z - z * v.y;
            yy = z * v.x - x * v.z;
            return Vector3(xx, yy, zz);
        }

        template <class U>
        Vector3 operator*(const Matrix33<U> &v) // Matrix product
        {
            if (row != v.row)
                throw std::invalid_argument("Only a row vector can be multiplied to a matrix.");
            T xx, yy, zz;
            xx = x * v(0, 0) + y * v(1, 0) + z * v(2, 0);
            yy = x * v(0, 1) + y * v(1, 1) + z * v(2, 1);
            zz = x * v(0, 2) + y * v(1, 2) + z * v(2, 2);
            return Vector3(xx, yy, zz);
        }

        template <class U>
        void operator*=(const Matrix33<U> &v) // Matrix product
        {
            if (row != v.row)
                throw std::invalid_argument("Only a row vector can be multiplied to a matrix.");
            T xx, yy, zz;
            xx = x * v(0, 0) + y * v(1, 0) + z * v(2, 0);
            yy = x * v(0, 1) + y * v(1, 1) + z * v(2, 1);
            zz = x * v(0, 2) + y * v(1, 2) + z * v(2, 2);
            x = xx;
            y = yy;
            z = zz;
        }

        template <class U>
        Vector3 operator/(const Matrix33<U> &v) // Matrix product
        {
            if (row != v.row)
                throw std::invalid_argument("Only a row vector can be multiplied to a matrix.");
            Vector3 res(x, y, z);
            res *= 1/v;
            return res;
        }

        template <class U>
        double operator&(const Vector3<U> &vec) // dot product
        {
            if (row != vec.row)
                throw std::invalid_argument("Vectors are not of the same shape.");
            double res = x * vec.x + y * vec.y + z * vec.z;
            return res;
        }

        template <class U>
        bool operator==(const Vector3<U> &v)
        {
            return (x == v.x) & (y == v.y) & (z == v.z) & (row == v.isrow());
        }

        template <class U>
        friend Vector3 operator/(const U scalar, const Vector3<T> &v)
        {
            Vector3 res(v.x / scalar, v.y / scalar, v.z / scalar);
            return res;
        }

        T x;
        T y;
        T z;

    private:
        bool row;
    };
}

template <class T>
static std::ostream &operator<<(std::ostream &os, const vec::Vector3<T> &v)
{
    os << "[" << v.x << " " << v.y << " " << v.z << "]";
    if (!v.isrow())
        os << "'";
    return os;
}


#endif // VECTORS_HPP