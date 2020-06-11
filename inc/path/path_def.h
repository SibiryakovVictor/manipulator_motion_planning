#pragma once

#include "typedefs.h"
#include "path_parameters.h"



namespace motion_planner
{
    namespace path
    {

        struct PathElement
        {

            NodeId point;

            EdgeId segment;

        };

        struct Path
        {
            PathElement sections[ path::length_limit ];
        };

    }
}

