#pragma once

#include <iostream>

#include "config_space/conf_space_dims.h"



namespace roadmap
{
    const uint16_t start_node_pos = 0;
    const uint16_t goal_node_pos = 1;

    const uint16_t edges_limit = 19;
    const uint16_t nn_limit = 7;

    const uint16_t capacity = 210;

    const uint16_t init_amount_nodes = 120;

    const float radius_search_nn = 0.45f;
    const float radius_generation = 0.6f;
    const float generation_param = 0.225f;
    const float radius_limit_nn =
        static_cast< float >( conf_space_dims ) * std::powf( radius_search_nn, 2.f );

    const uint16_t limit_amount_nn = capacity / 12;
}

