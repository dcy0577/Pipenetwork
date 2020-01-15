#ifndef Tube_HPP
#define Tube_HPP

#include<string>
#include<vector>
#include "Node.hpp"
namespace cie
{
	namespace pipenetwork
	{


		class Tube
		{
		public:

			Tube(Node* node1, Node* node2, double diameter);
			double length() const;
			double permeability() const;
			double diameter() const;
			const Node* node1() const;
			const Node* node2() const; 
		private:
			const Node* node1_;
			const Node* node2_;
			double length_;
			double permeability_;
			double diameter_;

		};
	}
}
#endif // !Tube_H