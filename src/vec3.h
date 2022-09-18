/*
--------------------------------------------------------------------------------------------------------------------------
Implementing a 3 dimensional vector class with the following functions:

Negation: (does not modify object) return negative value of vector
Addition to another vector: (does modify object)
Scalar multiplication: (does modify object)
Indexing: (const and non-const versions)
Get Length: (does not modify object)

--------------------------------------------------------------------------------------------------------------------------
*/
#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

using std::sqrt;

class vec3 {

public:

    double e[3];

    //Constructors
    vec3() : e{ 0, 0, 0 } {} //Member initialiser lists
    vec3(double e1, double e2, double e3) : e{ e1, e2, e3 } {}

    //Getting individual components of vector (class methods)
    double x() const { //Declarations are const as we don't want these methods to change the class member 
        return e[0];
    }
    double y() const {
        return e[1];
    }
    double z() const {
        return e[2];
    }

    //Operator overloading 
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } //We don't want to modify the class body, so we use a const function body
    vec3& operator+=(const vec3& v) { //We want to modify the class member here, so we return a reference to the object, so it can be updated automatically with the += operation
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }
    vec3& operator *=(const double t) { //t not passed by reference as there's no real penalty in copying the value of a double.
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }
    vec3& operator /=(const double t) {
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;

        return *this;
    }

    double operator[](int i) const { return e[i]; } //Here we don't want to modify the value of a const object, so we don't bother with references. Just returns value.
    double& operator[](int i) { return e[i]; } //Reference of class object here, as we may want to modify this through something like v[0] = 10
    double length() const { return sqrt(length_squared()); }
    double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

};

using point3 = vec3;
using colour = vec3;


//Utility functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif