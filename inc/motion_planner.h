#pragma once


#include "intervals.h"
#include "path/path_traversal.h"
#include "path/path_finder.h"
#include "path/path_verifier/path_verifier.h"
#include "roadmap/roadmap_controller.h"
#include "roadmap/roadmap_corrector.h"
#include "roadmap/roadmap_explorer/roadmap_explorer.h"
#include "env/manipulator.h"
#include "env/obstacles.h"
#include "path/path_verifier/collision_detector.h"
#include "config_space/graph/shortest_path_finder/a_star.h"

#include "env/info_loader/info_loader.h"
#include "config_manager.h"





namespace motion_planner
{

    class MotionPlanner
    {

    public:

        ConfigManager _config;

        explicit MotionPlanner( float step ) :
            m_pathTraversal( m_roadmap.getNodesList(), step ),
            _config( m_pathVerifier.getLinksContainer(), m_pathVerifier.getObstsContainer() )
        {}


        void findPath( config_space::Point startConfig, config_space::Point goalConfig );

        bool isPathFound() const;

        bool isPathPassed() const;

        config_space::Point getPointTraj();

        void resetPath();

    private:

        RoadmapController m_roadmap;

        RoadmapCorrector m_corrector = RoadmapCorrector( m_roadmap );

        RoadmapExplorer m_visitor = RoadmapExplorer();

        path::PathTraversal m_pathTraversal;

        path::PathFinder m_pathCreator = path::PathFinder( m_roadmap );

        path::PathVerifier m_pathVerifier = 
            path::PathVerifier( m_roadmap.getNodesList(), m_roadmap.getEdgesList() );

        bool m_isPathFound = false;

        bool isPathValid();

        void setup( const config_space::Point & start, const config_space::Point & goal );

        void setNewPath();
    };

}
