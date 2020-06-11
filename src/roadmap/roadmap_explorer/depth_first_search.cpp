#include "roadmap/roadmap_explorer/depth_first_search.h"
#include "roadmap/roadmap_parameters.h"

using namespace roadmap;




void DepthFirstSearch::executeTraversal( NodeId startNodePos,
    const config_space::graph::IEdgesList & edgesList )
{

    std::fill( m_visited, m_visited + roadmap::capacity, false );

    tools::Stack< NodeId, roadmap::capacity * 10 > stack;

    NodeId curNodePos = startNodePos;

    stack.push( curNodePos );

    while ( ! stack.isEmpty() )
    {

        curNodePos = stack.top();

        stack.pop();


        if ( ! m_visited[ curNodePos ] )
        {
            m_visited[ curNodePos ] = true;
        }


        for ( EdgeId curEdge = 0; curEdge != roadmap::edges_limit; curEdge++ )
        {

            NodeId nodeNeighborPos = edgesList.getNodeId( curNodePos, curEdge );

            if ( ( nodeNeighborPos == UINT16_MAX ) || ( nodeNeighborPos == curNodePos ) )
            {
                continue;
            }

            if ( ! m_visited[ nodeNeighborPos ] )
            {
                stack.push( nodeNeighborPos );
            }

        }
       
    }

}



bool DepthFirstSearch::isNodeVisited( NodeId nodePos ) const
{

    return m_visited[ nodePos ];

}
