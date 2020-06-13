#pragma once

#include "roadmap/roadmap_controller.h"
#include "config_space/graph/shortest_path_finder/a_star.h"


namespace motion_planner
{

    namespace path
    {

        class PathFinder
        {

        public:

            explicit PathFinder( RoadmapController & roadmap ) :
                m_roadmap( roadmap )
            {}

            uint16_t findShortestPath( path::Path & pathData );

            float calcSumPathLength( const path::Path & pathData );

            void reset();

        private:

            RoadmapController & m_roadmap;

            config_space::graph::shortest_path::Astar m_pathFinder;

            float m_refPathLength = 0.f;

            void reinitializeRoadmap();


        };

    }

}


