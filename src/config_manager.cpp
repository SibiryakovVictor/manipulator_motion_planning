#include "config_manager.h"


using namespace motion_planner;



void ConfigManager::changeObjectBody( uint16_t objId, env::OBB body )
{

    if ( objId >= env::Obstacles::biasObstId )
    {
        m_obsts.changeBody( objId, body );
    }
    else
    {
        m_links.changeBody( objId, body );
    }

}



void ConfigManager::rotateObst( uint16_t obstId, float angle, Eigen::Vector3f axis )
{
    m_obsts.rotate( obstId, angle, axis );
}
