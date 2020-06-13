#include "config_space/point.h"
#include "float_operations.h"

#include <algorithm>

using namespace config_space;



float config_space::Point::calcDistance( const config_space::Point & p1,

                                         const config_space::Point & p2 )
{

    return std::sqrtf( 
        std::inner_product( p1.begin(), p1.end(), p2.begin(), 0.f,
            []( float arg, float result ){ return result + arg; },
            [](float arg1, float arg2){ return std::powf( ( arg1 - arg2 ), 2.f ); } )
    );

}


float config_space::Point::calcDistNoSqrt( const config_space::Point & p1,

                                         const config_space::Point & p2 )
{

    return std::inner_product( p1.begin(), p1.end(), p2.begin(), 0.f,
        []( float arg, float result ){ return result + arg; },
        [](float arg1, float arg2) 
        {

            float diff = arg1 - arg2;

            return diff * diff; 
            
        } );

}




void config_space::cvtDegsToRads( config_space::Point & p )
{

    static const float coeffDegToRad = 3.141592653589793238462643f / 180.f;

    std::for_each( p.begin(), p.end(), []( float & curDim ) 
    { 
        curDim = flt_op::cvtDegToRad( curDim );
    } );

}




void Point::alignToGrid( const float gridSize )
{

    std::for_each( m_pointData.dimensionValues,
                   m_pointData.dimensionValues + conf_space_dims,
        [ &gridSize ](float & arg)
        {
            arg = std::roundf( arg / gridSize ) * gridSize;
        } );

}



bool config_space::operator==( const Point & p1, const Point & p2 )
{
    static const float threshold_points_equal = 0.01f;

    return Point::calcDistance( p1, p2 ) < threshold_points_equal;
}

