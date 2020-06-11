#include "motion_planner.h"

#include "env/env_def.h"
#include "roadmap/roadmap_parameters.h"





void motion_planner::MotionPlanner::findPath( config_space::Point startConfig, config_space::Point goalConfig )
{
    m_isPathFound = false;

    m_roadmap.reset();

    m_roadmap.initializeRoadmap( startConfig, goalConfig );

    m_corrector.reset();

    m_pathTraversal.reset();

    m_pathCreator.reset();

    uint16_t supposedPathLength = m_pathCreator.findShortestPath( m_pathTraversal.getPathStorage() );
    bool isPathFound = false;

    while ( ! isPathFound )
    {

        while ( supposedPathLength )
        {
            m_pathTraversal.setPathLength( supposedPathLength );

            if ( isPathValid() )
            {
                m_pathTraversal.resetPointGetter();

                m_isPathFound = true;

                return;
            }

            m_pathTraversal.reset();

            supposedPathLength = m_pathCreator.findShortestPath( m_pathTraversal.getPathStorage() );
        }

        do
        {

            bool isRoadmapRebuilt = m_corrector.fixRoadmap();

            if ( isRoadmapRebuilt )
            {
                break;
            }

            m_visitor.executeTraversal( roadmap::start_node_pos, m_roadmap.getEdgesList() );

        } while ( ! m_visitor.isNodeVisited( roadmap::goal_node_pos ) );

        m_pathTraversal.reset();

        supposedPathLength = m_pathCreator.findShortestPath( m_pathTraversal.getPathStorage() );

    }



}




bool motion_planner::MotionPlanner::isPathValid()
{

    NodeId resultCheckNodes = m_pathVerifier.checkNodesForCollision( m_pathTraversal );
    if ( resultCheckNodes != UINT16_MAX )
    {

        m_corrector.removeConflictingNode( resultCheckNodes );

        return false;

    } 


    path::PathElement resultCheckEdges = m_pathVerifier.checkEdgesForCollision( m_pathTraversal );
    if ( resultCheckEdges.segment != UINT8_MAX )
    {

        m_corrector.removeConflictingEdge( resultCheckEdges.point, resultCheckEdges.segment );

        return false;

    }    

    return true;

}




bool motion_planner::MotionPlanner::isPathFound() const
{
    return m_isPathFound;
}




config_space::Point motion_planner::MotionPlanner::getPointTraj()
{
    return m_pathTraversal.getNextPointPath();
}

void motion_planner::MotionPlanner::resetPath()
{
    m_pathTraversal.resetPointGetter();
}
