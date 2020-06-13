#include "path/path_finder.h"


using namespace motion_planner::path;




uint16_t PathFinder::findShortestPath( motion_planner::path::Path & pathData )
{
    uint16_t pointsAmount = m_pathFinder.findShortestPath( pathData,
        m_roadmap.getNodesList(), m_roadmap.getEdgesList() );

    float pathLength = calcSumPathLength( pathData );

    while ( ( pathLength / m_refPathLength ) > path::length_tolerance )
    {
        std::fill( pathData.sections, pathData.sections + pointsAmount,
            PathElement{ UINT16_MAX, UINT8_MAX } );

        reinitializeRoadmap();

        pointsAmount = m_pathFinder.findShortestPath( pathData,
            m_roadmap.getNodesList(), m_roadmap.getEdgesList() );

        pathLength = calcSumPathLength( pathData );    
    }

    return pointsAmount;
}




float PathFinder::calcSumPathLength( const motion_planner::path::Path & pathData  )
{
    float sumLength = 0.f;

    for ( uint16_t curElem = 0; pathData.sections[ curElem ].segment != UINT8_MAX; curElem++ )
    {
        sumLength += config_space::Point::calcDistance( 
            m_roadmap.m_graph.getNodeConfig( pathData.sections[ curElem ].point ),
            m_roadmap.m_graph.getNodeConfig( pathData.sections[ curElem + 1 ].point ) );
    }

    return sumLength;
}



void PathFinder::reinitializeRoadmap()
{
    m_roadmap.m_graph.reset();

    m_roadmap.initializeRoadmap( m_roadmap.getStart(), m_roadmap.getGoal() );
}



void PathFinder::reset()
{
    m_refPathLength = 
        config_space::Point::calcDistance( m_roadmap.getStart(), m_roadmap.getGoal() );
}
