#include "config_space/graph/nodes_generation/nodes_generator.h"

using namespace config_space::graph::generation;
using namespace config_space::graph;



config_space::Point NodesGenerator::generate( 
	INodesList & nodesList,
	IEdgesList & edges,
	ISelectorReferenceNode & selectorRefNode,
	config_space::point::IMakerRandomPoints & makerRandomPoints,
	ISeekerNN & seekerNN )
{

	NodeId refNodePos = selectorRefNode.chooseReferenceNode( nodesList, edges );

	config_space::Point refConfig( nodesList.getNodeConfig( refNodePos ) );

	config_space::Point generatedConfig( makerRandomPoints.make( refConfig ) );

	seekerNN.seekNearestNeighbors( generatedConfig, nodesList );
	
	return generatedConfig;

}



