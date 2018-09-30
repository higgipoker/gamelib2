/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#pragma once
#include <cmath>

namespace gamelib2 {

#define RADIANS(a) a *(PI / 180.0f)
#define DEGREES(a) a *(180.0f / PI)
static const float PI = 3.14159265359f;
static const float TOL = 0.001f;
enum INDEX { X = 0, Y = 1, Z = 2 };

// maybe move this somewhere else
namespace Floats {

static bool equal(float a, float b, float epsilon = 0.0001f) {
    return fabsf(a - b) <=
      ((fabsf(a) < fabsf(b) ? fabsf(b) : fabsf(a)) * epsilon);
}

static bool greater_than(float a, float b, float epsilon = 0.0001f) {
    return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

static bool less_than(float a, float b, float epsilon = 0.0001f) {
    return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

} // namespace Floats

//  ----------------------------------------------------------------------------
//
//  A class to represent a Vector
//
//  convention is to return a new vector for operation and not
//    mutate *this. Except for operator overloads, naturally
//
//  ----------------------------------------------------------------------------
class Vector3 {
public:
    // ---------------------------------------------------------------------------
    // components
    // ---------------------------------------------------------------------------
    float x = 0;
    float y = 0;
    float z = 0;

    // ---------------------------------------------------------------------------
    // construct / destruct / setter
    // ---------------------------------------------------------------------------
    Vector3(void) {
    }
    Vector3(float xi, float yi, float zi);
    Vector3(float xi, float yi);
    void reset();

    // ---------------------------------------------------------------------------
    // operators
    // ---------------------------------------------------------------------------
    float operator[](INDEX idx) const;
    Vector3 &operator+=(const Vector3 &rhs);
    Vector3 &operator-=(const Vector3 &rhs);
    Vector3 &operator*=(const Vector3 &rhs);
    Vector3 &operator*=(const float rhs);
    Vector3 &operator/=(const float rhs);
    const Vector3 operator+(const Vector3 &rhs) const;
    const Vector3 operator-(const Vector3 &rhs) const;
    const Vector3 operator*(const float rhs) const;
    const Vector3 operator/(const float rhs) const;
    const Vector3 operator^(Vector3 &v);
    float operator*(Vector3 &rhs);

    // ---------------------------------------------------------------------------
    // vector operations
    // ---------------------------------------------------------------------------
    Vector3 roundAngle(int nearest_angle);
    Vector3 normalise();
    Vector3 reflect(Vector3 &normal) const;
    Vector3 perpendicular();
    Vector3 polar(float mag, float radians);
    Vector3 setMagnitude(float mag);
    Vector3 unit(Vector3 v);
    Vector3 reverse(void);
    Vector3 normalizeToUnits();
    Vector3 rotate(float a, float x_origin = 0, float y_origin = 0) const;
    // ---------------------------------------------------------------------------
    // scaler operations
    // ---------------------------------------------------------------------------
    float projectionOn(Vector3 line);
    float perpProduct(const Vector3 &v, bool right_normal = true);
    float magnitude(void) const;
    float magnidude2d(void);
    float magSquared(void);
    float dotProduct(const Vector3 &v) const;
    float angle(void);

    // ---------------------------------------------------------------------------
    // comparison operations
    // ---------------------------------------------------------------------------
    bool equals(const Vector3 &v);
    bool equals(const Vector3 &v, float tolerancce);
    static bool isMovingTowards(Vector3 testPoint, Vector3 objectPosition,
                                Vector3 objectVelocity);
};

} // namespace gamelib2
