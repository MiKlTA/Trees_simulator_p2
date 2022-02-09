#ifndef H_INTERPOLATION
#define H_INTERPOLATION



template<typename T>
T linearNInterp(T v1, T v2, float t)
{
    return (1 - t) * v1 + t * v2;
}

template<typename X_t, typename Y_t>
float linearInterp(float y1, float x1, float y2, float x2, float x)
{
    float dx = x2 - x1;
    if (dx == 0.0f)
        dx += __FLT_MIN__;
    return y1 + (x - x1) * (y2 - y1)/dx;
}



#endif // H_INTERPOLATION
