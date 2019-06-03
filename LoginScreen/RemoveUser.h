#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "MainScreen.h"
using namespace std;
void RemoveUser(string ID) {
	string temp, temp3, txt2;
	char *txt;
	ofstream temp2("temp2.txt", ios::trunc);
	fstream myfile("base.txt");
	if (!myfile)
	{
		cout << "Problem with opening file base.txt\n";
		return;
	}
	else
	{
		while (!myfile.eof())
		{
			getline(myfile, temp);
			if (ID == temp) {
				getline(myfile, temp3);
			}
			else {
				temp2 << endl << temp;
			}
		}
	}
	myfile.close();
	myfile.open("base.txt", ios::out | ios::trunc);
	myfile.close();
	temp2.close();
	string line, name = "";
	ifstream myfile2;
	myfile2.open("temp2.txt");
	ofstream temp4;
	temp4.open("temp4.txt", ios::trunc);
	while (!myfile2.eof())
	{
		getline(myfile2, line);
		if (line.empty()) {
			getline(myfile2, line);
			temp4 << line;
		}
		else
			temp4 << endl << line;
	}
	myfile2.close();
	temp4.close();
	remove("temp2.txt");
	remove("base.txt");
	rename("temp4.txt", "base.txt");
	txt2 = ID + ".txt";
	txt = new char[txt2.length()];
	for (int i = 0; i < (int)txt2.length(); i++) {
		txt[i] = txt2[i];
	}
	txt[txt2.length()] = '\0';
	if (remove(txt) != 0) perror("Error deleting file");
}


