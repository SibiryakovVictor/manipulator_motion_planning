#include "path/path_finder.h"




using namespace motion_planner::path;



uint16_t PathFinder::findShortestPath( motion_planner::path::Path & pathData )
{

    uint16_t supposedPathLength = m_pathFinder.findShortestPath( pathData,
        m_roadmap.getNodesList(), m_roadmap.getEdgesList() );

    float distPath = calcSumPathLength( pathData );

    while ( ( distPath / m_refDist ) > path::length_tolerance )
    {
        std::fill( pathData.sections, pathData.sections + supposedPathLength,
            PathElement{ UINT16_MAX, UINT8_MAX } );

        reinitializeRoadmap( m_start, m_goal );

        supposedPathLength = m_pathFinder.findShortestPath( pathData,
            m_roadmap.getNodesList(), m_roadmap.getEdgesList() );

        distPath = calcSumPathLength( pathData );    
    }

    return supposedPathLength;

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



void PathFinder::reinitializeRoadmap( 
    const config_space::Point & start, 
    const config_space::Point & goal )
{

    m_roadmap.m_graph.reset();

    m_roadmap.initializeRoadmap( start, goal );

}



void PathFinder::reset()
{
    config_space::Point m_start = m_roadmap.m_graph.getNodeConfig( 0 );
    config_space::Point m_goal = m_roadmap.m_graph.getNodeConfig( 1 );

    m_refDist = config_space::Point::calcDistance(
        m_roadmap.m_graph.getNodeConfig( 0 ),
        m_roadmap.m_graph.getNodeConfig( 1 )
    );
}
