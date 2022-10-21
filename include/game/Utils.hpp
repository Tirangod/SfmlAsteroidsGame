#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <SFML/System.hpp>

using namespace sf;

/**
 * Допоміжний клас
 */
class Utils
{
public:
    static constexpr float PI = 3.14159274101257324219f;

    static float radToDeg(float rad);

    static float magnitudeOf(Vector2f vec);

    static float angle(Vector2f vec1, Vector2f vec2);
    
    static Vector2f& normalize(Vector2f &vec);

    /*
    template <typename T1, typename T2>
    static float detOf(Vector2<T1> vec1, Vector2<T2> vec2);

    template <typename T1, typename T2>
    static float dotOf(Vector2<T1> vec1, Vector2<T2> vec2);
    
    template <typename T>
    static void invert(Vector2<T> &vec);
    */

    template<typename T>
    static long hashOf(T value) {
        return std::hash<std::string>{}(value);
    }
    
};

#endif