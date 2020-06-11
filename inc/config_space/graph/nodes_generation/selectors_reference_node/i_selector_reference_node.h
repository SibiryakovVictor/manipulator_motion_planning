#pragma once

#include "config_space/graph/i_nodes_list.h"
#include "config_space/graph/i_edges_list.h"



namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            class ISelectorReferenceNode
            {

            public:

                virtual ~ISelectorReferenceNode() {}

                virtual uint16_t chooseReferenceNode( 
                    const INodesList & nodes, const IEdgesList & edges ) const = 0;

            };

        }

    }

}
