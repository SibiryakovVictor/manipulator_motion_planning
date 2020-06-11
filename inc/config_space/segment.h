#pragma once

#include "config_space/point.h"




namespace config_space
{

    class Segment
    {

    public:

        explicit Segment() :
            m_start(), m_end(), m_intervals{ 0.f }, m_maxInterPos( 0 )
        {}

        explicit Segment( const Point & start, const Point & end ) :
            m_start( start ), m_end( end ), m_intervals{ 0.f }, m_maxInterPos( 0 )
        {
            calcIntervals();
        }

        explicit Segment( Point && start, Point && end ) :
            m_start( start ), m_end( end ), m_intervals{ 0.f }, m_maxInterPos( 0 )
        {
            calcIntervals();
        }

        Point getPoint( float param ) const;

        float getMaxInterval() const;

        void changeStartEnd( const Point & start, const Point & end );

        float calcParamStep( float prec ) const;

    private:

        Point m_start;
        Point m_end;

        float m_intervals[ conf_space_dims ];

        uint8_t m_maxInterPos;

        void calcIntervals();

    };

}

