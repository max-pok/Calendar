#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "GlobalClass.h"
//#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
void AddUserToSystem(char ID[10],string name, string surename, int rank, string group)
{
	char Password[7] = { "000000" }, *for_details;
	string temp, txt;
	ofstream details;
	ofstream myfile("base.txt", ios::app);
	if (!myfile)
	{
		cout << "Problem with opening file base.txt\n";
		return;
	}
	else
	{
		for (int j = 0; j < (int)strlen(ID) ; j++) {
			temp += ID[j];
		}
		for_details = new char[temp.length()];
		for (int i = 0; i < (int)temp.length() + 1; i++)
		{
			for_details[i] = temp[i];
		}
		myfile << endl;
		myfile << ID;
		myfile << endl;
		txt = temp + ".txt";
		details.open(txt);
		if (!details)
		{
			cout << "Problem with opening file Worker_Info.txt\n";
			return;
		}
		//put pass in file
		myfile << Password;
		details << "ID:"<<ID<<endl;
		//put rank in file
		details.write("Rank:", 5);
		switch (rank)
		{
		case 1:
			details.write("1", 1);
			break;
		case 2:
			details.write("2", 1);
			break;
		case 3:
			details.write("3", 1);
			break;
		default:
			break;
		}
		details << endl;
		//put first name in file
		for_details = new char[(name).length()];
		for (int i = 0; i < (int)(name).length() + 1; i++)
		{
			for_details[i] = (name)[i];
		}
		details.write("First Name:", 11);
		details.write(for_details, (name).length() + 1);
		details << endl;
		//put last name in file
		for_details = new char[(surename).length()];
		for (int i = 0; i < (int)(surename).length() + 1; i++)
		{
			for_details[i] = (surename)[i];

		}
		details.write("Last Name:", 10);
		details.write(for_details, (surename).length() + 1);
		details << endl;
		if (group != "") details << "Group: " << group;
		else details << "Group: None";
		details << endl;
	}
	
	myfile.close();
	details.close();
}