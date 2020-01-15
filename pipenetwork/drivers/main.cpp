#include <iostream>
#include <fstream>
#include "PipeNetwork.hpp"
#include "Tube.hpp"
#include "Node.hpp"
#include "linalg.hpp"
#include <string>
using namespace cie;
using namespace pipenetwork;
using namespace linalg;



int main()
{
     //readfile 
    std::string filename = "Pipedata.txt";
    PipeNetwork network(filename);
	std::cout << "read file finished" << std::endl;
	
	// get fluxes
	std::vector<double> fluxes = network.computeFluxes();
	std::cout << "Expected fluxes: " << std::endl;
	for (int i = 0; i < fluxes.size(); i++)
	{
		std::cout << fluxes[i] << std::endl;
	}
   
	return 0;
}
	


