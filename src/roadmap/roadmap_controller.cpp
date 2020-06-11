#include "roadmap/roadmap_controller.h"
#include "typedefs.h"

#include "config_space/graph/nodes_generation/generator_parameters.h"


using namespace motion_planner;




void RoadmapController::fillRoadmapRandomNodes( uint16_t nodesAmount )
{

	uint16_t amountAfterFilling = m_graph.getNodesAmount() + nodesAmount;

	if ( amountAfterFilling > roadmap::capacity )
	{
		while ( true )
		{
			; /* попытка вставить больше вершин, чем может вместить граф */
		}
	}

	while ( m_graph.getNodesAmount() < amountAfterFilling )
	{
		generateRoadmapNode();
	}

}




void RoadmapController::fillRoadmapRandomNodes(	uint16_t nodesAmount, 
												config_space::graph::Components & compStatus )
{

	uint16_t amountAfterFilling = m_graph.getNodesAmount() + nodesAmount;

	if ( amountAfterFilling > roadmap::capacity )
	{
		while ( true )
		{
			; /* попытка вставить больше вершин, чем может вместить граф */
		}
	}

	while ( m_graph.getNodesAmount() < amountAfterFilling )
	{
		generateRoadmapNode( compStatus );
	}

}




void RoadmapController::initializeRoadmap( const config_space::Point & startConfig,   
										   const config_space::Point & goalConfig )
{

	config_space::graph::Components componentsStatus;

	do 
	{

		componentsStatus.reset();

		m_graph.reset();

		m_graph.insertNode( startConfig );

		m_graph.insertNode( goalConfig );

		fillRoadmapRandomNodes( roadmap::init_amount_nodes, componentsStatus );

	} while ( ! hasWayFromStartToGoal( componentsStatus ) );

}




bool RoadmapController::hasWayFromStartToGoal( config_space::graph::Components & compStatus ) const
{
	return compStatus.findComp( roadmap::start_node_pos ) == 
		compStatus.findComp( roadmap::goal_node_pos );
}




void RoadmapController::generateRoadmapNode()
{
	using namespace config_space::graph::generation;

	SelectorRefNode selectorRefNode;
	MakerRandomPoint makerRandomPoint;
	SeekerNearestNeighbors seekerNN;

	config_space::Point generatedRoadmapNode = m_generator.generate(
		m_graph, m_graph,
		selectorRefNode, makerRandomPoint, seekerNN );

	NodeId generatedNodePos = m_graph.insertNode( generatedRoadmapNode );

	connectNodeWithNearestNeighbors( generatedNodePos, seekerNN );

}





void RoadmapController::generateRoadmapNode( config_space::graph::Components & compStatus )
{
	using namespace config_space::graph::generation;

	SelectorRefNode selectorRefNode;
	MakerRandomPoint makerRandomPoint;
	SeekerNearestNeighbors seekerNN;

	config_space::Point generatedRoadmapNode = m_generator.generate( 
		m_graph, m_graph,
		selectorRefNode, makerRandomPoint, seekerNN );

	NodeId generatedNodePos = m_graph.insertNode( generatedRoadmapNode );

	connectNodeWithNearestNeighbors( generatedNodePos, seekerNN, compStatus );

}




void RoadmapController::connectNodeWithNearestNeighbors( NodeId nodePos,
	config_space::graph::generation::ISeekerNN & seekerNN )
{

	while ( ! seekerNN.isEmpty() )
	{

		NodeId posCurNN = seekerNN.moveLastNNIndex();

		if ( ! m_graph.hasNodeFreeEdge( posCurNN ) )
		{
			continue;
		}

		if ( ! m_graph.hasNodeFreeEdge( nodePos ) )
		{
			break;
		}

		m_graph.addEdge( nodePos, posCurNN );

	}

}



void RoadmapController::connectNodeWithNearestNeighbors( NodeId nodePos,
	config_space::graph::generation::ISeekerNN & seekerNN,
	config_space::graph::Components & compStatus )
{

	while ( ! seekerNN.isEmpty() )
	{

		NodeId posCurNN = seekerNN.moveLastNNIndex();

		if ( ! m_graph.hasNodeFreeEdge( posCurNN ) )
		{
			continue;
		}

		if ( ! m_graph.hasNodeFreeEdge( nodePos ) )
		{
			break;
		}

		m_graph.addEdge( nodePos, posCurNN );

		compStatus.unionComp( nodePos, posCurNN );

	}

}



const config_space::graph::INodesList & RoadmapController::getNodesList() const
{
	return m_graph;
}



const config_space::graph::IEdgesList & RoadmapController::getEdgesList() const
{
	return m_graph;
}




void RoadmapController::reset()
{
	m_graph.reset();
}
