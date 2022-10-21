#include <game/Utils.hpp>

float Utils::radToDeg(float rad)
{
    return rad * (180.0 / PI);
}

float Utils::magnitudeOf(Vector2f vec)
{
    float res = vec.x * vec.x + vec.y * vec.y;
    if (res == 0)
        return 0;

    return sqrtf(res);
}

float Utils::angle(Vector2f vec1, Vector2f vec2)
{
    float angle = Utils::radToDeg(
        atan2f(
            vec1.y - vec2.y,
            vec1.x - vec2.x));

    if (angle < 0)
        angle = 360 + angle;

    return angle;
}

Vector2f& Utils::normalize(Vector2f &vec)
{
    float len = Utils::magnitudeOf(vec);
    if (vec.x != 0)
        vec.x /= len;
    if (vec.y != 0)
        vec.y /= len;

    return vec;
}

/*
template <typename T1, typename T2>
float Utils::detOf(Vector2<T1> vec1, Vector2<T2> vec2)
{
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

template <typename T1, typename T2>
float Utils::dotOf(Vector2<T1> vec1, Vector2<T2> vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

template <typename T>
void Utils::invert(Vector2<T> &vec)
{
    vec.x *= -1;
    vec.y *= -1;
}
*/
