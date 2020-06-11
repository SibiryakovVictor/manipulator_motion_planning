#pragma once

#include "selectors_reference_node/selector_random_btwn_comps.h"
#include "selectors_reference_node/selector_random_btwn_nodes.h"

#include "makers_random_points/maker_radius.h"
#include "makers_random_points/maker_interval.h"

#include "nearest_neighbors/seeker_nn_radius.h"
#include "nearest_neighbors/seeker_nn_cube.h"




namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            /* метод, используемый в оригинальном алгоритме LazyPRM: */
            /*typedef SelectorRandomBtwnNodes SelectorRefNode;
            typedef point::MakerRandomPointsInterval MakerRandomPoint;
            typedef SeekerNNRadius SeekerNearestNeighbors;*/


            /* кастомный метод генерации */
            typedef SelectorRandomBtwnComps SelectorRefNode;
            typedef point::MakerRandomPointsRadius MakerRandomPoint;
            typedef SeekerNNRadius SeekerNearestNeighbors;

        }

    }

}



