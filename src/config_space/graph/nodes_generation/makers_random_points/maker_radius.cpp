#include "config_space/graph/nodes_generation/makers_random_points/maker_radius.h"

#include "config_space/graph/nodes_generation/makers_random_points/maker_interval.h"


using namespace config_space::point;


config_space::Point config_space::point::MakerRandomPointsRadius::make( 
	const config_space::Point & refPoint ) const
{

	/*settings::IntervalsAllDims limits; 

	for ( uint16_t curDim = 0; curDim != conf_space_dims; curDim++ )
	{

		float lowLimitCalc = refPoint[ curDim ] - m_radius;

		limits[ curDim ].setlb( lowLimitCalc < settings::RangeLinksMotion::get()[ curDim ].getlb() ? 
			settings::RangeLinksMotion::get()[ curDim ].getlb() : lowLimitCalc );

		float highLimitCalc = refPoint[ curDim ] + m_radius;

		limits[ curDim ].sethb( highLimitCalc > settings::RangeLinksMotion::get()[ curDim ].gethb() ? 
			settings::RangeLinksMotion::get()[ curDim ].gethb() : highLimitCalc );

	}*/

	config_space::point::MakerRandomPointsInterval makerInterval( std::move( configureLimits( refPoint ) ) );

	return makerInterval.make( refPoint );

}




IntervalsAllDims MakerRandomPointsRadius::configureLimits( const config_space::Point & refPoint ) const
{

	IntervalsAllDims limits; 


	for ( uint16_t curDim = 0; curDim != conf_space_dims; curDim++ )
	{
		float lowBorder = settings::RangeLinksMotion::get()[ curDim ].getlb();
		limits[ curDim ].setlb( refPoint[ curDim ] + m_param * ( lowBorder - refPoint[ curDim ] ) );

		float highBorder = settings::RangeLinksMotion::get()[ curDim ].gethb();
		limits[ curDim ].sethb( refPoint[ curDim ] + m_param * ( highBorder - refPoint[ curDim ] ) );
	}

	return limits;

}
