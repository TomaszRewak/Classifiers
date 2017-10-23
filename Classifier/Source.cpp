#pragma once

#include <iostream>
#include <string>

#include "Iris.hpp"
#include "Glass.hpp"
#include "Credit.hpp"
#include "Ecoli.hpp"

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);

	Classifier::Test::Iris::iris_test();
	Classifier::Test::Glass::glass_test();
	Classifier::Test::Credit::credit_test();
	Classifier::Test::Ecoli::ecoli_test();

	getchar();
}