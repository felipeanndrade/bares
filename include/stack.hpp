#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <iostream>

namespace sc
{
	template <typename T>
		class stack{
		private:
			T *storage; //<! armazena os dados
			size_t m_size; //tamanho de armazenamento
			size_t m_topo; //indice do topo

			/*! Allocates twice the current amount of memory */
			void double_storage( void ){
/* Function implementation {{{*/
				T* temp = new T[2*m_size];
				for( auto i(0u); i < m_topo; i++) {
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
			explicit stack( void ) : storage(new T[1]), m_size(1), m_topo(0){ }
			~stack( void ){ delete [] storage; }

			/*! Inserts a new element at the top of the stack */
			void push( T& value ){
				/* Function implementation {{{*/
				// if it's full, allocates more
				if(m_size == m_topo){
					double_storage();
				}
				storage[m_topo++] = value;
			}
			/*}}}*/

			/*! Removes the element at the top of the stack*/
			void pop( void ){
/* Function implementation {{{*/
				if( empty() )
					throw std::runtime_error("pew pop");

				--m_topo;
			}
/*}}}*/

			/*! Returns the element at the top of the stack*/
			T top( void ) const{
/* Function implementation {{{*/
				if( empty() )
					throw std::runtime_error("pew top");
				return storage[m_topo-1];
			}
/*}}}*/

			/*! Checks if the stack is empty */
			bool empty( void ) const{
/* Function implementation {{{*/
				return m_topo == 0;
			}
/*}}}*/

			/*! Returns the size of the stack */
			size_t size( void ) const{
/* Function implementation {{{*/
				return m_topo;
			}
/*}}}*/

			/*! Deletes all elements from the stack*/
			void clear( void ){
/* Function implementation {{{*/
				m_topo = 0;
			}
/*}}}*/

	};
}
#endif
