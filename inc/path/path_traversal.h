#pragma once


#include "path_def.h"
#include "path_parameters.h"

#include "config_space/point.h"
#include "trajectory_iterator.h"
#include "config_space/graph/i_nodes_list.h"



namespace motion_planner
{
	namespace path
	{

		class PathTraversal
		{

		public:

			explicit PathTraversal( const config_space::graph::INodesList & nodesList,
				float step ) :
				m_nodesList( nodesList ),

				m_pathLength( 0 ),

				m_step( step ),

				m_curPoint( 0 ),

				m_trajIt(),

				m_path{}
			{
				std::fill( m_path.sections, m_path.sections + path::length_limit, 
					PathElement{ UINT16_MAX, UINT8_MAX } );
			}

			config_space::Point getNextPointPath() const;

			void resetPointGetter() const;

			void reset();

			Path & getPathStorage();

			void setPathLength( uint16_t pathLength );
			uint16_t getPathLength() const;

			bool isPathPassed() const;

			void changeStep( float step );

			float getStep() const;

			PathElement getCurPathElem() const;

			PathElement getPathElem( uint16_t elemIndex ) const;


		private:

			Path m_path;

			uint16_t m_pathLength;

			float m_step;

			mutable PointId m_curPoint;

			mutable TrajectoryIterator m_trajIt;

			const config_space::graph::INodesList & m_nodesList;

		};

	}
}
