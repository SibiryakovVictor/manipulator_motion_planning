#pragma once

#include "generator_parameters.h"




namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            class NodesGenerator
            {

            public:

                explicit NodesGenerator()
                {}

                config_space::Point generate( INodesList & nodesList, IEdgesList & edges,
                    ISelectorReferenceNode & selectorRefNode,
                    point::IMakerRandomPoints & makerRandomPoints,
                    ISeekerNN & seekerNN );

            };

        }

    }

}
