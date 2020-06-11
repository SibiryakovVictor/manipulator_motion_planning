#include "config_space/graph/nodes_generation/nearest_neighbors/i_seeker_nearest_neighbors.h"


using namespace config_space::graph::generation;



NodeId ISeekerNN::moveLastNNIndex()
{

    NodeId result = top();

    pop();

    return result;

}



bool ISeekerNN::isListNNEmpty() const
{

    return isEmpty();

}
