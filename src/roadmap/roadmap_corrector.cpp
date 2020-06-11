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

    if ( ( roadmap::capacity - m_roadmap.m_graph.getNodesAmount() )
        > nodes_addition )
    {
        m_roadmap.fillRoadmapRandomNodes( nodes_addition );

        return false;
    }

    if (  m_attempts < attempts_limit )
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

            removingNode = flt_op::getRandomFloat( 0, m_roadmap.m_graph.getNodesAmount() - 1 );

        } while ( ( removingNode == roadmap::start_node_pos ) || 
            ( removingNode == roadmap::goal_node_pos ) );

        removeConflictingNode( removingNode );

        amountNodes--;
    }

}




void RoadmapCorrector::reinitializeRoadmap()
{

    m_roadmap.m_graph.reset();

    m_roadmap.initializeRoadmap( m_start, m_goal );

}




void RoadmapCorrector::reset()
{
    m_attempts = 0;

    m_start = m_roadmap.m_graph.getNodeConfig( 0 );

    m_goal = m_roadmap.m_graph.getNodeConfig( 1 );
}
