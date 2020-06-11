#include "config_space/graph/nodes_generation/nearest_neighbors/seeker_nn_radius.h"




void config_space::graph::generation::SeekerNNRadius::seekNearestNeighbors( 
	const config_space::Point & refPoint, 
	const config_space::graph::INodesList & nodeList )
{
	static const float threshold_low = 0.001f;

	const uint16_t listLength = nodeList.getNodesAmount();

	uint16_t amountNodesInList = 0;

	uint16_t curIndexPoint= 0;
	while ( ( curIndexPoint != listLength ) && 
		( amountNodesInList != roadmap::nn_limit ) )
	{

		if ( ( ! nodeList.hasNodeFreeEdge( curIndexPoint ) ) && ( ! nodeList.isNodeInserted( curIndexPoint ) ) )
		{
			curIndexPoint++;
			continue;
		}

		const config_space::Point & curPoint = nodeList.getNodeConfig( curIndexPoint ); 

		float distance = config_space::Point::calcDistNoSqrt( refPoint, curPoint );

		if ( ( distance < m_radius ) && ( distance > threshold_low ) )
		{
			push( curIndexPoint );
			amountNodesInList++;
		}

		curIndexPoint++;
	}

}
