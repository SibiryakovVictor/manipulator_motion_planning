#pragma once

#include "i_selector_reference_node.h"
#include "config_space/graph/i_nodes_list.h"



namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            class SelectorRandomBtwnNodes : public ISelectorReferenceNode
            {

            public:

                explicit SelectorRandomBtwnNodes()
                {}

                uint16_t chooseReferenceNode( 
                    const INodesList & nodes, const IEdgesList & edges ) const;

            };

        }

    }





}
