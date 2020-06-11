#pragma once


#include "config_space/point.h"



namespace config_space
{

    namespace point
    {

        class IMakerRandomPoints
        {

        public:

            virtual ~IMakerRandomPoints() {}

            virtual Point make( const Point & refPoint ) const = 0;

        };

    }

}

