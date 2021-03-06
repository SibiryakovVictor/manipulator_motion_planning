#pragma once

#include <iostream>
#include <algorithm>

#include "config_space/point.h"
#include "config_space/segment.h"



namespace motion_planner
{
	namespace path
	{

		class TrajectoryIterator
		{

		public:

			explicit TrajectoryIterator()
			{}

			explicit TrajectoryIterator( const config_space::Point & start, 
				const config_space::Point & end,
				float maxPrec ) :
				m_segment( start, end )
			{
				m_paramStep = m_segment.calcParamStep( maxPrec );
			}

			void setTrajectory( const config_space::Point & startPoint, 
				const config_space::Point & endPoint,
				float maxPrec );

			config_space::Point getNextPoint();

			void resetStep();

			void changePrec( float prec );

			config_space::Point start() const;

			config_space::Point end() const;

			bool isPassed() const;

		private:

			config_space::Segment m_segment;

			float m_curParamValue = 0.f;
			float m_paramStep = 0.f;

		};

	}

}

