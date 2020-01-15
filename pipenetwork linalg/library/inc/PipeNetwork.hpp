#ifndef PipeNetwork_HPP
#define PipeNetwort_HPP


#include<string>
#include<vector>
#include "Tube.hpp"
#include "Node.hpp"

namespace cie
{
	namespace pipenetwork
	{


		class PipeNetwork
		{
		public:
			PipeNetwork(const std::string& filename); //read input file
			std::vector<double> computeFluxes() const;

		private:
			std::vector<Tube> Tubes;
			std::vector<Node> Nodes;
		};
	}
}
#endif // !PipeNetwork_H