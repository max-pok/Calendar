#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std; 

void reset() {
	int i = 0;
	string ID,temp;
	char* txt = (char*)malloc(sizeof(char) * 15);
	fstream myfile("base.txt");
	while (getline(myfile, ID)) {
		while (ID[i] != '\0') {
			txt[i] = ID[i];
			i++;
		}
		txt[i] = '.';
		txt[i + 1] = 't';
		txt[i + 2] = 'x';
		txt[i + 3] = 't';
		txt[i + 4] = '\0';
		i = 0;
		remove(txt);
		getline(myfile, ID);
	}
	myfile.close();
	//remove("base.txt");
	//remove("PersonalEvents.txt");
	//remove("GlobalEvents.txt");
	//remove("TeamEvents.txt");
	ofstream base, pmyfile, gmyfile, tmyfile;
	base.open("base.txt", ios::trunc);
	base << "123456" << endl << "000000";
	ofstream details;
	details.open("123456.txt", ios::trunc);
	details << "ID:123456" << endl << "Rank:3" << endl << "First Name:Unknown" << endl << "Last Name:Unknown" <<endl<< "Group:Unknown";
	pmyfile.open("PersonalEvents.txt",ios::trunc);
	gmyfile.open("GlobalEvents.txt",ios::trunc);
	tmyfile.open("TeamEvents.txt",ios::trunc);
	pmyfile.close();
	tmyfile.close();
	gmyfile.close();
	base.close();
}
