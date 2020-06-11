#pragma once

#include "typedefs.h"
#include "roadmap/roadmap_parameters.h"
#include "config_space/point.h"

#include "config_space/graph/i_nodes_list.h"
#include "config_space/graph/i_edges_list.h"



namespace config_space
{

    namespace graph
    {

        class Graph : public INodesList, public IEdgesList
        {

        public:

            explicit Graph();
            ~Graph();

            uint16_t getNodeAmountEdges( NodeId nodePos ) const;

            void reset();

            /* INodesList */
            const Point & getNodeConfig( NodeId nodePos ) const final;

            uint16_t getNodesAmount() const final;

            bool hasNodeFreeEdge( NodeId nodePos ) const final;

            uint8_t getAmountFreeEdges( NodeId nodesPos ) const final;

            uint16_t getNodesInArea( NodeId nodePos ) const final;

            bool isNodeInserted( NodeId nodePos ) const final;

            /* IEdgesList */
            NodeId getNodeId( NodeId nodePos, EdgeId edgePos ) const final;


            NodeId insertNode( const config_space::Point & config );
            void removeNode( NodeId nodePos );


            void addEdge( NodeId node1, NodeId node2 );
            void removeEdge( NodeId node, EdgeId edge );

        private:

            struct Node
            {

                config_space::Point m_config;

                uint8_t m_orderConnection[ roadmap::edges_limit ];

                NodeId edges[ roadmap::edges_limit ];

                uint16_t m_curFreeEdge;

                uint16_t m_amountEdgesConnected;

                uint16_t m_nodesInArea;

                bool m_isNodeInserted;

                Node() :

                    m_config(), m_curFreeEdge( 0 ),
                    m_amountEdgesConnected( 0 ), m_nodesInArea( 0 ), m_isNodeInserted( false )
                {
                    std::fill( edges, edges + roadmap::edges_limit, UINT16_MAX );

                    std::fill( m_orderConnection, 
                        m_orderConnection + roadmap::edges_limit, UINT8_MAX );
                }

                void reset()
                {

                    std::fill( edges, edges + roadmap::edges_limit, UINT16_MAX );

                    std::fill( m_orderConnection, m_orderConnection + roadmap::edges_limit,
                        UINT8_MAX );

                    m_curFreeEdge = 0;

                    m_amountEdgesConnected = 0;

                    m_nodesInArea = 0;

                    m_isNodeInserted = false;

                }

            };

            Node * m_nodesStorage;

            uint16_t m_freeNodePos;

            uint16_t m_nodesInvolved;

            void updateAvailableIndex();

            void verifyAvailableIndex( NodeId testingNodePos );

            void decreaseFreeEdges( uint16_t nodePos );

            bool isNodeInGraph( uint16_t nodePos ) const;

            void verifyFreeEdgePos( NodeId nodePos, EdgeId testingEdge );

            void findFreeEdgePos( NodeId nodePos );

        };

    }

}
