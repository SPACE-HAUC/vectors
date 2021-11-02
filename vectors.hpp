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
    class Vector3
    {
    private:
        bool row;
    public:
        Vector3()
        {
            x = 0;
            y = 0;
            z = 0;
            row = false;
        }
        Vector3(const T xyz)
        {
            x = xyz;
            y = xyz;
            z = xyz;
            row = false;
        }
        Vector3(T x, T y, T z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            row = false;
        }
        Vector3(const Vector3 &obj)
        {
            x = obj.x;
            y = obj.y;
            z = obj.z;
            row = obj.isrow();
        }
        // set a quaternion into a vector here

        // Self ops
        double norm()
        {
            return sqrt(x * x + y * y + z * z);
        }

        Vector3<T> transpose()
        {
            Vector3<T> tmp(x, y, z);
            tmp.row = !row;
            return tmp;
        }

        void normalize()
        {
            for (double n = this->norm(); n > 0; n = 0)
            {
                x /= n;
                y /= n;
                z /= n;
            }
        }

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
        void operator*=(const Vector3<U> &v) // in place cross product
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
        Vector3 operator*(const Vector3<U> &v) // cross product
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
        T x;
        T y;
        T z;
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