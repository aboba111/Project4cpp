#pragma once
#include<iostream>
#include "vessel.h"
#include <vector>
class table
{   protected:
	std::vector<vessel> my;
	std::vector<vessel> myOponent;
public:
	std::vector<std::string> getInfo();
	void addVessles(std::string x);
};

