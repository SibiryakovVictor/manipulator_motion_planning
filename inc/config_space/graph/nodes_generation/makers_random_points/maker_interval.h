#pragma once


#include "i_maker_random_points.h"

#include "intervals.h"


namespace config_space
{

    namespace point
    {

        class MakerRandomPointsInterval : public IMakerRandomPoints
        {

        public:

            explicit MakerRandomPointsInterval( 
                IntervalsAllDims ranges = settings::RangeLinksMotion::get() ) :
                
                m_ranges( ranges )

            {}

            Point make( const Point & refPoint ) const;

        private:

            const IntervalsAllDims m_ranges;

        };

    }

}

