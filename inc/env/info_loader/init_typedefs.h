#pragma once

#include "env/env_def.h"
#include "env/primitives/obb.h"
#include "env/primitives/attached_detail.h"
#include "env/manip_parameters.h"
#include "env/obst_parameters.h"




namespace env
{

    struct ManipInitInfo
    {
        struct LinkInitInfo
        {
            OBB body_ = OBB();

            Position mountPos_ = Eigen::Vector3f::Zero();

            uint8_t axisRot_ = 2;

            uint16_t groupId_ = 0;

            uint16_t mountId_ = 0;

            EulerAngles anglesOrient_ = EulerAngles( { 0.f, 0.f, 0.f } );
            bool isAngleSet_[ 3 ] = { false, false, false };
            bool areAnglesUsed_ = false;

            explicit LinkInitInfo( 
                OBB::Sizes sizes,
                Position centerPos,
                Position mountPos,
                uint16_t mountId,
                uint8_t axis,
                uint16_t id,
                const float (&angles)[ 3 ],
                const bool (&isAngleSet)[ 3 ],
                bool areAnglesUsed
            ) :
                body_( sizes, centerPos ),
                mountPos_( mountPos ),
                mountId_( mountId ),
                axisRot_( axis ),
                groupId_( id ),
                areAnglesUsed_( areAnglesUsed ),
                anglesOrient_( { angles[ 0 ], angles[ 1 ], angles[ 2 ] } )
            {
                std::copy( isAngleSet, isAngleSet + 3, isAngleSet_ );
            }

            explicit LinkInitInfo()
            {}
        };

        LinkInitInfo linksData[ manip::links_amount ];
    };


    struct ObstInitInfo
    {
        AttachedDetail obsts[ obst::obst_amount ];
    };
}
