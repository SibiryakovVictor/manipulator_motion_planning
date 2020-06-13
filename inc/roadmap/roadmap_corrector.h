#pragma once


#include "roadmap_controller.h"
#include "typedefs.h"



namespace motion_planner
{

    class RoadmapCorrector
    {

    public:

        explicit RoadmapCorrector( RoadmapController & roadmap ) :
            m_roadmap( roadmap )
        {}

        void removeConflictingNode( NodeId nodePos );

        void removeConflictingEdge( NodeId nodePos, EdgeId edgePos );

        bool fixRoadmap();

        void reset();

    private:

        static const uint16_t nodes_addition = 20;
        static const uint16_t nodes_replacement = 30;
        static const uint16_t attempts_limit = 5;

        RoadmapController & m_roadmap;

        uint16_t m_attempts = 0;

        void removeRandomNodes( uint16_t amountNodes );

        void reinitializeRoadmap();

    };

}

