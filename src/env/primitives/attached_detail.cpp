#include "env/primitives/attached_detail.h"
#include "env/motion_common.h"


using namespace env;




void AttachedDetail::rotateAroundAnchor( float angle, Eigen::Vector3f && rotAxis )
{
    auto && rotMat = getRotMat( angle, rotAxis );

    OBB::setCenterPos( m_mountPos + rotMat * ( m_initCenterPos - m_mountPos ) );

    OBB::setOrient( rotMat );
}

void AttachedDetail::rotateAroundAnchor( float angle, const Eigen::Vector3f & rotAxis )
{
    auto && rotMat = getRotMat( angle, rotAxis );

    OBB::setCenterPos( m_mountPos + rotMat * ( m_initCenterPos - m_mountPos ) );

    OBB::setOrient( rotMat );
}




void AttachedDetail::resetPosition()
{
    OBB::setCenterPos( m_initCenterPos );

    OBB::setOrient( Eigen::Matrix3f::Identity() );
}



AttachedDetail & AttachedDetail::operator=( const OBB & obb )
{
    OBB::operator=( obb );

    return *this;
}



AttachedDetail::AttachedDetail( const OBB & obb ) :
    OBB( obb )
{}

AttachedDetail::AttachedDetail( OBB && obb ) :
    OBB( obb )
{}

AttachedDetail::AttachedDetail( const OBB & obb, const Position & mountPos ) :
    OBB( obb ), m_mountPos( mountPos )
{}

AttachedDetail::AttachedDetail( OBB && obb, Position && mountPos ) :
    OBB( obb ), m_mountPos( mountPos )
{}




