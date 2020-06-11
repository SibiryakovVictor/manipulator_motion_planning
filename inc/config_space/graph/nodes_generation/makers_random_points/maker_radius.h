#pragma once

#include "i_maker_random_points.h"
#include "intervals.h"
#include "roadmap/roadmap_parameters.h"


namespace config_space
{

    namespace point
    {

        class MakerRandomPointsRadius : public IMakerRandomPoints
        {

        public:

            explicit MakerRandomPointsRadius( float param = roadmap::generation_param ) :

                m_param( param )
            {}

            Point make( const Point & refPoint ) const;

        private:

            float m_param;

            IntervalsAllDims configureLimits( const config_space::Point & refPoint ) const;

        };

    }

}
