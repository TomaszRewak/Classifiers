#include <iostream>
#include <string>

#include "FeatureSet.hpp"

#include "Glass.hpp"

using namespace std;

int main()
{
	Classifier::Test::Glass::glass_test();

	auto initialFeatureSet = Classifier::Data::FeatureSet<int, int, string, int, float>();
	
	//initialFeatureSet.add(10, 2, "13", 5, 0.3f);
	//initialFeatureSet.add(20, 2, "532", 5, 0.3f);
	//initialFeatureSet.add(30, 2, "12", 5, 0.3f);
	//
	//initialFeatureSet.print();
	//
	//auto transformed = 
	//	initialFeatureSet
	//		.transform<3>([&](int a) { return 2.1 * a; })
	//		.transform<2>([&](string a) { return stoi(a) + 10; })
	//		.remove<1>()
	//		.add<int>()
	//		.reorder<0, 2>();
	//
	//transformed.print();

	getchar();
}