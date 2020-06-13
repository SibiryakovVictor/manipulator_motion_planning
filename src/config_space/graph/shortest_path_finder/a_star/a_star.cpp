#include "config_space/graph/shortest_path_finder/a_star.h"

#include "config_space/point.h"
#include "intervals.h"



using namespace config_space::graph::shortest_path;
using namespace config_space::graph;

const float Astar::cost_threshold_zero = 0.001f;



uint16_t Astar::findShortestPath( motion_planner::path::Path & pathData,
	const INodesList & nodesList,
	const IEdgesList & edgesList )
{

	Astar::PriorityQueue openSet;

	float costToNodes[ roadmap::capacity ] { 0.f };

	motion_planner::path::PathElement previousInPath[ roadmap::capacity ];
	std::fill( previousInPath, previousInPath + roadmap::capacity,
		motion_planner::path::PathElement{ UINT16_MAX, UINT8_MAX } );


    openSet.putNodePriority( NodePriority( 
        roadmap::start_node_pos, 0.f ) );

	const config_space::Point & goalConfig = nodesList.getNodeConfig( 
		roadmap::goal_node_pos );

	while ( ! openSet.isEmpty() )
	{

		NodeId curNodePos = openSet.getMostPriorityNodePos();

		if ( curNodePos == roadmap::goal_node_pos )
		{
			break;
		}

		const config_space::Point & curNodeConfig = nodesList.getNodeConfig( curNodePos );

		for ( EdgeId curEdge = 0; curEdge != roadmap::edges_limit; curEdge++ )
		{

			NodeId curNeighborPos = edgesList.getNodeId( curNodePos, curEdge );

			if ( ( curNeighborPos == UINT16_MAX ) || ( curNeighborPos == curNodePos ) )
			{
				continue;
			}

			const config_space::Point & curNeighborConfig = 
				nodesList.getNodeConfig( curNeighborPos );

			float neighborCost = costToNodes[ curNodePos ] + calcCostNodesConfigs( 
				curNodeConfig, curNeighborConfig );

			if ( ( costToNodes[ curNeighborPos ] < Astar::cost_threshold_zero ) || 
				( neighborCost < costToNodes[ curNeighborPos ] ) )
			{
				costToNodes[ curNeighborPos ] = neighborCost;

				float priority = neighborCost + calcCostNodesConfigs( 
					curNeighborConfig, goalConfig );

				openSet.putNodePriority( NodePriority( curNeighborPos, priority ) );

				previousInPath[ curNeighborPos ] = { curNodePos, curEdge };
			}
		}
	}


	if ( previousInPath[ roadmap::goal_node_pos ].point == UINT16_MAX )
	{
		return 0;
	}


	return invertPath( pathData, previousInPath );
}




float Astar::calcCostNodesConfigs( const config_space::Point & config1, 
	const config_space::Point & config2 )
{
	auto dim = 0;

	return std::inner_product( config1.begin(), config1.end(), config2.begin(), 0.f,
		[]( float arg, float result ){ return result + arg; },
		[ this, &dim ](float arg1, float arg2) 
		{
			float diff = ( arg1 - arg2 ) * m_distCoeff[ dim ];

			dim++;

			return diff * diff; 
		} );
}




uint16_t Astar::invertPath( motion_planner::path::Path & result,
	motion_planner::path::PathElement (&prevInPath)[ roadmap::capacity ] )
{
	uint16_t pathLength = 0;

	NodeId curNodePath = 1;

	while ( curNodePath != roadmap::start_node_pos )
	{

		result.sections[ pathLength ] = prevInPath[ curNodePath ];

		pathLength++;

		curNodePath = prevInPath[ curNodePath ].point;

	}

	std::reverse( result.sections, result.sections + pathLength );

	result.sections[ pathLength ] = { roadmap::goal_node_pos, UINT8_MAX };
	pathLength++;

	return pathLength;
}



void Astar::calcDistCoeffs()
{
	for ( uint16_t dim = 0; dim != conf_space_dims; dim++ )
	{
		const auto & interval = settings::realRangesMotion[ dim ];

		m_distCoeff[ dim ] = std::fabsf( interval.gethb() - interval.getlb() );
	}
}

