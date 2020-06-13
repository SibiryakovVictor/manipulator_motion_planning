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
				m_step( step )
			{
				std::fill( m_path.sections, m_path.sections + path::length_limit, 
					PathElement{ UINT16_MAX, UINT8_MAX } );
			}

			config_space::Point getNextPointPath() const;

			void resetPointGetter() const;

			void reset();

			Path & getPathStorage();

			void setPointsAmount( uint16_t pathNodesAmount );
			uint16_t getPointsAmount() const;

			bool isPathPassed() const;

			void changeStep( float step );

			float getStep() const;

			PathElement getCurPathElem() const;

			PathElement getPathElem( uint16_t elemIndex ) const;


		private:

			Path m_path;

			uint16_t m_pointsAmount = 0;

			float m_step = 0.f;

			mutable PointId m_curPoint = 0;

			mutable TrajectoryIterator m_trajIt;

			const config_space::graph::INodesList & m_nodesList;

		};

	}
}
