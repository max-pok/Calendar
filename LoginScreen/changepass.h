#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void changepass(char id[10], char newpass[15]) {
	cout << newpass << endl;
	fstream base("base.txt");
	if (base.fail()) {
		cout << "Change pass error\n";
	}
	else {
		char id2[10];
		ofstream temp("tempPassChange.txt");
		while (!base.eof()) {
			base >> id2;
			if (strcmp(id, id2) != 0) {
				temp << id2 << endl;
			}
			else {
				temp << id2 << endl;
				temp << newpass << endl;
				base >> id2;
			}
		}
		base.close();
		base.open("base.txt", ios::out | ios::trunc);
		base.close();
		temp.close();
		ifstream infile("tempPassChange.txt");
		ofstream outfile("base.txt");
		string content = "";
		int i;
		for (i = 0; infile.eof() != true; i++) content += infile.get();
		i--;
		content.erase(content.length() - 2);
		infile.close();
		outfile << content; 
		outfile.close();
	}
}