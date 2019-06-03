#pragma once
#include <fstream>
#include "additionalFunc.h"
using namespace std;
int LoginSys(char ID[10], char pass[10]) {
	fstream base;
	base.open("base.txt");
	char temp[10];
	while (!base.eof()) {
		base.getline(temp, 10);
		if (strcmp(temp, ID) == 0) {
			base.getline(temp, 10);
			if (strcmp(temp, pass) == 0) return checkRank(convertCharArrayToInt(ID));
			else return 4;
		}
	}
	return 5;
}