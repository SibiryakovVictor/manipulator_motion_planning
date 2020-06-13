#pragma once

#include "typedefs.h"
#include "config_space/point.h"



namespace config_space
{

    namespace graph
    {

        class INodesList
        {

        public:

            virtual ~INodesList() {}

            virtual uint16_t getNodesAmount() const = 0;

            virtual bool hasNodeFreeEdge( NodeId nodePos ) const = 0;

            virtual uint8_t getAmountFreeEdges( NodeId nodesPos ) const = 0;

            virtual bool isNodeInserted( NodeId nodePos ) const = 0;

            virtual const config_space::Point & getNodeConfig( NodeId nodePos ) const = 0;

        };

    }

}
