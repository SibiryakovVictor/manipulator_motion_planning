#include "motion_planner.h"

#include "env/env_def.h"
#include "roadmap/roadmap_parameters.h"





void motion_planner::MotionPlanner::findPath( config_space::Point startConfig, config_space::Point goalConfig )
{
    setup( startConfig, goalConfig );

    setNewPath();

    while ( ! m_isPathFound )
    {
        while ( m_pathTraversal.getPointsAmount() )
        {
            if ( isPathValid() )
            {
                m_pathTraversal.resetPointGetter();

                m_isPathFound = true;

                return;
            }

            setNewPath();
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

        setNewPath();
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



bool motion_planner::MotionPlanner::isPathPassed() const
{
    return m_pathTraversal.isPathPassed();
}



void motion_planner::MotionPlanner::setup( const config_space::Point & start, 
                                           const config_space::Point & goal )
{
    m_isPathFound = false;

    m_roadmap.reset();

    m_roadmap.initializeRoadmap( start, goal );

    m_corrector.reset();

    m_pathCreator.reset();
}



void motion_planner::MotionPlanner::setNewPath()
{
    m_pathTraversal.reset();

    uint16_t pointsAmount = m_pathCreator.findShortestPath( m_pathTraversal.getPathStorage() );

    m_pathTraversal.setPointsAmount( pointsAmount );
}
