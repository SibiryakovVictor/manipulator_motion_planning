#pragma once

#include "env/env_def.h"



namespace env
{

    class OBB
    {

    public:

        struct Sizes
        {
            float dims[ 3 ] = { 0.f, 0.f, 0.f };

            Sizes( const float (&dimValues)[ 3 ] )
            {
                std::copy( dimValues, dimValues + 3, dims );
            }
        };


        const Orient & getOrient() const;

        const Position & getCenterPos() const;

        const OBB::Sizes & getSizes() const;

        float getMaxSize() const;



        void setOrient( const Orient & orient );
        void setOrient( Orient && orient );

        void setCenterPos( const Position & pos );
        void setCenterPos( Position && pos );

        void setSizes( const OBB::Sizes & sizes );
        void setSizes( OBB::Sizes && sizes );



        explicit OBB()
        {}

        explicit OBB( const OBB::Sizes & sizes, const Position & centerPos );

        explicit OBB( OBB::Sizes && sizes, Position && centerPos );

        explicit OBB( const OBB::Sizes & sizes, const Position & centerPos, 
                      const Orient & orient );

        explicit OBB( OBB::Sizes && sizes, Position && centerPos, Orient && orient );

        OBB( const OBB & obb );

        OBB & operator=( OBB && obb );

        OBB & operator=( const OBB & obb );

    private:

        OBB::Sizes m_sizes = OBB::Sizes( { 0.f, 0.f, 0.f } );

        Position m_centerPos = Eigen::Vector3f::Zero();

        Orient m_orient = Eigen::Matrix3f::Identity();

        float m_maxSize = 0.f;


        float calcMaxSize( const float (&sizesList)[ 3 ] ) const;

    };

}

