#pragma once



#include "env/info_loader/info_loader.h"
#include "env/manipulator.h"
#include "env/obstacles.h"
#include "collision_detector.h"
#include "config_space/graph/i_nodes_list.h"
#include "config_space/graph/i_edges_list.h"
#include "path/path_traversal.h"
#include "config_space/segment.h"
#include "typedefs.h"
#include "path/path_def.h"
#include "collision_check_pairs.h"




namespace motion_planner
{
    class MotionPlanner;

    namespace path
    {

        class PathVerifier
        {

        public:

            friend class motion_planner::MotionPlanner;

            explicit PathVerifier( const config_space::graph::INodesList & nodesList,
                                   const config_space::graph::IEdgesList & edgesList ) :
                m_nodesList( nodesList ),
                m_edgesList( edgesList ),
                m_manip( env::load::getManipInitInfo() ),
                m_obst( env::load::getObstInitInfo() ),
                m_collDetect()
            {}


            NodeId checkNodesForCollision( const path::PathTraversal & path );

            path::PathElement checkEdgesForCollision( const path::PathTraversal & path );




        private:

            static const float threshold_config_change;

            env::ManipulatorController m_manip;

            env::Obstacles m_obst;

            coll::CollisionDetector m_collDetect;

            const config_space::graph::INodesList & m_nodesList;
            const config_space::graph::IEdgesList & m_edgesList;


            bool isSegmentValid( const config_space::Segment & segment, const float pointsCheck );

            bool isConfigValid( const config_space::Point & config );

            bool isConfigCorrect( const config_space::Point & conf );

            bool checkManipVsManip( uint16_t id1, uint16_t id2 ) const;
            bool checkManipVsObst( uint16_t manipId, uint16_t obstId ) const;

            bool checkGroupVsLink( uint16_t groupId, uint16_t linkId ) const;
            bool checkGroupVsGroup( uint16_t groupId1, uint16_t groupId2 ) const;
            bool checkGroupVsObst( uint16_t groupId, uint16_t obstId ) const;

            uint16_t moveToNextGroup( uint16_t pairPos, uint16_t confPos ) const;

            env::ManipulatorController & getLinksContainer();
            env::Obstacles & getObstsContainer();
        };

    }

}
