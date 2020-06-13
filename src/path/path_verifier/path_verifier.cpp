#include "path/path_verifier/path_verifier.h"


using namespace motion_planner::path;

const float PathVerifier::threshold_config_change = 0.005f;



NodeId PathVerifier::checkNodesForCollision( const PathTraversal & path )
{
    for ( uint16_t curPathElem = 0; curPathElem != path.getPointsAmount(); curPathElem++ )
    {
        NodeId curNodePos = path.getPathElem( curPathElem ).point;

        if ( ! isConfigCorrect( m_nodesList.getNodeConfig( curNodePos ) ) )
        {
            return curNodePos;
        }
    }

    return UINT16_MAX;
}




PathElement PathVerifier::checkEdgesForCollision( const PathTraversal & path )
{
    auto amountPointsCheck = 2.f;
    auto prevAmountPoints = 1.f;

    while ( amountPointsCheck < path::check_points_limit )
    {
        auto curPathElem = path.getPathElem( 0 );
        uint16_t elemCounter = 0;

        while ( curPathElem.segment != UINT8_MAX )
        {
            const auto & startSeg = m_nodesList.getNodeConfig( curPathElem.point );
            const auto & endSeg = m_nodesList.getNodeConfig( m_edgesList.getNodeId(
                curPathElem.point, curPathElem.segment ) );

            config_space::Segment segment( startSeg, endSeg );

            if ( ! isSegmentValid( segment, amountPointsCheck ) )
            {
                return curPathElem;
            }

            elemCounter++;
            curPathElem = path.getPathElem( elemCounter );
        }

        auto tempPrevPoints = amountPointsCheck;

        amountPointsCheck += prevAmountPoints;

        prevAmountPoints = tempPrevPoints;
    }

    return path::PathElement{ UINT16_MAX, UINT8_MAX };
}




bool PathVerifier::isSegmentValid( const config_space::Segment & segment, const float pointsCheck )
{

    if ( ( segment.getMaxInterval() / pointsCheck ) < path::check_prec )
    {
        return true;
    }

    const auto prec = 1.f / pointsCheck;
    auto step = prec;

    while ( step < 0.995f )
    {
        auto point( segment.getPoint( step ) );

        if ( ! isConfigCorrect( point ) )
        {
            return false;
        }

        step += prec;
    }

    return true;
}




bool PathVerifier::isConfigCorrect( const config_space::Point & conf )
{
    static config_space::Point prevConfig( config_space::PointData( FLT_MAX ) );
    static bool prevResult = false;

    m_manip.reset();

    uint16_t configPos = 0;

    uint16_t manip = 0;

    uint16_t pairPos = 0;

    while ( configPos < conf_space_dims )
    {
        manip = list_check_pairs[ pairPos ].body1;

        m_manip.setConfigCurrentLink( conf[ configPos ] );

        if ( prevResult &&
            std::fabsf( prevConfig[ configPos ] - conf[ configPos ] ) < threshold_config_change )
        {
            pairPos = moveToNextGroup( pairPos, configPos );

            configPos++;

            m_manip.moveGroupCounter();

            continue;
        }

        configPos++;

        while ( pairPos != list_config_change[ configPos ] )
        {
            bool checkResult = true;
            if ( list_check_pairs[ pairPos ].body2 >= env::Obstacles::biasObstId )
            {
                checkResult = checkManipVsObst( manip, list_check_pairs[ pairPos ].body2 );
            }
            else
            {
                checkResult = checkManipVsManip( manip, list_check_pairs[ pairPos ].body2 );
            }


            if ( ! checkResult )
            {
                prevResult = false;
                return false;
            }

            pairPos++;
        }

        m_manip.moveGroupCounter();
    }

    prevConfig = conf;
    prevResult = true;
    return true;
}




bool PathVerifier::checkManipVsManip( uint16_t id1, uint16_t id2 ) const
{

    const auto & body1 = m_manip.getBody( id1 );
    const auto & body2 = m_manip.getBody( id2 );

    if ( ! m_collDetect.areObjectsCollided( body1, body2 ) )
    {
        return true;
    }

    bool isId1Link = id1 < env::ManipulatorController::biasGroupId;
    bool isId2Link = id2 < env::ManipulatorController::biasGroupId;

    if ( isId1Link && isId2Link )
    {
        return false;
    }

    if ( ( ! isId1Link ) && isId2Link )
    {
        return checkGroupVsLink( id1, id2 );
    }

    if ( isId1Link && ( ! isId2Link ) )
    {
        return checkGroupVsLink( id2, id1 );
    }

    return checkGroupVsGroup( id1, id2 );
}




bool PathVerifier::checkManipVsObst( uint16_t manipId, uint16_t obstId ) const
{
    const auto & body1 = m_manip.getBody( manipId );
    const auto & body2 = m_obst.getBody( obstId );

    if ( ! m_collDetect.areObjectsCollided( body1, body2 ) )
    {
        return true;
    }

    bool isLink = manipId < env::ManipulatorController::biasGroupId;

    if ( isLink )
    {
        return false;
    }

    return checkGroupVsObst( manipId, obstId );
}



bool PathVerifier::checkGroupVsLink( uint16_t groupId, uint16_t linkId ) const
{
    auto firstLinkGroup = m_manip.getFirstLinkComplex( groupId );
    auto linkNextGroup = firstLinkGroup + m_manip.getLinkType( firstLinkGroup );

    const auto & linkBody = m_manip.getBody( linkId ); 

    for ( auto link = firstLinkGroup; link != linkNextGroup; link++ )
    {
        if ( m_collDetect.areObjectsCollided( m_manip.getBody( link + m_manip.biasLinkId ), linkBody ) )
        {
            return false;
        }
    }

    return true;
}




bool PathVerifier::checkGroupVsGroup( uint16_t groupId1, uint16_t groupId2 ) const
{
    auto firstLinkGroup1 = m_manip.getFirstLinkComplex( groupId1 );
    auto firstLinkGroup2 = m_manip.getFirstLinkComplex( groupId2 );

    auto linkNextGroup1 = firstLinkGroup1 + m_manip.getLinkType( firstLinkGroup1 );
    auto linkNextGroup2 = firstLinkGroup2 + m_manip.getLinkType( firstLinkGroup2 );

    for ( auto links1 = firstLinkGroup1; links1 != linkNextGroup1; links1++ )
    {
        const auto & body1 = m_manip.getBody( links1 + m_manip.biasLinkId );

        for ( auto links2 = firstLinkGroup2; links2 != linkNextGroup2; links2++ )
        {
            const auto & body2 = m_manip.getBody( links2 + m_manip.biasLinkId );

            if ( m_collDetect.areObjectsCollided( body1, body2 ) )
            {
                return false;
            }
        }
    }

    return true;
}



bool PathVerifier::checkGroupVsObst( uint16_t groupId, uint16_t obstId ) const
{
    static const auto biasLinkId = m_manip.biasLinkId;

    auto firstLinkGroup = m_manip.getFirstLinkComplex( groupId );
    auto linkNextGroup = firstLinkGroup + m_manip.getLinkType( firstLinkGroup );

    const auto & obstBody = m_obst.getBody( obstId );

    for ( auto link = firstLinkGroup; link != linkNextGroup; link++ )
    {
        if ( m_collDetect.areObjectsCollided( 
            m_manip.getBody( link + m_manip.biasLinkId ), obstBody ) )
        {
            return false;
        }
    }

    return true;
}



uint16_t PathVerifier::moveToNextGroup( uint16_t pairPos, uint16_t confPos ) const
{
    confPos++;

    if ( confPos == conf_space_dims )
    {
        return pairsAmount;
    }

    return list_config_change[ confPos ];
}




env::ManipulatorController & PathVerifier::getLinksContainer()
{
    return m_manip;
}



env::Obstacles & PathVerifier::getObstsContainer()
{
    return m_obst;
}

