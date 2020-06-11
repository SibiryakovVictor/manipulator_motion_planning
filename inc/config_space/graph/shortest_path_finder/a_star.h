#pragma once

#include <algorithm>


#include "shortest_path_finder.h"
#include "config_space/graph/i_nodes_list.h"
#include "config_space/graph/i_edges_list.h"
#include "path/path_def.h"




namespace config_space
{

    namespace graph
    {

        namespace shortest_path
        {

            class Astar : public IShortestPathFinder
            {

            public:

                explicit Astar()
				{}


                uint16_t findShortestPath( 
					motion_planner::path::Path & pathData,
					const INodesList & nodesList,
					const IEdgesList & edgesList );


            private:

				class NodePriority
				{

				public:

					uint16_t m_nodePos;

					float m_priority;

					explicit NodePriority() :
						m_nodePos( UINT8_MAX ),
						m_priority( UINT16_MAX )
					{}

					NodePriority( uint16_t nodePos, float priority) :
						m_nodePos(nodePos),
						m_priority(priority)
					{}

				};

				class PriorityQueue
				{

				public:

					explicit PriorityQueue() :
						m_queueContainer(),
						m_containerPos( 0 )
					{}


					bool isEmpty() const;

					void putNodePriority( Astar::NodePriority nodeInfo );

					uint16_t getMostPriorityNodePos();

				private:

					class PriorityComparator
					{

					public:

						bool operator()( const Astar::NodePriority & n1, 
							const Astar::NodePriority & n2 ) const;

					};

					Astar::NodePriority m_queueContainer[ roadmap::capacity ];

					uint16_t m_containerPos;					

				};

				static const float cost_threshold_zero;

				float calcCostNodesConfigs( const Point & config1, const Point & config2 );

				uint16_t invertPath( motion_planner::path::Path & result,
					motion_planner::path::PathElement (&prevInPath)[ roadmap::capacity ] );							   

            };

        }

    }

}
