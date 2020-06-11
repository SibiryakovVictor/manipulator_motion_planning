#pragma once

#include "typedefs.h"



namespace config_space
{

    namespace graph
    {

        class IEdgesList
        {

        public:

            virtual ~IEdgesList() {}

            virtual NodeId getNodeId( NodeId nodePos, EdgeId edgePos ) const = 0;

        };

    }

}
