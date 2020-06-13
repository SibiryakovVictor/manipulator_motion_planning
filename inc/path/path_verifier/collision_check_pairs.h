#pragma once

#include "env/obstacles.h"
#include "env/manipulator.h"


namespace coll
{
    struct CheckPair
    {
        uint16_t body1 = 0;
        uint16_t body2 = 0;
    };
}


static const uint16_t pairsAmount =
    manip::links_amount * obst::obst_amount;

static const uint16_t obsts = env::Obstacles::biasObstId;
static const uint16_t links = env::ManipulatorController::biasLinkId;
static const uint16_t groups = env::ManipulatorController::biasGroupId;



static const coll::CheckPair list_check_pairs[ pairsAmount ] = {
    { links + 1, obsts + 2 }, { links + 1, obsts + 3 },
    { groups + 1, obsts + 0 }, { groups + 1, obsts + 1 }, 
    { groups + 1, obsts + 2 }, { groups + 1, obsts + 3 },
    { links + 4, obsts + 0 }, { links + 4, obsts + 1 },
    { links + 4, obsts + 2 }, { links + 4, obsts + 3 },
    { links + 5, obsts + 0 }, { links + 5, obsts + 1 },
    { links + 5, obsts + 2 }, { links + 5, obsts + 3 },
    { links + 5, obsts + 4 }, { links + 5, obsts + 5 },
    { links + 5, links + 1 }, { links + 5, links + 2 },
    { links + 6, links + 4 },
    { groups + 2, obsts + 0 }, { groups + 2, obsts + 1 },
    { groups + 2, obsts + 2 }, { groups + 2, obsts + 3 },
    { groups + 2, obsts + 4 }, { groups + 2, obsts + 5 },
    { groups + 2, links + 1 }, { groups + 2, links + 2 },
    { links + 8, links + 4 },
    { groups + 3, obsts + 0 }, { groups + 3, obsts + 1 },
    { groups + 3, obsts + 2 }, { groups + 3, obsts + 3 },
    { groups + 3, obsts + 4 }, { groups + 3, obsts + 5 },
    { groups + 3, links + 1 }, { groups + 3, links + 2 },
    { links + 10, links + 4 }, { links + 10, links + 8 }
};


static const uint16_t list_config_change[ conf_space_dims + 1 ] = {
    0, 2, 6, 10, 18, 19, 28, 37
};

