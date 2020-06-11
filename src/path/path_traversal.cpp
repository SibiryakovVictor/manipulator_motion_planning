#include "path/path_traversal.h"



using namespace motion_planner::path;




Path & PathTraversal::getPathStorage()
{

    return m_path;

}




void PathTraversal::setPathLength( uint16_t pathLength )
{
	m_pathLength = pathLength;
}




uint16_t PathTraversal::getPathLength() const
{
	return m_pathLength;
}




float PathTraversal::getStep() const
{
	return m_step;
}




bool PathTraversal::isPathPassed() const
{
	return ( m_curPoint > m_pathLength - 2 );
}



config_space::Point PathTraversal::getNextPointPath() const
{

	if ( m_trajIt.isPassed() )
	{

		m_curPoint++;

		if ( m_curPoint > ( m_pathLength - 2 ) )
		{
			m_curPoint = m_pathLength - 1;

			return m_trajIt.end();
		}

		m_trajIt.setTrajectory(
			m_nodesList.getNodeConfig( m_path.sections[ m_curPoint ].point ),
			m_nodesList.getNodeConfig( m_path.sections[ m_curPoint + 1 ].point ),
			m_step
		);

		return m_trajIt.getNextPoint();
	}

	return m_trajIt.getNextPoint();

}



void PathTraversal::resetPointGetter() const
{

	m_curPoint = 0;

	m_trajIt.setTrajectory(
		m_nodesList.getNodeConfig( m_path.sections[ m_curPoint ].point ),
		m_nodesList.getNodeConfig( m_path.sections[ m_curPoint + 1 ].point ),
		m_step
	);

}



void PathTraversal::reset()
{

	PathElement fillElem{ UINT16_MAX, UINT8_MAX };
	std::fill( m_path.sections, m_path.sections + m_pathLength, fillElem );

	m_pathLength = 0;

	m_curPoint = 0;

	m_trajIt.resetStep();

}



PathElement PathTraversal::getCurPathElem() const
{
	return m_path.sections[ m_curPoint ];
}



PathElement PathTraversal::getPathElem( uint16_t elemIndex ) const
{
	return m_path.sections[ elemIndex ];
}



void PathTraversal::changeStep( float step )
{

	m_step = step;

	resetPointGetter();

}


