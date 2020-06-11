#pragma once

#include "roadmap/roadmap_parameters.h"



namespace config_space
{

    namespace graph
    {

        class Components
        {

        public:

            explicit Components()
            {
                reset();
            }

            void unionComp( uint16_t comp1, uint16_t comp2 );

            uint16_t findComp( uint16_t nodePos ) const;

            bool areConnected( uint16_t node1Pos, uint16_t node2Pos ) const;

            void disunionComp( uint16_t comp );

            void reset();

        private:

            mutable uint16_t m_componentsStatus[ roadmap::capacity ];

            uint16_t m_amountNodesTree[ roadmap::capacity ];

            uint16_t getRootPosition( uint16_t pos ) const;

        };

    }

}
