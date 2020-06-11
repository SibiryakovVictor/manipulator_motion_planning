#include "config_space/graph/nodes_generation/nearest_neighbors/seeker_nn_cube.h"
#include "intervals.h"


void config_space::graph::generation::SeekerNNCube::seekNearestNeighbors( 
    const config_space::Point & refPoint, 
    const config_space::graph::INodesList & listPoints )
{
	constructCubeInterval( refPoint );

	const unsigned listLength = listPoints.getNodesAmount();

	uint16_t curIndexPoint= 0;
	while ( ( curIndexPoint != listLength ) && ( ! isFull() ) )
	{

		const config_space::Point & curPoint = listPoints.getNodeConfig( curIndexPoint ); 

		if ( isPointInCube( curPoint ) )
		{
			push( curIndexPoint );
		}

	}

}



bool config_space::graph::generation::SeekerNNCube::isPointInCube( const config_space::Point & p )
{

	for ( uint16_t curDim = 0; curDim != conf_space_dims; curDim++ )
	{

		if ( ! m_intervals[ curDim ].isInInterval( p[ curDim ] ) )
		{
			return false;
		}

	}

	return true;

}




IntervalsAllDims config_space::graph::generation::SeekerNNCube::constructCubeInterval( 
	const Point & refPoint )
{

	IntervalsAllDims result;

	for ( uint16_t curDim = 0; curDim != conf_space_dims; curDim++ )
	{

		result[curDim] = Interval { refPoint[ curDim ] - m_edgeCube, 
			refPoint[ curDim ] + m_edgeCube }; 

	}

	return result;

}

