#include "config_space/graph/nodes_generation/selectors_reference_node/selector_random_btwn_comps.h"
#include "stack.h"


#include <random>


using namespace config_space::graph::generation;
using namespace config_space::graph;



uint16_t SelectorRandomBtwnComps::chooseReferenceNode( 
	const INodesList & nodes, const IEdgesList & edges ) const
{
	static std::default_random_engine generator;
	

	NodeId listNode[ 10 ] { UINT16_MAX };
	std::fill( listNode, listNode + 10, UINT16_MAX );

	uint8_t maxFreeEdges = 0;
	NodeId nodeMaxFreeEdges = 0;
	uint8_t listPos = 0;

	uint16_t nodesAmount = nodes.getNodesAmount();
	for ( NodeId curNodeId = 0; curNodeId != nodesAmount; curNodeId++ )
	{

		if ( nodes.getAmountFreeEdges( curNodeId ) < roadmap::nn_limit )
		{
			continue;
		}

		if ( listPos == 10 )
		{
			break;
		}

		if ( ! nodes.isNodeInserted( curNodeId ) )
		{
			continue;
		}

		uint8_t curAmountFreeEdges = nodes.getAmountFreeEdges( curNodeId );
		if ( curAmountFreeEdges > maxFreeEdges )
		{
			nodeMaxFreeEdges = curNodeId;
			maxFreeEdges = curAmountFreeEdges;
			listNode[ listPos ] = curNodeId;
			listPos++;
		}

	}

	std::uniform_int_distribution< uint16_t > distribution( 0, listPos - 1 );

	NodeId chosenNode = listNode[ distribution( generator ) ];
	while ( chosenNode == UINT16_MAX )
	{
		chosenNode = listNode[ distribution( generator ) ];
	}

	return chosenNode;
}