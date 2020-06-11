#include "float_operations.h"

#include <random>



float flt_op::getRandomFloat( float lowLimit, float highLimit )
{
    //static std::random_device rd; 
    static std::mt19937 gen;

    std::uniform_real_distribution< float > dis( lowLimit, highLimit );

    return dis( gen );
}



float flt_op::cvtDegToRad( float degrees )
{

    static const float coeffDegToRad = flt_op::mathPI / 180.f;

    return degrees * coeffDegToRad;

}
