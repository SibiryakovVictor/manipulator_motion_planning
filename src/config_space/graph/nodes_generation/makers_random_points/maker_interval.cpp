#include "config_space/graph/nodes_generation/makers_random_points/maker_interval.h"

#include "float_operations.h"



config_space::Point config_space::point::MakerRandomPointsInterval::make( 
    const Point & refPoint ) const
{

    Point result;

    for ( uint16_t curDim = 0; curDim != conf_space_dims; curDim++ )
    {

        result[ curDim ] = flt_op::getRandomFloat( 
            m_ranges[ curDim ].getlb(), m_ranges[ curDim ].gethb() );

    }

    return result;

}
