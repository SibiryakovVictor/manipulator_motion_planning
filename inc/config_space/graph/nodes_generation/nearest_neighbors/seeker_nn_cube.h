#pragma once


#include "i_seeker_nearest_neighbors.h"
#include "intervals.h"
#include "roadmap/roadmap_parameters.h"



namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            class SeekerNNCube : public ISeekerNN
            {

            public:

                explicit SeekerNNCube( float edgeCube = roadmap::radius_limit_nn ) :
                    m_edgeCube( edgeCube )
                {}

                void seekNearestNeighbors( const Point & refPoint, 
                                           const INodesList & listPoints );

            private:

                IntervalsAllDims m_intervals;

                float m_edgeCube;

                IntervalsAllDims constructCubeInterval( const Point & refPoint );

                bool isPointInCube( const Point & p );

            };

        }

    }

}


