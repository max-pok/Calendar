#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;
string GetRank(int rank) {
	if (rank == 3) return "Status: Admin";
	else if (rank == 2) return "Status: Team Leader";
	else return "Status: Regular User";
}
bool leapYear(int y) { return (y % 4 == 0); }
bool fullMonth(int m) { return (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12); }
int nextMonth(int curr) {
	if (curr > 0 && curr < 12) return curr + 1;
	else return 1;
}
int prevMonth(int curr) {
	if (curr > 1 && curr < 13) return curr - 1;
	else return 12;
}
int convertCharArrayToInt(char in[10]) {
	int out = 0;
	for (int i = 0; i < (int)strlen(in); i++) out = (out * 10) + (in[i] - '0');
	return out;
}
int checkRank(int id) {
	fstream personalDetails;
	string theID = to_string(id) + ".txt",temp;
	personalDetails.open(theID);
	personalDetails >> temp;
	personalDetails >> temp;
	personalDetails.close();
	return temp[5] - '0';
}
string GetUserName(int id) {
	fstream personalDetails;
	string theID = to_string(id) + ".txt",temp, name = "";
	personalDetails.open(theID);
	for (int i = 0; i < 3; i++) getline(personalDetails, temp);
	for (int i = 11; i < (int)temp.length(); i++) name = name + temp[i];
	personalDetails.close();
	return name;
}
string GetUserSurname(int id) {
	fstream personalDetails;
	string theID = to_string(id) + ".txt", temp, name = "";
	personalDetails.open(theID);
	for (int i = 0; i < 4; i++) getline(personalDetails, temp);
	for (int i = 10; i < (int)temp.length(); i++) name = name + temp[i];
	personalDetails.close();
	return name;
}
string getUserTeamName(int id) {
	fstream personalDetails;
	string theID = to_string(id) + ".txt", temp, name = "";
	personalDetails.open(theID);
	getline(personalDetails, temp);
	getline(personalDetails, temp);
	getline(personalDetails, temp);
	getline(personalDetails, temp);
	getline(personalDetails, temp);
	for (int i = 7; i < (int)temp.length(); i++) name = name + (char)temp[i];
	personalDetails.close();
	return name;
}
string returnCurrentMonthString(int m) {
	switch (m) {
	case 1: return "January";
	case 2: return "February";
	case 3: return "March";
	case 4: return "April";
	case 5: return "May";
	case 6: return "June";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "October";
	case 11: return "November";
	case 12: return "December";
	}
	return "January";
}
string getTimeOfEvent(string nameOfEvent,string id, string date) {
	fstream personalEvents;
	string timeOfEvent,temp;
	personalEvents.open("PersonalEvents.txt");
	while (!personalEvents.eof()) {
		getline(personalEvents, temp);
		if (temp == id) {
			getline(personalEvents, temp);
			if (temp == date) {
				getline(personalEvents, temp);
				if (temp == nameOfEvent) {
					getline(personalEvents, temp);
					getline(personalEvents, timeOfEvent);
					personalEvents.close();
					return timeOfEvent;
				} else for (int i = 0; i < 3; i++) getline(personalEvents, temp);
			} else for (int i = 0; i < 4; i++) getline(personalEvents, temp);
		} else for (int i = 0; i < 5; i++) getline(personalEvents, temp);
	}
	personalEvents.close();
	return "00:00";
}
string getPriorityOfEvent(string nameOfEvent, string id, string date) {
	fstream personalEvents;
	string temp;
	personalEvents.open("PersonalEvents.txt");
	while (!personalEvents.eof()) {
		getline(personalEvents, temp);
		if (temp == id) {
			getline(personalEvents, temp);
			if (temp == date) {
				getline(personalEvents, temp);
				if (temp == nameOfEvent) {
					getline(personalEvents, temp);
					return temp;
					personalEvents.close();
				} else for (int i = 0; i < 3; i++) getline(personalEvents, temp);
			} else for (int i = 0; i < 4; i++) getline(personalEvents, temp);
		} else for (int i = 0; i < 5; i++) getline(personalEvents, temp);
	}
	personalEvents.close();
	return "";
}
string getEventType(string nameOfEvent, string id, string date) {
	fstream personalEvents;
	personalEvents.open("PersonalEvents.txt");
	string temp, eventType;
	while (!personalEvents.eof()) {
		getline(personalEvents, temp);
		if (temp == id) {
			getline(personalEvents, temp);
			if (temp == date) {
				getline(personalEvents, temp);
				if (temp == nameOfEvent) {
					getline(personalEvents, temp);
					getline(personalEvents, temp);
					getline(personalEvents, eventType);
					personalEvents.close();
					return eventType;
				} else for (int i = 0; i < 3; i++) getline(personalEvents, temp);
			} else for (int i = 0; i < 4; i++) getline(personalEvents, temp);
		} else for (int i = 0; i < 5; i++) getline(personalEvents, temp);
	}
	personalEvents.close();
	return "";
}
string getTimeOfTeamEvent(string nameOfEvent, string teamName , string date) {
	fstream personalEvents;
	string timeOfEvent, temp;
	personalEvents.open("TeamEvents.txt");
	while (!personalEvents.eof()) {
		getline(personalEvents, temp);
		if (temp == teamName) {
			getline(personalEvents, temp);
			if (temp == date) {
				getline(personalEvents, temp);
				if (temp == nameOfEvent) {
					getline(personalEvents, temp);
					getline(personalEvents, timeOfEvent);
					personalEvents.close();
					return timeOfEvent;
				}
				else for (int i = 0; i < 3; i++) getline(personalEvents, temp);
			}
			else for (int i = 0; i < 4; i++) getline(personalEvents, temp);
		}
		else for (int i = 0; i < 5; i++) getline(personalEvents, temp);
	}
	personalEvents.close();
	return "00:00";
}
string getPriorityOfTeamEvent(string nameOfEvent, string teamName, string date) {
	fstream personalEvents;
	string temp;
	personalEvents.open("TeamEvents.txt");
	while (!personalEvents.eof()) {
		getline(personalEvents, temp);
		if (temp == teamName) {
			getline(personalEvents, temp);
			if (temp == date) {
				getline(personalEvents, temp);
				if (temp == nameOfEvent) {
					getline(personalEvents, temp);
					return temp;
					personalEvents.close();
				}
				else for (int i = 0; i < 3; i++) getline(personalEvents, temp);
			}
			else for (int i = 0; i < 4; i++) getline(personalEvents, temp);
		}
		else for (int i = 0; i < 5; i++) getline(personalEvents, temp);
	}
	personalEvents.close();
	return "";
}
string getTeamEventType(string nameOfEvent, string teamName, string date) {
	fstream personalEvents;
	personalEvents.open("TeamEvents.txt");
	string temp, eventType;
	while (!personalEvents.eof()) {
		getline(personalEvents, temp);
		if (temp == teamName) {
			getline(personalEvents, temp);
			if (temp == date) {
				getline(personalEvents, temp);
				if (temp == nameOfEvent) {
					getline(personalEvents, temp);
					getline(personalEvents, temp);
					getline(personalEvents, eventType);
					personalEvents.close();
					return eventType;
				}
				else for (int i = 0; i < 3; i++) getline(personalEvents, temp);
			}
			else for (int i = 0; i < 4; i++) getline(personalEvents, temp);
		}
		else for (int i = 0; i < 5; i++) getline(personalEvents, temp);
	}
	personalEvents.close();
	return "";
}
int convertStringToInt(string oldOne) {
	int newOne = 0;
	for (int i = 0; i < (int)oldOne.length(); i++) newOne = (newOne * 10) + (int)(oldOne[i] - '0');
	return newOne;
}