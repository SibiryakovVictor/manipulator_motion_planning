#pragma once

#include "typedefs.h"
#include "config_space/graph/i_edges_list.h"



namespace roadmap
{

    class IRoadmapExplorer
    {

    public:

        virtual ~IRoadmapExplorer() {}

        virtual void executeTraversal( NodeId startNodePos,
            const config_space::graph::IEdgesList & edgesList ) = 0;

        virtual bool isNodeVisited( NodeId nodePos ) const = 0;

    };

}
