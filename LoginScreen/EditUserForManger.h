#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void ChangeGroup(string ID, string NewGroup) {
	string txt, data, temp2;
	txt = ID + ".txt";
	fstream details(txt);
	if (details.fail()) {
		cout << "Change group error\n";
	}
	else {
		ofstream temp("tempUserChange.txt", ios::trunc);
		while (!details.eof()) {
			getline(details, temp2);
			if ('G' == temp2[0] && temp2[1] == 'r') {
				temp << "Group: " << NewGroup << endl;
			}
			else {
				temp << temp2 << endl;
			}
		}
		details.close();
		details.open(txt, ios::out | ios::trunc);
		details.close();
		temp.close();
		ifstream infile("tempUserChange.txt");
		ofstream outfile(txt);
		string content = "";
		int i;

		for (i = 0; infile.eof() != true; i++)
			content += infile.get();
		i--;
		content.erase(content.end() - 1);
		infile.close();
		outfile << content;
		outfile.close();
	}
}
void ChangeLastName(string ID, string NewLN) {
	string txt, data, temp2;
	txt = ID + ".txt";
	fstream details(txt);
	if (details.fail()) {
		cout << "Last name change error\n";
	}
	else {
		ofstream temp("tempUserChange.txt", ios::trunc);
		while (!details.eof()) {
			getline(details, temp2);
			if ('L' == temp2[0] && temp2[1] == 'a') {
				temp << "Last Name:" << NewLN << endl;
			}
			else {
				temp << temp2 << endl;
			}
		}
		details.close();
		details.open(txt, ios::out | ios::trunc);
		details.close();
		temp.close();
		ifstream infile("tempUserChange.txt");
		ofstream outfile(txt);
		string content = "";
		int i;

		for (i = 0; infile.eof() != true; i++)
			content += infile.get();
		i--;
		content.erase(content.end() - 1);
		infile.close();
		outfile << content;
		outfile.close();
	}
}
void ChangeFirstName(string ID, string NewFN) {
	string txt, data, temp2;
	txt = ID + ".txt";
	fstream details(txt);
	if (details.fail()) {
		cout << "First name change error\n";
	}
	else {

		ofstream temp("tempUserChange.txt", ios::trunc);
		while (!details.eof()) {
			getline(details, temp2);
			if ('F' == temp2[0] && temp2[1] == 'i') {
				temp << "First Name:" << NewFN << endl;
			}
			else {
				temp << temp2 << endl;
			}
		}
		details.close();
		details.open(txt, ios::out | ios::trunc);
		details.close();
		temp.close();
		ifstream infile("tempUserChange.txt");
		ofstream outfile(txt);
		string content = "";
		int i;
		for (i = 0; infile.eof() != true; i++)
			content += infile.get();
		i--;
		content.erase(content.end() - 1);
		infile.close();
		outfile << content;
		outfile.close();
	}
}
void ChangeRank(string ID, string NewRank){
	string txt, data, temp2;
	txt = ID + ".txt";
	fstream details(txt);
	if (details.fail()) {
		cout << "Rank change error\n";
	}
	else {
		ofstream temp("tempUserChange.txt",ios::trunc);
		while (!details.eof()) {
			getline(details, temp2);
			if ('R' == temp2[0] && temp2[1]=='a') {
				temp <<"Rank:"<<NewRank<< endl;
			}
			else {
				temp << temp2 << endl;
			}
		}
		details.close();
		details.open(txt, ios::out | ios::trunc);
		details.close();
		temp.close();
		ifstream infile("tempUserChange.txt");
		ofstream outfile(txt);
		string content = "";
		int i;
		for (i = 0; infile.eof() != true; i++)
			content += infile.get();
		i--;
		content.erase(content.end() - 1);
		infile.close();
		outfile << content;
		outfile.close();
	}
	cout << " The Rank changed" << endl;
}