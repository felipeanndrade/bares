#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <iostream>

/*!	\file	stack.hpp
 * 	\author Felipe Ramos
 */

namespace sc
{
	/** Stack implementation */
	template <typename T>
		class stack{
		private:
			T *storage; 			//!< Stores all data
			size_t m_size; 			//!< Size of the stored data
			size_t m_top; 			//!< Top number

			/*! Allocates twice the current amount of memory */
			void double_storage( void ){
			/* Function implementation {{{*/
				T* temp = new T[2*m_size];
				for( auto i(0u); i < m_top; i++) {
					// copy data to a new area
					temp[i] = storage[i];
				}
				
				// free's the old area
				delete [] storage;

				// Redirects the pointer to the new area
				storage = temp;

				// doubles the size
				m_size *= 2;
			}
			/*}}}*/

		public:
			/*! Constructor */
			explicit stack( void ) : storage(new T[1]), m_size(1), m_top(0){ }	//!< Default constructor
			~stack( void ){ delete [] storage; }								//!< Default destructor

			/*! Inserts a new element at the top of the stack */
			void push( T& value ){
			/* Function implementation {{{*/
				// if it's full, allocates more
				if(m_size == m_top){
					double_storage();
				}
				storage[m_top++] = value;
			}
			/*}}}*/

			/*! Removes the element at the top of the stack*/
			void pop( void ){
			/* Function implementation {{{*/
				if( empty() )
					throw std::runtime_error("pew pop");

				--m_top;
			}
			/*}}}*/

			/*! Returns the element at the top of the stack*/
			T top( void ) const{
			/* Function implementation {{{*/
				if( empty() )
					throw std::runtime_error("pew top");
				return storage[m_top-1];
			}
			/*}}}*/

			/*! Checks if the stack is empty */
			bool empty( void ) const{
			/* Function implementation {{{*/
				return m_top == 0;
			}
			/*}}}*/

			/*! Returns the size of the stack */
			size_t size( void ) const{
			/* Function implementation {{{*/
				return m_top;
			}
			/*}}}*/

			/*! Deletes all elements from the stack*/
			void clear( void ){
			/* Function implementation {{{*/
				m_top = 0;
			}
			/*}}}*/

	};
}
#endif
