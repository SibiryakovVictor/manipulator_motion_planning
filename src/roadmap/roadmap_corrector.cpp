#include "roadmap/roadmap_corrector.h"
#include "float_operations.h"


using namespace motion_planner;




void RoadmapCorrector::removeConflictingNode( NodeId nodePos )
{
    m_roadmap.m_graph.removeNode( nodePos );
}



void RoadmapCorrector::removeConflictingEdge( NodeId nodePos, EdgeId edgePos )
{
    m_roadmap.m_graph.removeEdge( nodePos, edgePos );
}





bool RoadmapCorrector::fixRoadmap()
{

    if ( ( ( roadmap::capacity - 2 ) - m_roadmap.m_graph.getNodesAmount() )
        > nodes_addition )
    {
        m_roadmap.fillRoadmapRandomNodes( nodes_addition );

        return false;
    }

    if ( ( m_attempts < attempts_limit )
        && ( ( m_roadmap.m_graph.getNodesAmount() + 2 ) > nodes_replacement ) )
    {
        m_attempts++;

        removeRandomNodes( nodes_replacement );

        m_roadmap.fillRoadmapRandomNodes( nodes_replacement );

        return false;
    }

    m_attempts = 0;

    reinitializeRoadmap();

    return true;
}



void RoadmapCorrector::removeRandomNodes( uint16_t amountNodes )
{

    while ( amountNodes != 0 )
    {
        NodeId removingNode = 0;

        do 
        {

            removingNode = flt_op::getRandomFloat( 2, m_roadmap.m_graph.getNodesAmount() - 1 );

        } while ( ! m_roadmap.m_graph.isNodeInserted( removingNode ) );

        m_roadmap.m_graph.removeNode( removingNode );

        amountNodes--;
    }

}




void RoadmapCorrector::reinitializeRoadmap()
{
    m_roadmap.m_graph.reset();

    m_roadmap.initializeRoadmap( m_roadmap.getStart(), m_roadmap.getGoal() );
}




void RoadmapCorrector::reset()
{
    m_attempts = 0;
}
