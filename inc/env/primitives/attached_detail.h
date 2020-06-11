#pragma once

#include "obb.h"


namespace env
{
    class AttachedDetail;
}



class env::AttachedDetail : public env::OBB
{

public:

    void rotateAroundAnchor( float angle, const Eigen::Vector3f & rotAxis );
    void rotateAroundAnchor( float angle, Eigen::Vector3f && rotAxis );

    void resetPosition();

    explicit AttachedDetail()
    {}

    explicit AttachedDetail( const OBB & obb );
    explicit AttachedDetail( OBB && obb );

    explicit AttachedDetail( const OBB & obb, const Position & mountPos );
    explicit AttachedDetail( OBB && obb, Position && mountPos );

    AttachedDetail & operator=( const OBB & obb );

private:

    Position m_mountPos = OBB::getCenterPos();

    Position m_initCenterPos = OBB::getCenterPos();

};


