#pragma once

#include "env/primitives/obb.h"

#include "Eigen/Core"



namespace coll
{
	using namespace env;

	class CollisionDetector
	{

	public:

		bool areObjectsCollided( const OBB & obj1, const OBB & obj2 ) const;

	private:

		bool spherePhase( 
			const Position & centerPos1, const Position & centerPos2,
			float r1, float r2 
		) const;


		bool satPhase( const OBB & obj1, const OBB & obj2 ) const;


		bool checkSeparatingPlane(
			const Position & diffP, const Position & Plane,
			const Orient & axisOrient1, const Orient & axisOrient2,
			const OBB::Sizes & sizes1, const OBB::Sizes & sizes2
		) const;

		Eigen::Vector3f cross( const Eigen::Vector3f & v1, const Eigen::Vector3f & v2 ) const;

	};

}
