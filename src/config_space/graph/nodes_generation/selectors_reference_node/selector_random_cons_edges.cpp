#include "config_space/graph/nodes_generation/selectors_reference_node/selector_random_cons_edges.h"
#include "float_operations.h"
#include "roadmap/roadmap_parameters.h"


using namespace config_space::graph::generation;
using namespace config_space::graph;


uint16_t SelectorRandomConsEdges::chooseReferenceNode( 
	const INodesList & nodes, const IEdgesList & edges ) const const
{

	float limitHigh = 0.f;

	for ( uint16_t curNode = 0; curNode != nodes.getNodesAmount(); curNode++ )
	{
		limitHigh += calcWeightNode( nodes, curNode );
	}

	uint16_t refNodeIndex = 0;
	do 
	{

		float selectedRange = flt_op::getRandomFloat( 0.00001f, limitHigh );

		float curHighBorder = 0.f;
		for ( uint16_t curNode = 0; curNode != nodes.getNodesAmount(); curNode++ )
		{

			curHighBorder += calcWeightNode( nodes, curNode );

			if ( selectedRange < curHighBorder ) 
			{
				refNodeIndex = curNode;
				break;
			}

		}

	} while ( ! nodes.getAmountFreeEdges( refNodeIndex ) < roadmap::nn_limit );

	return refNodeIndex;

}


float SelectorRandomConsEdges::calcWeightNode( const INodesList & nodes,
	uint16_t nodePos ) const
{
	return 1.f / ( 1.f + static_cast< float >( nodes.getNodesInArea( nodePos ) ) );
}
