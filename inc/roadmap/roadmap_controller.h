#pragma once


#include "roadmap_parameters.h"

#include "config_space/point.h"

#include "config_space/graph/graph.h"
#include "config_space/graph/i_nodes_list.h"
#include "config_space/graph/i_edges_list.h"

#include "config_space/graph/nodes_generation/nearest_neighbors/i_seeker_nearest_neighbors.h"
#include "config_space/graph/components.h"
#include "config_space/graph/nodes_generation/nodes_generator.h"




namespace motion_planner
{

	class RoadmapCorrector;

	namespace path
	{
		class PathFinder;
	}

	class RoadmapController
	{

	public:

		friend class RoadmapCorrector;

		friend class path::PathFinder;


		explicit RoadmapController() :
			m_graph(),
			m_generator()
		{}

		void initializeRoadmap( const config_space::Point & startConfig,   
								const config_space::Point & goalConfig );


		const config_space::Point & getStart() const;
		const config_space::Point & getGoal() const;


		const config_space::graph::INodesList & getNodesList() const;
		const config_space::graph::IEdgesList & getEdgesList() const;


		void reset();

	private:

		config_space::Point m_start;

		config_space::Point m_goal;

		config_space::graph::Graph m_graph;

		config_space::graph::generation::NodesGenerator m_generator;


		bool hasWayFromStartToGoal( config_space::graph::Components & compStatus ) const;

		void fillRoadmapRandomNodes(  uint16_t nodesAmount, config_space::graph::Components & compStatus );

		void fillRoadmapRandomNodes(  uint16_t nodesAmount );

		void generateRoadmapNode();

		void generateRoadmapNode( config_space::graph::Components & compStatus );

		void connectNodeWithNearestNeighbors( NodeId nodePos,
			config_space::graph::generation::ISeekerNN & seekerNN );

		void connectNodeWithNearestNeighbors( NodeId nodePos,
			config_space::graph::generation::ISeekerNN & seekerNN,
			config_space::graph::Components & compStatus );

	};


}

