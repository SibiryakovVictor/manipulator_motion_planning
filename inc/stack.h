#pragma once

#include <iostream>
#include <iterator>

#include "roadmap/roadmap_parameters.h"



namespace tools
{

    template < typename T, unsigned stackSize > class Stack;

    typedef Stack< unsigned, roadmap::limit_amount_nn > stackDefault;

    template < class T, unsigned stackSize >
    class Stack
    {

    public:

        Stack() :
            m_data(),
            m_headPos( 0 )
        {
            std::fill( m_data, m_data + stackSize, UINT16_MAX );
        }

        void push( T obj )
        {

            if ( m_headPos == stackSize )
            {

                while ( true )
                {
                    ; /* попытка поместить элемент в заполненный стек */ 
                }

            }

            m_data[ m_headPos ] = obj;

            m_headPos++;

        }

        void pop()
        {

            if ( m_headPos == 0 )
            {

                while ( true )
                {
                    ; /* попытка вытолкнуть элемент из пустого стека */
                }

            }

            m_headPos--;

        }

        T top() const
        {

            if ( m_headPos == 0 )
            {

                while ( true )
                {
                    ; /* попытка вз€ть верхний элемент из пустого стека */
                }

            }

            return m_data[ m_headPos - 1 ];

        }

        void clear()
        {
            m_headPos = 0;
        }

        bool isFull() const
        {
            return ( m_headPos == stackSize );
        }

        bool isEmpty() const
        {
            return ( m_headPos == 0 );
        }

        T const * begin() const
        {
            return m_data;
        }

        T const * end() const
        {
            return m_data + m_headPos;
        }


    private:

        T m_data[ stackSize ];

        int m_headPos;

    };

}

