#pragma once

#include "typedefs.h"

#include "stack.h"

#include "config_space/point.h"

#include "config_space/graph/i_nodes_list.h"




namespace config_space
{

    namespace graph
    {

        namespace generation
        {

            class ISeekerNN : public tools::stackDefault
            {

            public:

                virtual ~ISeekerNN() {}

                NodeId moveLastNNIndex();

                bool isListNNEmpty() const;

                virtual void seekNearestNeighbors( const Point & refPoint, 
                    const INodesList & nodesList ) = 0;

            };

        }

    }

}
