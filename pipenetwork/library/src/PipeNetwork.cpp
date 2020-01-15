#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include "PipeNetwork.hpp"
#include <fstream>
#include"linalg.hpp"


namespace cie
{
	namespace pipenetwork
	{

		// soll richtig
		PipeNetwork::PipeNetwork(const std::string& filename)
		{
			std::ifstream infile(filename);
			int numberOfNodes;
			int numberOfTubes;
			infile >> numberOfNodes;
			infile >> numberOfTubes;
			Nodes.reserve(numberOfNodes);
			Tubes.reserve(numberOfTubes);
			for (int i = 0; i < numberOfNodes; ++i)
			{
				double x, y, flow;
				infile >> x >> y >> flow;
				Node newNode(x, y, flow, i);
				Nodes.push_back(newNode);
			}
			for (int i = 0; i < numberOfTubes; ++i)
			{
				int nodeId1, nodeId2;
				double diameter;
				infile >> nodeId1 >> nodeId2 >> diameter;
				Tube newTube(&Nodes[nodeId1], &Nodes[nodeId2], diameter); //reference/pointer?
				Tubes.push_back(newTube);
			}
		}


		std::vector <double> PipeNetwork::computeFluxes() const
		{
			// set up permeability matrix
			linalg::Matrix Bmatrix(Nodes.size(), Nodes.size(), 0.0);
			std::vector<double> B(Tubes.size());
			for (int i = 0; i < Tubes.size(); i++)
			{
				B[i] = Tubes[i].permeability();
			}
			for (int i = 0; i < Tubes.size(); i++)
			{
				Bmatrix(Tubes[i].node1()->id(), Tubes[i].node1()->id()) += B[i];
				Bmatrix(Tubes[i].node2()->id(), Tubes[i].node2()->id()) += B[i];
				Bmatrix(Tubes[i].node1()->id(), Tubes[i].node2()->id()) -= B[i];
				Bmatrix(Tubes[i].node2()->id(), Tubes[i].node1()->id()) -= B[i];

			}

			//load vector
			std::vector <double> Q(Nodes.size());
			for (int i = 0; i < Nodes.size(); i++)
			{
				Q[i] = -1 * Nodes[i].flow();
			}
			// boundary condition
			for (int i = 1; i < Nodes.size(); i++)
			{
				Bmatrix(i, 0) = 0;
				Bmatrix(0, i) = 0;
			}
			Bmatrix(0, 0) = 1;
			Q[0] = 0;

			//solve linear system get head vector h
			std::vector <double> h = linalg::solve(Bmatrix, Q);

			// postprocess fluxes q
			std::vector <double> q(Tubes.size());
			for (int i = 0; i < Tubes.size(); i++)
			{
				double h1 = h[Tubes[i].node1()->id()];
				double h2 = h[Tubes[i].node2()->id()];
				q[i] = B[i] * (h1 - h2);
			}


			return q;
		}



	}
}

