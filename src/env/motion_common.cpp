#include "env/motion_common.h"



const Eigen::Vector3f & env::getUnitAxis( env::Axis axis )
{

    static const Eigen::Vector3f vuX = Eigen::Vector3f::UnitX();
    static const Eigen::Vector3f vuY = Eigen::Vector3f::UnitY();
    static const Eigen::Vector3f vuZ = Eigen::Vector3f::UnitZ();

    switch ( axis )
    {

    case ( env::Axis::X ) :
    {
        return vuX;
    }
    case ( env::Axis::Y ) :
    {
        return vuY;
    }
    default :
    {
        return vuZ;
    }

    }

}



const Eigen::Vector3f & env::getUnitAxis( uint8_t axis )
{

    static const Eigen::Vector3f unitX = Eigen::Vector3f::UnitX();
    static const Eigen::Vector3f unitY = Eigen::Vector3f::UnitY();
    static const Eigen::Vector3f unitZ = Eigen::Vector3f::UnitZ();

    switch ( axis )
    {

    case ( 0 ) :
    {
        return unitX;
    }
    case ( 1 ) :
    {
        return unitY;
    }
    default :
    {
        return unitZ;
    }

    }

}



uint8_t env::cvtAxisToId( Axis axis )
{

    switch ( axis )
    {

    case ( env::Axis::X ) :
    {
        return 0;
    }
    case ( env::Axis::Y ) :
    {
        return 1;
    }
    default :
    {
        return 2;
    }

    }

}



Eigen::Matrix3f env::getRotMat( const float & angleRad, const Eigen::Vector3f & rotAxis )
{
    return Eigen::AngleAxis< float >( angleRad, rotAxis ).toRotationMatrix();
}
Eigen::Matrix3f env::getRotMat( const float & angleRad, Eigen::Vector3f && rotAxis )
{
    return Eigen::AngleAxis< float >( angleRad, rotAxis ).toRotationMatrix();
}




void env::rotateVector( env::Position & pos, const float & angleRad, 
    const Eigen::Vector3f & rotAxis )
{
    pos = getRotMat( angleRad, rotAxis ) * pos;
}
Eigen::Vector3f env::rotateVector( const env::Position & pos, const float & angleRad, 
    const Eigen::Vector3f & rotAxis )
{
    return getRotMat( angleRad, rotAxis ) * pos;
}
Eigen::Vector3f env::rotateVector( env::Position && pos, const float & angleRad, 
    const Eigen::Vector3f & rotAxis )
{
    return getRotMat( angleRad, rotAxis ) * pos;
}



void env::rotateOrient( env::Orient & orient, const float & angleRad,
    const Eigen::Vector3f & rotAxis )
{
    orient = getRotMat( angleRad, rotAxis ) * orient;
}
env::Orient env::rotateOrient( const env::Orient & orient, const float & angleRad, 
    const Eigen::Vector3f & rotAxis )
{
    return getRotMat( angleRad, rotAxis ) * orient;
}
env::Orient env::rotateOrient( env::Orient && orient, const float & angleRad, 
    const Eigen::Vector3f & rotAxis )
{
    return getRotMat( angleRad, rotAxis ) * orient;
}