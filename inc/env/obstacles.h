#pragma once

#include "env_def.h"
#include "env/info_loader/init_typedefs.h"
#include "primitives/obb.h"


namespace motion_planner
{
    class ConfigManager;                                                                                                                                                                                                                                                                           
}


namespace env
{

    class Obstacles
    {

    public:

        friend class motion_planner::ConfigManager;

        static const uint16_t biasObstId = UINT16_MAX / 2;

        explicit Obstacles( ObstInitInfo && objects ) :
            m_obstInfo( std::move( objects ) )
        {}

        const OBB * begin() const;

        const OBB * end() const;

        const OBB & getBody( uint16_t obstBiasedId ) const;    

        const Position & getObstPos( uint16_t obstId ) const;

        const Orient & getObstOrient( uint16_t obstId ) const;

        const OBB::Sizes & getObstSizes( uint16_t obstId ) const;


    private:

        ObstInitInfo m_obstInfo;


        void changeBody( uint16_t obstBiasedId, const OBB & body );

        void rotate( uint16_t obstBiasedId, float angle, Eigen::Vector3f axis );
    };


}

