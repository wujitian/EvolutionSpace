#ifndef __VMATH_H__
#define __VMATH_H__


#define _USE_MATH_DEFINES  1 // Include constants defined in math.h
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "fp16.h"
#include "Sfu.h"

namespace vmath
{

template <typename T, const int w, const int h> class matNM;
template <typename T, const int len> class vecN;
template <typename T> class Tquaternion;

template <typename T> 
inline T degrees(T angleInRadians)
{
    return angleInRadians * static_cast<T>(180.0/M_PI);
}

template <typename T>
inline T radians(T angleInDegrees)
{
    return angleInDegrees * static_cast<T>(M_PI/180.0);
}

template <typename T>
struct random
{
    operator T ()
    {
        static unsigned int seed = 0x13371337;
        unsigned int res;
        unsigned int tmp;
        
        seed *= 16807;
        
        tmp = seed ^ (seed >> 4) ^ (seed << 15);
        
        res = (tmp >> 9) | 0x3F800000;

        return static_cast<T>(res);
    }
};

template<>
struct random<float>
{
    operator float()
    {
        static unsigned int seed = 0x13371337;
        float res;
        unsigned int tmp;

        seed *= 16807;

        tmp = seed ^ (seed >> 4) ^ (seed << 15);

        *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

        return (res - 1.0f);
    }
};

template<>
struct random<unsigned int>
{
    operator unsigned int()
    {
        static unsigned int seed = 0x13371337;
        unsigned int res;
        unsigned int tmp;

        seed *= 16807;

        tmp = seed ^ (seed >> 4) ^ (seed << 15);

        res = (tmp >> 9) | 0x3F800000;

        return res;
    }
};

enum DataType
{
    DATA_TYPE_FLOAT,
    DATA_TYPE_INT32,
    DATA_TYPE_UINT32,
    DATA_TYPE_VEC4,
    DATA_TYPE_VEC3,
    DATA_TYPE_VEC2,
    DATA_TYPE_IVEC4,
    DATA_TYPE_IVEC3,
    DATA_TYPE_IVEC2,
    DATA_TYPE_MAT4,
    DATA_TYPE_MAT3,
    DATA_TYPE_MAT2,
    DATA_TYPE_IMAT4,
    DATA_TYPE_IMAT3,
    DATA_TYPE_IMAT2,
    DATA_TYPE_BLOCK,
};

class DataBase
{
public:
    DataBase() {}
};

template <typename T, const int len>
class vecN : public DataBase
{
public:
    typedef class vecN<T,len> my_type;
    typedef T element_type;

    // Default constructor does nothing, just like built-in types
    inline vecN()
    {
        // Uninitialized variable
    }

    // Copy constructor
    inline vecN(const vecN& that)
    {
        assign(that);
    }

    // Construction from scalar
    inline vecN(T s)
    {
        int n;
        for (n = 0; n < len; n++)
        {
            data[n] = s;
        }
    }

    // Assignment operator
    inline vecN& operator=(const vecN& that)
    {
        assign(that);
        return *this;
    }

    inline vecN& operator=(const T& that)
    {
        int n;
        for (n = 0; n < len; n++)
            data[n] = that;

        return *this;
    }

    inline vecN operator+(const vecN& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < len; n++)
            result.data[n] = data[n] + that.data[n];
        return result;
    }

    inline vecN& operator+=(const vecN& that)
    {
        return (*this = *this + that);
    }

    inline vecN operator-() const
    {
        my_type result;
        int n;
        for (n = 0; n < len; n++)
            result.data[n] = -data[n];
        return result;
    }

    inline vecN operator-(const vecN& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < len; n++)
            result.data[n] = data[n] - that.data[n];
        return result;
    }

    inline vecN& operator-=(const vecN& that)
    {
        return (*this = *this - that);
    }

    inline vecN operator*(const vecN& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < len; n++)
            result.data[n] = data[n] * that.data[n];
        return result;
    }

    inline vecN& operator*=(const vecN& that)
    {
        return (*this = *this * that);
    }

    inline vecN operator*(const T& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < len; n++)
            result.data[n] = data[n] * that;
        return result;
    }

    inline vecN& operator*=(const T& that)
    {
        assign(*this * that);

        return *this;
    }

    inline vecN operator/(const vecN& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < len; n++)
            result.data[n] = data[n] / that.data[n];
        return result;
    }

    inline vecN& operator/=(const vecN& that)
    {
        assign(*this / that);

        return *this;
    }

    inline vecN operator/(const T& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < len; n++)
            result.data[n] = data[n] / that;
        return result;
    }

    inline vecN& operator/=(const T& that)
    {
        assign(*this / that);
        return *this;
    }

    inline T& operator[](int n) { return data[n]; }
    inline const T& operator[](int n) const { return data[n]; }

    inline static int size(void) { return len; }

    inline operator const T* () const { return &data[0]; }

    static inline vecN random()
    {
        vecN result;
        int i;

        for (i = 0; i < len; i++)
        {
            result[i] = vmath::random<T>();
        }
        return result;
    }

protected:
    T data[len];

    inline void assign(const vecN& that)
    {
        int n;
        for (n = 0; n < len; n++)
            data[n] = that.data[n];
    }
};

template <typename T>
class Tvec3;

template <typename T>
class Tvec4;

template <typename T>
class Tvec2 : public vecN<T,2>
{
public:
    typedef vecN<T,2> base;

    // Uninitialized variable
    inline Tvec2() 
    {
        base::data[0] = 0;
        base::data[1] = 0;
    }
    // Copy constructor
    inline Tvec2(const base& v) : base(v) {}

    // vec2(x, y);
    inline Tvec2(T x, T y)
    {
        base::data[0] = x;
        base::data[1] = y;
    }

    // vec2(x, v) from Tvec3
    inline Tvec2(const Tvec3<T>& v)
    {
        base::data[0] = v[0];
        base::data[1] = v[1];
    }

    // vec2(x, v) from Tvec4
    inline Tvec2(const Tvec4<T>& v)
    {
        base::data[0] = v[0];
        base::data[1] = v[1];
    }

    inline Tvec2(T x)
    {
        base::data[0] = x;
        base::data[1] = x;
    }

    inline Tvec2(uint32_t* pHexFloats)
    {
        for (int n = 0; n < 2; n++)
        {
            base::data[n] = *(T*)(pHexFloats + n);
        }
    }

    inline T &x()
    {
        return base::data[0];
    }

    inline T y()
    {
        return &base::data[1];
    }
};

template <typename T>
class Tvec3 : public vecN<T,3>
{
public:
    typedef vecN<T,3> base;

    // Uninitialized variable
    inline Tvec3() 
    {
        base::data[0] = 0;
        base::data[1] = 0;
        base::data[2] = 0;
    }

    // Copy constructor
    inline Tvec3(const base& v) : base(v) {}

    // vec3(x, y, z);
    inline Tvec3(T x, T y, T z)
    {
        base::data[0] = x;
        base::data[1] = y;
        base::data[2] = z;
    }

    // vec3(v, z);
    inline Tvec3(const Tvec2<T>& v, T z)
    {
        base::data[0] = v[0];
        base::data[1] = v[1];
        base::data[2] = z;
    }

    // vec3(x, v)
    inline Tvec3(T x, const Tvec2<T>& v)
    {
        base::data[0] = x;
        base::data[1] = v[0];
        base::data[2] = v[1];
    }

    // vec3(x, v) from Tvec4
    inline Tvec3(const Tvec4<T>& v)
    {
        base::data[0] = v[0];
        base::data[1] = v[1];
        base::data[2] = v[2];
    }

    inline Tvec3(T x)
    {
        base::data[0] = x;
        base::data[1] = x;
        base::data[2] = x;
    }

    inline Tvec3(uint32_t* pHexFloats)
    {
        for (int n = 0; n < 3; n++)
        {
            base::data[n] = *(T*)(pHexFloats + n);
        }
    }

    inline T &x()
    {
        return base::data[0];
    }

    inline T &y()
    {
        return base::data[1];
    }

    inline T &z()
    {
        return base::data[2];
    }

    inline Tvec2<T> xy()
    {
        Tvec2<T> v;
        v[0] =  base::data[0];
        v[1] =  base::data[1];

        return v;
    }

    inline Tvec2<T> yz()
    {
        Tvec2<T> v;
        v[0] =  base::data[1];
        v[1] =  base::data[2];

        return v;
    }
};

template <typename T>
class Tvec4 : public vecN<T,4>
{
public:
    typedef vecN<T,4> base;

    // Uninitialized variable
    inline Tvec4() 
    { 
        base::data[0] = 0;
        base::data[1] = 0;
        base::data[2] = 0;

        if (std::is_same<T, float>::value || std::is_same<T, double>::value)
        {
            base::data[3] = 1.0;
        }
        else
        {
            base::data[3] = 0;
        }
    }

    // Copy constructor
    inline Tvec4(const base& v) : base(v) {}

    // vec4(x, y, z, w);
    inline Tvec4(T x, T y, T z, T w)
    {
        base::data[0] = x;
        base::data[1] = y;
        base::data[2] = z;
        base::data[3] = w;
    }

    // vec4(v, z, w);
    inline Tvec4(const Tvec2<T>& v, T z, T w)
    {
        base::data[0] = v[0];
        base::data[1] = v[1];
        base::data[2] = z;
        base::data[3] = w;
    }

    // vec4(x, v, w);
    inline Tvec4(T x, const Tvec2<T>& v, T w)
    {
        base::data[0] = x;
        base::data[1] = v[0];
        base::data[2] = v[1];
        base::data[3] = w;
    }

    // vec4(x, y, v);
    inline Tvec4(T x, T y, const Tvec2<T>& v)
    {
        base::data[0] = x;
        base::data[1] = y;
        base::data[2] = v[0];
        base::data[3] = v[1];
    }

    // vec4(v1, v2);
    inline Tvec4(const Tvec2<T>& u, const Tvec2<T>& v)
    {
        base::data[0] = u[0];
        base::data[1] = u[1];
        base::data[2] = v[0];
        base::data[3] = v[1];
    }

    // vec4(v, w);
    inline Tvec4(const Tvec3<T>& v, T w)
    {
        base::data[0] = v[0];
        base::data[1] = v[1];
        base::data[2] = v[2];
        base::data[3] = w;
    }

    // vec4(x, v);
    inline Tvec4(T x, const Tvec3<T>& v)
    {
        base::data[0] = x;
        base::data[1] = v[0];
        base::data[2] = v[1];
        base::data[3] = v[2];
    }

    inline Tvec4(T x)
    {
        base::data[0] = x;
        base::data[1] = x;
        base::data[2] = x;
        base::data[3] = x;
    }

    inline Tvec4(uint32_t* pHexFloats)
    {
        for (int n = 0; n < 4; n++)
        {
            base::data[n] = *(T*)(pHexFloats + n);
        }
    }

    inline T &x()
    {
        return base::data[0];
    }

    inline T &y()
    {
        return base::data[1];
    }

    inline T &z()
    {
        return base::data[2];
    }

    inline T &w()
    {
        return base::data[3];
    }

    inline Tvec2<T> xy()
    {
        Tvec2<T> v;
        v[0] =  base::data[0];
        v[1] =  base::data[1];

        return v;
    }

    inline Tvec2<T> yz()
    {
        Tvec2<T> v;
        v[0] =  base::data[1];
        v[1] =  base::data[2];

        return v;
    }

    inline Tvec2<T> zw()
    {
        Tvec2<T> v;
        v[0] =  base::data[2];
        v[1] =  base::data[3];

        return v;
    }

    inline Tvec3<T> xyz()
    {
        Tvec3<T> v;
        v[0] =  base::data[0];
        v[1] =  base::data[1];
        v[2] =  base::data[2];

        return v;
    }

    inline Tvec3<T> yzw()
    {
        Tvec3<T> v;
        v[0] =  base::data[1];
        v[1] =  base::data[2];
        v[2] =  base::data[3];

        return v;
    }

    inline Tvec3<T> xyw()
    {
        Tvec3<T> v;
        v[0] =  base::data[0];
        v[1] =  base::data[1];
        v[2] =  base::data[3];

        return v;
    }
};

// These types don't exist in GLSL and don't have full implementations
// (constructors and such). This is enough to get some template functions
// to compile correctly.
typedef vecN<float, 1> vec1;
typedef vecN<int, 1> ivec1;
typedef vecN<unsigned int, 1> uvec1;
typedef vecN<double, 1> dvec1;

typedef Tvec2<float> vec2;
typedef Tvec2<int> ivec2;
typedef Tvec2<unsigned int> uvec2;
typedef Tvec2<double> dvec2;

typedef Tvec3<float> vec3;
typedef Tvec3<int> ivec3;
typedef Tvec3<unsigned int> uvec3;
typedef Tvec3<double> dvec3;

typedef Tvec4<float> vec4;
typedef Tvec4<int> ivec4;
typedef Tvec4<unsigned int> uvec4;
typedef Tvec4<double> dvec4;

template <typename T, int n>
static inline const vecN<T,n> operator * (T x, const vecN<T,n>& v)
{
    return v * x;
}

template <typename T>
static inline const Tvec2<T> operator / (T x, const Tvec2<T>& v)
{
    return Tvec2<T>(x / v[0], x / v[1]);
}

template <typename T>
static inline const Tvec3<T> operator / (T x, const Tvec3<T>& v)
{
    return Tvec3<T>(x / v[0], x / v[1], x / v[2]);
}

template <typename T>
static inline const Tvec4<T> operator / (T x, const Tvec4<T>& v)
{
    return Tvec4<T>(x / v[0], x / v[1], x / v[2], x / v[3]);
}

template <typename T, int len>
static inline T dot(const vecN<T,len>& a, const vecN<T,len>& b)
{
    int n;
    T total = T(0);
    for (n = 0; n < len; n++)
    {
        total += a[n] * b[n];
    }
    return total;
}

template <typename T>
static inline vecN<T,3> cross(const vecN<T,3>& a, const vecN<T,3>& b)
{
    return Tvec3<T>(a[1] * b[2] - b[1] * a[2],
                    a[2] * b[0] - b[2] * a[0],
                    a[0] * b[1] - b[0] * a[1]);
}

template <typename T>
static inline T cross(const vecN<T,2>& a, const vecN<T,2>& b)
{
    return T (a[0] * b[1] - a[1] * b[0]);
}

template <typename T, int len>
static inline T length(const vecN<T,len>& v)
{
    T result(0);

    for (int i = 0; i < v.size(); ++i)
    {
        result += v[i] * v[i];
    }

    return (T)sqrt(result);
}

template <typename T, int len>
static inline vecN<T,len> normalize(const vecN<T,len>& v)
{
    return v / length(v);
}

template <typename T, int len>
static inline T distance(const vecN<T,len>& a, const vecN<T,len>& b)
{
    return length(b - a);
}

template <typename T, int len>
static inline T angle(const vecN<T,len>& a, const vecN<T,len>& b)
{
    return arccos(dot(a, b));
}

template <typename T>
class Tquaternion
{
public:
    inline Tquaternion()
    {

    }

    inline Tquaternion(const Tquaternion& q)
        : r(q.r),
          v(q.v)
    {

    }

    inline Tquaternion(T _r)
        : r(_r),
          v(T(0))
    {

    }

    inline Tquaternion(T _r, const Tvec3<T>& _v)
        : r(_r),
          v(_v)
    {

    }

    inline Tquaternion(const Tvec4<T>& _v)
        : r(_v[0]),
          v(_v[1], _v[2], _v[3])
    {
    }

    inline Tquaternion(T _x, T _y, T _z, T _w)
        : r(_x),
          v(_y, _z, _w)
    {

    }

    inline T& operator[](int n)
    {
        return a[n];
    }

    inline const T& operator[](int n) const
    {
        return a[n];
    }

    inline Tquaternion operator+(const Tquaternion& q) const
    {
        return quaternion(r + q.r, v + q.v);
    }

    inline Tquaternion& operator+=(const Tquaternion& q)
    {
        r += q.r;
        v += q.v;

        return *this;
    }

    inline Tquaternion operator-(const Tquaternion& q) const
    {
        return quaternion(r - q.r, v - q.v);
    }

    inline Tquaternion& operator-=(const Tquaternion& q)
    {
        r -= q.r;
        v -= q.v;

        return *this;
    }

    inline Tquaternion operator-() const
    {
        return Tquaternion(-r, -v);
    }

    inline Tquaternion operator*(const T s) const
    {
        return Tquaternion(a[0] * s, a[1] * s, a[2] * s, a[3] * s);
    }

    inline Tquaternion& operator*=(const T s)
    {
        r *= s;
        v *= s;

        return *this;
    }

    inline Tquaternion operator*(const Tquaternion& q) const
    {
        const T x1 = a[0];
        const T y1 = a[1];
        const T z1 = a[2];
        const T w1 = a[3];
        const T x2 = q.a[0];
        const T y2 = q.a[1];
        const T z2 = q.a[2];
        const T w2 = q.a[3];

        return Tquaternion(w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2,
                           w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2,
                           w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2,
                           w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2);
    }

    inline Tquaternion operator/(const T s) const
    {
        return Tquaternion(a[0] / s, a[1] / s, a[2] / s, a[3] / s);
    }

    inline Tquaternion& operator/=(const T s)
    {
        r /= s;
        v /= s;

        return *this;
    }

    inline operator Tvec4<T>&()
    {
        return *(Tvec4<T>*)&a[0];
    }

    inline operator const Tvec4<T>&() const
    {
        return *(const Tvec4<T>*)&a[0];
    }

    inline bool operator==(const Tquaternion& q) const
    {
        return (r == q.r) && (v == q.v);
    }

    inline bool operator!=(const Tquaternion& q) const
    {
        return (r != q.r) || (v != q.v);
    }

    inline matNM<T,4,4> asMatrix() const
    {
        matNM<T,4,4> m;

        const T xx = x * x;
        const T yy = y * y;
        const T zz = z * z;
        const T ww = w * w;
        const T xy = x * y;
        const T xz = x * z;
        const T xw = x * w;
        const T yz = y * z;
        const T yw = y * w;
        const T zw = z * w;

        m[0][0] = T(1) - T(2) * (yy + zz);
        m[0][1] =        T(2) * (xy - zw);
        m[0][2] =        T(2) * (xz + yw);
        m[0][3] =        T(0);

        m[1][0] =        T(2) * (xy + zw);
        m[1][1] = T(1) - T(2) * (xx + zz);
        m[1][2] =        T(2) * (yz - xw);
        m[1][3] =        T(0);

        m[2][0] =        T(2) * (xz - yw);
        m[2][1] =        T(2) * (yz + xw);
        m[2][2] = T(1) - T(2) * (xx + yy);
        m[2][3] =        T(0);

        m[3][0] =        T(0);
        m[3][1] =        T(0);
        m[3][2] =        T(0);
        m[3][3] =        T(1);

        return m;
    }

    /*
    inline T length() const
    {
        return vmath::length( Tvec4<T>(r, v) );
    }
    */

private:
    union
    {
        struct
        {
            T           r;
            Tvec3<T>    v;
        };
        struct
        {
            T           x;
            T           y;
            T           z;
            T           w;
        };
        T               a[4];
    };
};

typedef Tquaternion<float> quaternion;
typedef Tquaternion<int> iquaternion;
typedef Tquaternion<unsigned int> uquaternion;
typedef Tquaternion<double> dquaternion;

template <typename T>
static inline Tquaternion<T> operator*(T a, const Tquaternion<T>& b)
{
    return b * a;
}

template <typename T>
static inline Tquaternion<T> operator/(T a, const Tquaternion<T>& b)
{
    return Tquaternion<T>(a / b[0], a / b[1], a / b[2], a / b[3]);
}

template <typename T>
static inline Tquaternion<T> normalize(const Tquaternion<T>& q)
{
    return q / length(vecN<T,4>(q));
}

template <typename T, const int w, const int h>
class matNM : public DataBase
{
public:
    typedef class matNM<T,w,h> my_type;
    typedef class vecN<T,h> vector_type;

    // Default constructor does nothing, just like built-in types
    inline matNM()
    {
        // Uninitialized variable
    }

    // Copy constructor
    inline matNM(const matNM& that)
    {
        assign(that);
    }

    // Construction from element type
    // explicit to prevent assignment from T
    explicit inline matNM(T f)
    {
        for (int n = 0; n < w; n++)
        {
            data[n] = f;
        }
    }

    // Construction from vector
    inline matNM(const vector_type& v)
    {
        for (int n = 0; n < w; n++)
        {
            data[n] = v;
        }
    }

    // Assignment operator
    inline matNM& operator=(const my_type& that)
    {
        assign(that);
        return *this;
    }

    inline matNM operator+(const my_type& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < w; n++)
            result.data[n] = data[n] + that.data[n];
        return result;
    }

    inline my_type& operator+=(const my_type& that)
    {
        return (*this = *this + that);
    }

    inline my_type operator-(const my_type& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < w; n++)
            result.data[n] = data[n] - that.data[n];
        return result;
    }

    inline my_type& operator-=(const my_type& that)
    {
        return (*this = *this - that);
    }

    inline my_type operator*(const T& that) const
    {
        my_type result;
        int n;
        for (n = 0; n < w; n++)
            result.data[n] = data[n] * that;
        return result;
    }

    inline my_type& operator*=(const T& that)
    {
        int n;
        for (n = 0; n < w; n++)
            data[n] = data[n] * that;
        return *this;
    }

    // Matrix multiply.
    // TODO: This only works for square matrices. Need more template skill to make a non-square version.
    inline my_type operator*(const my_type& that) const
    {
        my_type result(0);

        for (int j = 0; j < w; j++)
        {
            for (int i = 0; i < h; i++)
            {
                T sum(0);

                for (int n = 0; n < w; n++)
                {
                    sum += data[n][i] * that[j][n];
                }

                result[j][i] = sum;
            }
        }

        return result;
    }

    inline my_type& operator*=(const my_type& that)
    {
        return (*this = *this * that);
    }

    inline vector_type& operator[](int n) { return data[n]; }
    inline const vector_type& operator[](int n) const { return data[n]; }
    inline operator T*() { return &data[0][0]; }
    inline operator const T*() const { return &data[0][0]; }

    inline matNM<T,h,w> transpose(void) const
    {
        matNM<T,h,w> result;
        int x, y;

        for (y = 0; y < w; y++)
        {
            for (x = 0; x < h; x++)
            {
                result[x][y] = data[y][x];
            }
        }

        return result;
    }

    static inline my_type identity()
    {
        my_type result(0);

        for (int i = 0; i < w; i++)
        {
            result[i][i] = 1;
        }

        return result;
    }

    static inline int width(void) { return w; }
    static inline int height(void) { return h; }

protected:
    // Column primary data (essentially, array of vectors)
    vecN<T,h> data[w];

    // Assignment function - called from assignment operator and copy constructor.
    inline void assign(const matNM& that)
    {
        int n;
        for (n = 0; n < w; n++)
            data[n] = that.data[n];
    }
};

/*
template <typename T, const int N>
class TmatN : public matNM<T,N,N>
{
public:
    typedef matNM<T,N,N> base;
    typedef TmatN<T,N> my_type;

    inline TmatN() {}
    inline TmatN(const my_type& that) : base(that) {}
    inline TmatN(float f) : base(f) {}
    inline TmatN(const vecN<T,4>& v) : base(v) {}

    inline my_type transpose(void)
    {
        my_type result;
        int x, y;

        for (y = 0; y < h; y++)
        {
            for (x = 0; x < h; x++)
            {
                result[x][y] = data[y][x];
            }
        }

        return result;
    }
};
*/

template <typename T>
class Tmat3 ;

template <typename T>
class Tmat4 : public matNM<T,4,4>
{
public:
    typedef matNM<T,4,4> base;
    typedef Tmat4<T> my_type;

    inline Tmat4() {}
    inline Tmat4(const my_type& that) : base(that) {}
    inline Tmat4(const base& that) : base(that) {}
    inline Tmat4(const vecN<T,4>& v) : base(v) {}
    inline Tmat4(const vecN<T,4>& v0,
                 const vecN<T,4>& v1,
                 const vecN<T,4>& v2,
                 const vecN<T,4>& v3)
    {
        base::data[0] = v0;
        base::data[1] = v1;
        base::data[2] = v2;
        base::data[3] = v3;
    }

    inline Tmat4(uint32_t* pHexFloats)
    {
        for (int n = 0; n < 4; n++)
        {
            for (int m = 0; m < 4; m++)
            {
                base::data[n][m] = *(T*)(pHexFloats + n * 4 + m);
            }
        }
    }
};

typedef Tmat4<float> mat4;
typedef Tmat4<int> imat4;
typedef Tmat4<unsigned int> umat4;
typedef Tmat4<double> dmat4;

template <typename T>
class Tmat3 : public matNM<T,3,3>
{
public:
    typedef matNM<T,3,3> base;
    typedef Tmat3<T> my_type;

    inline Tmat3() {}
    inline Tmat3(const my_type& that) : base(that) {}
    inline Tmat3(const base& that) : base(that) {}
    inline Tmat3(const vecN<T,3>& v) : base(v) {}
    inline Tmat3(const vecN<T,3>& v0,
                 const vecN<T,3>& v1,
                 const vecN<T,3>& v2)
    {
        base::data[0] = v0;
        base::data[1] = v1;
        base::data[2] = v2;
    }
    
    //from Tmat4<T>
    inline Tmat3(const Tmat4<T> & v)
    {
        for (int n = 0; n < 3; n++)
        {
            for (int m = 0; m < 3; m++)
            {
                base::data[n][m] = v[n][m];
            }
        }
    }

    inline Tmat3(uint32_t* pHexFloats)
    {
        for (int n = 0; n < 3; n++)
        {
            for (int m = 0; m < 3; m++)
            {
                base::data[n][m] = *(T*)(pHexFloats + n * 3 + m);
            }
        }
    }
};

typedef Tmat3<float> mat3;
typedef Tmat3<int> imat3;
typedef Tmat3<unsigned int>umat3;
typedef Tmat3<double> dmat3;

template <typename T>
class Tmat2 : public matNM<T,2,2>
{
public:
    typedef matNM<T,2,2> base;
    typedef Tmat2<T> my_type;

    inline Tmat2() {}
    inline Tmat2(const my_type& that) : base(that) {}
    inline Tmat2(const base& that) : base(that) {}
    inline Tmat2(const vecN<T,2>& v) : base(v) {}
    inline Tmat2(const vecN<T,2>& v0,
                 const vecN<T,2>& v1)
    {
        base::data[0] = v0;
        base::data[1] = v1;
    }

    //from Tmat4<T>
    inline Tmat2(const Tmat4<T>& v)
    {
        for (int n = 0; n < 2; n++)
        {
            for (int m = 0; m < 2; m++)
            {
                base::data[n][m] = v[n][m];
            }
        }
    }

    //from Tmat3<T>
    inline Tmat2(const Tmat3<T>& v)
    {
        for (int n = 0; n < 2; n++)
        {
            for (int m = 0; m < 2; m++)
            {
                base::data[n][m] = v[n][m];
            }
        }
    }

    inline Tmat2(uint32_t* pHexFloats)
    {
        for (int n = 0; n < 2; n++)
        {
            for (int m = 0; m < 2; m++)
            {
                base::data[n][m] = *(T*)(pHexFloats + n * 2 + m);
            }
        }
    }
};

typedef Tmat2<float> mat2;
typedef Tmat2<int> imat2;

static inline mat4 frustum(float left, float right, float bottom, float top, float n, float f)
{
    mat4 result(mat4::identity());

    if ((right == left) ||
        (top == bottom) ||
        (n == f) ||
        (n < 0.0) ||
        (f < 0.0))
       return result;

    result[0][0] = (2.0f * n) / (right - left);
    result[1][1] = (2.0f * n) / (top - bottom);

    result[2][0] = (right + left) / (right - left);
    result[2][1] = (top + bottom) / (top - bottom);
    result[2][2] = -(f + n) / (f - n);
    result[2][3]= -1.0f;

    result[3][2] = -(2.0f * f * n) / (f - n);
    result[3][3] =  0.0f;

    return result;
}

static inline mat4 viewport(float x, float y, float width, float height, float n = 0, float f = 1, bool y_invert = false, float fb_height = 0)
{
    mat4 result;

    result[0] = vec4(width/2, 0.0f, 0.0f, 0.0f);
    result[1] = vec4(0.0f, height/2, 0.0f, 0.0f);
    result[2] = vec4(0.0f, 0.0f, (f - n) / 2.0f, 0.0f);
    result[3] = vec4(x + width / 2.0f, y + height / 2, (f + n) / 2, 1.0f);

    if (y_invert)
    {
        result[1][1] = result[1][1] * -1;
        result[3][1] = fb_height - result[3][1];
    }

    return result;
}

static inline mat4 perspective(float fovy, float aspect, float n, float f)
{
    float q = 1.0f / tan(radians(0.5f * fovy));
    float A = q / aspect;
    float B = (n + f) / (n - f);
    float C = (2.0f * n * f) / (n - f);

    mat4 result;

    result[0] = vec4(A, 0.0f, 0.0f, 0.0f);
    result[1] = vec4(0.0f, q, 0.0f, 0.0f);
    result[2] = vec4(0.0f, 0.0f, B, -1.0f);
    result[3] = vec4(0.0f, 0.0f, C, 0.0f);

    return result;
}

static inline mat4 ortho(float left, float right, float bottom, float top, float n, float f)
{
    return mat4( vec4(2.0f / (right - left), 0.0f, 0.0f, 0.0f),
                 vec4(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f),
                 vec4(0.0f, 0.0f, 2.0f / (n - f), 0.0f),
                 vec4((left + right) / (left - right), (bottom + top) / (bottom - top), (n + f) / (f - n), 1.0f) );
}

template <typename T>
static inline Tmat4<T> translate(T x, T y, T z)
{
    return Tmat4<T>(Tvec4<T>(1.0f, 0.0f, 0.0f, 0.0f),
                    Tvec4<T>(0.0f, 1.0f, 0.0f, 0.0f),
                    Tvec4<T>(0.0f, 0.0f, 1.0f, 0.0f),
                    Tvec4<T>(x, y, z, 1.0f));
}

template <typename T>
static inline Tmat4<T> translate(const vecN<T,3>& v)
{
    return translate(v[0], v[1], v[2]);
}

template <typename T>
static inline Tmat4<T> lookat(const vecN<T,3>& eye, const vecN<T,3>& center, const vecN<T,3>& up)
{
    const Tvec3<T> f = normalize(center - eye);
    const Tvec3<T> upN = normalize(up);
    const Tvec3<T> s = cross(f, upN);
    const Tvec3<T> u = cross(s, f);
    const Tmat4<T> M = Tmat4<T>(Tvec4<T>(s[0], u[0], -f[0], T(0)),
                                Tvec4<T>(s[1], u[1], -f[1], T(0)),
                                Tvec4<T>(s[2], u[2], -f[2], T(0)),
                                Tvec4<T>(T(0), T(0), T(0), T(1)));

    return M * translate<T>(-eye);
}

template <typename T>
static inline Tmat4<T> scale(T x, T y, T z)
{
    return Tmat4<T>(Tvec4<T>(x, 0.0f, 0.0f, 0.0f),
                    Tvec4<T>(0.0f, y, 0.0f, 0.0f),
                    Tvec4<T>(0.0f, 0.0f, z, 0.0f),
                    Tvec4<T>(0.0f, 0.0f, 0.0f, 1.0f));
}

template <typename T>
static inline Tmat4<T> scale(const Tvec3<T>& v)
{
    return scale(v[0], v[1], v[2]);
}

template <typename T>
static inline Tmat4<T> scale(T x)
{
    return Tmat4<T>(Tvec4<T>(x, 0.0f, 0.0f, 0.0f),
                    Tvec4<T>(0.0f, x, 0.0f, 0.0f),
                    Tvec4<T>(0.0f, 0.0f, x, 0.0f),
                    Tvec4<T>(0.0f, 0.0f, 0.0f, 1.0f));
}

template <typename T>
static inline Tmat4<T> rotate(T angle, T x, T y, T z)
{
    Tmat4<T> result;

    const T x2 = x * x;
    const T y2 = y * y;
    const T z2 = z * z;
    float rads = float(angle) * 0.0174532925f;
    const float c = cosf(rads);
    const float s = sinf(rads);
    const float omc = 1.0f - c;

    result[0] = Tvec4<T>(T(x2 * omc + c), T(y * x * omc + z * s), T(x * z * omc - y * s), T(0));
    result[1] = Tvec4<T>(T(x * y * omc - z * s), T(y2 * omc + c), T(y * z * omc + x * s), T(0));
    result[2] = Tvec4<T>(T(x * z * omc + y * s), T(y * z * omc - x * s), T(z2 * omc + c), T(0));
    result[3] = Tvec4<T>(T(0), T(0), T(0), T(1));

    return result;
}

template <typename T>
static inline Tmat4<T> rotate(T angle, const vecN<T,3>& v)
{
    return rotate<T>(angle, v[0], v[1], v[2]);
}

template <typename T>
static inline Tmat4<T> rotate(T angle_x, T angle_y, T angle_z)
{
    return rotate(angle_z, 0.0f, 0.0f, 1.0f) *
           rotate(angle_y, 0.0f, 1.0f, 0.0f) *
           rotate(angle_x, 1.0f, 0.0f, 0.0f);
}

template <typename T, const int N, const int M>
static inline matNM<T,N,M> matrixCompMult(const matNM<T,N,M>& x, const matNM<T,N,M>& y)
{
    matNM<T,N,M> result;
    int i, j;

    for (j = 0; j < M; ++j)
    {
        for (i = 0; i < N; ++i)
        {
            result[i][j] = x[i][j] * y[i][j];
        }
    }

    return result;
}

template <typename T, const int N, const int M>
static inline vecN<T,N> operator*(const vecN<T,M>& vec, const matNM<T,N,M>& mat)
{
    int n, m;
    vecN<T,N> result(T(0));

    for (m = 0; m < M; m++)
    {
        for (n = 0; n < N; n++)
        {
            result[n] += vec[m] * mat[n][m];
        }
    }

    return result;
}

template <typename T, const int N, const int M>
static inline vecN<T, M> operator*(const matNM<T, N, M>& mat, const vecN<T, N>& vec)
{
    int n, m;
    vecN<T, N> result(T(0));

    for (m = 0; m < M; m++)
    {
        for (n = 0; n < N; n++)
        {
            result[m] += vec[n] *  mat[n][m];
        }
    }

    return result;
}

template <typename T, const int N>
static inline vecN<T,N> operator/(const T s, const vecN<T,N>& v)
{
    int n;
    vecN<T,N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = s / v[n];
    }

    return result;
}

/*
template <typename T>
static inline void quaternionToMatrix(const Tquaternion<T>& q, matNM<T,4,4>& m)
{
    m[0][0] = q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
    m[0][1] = T(2) * (q[1] * q[2] + q[0] * q[3]);
    m[0][2] = T(2) * (q[1] * q[3] - q[0] * q[2]);
    m[0][3] = 0.0f;

    m[1][0] = T(2) * (q[1] * q[2] - q[0] * q[3]);
    m[1][1] = q[0] * q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
    m[1][2] = T(2) * (q[2] * q[3] + q[0] * q[1]);
    m[1][3] = 0.0f;

    m[2][0] = T(2) * (q[1] * q[3] + q[0] * q[2]);
    m[2][1] = T(2) * (q[2] * q[3] - q[0] * q[1]);
    m[2][2] = q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}
*/

template <typename T>
static inline void quaternionToMatrix(const Tquaternion<T>& q, matNM<T,4,4>& m)
{
    m = q.asMatrix();
}

//shader api

#ifdef min
#undef min
#endif

template <typename T>
static inline T min(T a, T b)
{
    return a < b ? a : b;
}

#ifdef max
#undef max
#endif

template <typename T>
static inline T max(T a, T b)
{
    return a >= b ? a : b;
}

template <typename T, const int N>
static inline vecN<T, N> minv(const vecN<T, N>& x, const vecN<T, N>& y)
{
    vecN<T, N> t;
    int n;

    for (n = 0; n < N; n++)
    {
        t[n] = min(x[n], y[n]);
    }

    return t;
}

template <typename T, const int N>
static inline vecN<T, N> maxv(const vecN<T, N>& x, const vecN<T, N>& y)
{
    vecN<T, N> t;
    int n;

    for (n = 0; n < N; n++)
    {
        t[n] = max<T>(x[n], y[n]);
    }

    return t;
}

template <typename T, const int N>
static inline vecN<T, N> maxv(const vecN<T, N>& x, const float value)
{
    vecN<T, N> t;
    int n;

    for (n = 0; n < N; n++)
    {
        t[n] = max<T>(x[n], value);
    }

    return t;
}

template <typename T, const int N>
static inline vecN<T, N> minv(const vecN<T, N>& x, const float value)
{
    vecN<T, N> t;
    int n;

    for (n = 0; n < N; n++)
    {
        t[n] = min<T>(x[n], value);
    }

    return t;
}

template <typename T>
static inline T pow(T a, T b)
{
    return (T)powf((float)a, (float)b);
}

template <typename T, const int N>
static inline vecN<T, N> powv(const vecN<T, N>& x, const vecN<T, N>& y)
{
    vecN<T, N> t;
    int n;

    for (n = 0; n < N; n++)
    {
        t[n] = pow<T>(x[n], y[n]);
    }

    return t;
}

template <typename T, const int N>
static inline vecN<T, N> clamp(const vecN<T, N>& x, const vecN<T, N>& minVal, const vecN<T, N>& maxVal)
{
    return min<T>(max<T>(x, minVal), maxVal);
}

template <typename T, const int N>
static inline vecN<T, N> smoothstep(const vecN<T, N>& edge0, const vecN<T, N>& edge1, const vecN<T, N>& x)
{
    vecN<T, N> t;
    t = clamp((x - edge0) / (edge1 - edge0), vecN<T, N>(T(0)), vecN<T, N>(T(1)));
    return t * t * (vecN<T, N>(T(3)) - vecN<T, N>(T(2)) * t);
}

template <typename T, const int S>
static inline vecN<T, S> reflect(const vecN<T, S>& I, const vecN<T, S>& N)
{
    return I - 2 * dot(N, I) * N;
}

template <typename T, const int S>
static inline vecN<T, S> refract(const vecN<T, S>& I, const vecN<T, S>& N, const T eta)
{
    T d = dot(N, I);
    T k = T(1) - eta * eta * (T(1) - d * d);
    if (k < 0.0)
    {
        return vecN<T, S>(0);
    }
    else
    {
        return eta * I - (eta * d + sqrt(k)) * N;
    }
}

template <typename T>
static inline T mix(const T& A, const T& B, const float t)
{
    return A * (1 - t) + B * t;
}

template <typename T, const int N>
static inline vecN<T, N> mixv(const vecN<T, N> &a, const vecN<T, N> &b, const float t)
{
    int n;
    vecN<T, N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = mix<T>(a[n], b[n], t);
    }

    return result;
}

template <typename T, const int N>
static inline vecN<T, N> mixv(const vecN<T, N> &a, const vecN<T, N> &b, const vecN<float, N> &t)
{
    int n;
    vecN<T, N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = mix<T>(a[n], b[n], t[n]);
    }

    return result;
}

template <typename T>
static inline T clamp(const T& x, const T& minVal, const T& maxVal)
{
    return min<T>(max<T>(x, minVal), maxVal);
}

template <typename T>
static inline T mod(const T& x, const T& y)
{
    return x - y * ::floorf(1.0f * x / y);
}

/*
genFType t;
t = clamp ((x - edge0) / (edge1 - edge0), 0, 1);
return t * t * (3 - 2 * t);*/
static inline float smoothstep(const float edge0, const float edge1, const float x)
{
    float t = (x - edge0) / (edge1 - edge0);
    t = std::max(0.0f, t);
    t = std::min(1.0f, t);
    return t * t * (3 - 2 * t);
}

static inline float fract(const float x)
{
    float t = x - ::floorf(x);
    return t;
}

template <typename T, const int N>
static inline vecN<T, N> fractv(const vecN<T, N> &v)
{
    int n;
    vecN<T, N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = fract((float)v[n]);
    }

    return result;
}

static inline float floor(float x)
{
    return ::floorf(x);
}

template <typename T, const int N>
static inline vecN<T, N> floorv(const vecN<T, N> &v)
{
    int n;
    vecN<T, N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = floor((float)v[n]);
    }

    return result;
}

template <typename T>
static inline T abs(T a)
{
    return ::abs(a);
}

template <typename T, const int N>
static inline vecN<T, N> absv(const vecN<T, N> &v)
{
    int n;
    vecN<T, N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = abs<T>(v[n]);
    }

    return result;
}

template <typename T>
static inline T sin(const T a)
{
    Sfu sfu(false);
    float f = sfu.sin(a);

    return f;
    //return ::sin(a);
}

template <typename T, const int N>
static inline vecN<T, N> sinv(const vecN<T, N> &v)
{
    int n;
    vecN<T, N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = sin<T>(v[n]);
    }

    return result;
}

template <typename T>
static inline T cos(T a)
{
    Sfu sfu(false);
    float f = sfu.cos(a);

    return f;
    //return ::cos(a);
}

template <typename T, const int N>
static inline vecN<T, N> cosv(const vecN<T, N> &v)
{
    int n;
    vecN<T, N> result;

    for (n = 0; n < N; n++)
    {
        result[n] = cos<T>(v[n]);
    }

    return result;
}

static inline uint32_t packHalf2x16(const vec2 &v)
{
    return (fp16_ieee_from_fp32_value(v[1])<<16) | fp16_ieee_from_fp32_value(v[0]);
}

static inline vec2 unpackHalf2x16(const uint32_t v)
{
    return vec2(fp16_ieee_to_fp32_value(v & 0xFFFF), fp16_ieee_to_fp32_value((v >> 16) & 0xFFFF));
}

};

#endif /* __VMATH_H__ */
