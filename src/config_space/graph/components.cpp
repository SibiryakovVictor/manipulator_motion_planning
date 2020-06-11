#include "config_space/graph/components.h"
#include "roadmap/roadmap_parameters.h"



void config_space::graph::Components::unionComp( uint16_t comp1, uint16_t comp2 )
{

	uint16_t rootComp1 = getRootPosition( comp1 );
	uint16_t rootComp2 = getRootPosition( comp2 );

	if ( rootComp1 == rootComp2 )
	{
		return;
	}

	if ( m_amountNodesTree[ rootComp1 ] < m_amountNodesTree[ rootComp2 ] )
	{

		m_componentsStatus[ rootComp1 ] = m_componentsStatus[ rootComp2 ];

		m_amountNodesTree[ rootComp2 ] += m_amountNodesTree[ rootComp1 ];

	}
	else
	{

		m_componentsStatus[ rootComp2 ] = m_componentsStatus[ rootComp1 ];

		m_amountNodesTree[ rootComp1 ] += m_amountNodesTree[ rootComp2 ];

	}

}



bool config_space::graph::Components::areConnected( uint16_t node1Pos, uint16_t node2Pos ) const
{

	return getRootPosition( node1Pos ) == getRootPosition( node2Pos );

}



uint16_t config_space::graph::Components::findComp( uint16_t nodePos ) const
{

	return getRootPosition( nodePos );

}



uint16_t config_space::graph::Components::getRootPosition( uint16_t pos ) const
{

	while (  m_componentsStatus[ pos ] != pos )
	{

		m_componentsStatus[ pos ] = m_componentsStatus[ m_componentsStatus[ pos ] ];

		pos = m_componentsStatus[ pos ];

	}

	return pos;

}



void config_space::graph::Components::reset()
{

	for ( uint16_t curComp = 0; curComp != roadmap::capacity; curComp++ )
	{
		m_componentsStatus[ curComp ] = curComp;
	}

	std::fill( m_amountNodesTree, m_amountNodesTree + roadmap::capacity, 1 );

}



void config_space::graph::Components::disunionComp( uint16_t comp )
{

	m_componentsStatus[ comp ] = comp;

}

