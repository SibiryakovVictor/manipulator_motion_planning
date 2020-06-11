#pragma once


#include "i_roadmap_explorer.h"
#include "stack.h"



namespace roadmap
{

    class DepthFirstSearch : public IRoadmapExplorer
    {

    public:

        explicit DepthFirstSearch()
        {}

    public:

        void executeTraversal( NodeId startNodePos,
            const config_space::graph::IEdgesList & edgesList ) final;

        bool isNodeVisited( NodeId nodePos ) const final;

    private:

        bool m_visited[ roadmap::capacity ];

    };

}
