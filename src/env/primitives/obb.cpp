#include "env/primitives/obb.h"


using namespace env;




const Orient & OBB::getOrient() const
{
    return m_orient;
}



const Position & OBB::getCenterPos() const
{
    return m_centerPos;
}



const OBB::Sizes & OBB::getSizes() const
{
    return m_sizes;
}



float OBB::getMaxSize() const
{
    return m_maxSize;
}





void OBB::setOrient( const Orient & orient )
{
    m_orient = orient;
}
void OBB::setOrient( Orient && orient )
{
    m_orient = orient;
}



void OBB::setCenterPos( const Position & pos )
{
    m_centerPos = pos;
}
void OBB::setCenterPos( Position && pos )
{
    m_centerPos = pos;
}



void OBB::setSizes( const OBB::Sizes & sizes )
{
    m_sizes = sizes;

    m_maxSize = *std::max_element( sizes.dims, sizes.dims + dim_space );
}
void OBB::setSizes( OBB::Sizes && sizes )
{
    m_sizes = sizes;

    m_maxSize = *std::max_element( sizes.dims, sizes.dims + dim_space );
}



float OBB::calcMaxSize( const float (&sizesList)[ 3 ] ) const
{
    return *std::max_element( sizesList, sizesList + dim_space );
}





OBB::OBB( const OBB::Sizes & sizes, const Position & centerPos ) :
    m_sizes( sizes ),
    m_centerPos( centerPos),
    m_maxSize( calcMaxSize( sizes.dims ) )
{}



OBB::OBB( OBB::Sizes && sizes, Position && centerPos ) :
    m_sizes( sizes ),
    m_centerPos( centerPos ),
    m_maxSize( calcMaxSize( sizes.dims ) )
{}



OBB::OBB( const OBB::Sizes & sizes, const Position & centerPos, 
    const Orient & orient ) :
    m_sizes( sizes ),
    m_centerPos( centerPos ),
    m_orient( orient ),
    m_maxSize( calcMaxSize( sizes.dims ) )
{}



OBB::OBB( OBB::Sizes && sizes, Position && centerPos, Orient && orient ) :
    m_sizes( sizes ),
    m_centerPos( centerPos ),
    m_orient( orient ),
    m_maxSize( calcMaxSize( sizes.dims ) )
{}



OBB::OBB( const OBB & obb ) :
    m_sizes( obb.m_sizes ),
    m_centerPos( obb.m_centerPos ),
    m_orient( obb.m_orient ),
    m_maxSize( calcMaxSize( obb.m_sizes.dims ) )
{}



OBB & OBB::operator=( OBB && obb )
{
    m_sizes = obb.m_sizes;
    m_maxSize = calcMaxSize( obb.m_sizes.dims );

    m_centerPos = obb.m_centerPos;

    m_orient = obb.m_orient;

    return *this;
}




OBB & OBB::operator=( const OBB & obb )
{
    if ( this == &obb )
    {
        return *this;
    }

    m_sizes = obb.m_sizes;
    m_maxSize = calcMaxSize( obb.m_sizes.dims );

    m_centerPos = obb.m_centerPos;

    m_orient = obb.m_orient;

    return *this;
}

