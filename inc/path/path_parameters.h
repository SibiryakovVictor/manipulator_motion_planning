#pragma once

#include "roadmap/roadmap_parameters.h"


namespace motion_planner
{
    namespace path
    {
        const uint16_t length_limit = static_cast< float >( roadmap::capacity ) * 0.6f;  

        const float length_tolerance = 4.0f;

        const float traj_prec = 0.01745f;
        const float check_prec = traj_prec / 2.f;
        const float check_points_limit = 100.f;
    }
}

