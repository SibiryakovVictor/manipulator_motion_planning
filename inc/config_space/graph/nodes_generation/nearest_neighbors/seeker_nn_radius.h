#pragma once

#include "i_seeker_nearest_neighbors.h"
#include "config_space/graph/i_nodes_list.h"
#include "roadmap/roadmap_parameters.h"




namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            class SeekerNNRadius : public ISeekerNN
            {

            public:

                explicit SeekerNNRadius( float radius = roadmap::radius_limit_nn ) :
                    m_radius( radius )
                {}

                void seekNearestNeighbors( const Point & refPoint, 
                                           const INodesList & nodeList );

            private:

                float m_radius;

            };

        }

    }

}

