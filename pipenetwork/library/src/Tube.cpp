#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include"Tube.hpp"
#include<cmath>
#define PI acos(-1)

namespace cie
{
	namespace pipenetwork
	{


		Tube::Tube(Node* node1, Node* node2, double diameter)
		{
			node1_ = node1;
			node2_ = node2;
			diameter_ = diameter;
		}
		double Tube::length() const
		{
			double x1 = node1_->x();
			double y1 = node1_->y();
			double x2 = node2_->x();
			double y2 = node2_->y();
			double a = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
			double length_ = std::sqrt(a);
			return length_ ; //local
		}
		double Tube::permeability() const
		{
			//double pi = 3.14159265358979323846
			double pi = 3.14159265358979323846;
			//this statt length_
			double permeability_ = pi * 9.81 * std::pow(diameter_, 4) / (128 * 1e-6 * this->length()); // double B = pi * 9.81 * std::pow( 0.3, 4 ) / ( 128 * 1e-6 * 2.5 );
			return permeability_;
		}

		double Tube::diameter() const
		{
			return diameter_;
		}

		const Node* Tube::node1() const
		{
			return node1_;
		}

		const Node* Tube::node2() const
		{
			return node2_;
		}
	}
}