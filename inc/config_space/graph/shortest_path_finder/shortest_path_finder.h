#pragma once

#include <iostream>


#include "../i_nodes_list.h"
#include "../i_edges_list.h"
#include "path/path_def.h"



namespace config_space
{

    namespace graph
    {

        namespace shortest_path
        {

            class IShortestPathFinder
            {

            public:

                virtual ~IShortestPathFinder() {}

                virtual uint16_t findShortestPath( 
                    motion_planner::path::Path & pathData,
                    const INodesList & nodesList,
                    const IEdgesList & edgesList ) = 0;

            };

        } 

    }

}
