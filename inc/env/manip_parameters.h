#pragma once

#include <iostream>

#include "config_space/conf_space_dims.h"


namespace manip
{ 
    const uint8_t links_groups = conf_space_dims;

    const uint8_t links_amount = 11;

    struct OrientDependency
    {
        uint16_t src = 0;
        uint16_t dst = 0;
    };

    const uint8_t links_complex_amount = 4;

    const uint8_t links_align_last[ links_amount ] = { 
        links_amount, links_amount, links_amount, links_amount, links_amount,
        links_amount, links_amount, 9, 9, links_amount, links_amount };

    const uint8_t links_matrix_using[ links_amount ] = { 0, 0, 0, 2, 2, 4, 5, 6, 7, 6, 9 };
}            

