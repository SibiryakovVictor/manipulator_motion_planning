#pragma once

#include "i_selector_reference_node.h"
#include "config_space/graph/i_nodes_list.h"




namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            class SelectorRandomConsEdges : public ISelectorReferenceNode
            {

            public:

                explicit SelectorRandomConsEdges()
                {}

                uint16_t chooseReferenceNode( 
                    const INodesList & nodes, const IEdgesList & edges ) const;

            private:

                float calcWeightNode( const INodesList & selectorData, 
                    uint16_t nodePos ) const;

            };




        }

    }

}
