#include "config_space/graph/nodes_generation/selectors_reference_node/selector_random_btwn_nodes.h"
#include "roadmap/roadmap_parameters.h"

#include <random>

using namespace config_space::graph::generation;
using namespace config_space::graph;



uint16_t SelectorRandomBtwnNodes::chooseReferenceNode( 
	const INodesList & nodes, const IEdgesList & edges ) const
{

	/*static std::default_random_engine generator;
	std::uniform_int_distribution< uint16_t > distribution( 0, nodes.getNodesAmount() - 1 );

	uint16_t nodeId = distribution( generator );

	while ( nodes.getAmountFreeEdges( nodeId ) < roadmap::nn_limit )
	{
		nodeId = distribution( generator );
	}

	return nodeId;*/

	return roadmap::start_node_pos;

}

