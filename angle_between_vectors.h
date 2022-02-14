#ifndef H_ANGLE_BETWEEN_VECTORS
#define H_ANGLE_BETWEEN_VECTORS



#include <math.h>



template<typename T>
T fullAngle(T x, T y)
{
    float length = std::sqrt(x*x + y*y);
    
    if (y < 0.f)
        return M_PI + std::acos(-x / length);
    else
        return std::acos(x / length);
}

template<typename Vector_t, typename Result_t>
Result_t fullAngle(Vector_t v)
{
    return fullAngle(v.x, v.y);
}

template<typename T>
T vecAngle(T x1, T y1, T x2, T y2)
{
    return fullAngle(x2, y2) - fullAngle(x1, y1);
}

template<typename Vector_t, typename Result_t>
Result_t fullAngle(Vector_t v1, Vector_t v2)
{
    return fullAngle(v1.x, v1.y, v2.x, v2.y);
}



#endif // H_ANGLE_BETWEEN_VECTORS
