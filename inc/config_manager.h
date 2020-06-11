#pragma once

#include "env/manipulator.h"
#include "env/obstacles.h"




namespace motion_planner
{
    class ConfigManager;
}

class motion_planner::ConfigManager
{

public:

    explicit ConfigManager( env::ManipulatorController & links,
                            env::Obstacles & obsts ) :
        m_links( links ),
        m_obsts( obsts )
    {}


    void changeObjectBody( uint16_t objId, env::OBB body );

    void rotateObst( uint16_t obstId, float angle, Eigen::Vector3f axis );



private:

    env::ManipulatorController & m_links;

    env::Obstacles & m_obsts;


};

