#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include "GlobalClass.h"
#include "add_personal_event.h"
#include "AddUserSCR.h"
#include "DeleteUserSCR.h"
#include "EditUserSCR.h"
#include "additionalFunc.h"
#include "AddUserToTeamSCR.h"
#include "ChangePasswordSCR.h"
#include "ResetSCR.h"
#include "additionalFunc.h"
namespace MainScreen {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Text;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Globals;
	///static info
	int ShowCurrentMonth = 1, ShowMonth = ShowCurrentMonth, ShowCurrentYear = 2019, ShowYear = ShowCurrentYear;
	int currentUserID, currentUserRank, currentSelectedTypeOfEvent;
	string teamName, chosen_event;
	bool dateChosen = false;
	string converSpecialStringToString(String ^ oldOne) {
		string newOne = "";
		for (int i = 0; i < oldOne->Length; i++) newOne = newOne + (char)oldOne[i];
		return newOne;
	}
	String ^ returnCurrentMonth(int m) {
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
	String ^ returnYear(int y) {
		string temp = "0000";
		for (int i = 3; i >= 0; i--) {
			temp[i] = char('0' + y % 10);
			y = y / 10;
		}
		return gcnew String(temp.c_str());
	}
	void HideAddGlobalEvent();
	void HelloUserShow();
	void month_and_year_check(int days, int month, int year) {
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			days = 30;
		}
		else if (month == 02)
		{
			bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
			if (leapyear == 0)
				days = 29;
			else
				days = 29;
		}
		else
			days = 31;
	}
	int convertSpecialStringToInt(String ^ oldOne) {
		int newOne = 0;
		for (int i = 0; i < oldOne->Length; i++) newOne = (newOne * 10) + (int)(oldOne[i] - '0');
		return newOne;
	}
	string currentTime() {
		time_t now = time(0);
		struct tm  tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%X", &tstruct);
		return buf;
	}
	string correntMonth_and_Year() {
		time_t now = time(0);
		struct tm  tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%m", &tstruct);
		return buf;
	}
	///
	/// <summary>
	/// Summary for MainScreen
	/// </summary>
	public ref class MainScreen : public System::Windows::Forms::Form
	{
	public:
		MainScreen(void) { // Constractor
			InitializeComponent();
			HelloUserShow();
			HideAddGlobalEvent();
			ShowMonth = ShowCurrentMonth;
			ShowYear = ShowCurrentYear;
			ShowCurrentMonthButton->Text = returnCurrentMonth(ShowMonth);
			ShowCurrentYearButton->Text = returnYear(ShowYear);
			AddTeamGlobalEventButton->Visible = false;
			AddLocalEventButton->Visible = false;
			DayEventsViewPanel->Visible = false;
			SettingsPanel->Visible = false;
			AddNewUserButton->Visible = false;
			SysInfoButton->Visible = false;
			UserListLabel->Visible = false;
			UserList->Visible = false;
			DeleteUserButton->Visible = false;
			EditUserButton->Visible = false;
			UserIDLabel->Visible = false;
			UserIDTextBox->Visible = false;
			UserNameLabel->Visible = false;
			UserNameTextBox->Visible = false;
			UserSurnameTextBox->Visible = false;
			UserRankLabel->Visible = false;
			UserRankTextBox->Visible = false;
			UserTeamLabel->Visible = false;
			UserTeamtextBox->Visible = false;
			UserDetailsLabel->Visible = false;
			SysInfoPanel->Visible = false;
			TimeLabel->Text = gcnew String(currentTime().c_str());
			timer1->Start();
			PersonaIDLabel->Text = gcnew String(("ID: " + to_string(currentUserID)).c_str());
			PersonalNameLabel->Text = gcnew String(("Name: " + GetUserName(currentUserID) + " " + GetUserSurname(currentUserID)).c_str());
			PersonalTeamStatusLabel->Text = gcnew String((GetRank(currentUserRank)).c_str());
			PersonalTeamLabel->Text = gcnew String(("Team: " + getUserTeamName(currentUserID)).c_str());

		}
		void HelloUserShow() {
			//Hello user feature
			String ^ temp = gcnew String(GetUserName(currentUserID).c_str());
			HelloUserLabel->Text = "Hello " + temp + "!";
		}
		void month_and_year_check(int month, int year) {
			//Num of day in the month check
			if (month == 4 || month == 6 || month == 9 || month == 11) {
				Day29Button->Enabled = true;
				Day30Button->Enabled = true;
				Day31Button->Enabled = false;
			}
			else if (month == 2) {
				bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
				if (leapyear == false) {
					Day29Button->Enabled = false;
					Day30Button->Enabled = false;
					Day31Button->Enabled = false;
				}
				else {
					Day29Button->Enabled = true;
					Day30Button->Enabled = false;
					Day31Button->Enabled = false;
				}
			}
			else {
				Day29Button->Enabled = true;
				Day30Button->Enabled = true;
				Day31Button->Enabled = true;
			}
		}
		void HideAddGlobalEvent() {
			//Add events check (by rank)
			if (currentUserRank == 1) this->AddTeamGlobalEventButton->Hide();
			else if (currentUserRank == 2) this->AddTeamGlobalEventButton->Text = "Add Team Event";
			else if (currentUserRank == 3) this->AddTeamGlobalEventButton->Text = "Add Global Event";
		}
		void show_date(int day) {
			//Day show feature
			GlobalClass::month = returnCurrentMonth(ShowMonth);
			GlobalClass::year = returnYear(ShowYear);
			ViewDayEventsButton->Text = returnCurrentMonth(ShowMonth) + " " + day + ", " + returnYear(ShowYear);
			if ((currentUserRank == 3) || (currentUserRank == 2 && teamName != "None")) AddTeamGlobalEventButton->Visible = true;
			AddLocalEventButton->Visible = true;
		}
		void RefreshDayEventsPanel() {
			//Day events panel refresh
			ListOfDayEvents->Items->Clear();
			ListOfTeamEvents->Items->Clear();
			ListOfGlobalEvents->Items->Clear();
			currentSelectedTypeOfEvent = 0;
			DayEventsViewPanel->Show();
			int tempDay = convertSpecialStringToInt(GlobalClass::day);
			string currentDate = returnCurrentMonthString(ShowMonth) + " " + to_string(tempDay) + " " + to_string(ShowYear);
			string checkID, checkDate, ignore, newItem = "", checkTeam;
			fstream personalEvents, teamEvents, GlobalEvents;
			ViewDayLabel->Text = GlobalClass::day;
			ViewMonthLabel->Text = GlobalClass::month;
			ViewYearLabel->Text = GlobalClass::year;
			personalEvents.open("PersonalEvents.txt");
			teamEvents.open("TeamEvents.txt");
			GlobalEvents.open("GlobalEvents.txt");
			while (!personalEvents.eof()) {
				getline(personalEvents, checkID);
				if (checkID.empty()) {
					getline(personalEvents, checkID);
				}
				getline(personalEvents, checkDate);
				getline(personalEvents, ignore);
				if (checkDate == currentDate && checkID == to_string(currentUserID)) {
					ListOfDayEvents->Items->Add(gcnew String(ignore.c_str()));
				}
				for (int i = 0; i < 3; i++) getline(personalEvents, ignore);
			}
			while (!teamEvents.eof()) {
				getline(teamEvents, checkTeam);
				getline(teamEvents, checkDate);
				getline(teamEvents, ignore);
				if (checkDate == currentDate && checkTeam == teamName) {
					ListOfTeamEvents->Items->Add(gcnew String(ignore.c_str()));
				}
				for (int i = 0; i < 3; i++) getline(teamEvents, ignore);
			}
			while (!GlobalEvents.eof()) {
				getline(GlobalEvents, checkDate);
				getline(GlobalEvents, ignore);
				if (checkDate == currentDate) {
					ListOfGlobalEvents->Items->Add(gcnew String(ignore.c_str()));
				}
				for (int i = 0; i < 3; i++) getline(GlobalEvents, ignore);
			}
			personalEvents.close();
			teamEvents.close();
			GlobalEvents.close();
			if (ListOfDayEvents->Items->Count > 0) ListOfDayEvents->SelectedIndex = 0;
			if (ListOfTeamEvents->Items->Count > 0) ListOfTeamEvents->SelectedIndex = 0;
			if (ListOfGlobalEvents->Items->Count > 0) ListOfGlobalEvents->SelectedIndex = 0;
			PriorityFillLabel->Text = "";
			TimeFillLabel->Text = "";
			TypeFillLabel->Text = "";
			DescriptionTextBox->Clear();
			EditEventButton->Show();
			EditEventButton->Enabled = false;
			DeleteEventButton->Show();
			DeleteEventButton->Enabled = false;
		}
		void refreshUserList() {
			//User list refresh
			fstream base;
			string IDString, temp;
			base.open("base.txt");
			UserList->Items->Clear();
			while (!base.eof()) {
				getline(base, IDString);
				if (to_string(currentUserID) != IDString) UserList->Items->Add(gcnew String(IDString.c_str()));
				getline(base, temp);
			}
		}
		void refreshTeamUserList() {
			fstream base;
			string IDString, temp;
			int IDint;
			base.open("base.txt");
			UserList->Items->Clear();
			while (!base.eof()) {
				getline(base, IDString);
				IDint = convertStringToInt(IDString);
				if (teamName == getUserTeamName(IDint) && to_string(currentUserID) != IDString) UserList->Items->Add(gcnew String(IDString.c_str()));
				getline(base, temp);
			}
			base.close();
		}
		void RemoveGlobalEvent() {
			string temp2, temp3, temp4, temp5, temp6;
			string month, day, year;
			fstream Gevent("GlobalEvents.txt");
			fstream temp("temp.txt", ios::app);
			while (!Gevent.eof()) {
				Gevent >> month;
				Gevent >> day;
				Gevent >> year;
				if (Gevent.eof()) {
					temp << endl;
					break;
				}
				String^ tempS2 = gcnew String(month.c_str());
				String^ tempS3 = gcnew String(day.c_str());
				String^ tempS4 = gcnew String(year.c_str());
				getline(Gevent, temp2);//next line
				getline(Gevent, temp3);//event name
				getline(Gevent, temp4);//priority
				getline(Gevent, temp5);//time
				getline(Gevent, temp6);//type
				String^ tempS5 = gcnew String(temp3.c_str());
				if (GlobalClass::month != tempS2 || GlobalClass::day != tempS3 || GlobalClass::year != tempS4 || tempS5 != GlobalClass::old_event_name) {
					temp << month << " " << day << " " << year << endl;
					temp << temp3 << endl;
					temp << temp4 << endl;
					temp << temp5 << endl;
					temp << temp6;
					if (!Gevent.eof()) temp << endl;
				}
			}
			Gevent.close();
			Gevent.open("GlobalEvents.txt", ios::out | ios::trunc);
			Gevent.close();
			temp.close();

			string line;
			ifstream myfile;
			myfile.open("temp.txt");
			ofstream tmp;
			tmp.open("tmp.txt", ios::trunc);
			while (!myfile.eof()) {
				getline(myfile, line);
				if (line.empty()) {
					getline(myfile, line);
					tmp << line;
				}
				else tmp << line<<endl;
			}
			myfile.close();
			tmp.close();
			remove("temp.txt");
			remove("GlobalEvents.txt");
			rename("tmp.txt", "GlobalEvents.txt");
		}
		void RemovePersonalTeamEvent(string fileName) {
			string temp2, temp1, temp3, temp4, temp5, temp6;
			string month, day, year;
			fstream Pevent(fileName);
			ofstream temp("temp.txt", ios::trunc);
			while (!Pevent.eof()) {
				getline(Pevent, temp1);//id
				String^ S1 = gcnew String(temp1.c_str());
				Pevent >> month;
				Pevent >> day;
				Pevent >> year;
				if (Pevent.eof()) {
					temp << endl;
					break;
				}
				String^ S2 = gcnew String(month.c_str());
				String^ S3 = gcnew String(day.c_str());
				String^ S4 = gcnew String(year.c_str());
				getline(Pevent, temp3);//empty line
				getline(Pevent, temp3);//event name
				String^ S5 = gcnew String(temp3.c_str());
				getline(Pevent, temp4);//priority
				getline(Pevent, temp5);//time
				getline(Pevent, temp6);//type
				if (S1 != GlobalClass::user_id || S2 != GlobalClass::month || S3 != GlobalClass::day || S4 != GlobalClass::year || S5 != GlobalClass::old_event_name) {
					temp << temp1 << endl;
					temp << month << " " << day << " " << year << endl;
					temp << temp3 << endl;
					temp << temp4 << endl;
					temp << temp5 << endl;
					temp << temp6;
					if (!Pevent.eof()) temp << endl;
				}
			}
			Pevent.close();
			Pevent.open(fileName, ios::out | ios::trunc);
			Pevent.close();
			temp.close();
			string line;
			ifstream myfile;
			myfile.open("temp.txt");
			ofstream tmp;
			tmp.open("tmp.txt", ios::trunc);
			while (!myfile.eof()) {
				getline(myfile, line);
				if (line.empty()) {
					getline(myfile, line);
					tmp << line;
				}
				else tmp << line << endl;
			}
			myfile.close();
			tmp.close();
			remove("temp.txt");
			remove("PersonalEvents.txt");
			rename("tmp.txt", "PersonalEvents.txt");

		}
		void delete_team_event(string fileName) {
			string temp2, temp1, temp3, temp4, temp5, temp6;
			string month, day, year;
			fstream Pevent(fileName);
			ofstream temp("temp.txt", ios::trunc);
			while (!Pevent.eof()) {
				getline(Pevent, temp1);//team name
				String^ S1 = gcnew String(getUserTeamName(currentUserID).c_str());
				Pevent >> month;
				Pevent >> day;
				Pevent >> year;
				if (Pevent.eof()) {
					temp << endl;
					break;
				}
				String^ S2 = gcnew String(month.c_str());
				String^ S3 = gcnew String(day.c_str());
				String^ S4 = gcnew String(year.c_str());
				getline(Pevent, temp3);//empty line
				getline(Pevent, temp3);//event name
				String^ S5 = gcnew String(temp3.c_str());
				getline(Pevent, temp4);//priority
				getline(Pevent, temp5);//time
				getline(Pevent, temp6);//type
				if (S1 != GlobalClass::team_name || S2 != GlobalClass::month || S3 != GlobalClass::day || S4 != GlobalClass::year || S5 != GlobalClass::old_event_name) {
					temp << temp1 << endl;
					temp << month << " " << day << " " << year << endl;
					temp << temp3 << endl;
					temp << temp4 << endl;
					temp << temp5 << endl;
					temp << temp6;
					if (!Pevent.eof()) temp << endl;
				}
			}
			Pevent.close();
			Pevent.open(fileName, ios::out | ios::trunc);
			Pevent.close();
			temp.close();
			string line;
			ifstream myfile;
			myfile.open("temp.txt");
			ofstream tmp;
			tmp.open("tmp.txt", ios::trunc);
			while (!myfile.eof()) {
				getline(myfile, line);
				if (line.empty()) {
					getline(myfile, line);
					tmp << line;
				}
				else tmp << line << endl;
			}
			myfile.close();
			tmp.close();
			remove("temp.txt");

			remove("TeamEvents.txt");
			rename("tmp.txt", "TeamEvents.txt");

		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Day1Button;
	private: System::Windows::Forms::Button^  Day2Button;
	private: System::Windows::Forms::Button^  Day3Button;
	private: System::Windows::Forms::Button^  Day4Button;
	private: System::Windows::Forms::Button^  Day5Button;
	private: System::Windows::Forms::Button^  Day6Button;
	private: System::Windows::Forms::Button^  Day7Button;
	private: System::Windows::Forms::Button^  Day8Button;
	private: System::Windows::Forms::Button^  Day9Button;
	private: System::Windows::Forms::Button^  Day10Button;
	private: System::Windows::Forms::Button^  Day11Button;
	private: System::Windows::Forms::Button^  Day12Button;
	private: System::Windows::Forms::Button^  Day13Button;
	private: System::Windows::Forms::Button^  Day14Button;
	private: System::Windows::Forms::Button^  Day15Button;
	private: System::Windows::Forms::Button^  Day16Button;
	private: System::Windows::Forms::Button^  Day17Button;
	private: System::Windows::Forms::Button^  Day18Button;
	private: System::Windows::Forms::Button^  Day19Button;
	private: System::Windows::Forms::Button^  Day20Button;
	private: System::Windows::Forms::Button^  Day21Button;
	private: System::Windows::Forms::Button^  Day22Button;
	private: System::Windows::Forms::Button^  Day23Button;
	private: System::Windows::Forms::Button^  Day24Button;
	private: System::Windows::Forms::Button^  Day25Button;
	private: System::Windows::Forms::Button^  Day26Button;
	private: System::Windows::Forms::Button^  Day27Button;
	private: System::Windows::Forms::Button^  Day28Button;
	private: System::Windows::Forms::Button^  Day29Button;
	private: System::Windows::Forms::Button^  Day30Button;
	private: System::Windows::Forms::Button^  Day31Button;
	private: System::Windows::Forms::Label^  QuickSearchButton;
	private: System::Windows::Forms::Label^  QuickSearchMonthLabel;
	private: System::Windows::Forms::Label^  QuickSearchYearButton;
	private: System::Windows::Forms::Button^  ActivateQuickSearchButton;
	private: System::Windows::Forms::Button^  PrevMonthButton;
	private: System::Windows::Forms::Button^  NextMonthButton;
	private: System::Windows::Forms::Button^  ShowCurrentMonthButton;
	private: System::Windows::Forms::Button^  PrevYearButton;
	private: System::Windows::Forms::Button^  NextYearButton;
	private: System::Windows::Forms::Button^  ShowCurrentYearButton;
	private: System::Windows::Forms::Button^  TODAYButton;
	private: System::Windows::Forms::ComboBox^  QSMonthCombobox;
	private: System::Windows::Forms::TextBox^  QSYearTextbox;
	private: System::Windows::Forms::Button^  ViewDayEventsButton;
	private: System::Windows::Forms::Button^  SettingsButton;
	private: System::Windows::Forms::Button^  LogOutButton;
	private: System::Windows::Forms::Button^  AddLocalEventButton;
	private: System::Windows::Forms::Button^  AddTeamGlobalEventButton;
	private: System::Windows::Forms::Label^  HelloUserLabel;
	private: System::Windows::Forms::Panel^  DayEventsViewPanel;
	private: System::Windows::Forms::Button^  ViewEventsPanelBackButton;
	private: System::Windows::Forms::ListBox^  ListOfDayEvents;
	private: System::Windows::Forms::Label^  ViewPersonalEventsLabel;
	private: System::Windows::Forms::Label^  NameStaticLabel;
	private: System::Windows::Forms::Label^  TimeStaticLabel;
	private: System::Windows::Forms::TextBox^  DescriptionTextBox;
	private: System::Windows::Forms::Label^  TimeFillLabel;
	private: System::Windows::Forms::Label^  PriorityStaticLabel;
	private: System::Windows::Forms::Label^  PriorityFillLabel;
	private: System::Windows::Forms::ListBox^  ListOfGlobalEvents;
	private: System::Windows::Forms::Label^  ViewGlobalEventsLabel;
	private: System::Windows::Forms::ListBox^  ListOfTeamEvents;
	private: System::Windows::Forms::Label^  ViewTeamEventsLabel;
	private: System::Windows::Forms::Label^  TypeFillLabel;
	private: System::Windows::Forms::Label^  TypeStaticLabel;
	private: System::Windows::Forms::Button^  DeleteEventButton;
	private: System::Windows::Forms::Button^  EditEventButton;
	private: System::Windows::Forms::Label^  ViewYearLabel;
	private: System::Windows::Forms::Label^  ViewDayLabel;
	private: System::Windows::Forms::Label^  ViewMonthLabel;
	private: System::Windows::Forms::Panel^  SettingsPanel;
	private: System::Windows::Forms::Button^  SecondBackButton;
	private: System::Windows::Forms::Button^  AddNewUserButton;
	private: System::Windows::Forms::Button^  ChangePasswordButton;
	private: System::Windows::Forms::Button^  SysInfoButton;
	private: System::Windows::Forms::Label^  UserListLabel;
	private: System::Windows::Forms::ListBox^  UserList;
	private: System::Windows::Forms::Label^  UserNameLabel;
	private: System::Windows::Forms::Label^  UserIDLabel;
	private: System::Windows::Forms::Label^  UserDetailsLabel;
	private: System::Windows::Forms::Label^  UserTeamLabel;
	private: System::Windows::Forms::Label^  UserRankLabel;
	private: System::Windows::Forms::TextBox^  UserTeamtextBox;
	private: System::Windows::Forms::TextBox^  UserNameTextBox;
	private: System::Windows::Forms::TextBox^  UserIDTextBox;
	private: System::Windows::Forms::TextBox^  UserRankTextBox;
	private: System::Windows::Forms::TextBox^  UserSurnameTextBox;
	private: System::Windows::Forms::Button^  EditUserButton;
	private: System::Windows::Forms::Button^  DeleteUserButton;
	private: System::Windows::Forms::Panel^  SysInfoPanel;
	private: System::Windows::Forms::Button^  SysResetButton;
	private: System::Windows::Forms::Button^  SysInfoBackButton;
	private: System::Windows::Forms::LinkLabel^  InfoEmailLinkLabel;
	private: System::Windows::Forms::Label^  InfoEmailLabel;
	private: System::Windows::Forms::Label^  InfoPhoneLabel;
	private: System::Windows::Forms::ListBox^  InfoDevList;
	private: System::Windows::Forms::Label^  InfoDevLabel;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  InfoHDDLabel;
	private: System::Windows::Forms::Label^  InfoRamLabel;
	private: System::Windows::Forms::Label^  InfoWindowsLabel;
	private: System::Windows::Forms::Label^  nfoSysReqLabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  InfoVersionLabel;
	private: System::Windows::Forms::Label^  InfoNameLabel;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  TimeLabel;
private: System::Windows::Forms::Label^  PersonalTeamLabel;
private: System::Windows::Forms::Label^  PersonalTeamStatusLabel;
private: System::Windows::Forms::Label^  PersonalNameLabel;
private: System::Windows::Forms::Label^  PersonaIDLabel;
private: System::Windows::Forms::Label^  PersonalDetailsLabel;
	private: System::ComponentModel::IContainer^  components;
		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->Day1Button = (gcnew System::Windows::Forms::Button());
				 this->Day2Button = (gcnew System::Windows::Forms::Button());
				 this->Day3Button = (gcnew System::Windows::Forms::Button());
				 this->Day4Button = (gcnew System::Windows::Forms::Button());
				 this->Day5Button = (gcnew System::Windows::Forms::Button());
				 this->Day6Button = (gcnew System::Windows::Forms::Button());
				 this->Day7Button = (gcnew System::Windows::Forms::Button());
				 this->Day8Button = (gcnew System::Windows::Forms::Button());
				 this->Day9Button = (gcnew System::Windows::Forms::Button());
				 this->Day10Button = (gcnew System::Windows::Forms::Button());
				 this->Day11Button = (gcnew System::Windows::Forms::Button());
				 this->Day12Button = (gcnew System::Windows::Forms::Button());
				 this->Day13Button = (gcnew System::Windows::Forms::Button());
				 this->Day14Button = (gcnew System::Windows::Forms::Button());
				 this->Day15Button = (gcnew System::Windows::Forms::Button());
				 this->Day16Button = (gcnew System::Windows::Forms::Button());
				 this->Day17Button = (gcnew System::Windows::Forms::Button());
				 this->Day18Button = (gcnew System::Windows::Forms::Button());
				 this->Day19Button = (gcnew System::Windows::Forms::Button());
				 this->Day20Button = (gcnew System::Windows::Forms::Button());
				 this->Day21Button = (gcnew System::Windows::Forms::Button());
				 this->Day22Button = (gcnew System::Windows::Forms::Button());
				 this->Day23Button = (gcnew System::Windows::Forms::Button());
				 this->Day24Button = (gcnew System::Windows::Forms::Button());
				 this->Day25Button = (gcnew System::Windows::Forms::Button());
				 this->Day26Button = (gcnew System::Windows::Forms::Button());
				 this->Day27Button = (gcnew System::Windows::Forms::Button());
				 this->Day28Button = (gcnew System::Windows::Forms::Button());
				 this->Day29Button = (gcnew System::Windows::Forms::Button());
				 this->Day30Button = (gcnew System::Windows::Forms::Button());
				 this->Day31Button = (gcnew System::Windows::Forms::Button());
				 this->QuickSearchButton = (gcnew System::Windows::Forms::Label());
				 this->QuickSearchMonthLabel = (gcnew System::Windows::Forms::Label());
				 this->QuickSearchYearButton = (gcnew System::Windows::Forms::Label());
				 this->ActivateQuickSearchButton = (gcnew System::Windows::Forms::Button());
				 this->PrevMonthButton = (gcnew System::Windows::Forms::Button());
				 this->NextMonthButton = (gcnew System::Windows::Forms::Button());
				 this->ShowCurrentMonthButton = (gcnew System::Windows::Forms::Button());
				 this->PrevYearButton = (gcnew System::Windows::Forms::Button());
				 this->NextYearButton = (gcnew System::Windows::Forms::Button());
				 this->ShowCurrentYearButton = (gcnew System::Windows::Forms::Button());
				 this->TODAYButton = (gcnew System::Windows::Forms::Button());
				 this->QSMonthCombobox = (gcnew System::Windows::Forms::ComboBox());
				 this->QSYearTextbox = (gcnew System::Windows::Forms::TextBox());
				 this->ViewDayEventsButton = (gcnew System::Windows::Forms::Button());
				 this->SettingsButton = (gcnew System::Windows::Forms::Button());
				 this->LogOutButton = (gcnew System::Windows::Forms::Button());
				 this->AddLocalEventButton = (gcnew System::Windows::Forms::Button());
				 this->AddTeamGlobalEventButton = (gcnew System::Windows::Forms::Button());
				 this->HelloUserLabel = (gcnew System::Windows::Forms::Label());
				 this->DayEventsViewPanel = (gcnew System::Windows::Forms::Panel());
				 this->ViewMonthLabel = (gcnew System::Windows::Forms::Label());
				 this->ViewYearLabel = (gcnew System::Windows::Forms::Label());
				 this->ViewDayLabel = (gcnew System::Windows::Forms::Label());
				 this->DeleteEventButton = (gcnew System::Windows::Forms::Button());
				 this->EditEventButton = (gcnew System::Windows::Forms::Button());
				 this->TypeFillLabel = (gcnew System::Windows::Forms::Label());
				 this->TypeStaticLabel = (gcnew System::Windows::Forms::Label());
				 this->ListOfGlobalEvents = (gcnew System::Windows::Forms::ListBox());
				 this->ViewGlobalEventsLabel = (gcnew System::Windows::Forms::Label());
				 this->ListOfTeamEvents = (gcnew System::Windows::Forms::ListBox());
				 this->ViewTeamEventsLabel = (gcnew System::Windows::Forms::Label());
				 this->PriorityFillLabel = (gcnew System::Windows::Forms::Label());
				 this->PriorityStaticLabel = (gcnew System::Windows::Forms::Label());
				 this->TimeFillLabel = (gcnew System::Windows::Forms::Label());
				 this->TimeStaticLabel = (gcnew System::Windows::Forms::Label());
				 this->DescriptionTextBox = (gcnew System::Windows::Forms::TextBox());
				 this->NameStaticLabel = (gcnew System::Windows::Forms::Label());
				 this->ViewPersonalEventsLabel = (gcnew System::Windows::Forms::Label());
				 this->ListOfDayEvents = (gcnew System::Windows::Forms::ListBox());
				 this->ViewEventsPanelBackButton = (gcnew System::Windows::Forms::Button());
				 this->SysInfoPanel = (gcnew System::Windows::Forms::Panel());
				 this->InfoEmailLinkLabel = (gcnew System::Windows::Forms::LinkLabel());
				 this->InfoEmailLabel = (gcnew System::Windows::Forms::Label());
				 this->InfoPhoneLabel = (gcnew System::Windows::Forms::Label());
				 this->InfoDevList = (gcnew System::Windows::Forms::ListBox());
				 this->InfoDevLabel = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->InfoHDDLabel = (gcnew System::Windows::Forms::Label());
				 this->InfoRamLabel = (gcnew System::Windows::Forms::Label());
				 this->InfoWindowsLabel = (gcnew System::Windows::Forms::Label());
				 this->nfoSysReqLabel = (gcnew System::Windows::Forms::Label());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->InfoVersionLabel = (gcnew System::Windows::Forms::Label());
				 this->InfoNameLabel = (gcnew System::Windows::Forms::Label());
				 this->SysInfoBackButton = (gcnew System::Windows::Forms::Button());
				 this->SettingsPanel = (gcnew System::Windows::Forms::Panel());
				 this->PersonalTeamLabel = (gcnew System::Windows::Forms::Label());
				 this->PersonalTeamStatusLabel = (gcnew System::Windows::Forms::Label());
				 this->PersonalNameLabel = (gcnew System::Windows::Forms::Label());
				 this->PersonaIDLabel = (gcnew System::Windows::Forms::Label());
				 this->PersonalDetailsLabel = (gcnew System::Windows::Forms::Label());
				 this->SysResetButton = (gcnew System::Windows::Forms::Button());
				 this->EditUserButton = (gcnew System::Windows::Forms::Button());
				 this->DeleteUserButton = (gcnew System::Windows::Forms::Button());
				 this->UserSurnameTextBox = (gcnew System::Windows::Forms::TextBox());
				 this->UserRankTextBox = (gcnew System::Windows::Forms::TextBox());
				 this->UserTeamtextBox = (gcnew System::Windows::Forms::TextBox());
				 this->UserNameTextBox = (gcnew System::Windows::Forms::TextBox());
				 this->UserIDTextBox = (gcnew System::Windows::Forms::TextBox());
				 this->UserRankLabel = (gcnew System::Windows::Forms::Label());
				 this->UserTeamLabel = (gcnew System::Windows::Forms::Label());
				 this->UserNameLabel = (gcnew System::Windows::Forms::Label());
				 this->UserIDLabel = (gcnew System::Windows::Forms::Label());
				 this->UserDetailsLabel = (gcnew System::Windows::Forms::Label());
				 this->UserListLabel = (gcnew System::Windows::Forms::Label());
				 this->UserList = (gcnew System::Windows::Forms::ListBox());
				 this->SysInfoButton = (gcnew System::Windows::Forms::Button());
				 this->AddNewUserButton = (gcnew System::Windows::Forms::Button());
				 this->ChangePasswordButton = (gcnew System::Windows::Forms::Button());
				 this->SecondBackButton = (gcnew System::Windows::Forms::Button());
				 this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				 this->TimeLabel = (gcnew System::Windows::Forms::Label());
				 this->DayEventsViewPanel->SuspendLayout();
				 this->SysInfoPanel->SuspendLayout();
				 this->SettingsPanel->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // Day1Button
				 // 
				 this->Day1Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day1Button->Location = System::Drawing::Point(149, 103);
				 this->Day1Button->Name = L"Day1Button";
				 this->Day1Button->Size = System::Drawing::Size(50, 44);
				 this->Day1Button->TabIndex = 0;
				 this->Day1Button->Text = L"1";
				 this->Day1Button->UseVisualStyleBackColor = false;
				 this->Day1Button->Click += gcnew System::EventHandler(this, &MainScreen::button1_Click);
				 // 
				 // Day2Button
				 // 
				 this->Day2Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day2Button->Location = System::Drawing::Point(196, 103);
				 this->Day2Button->Name = L"Day2Button";
				 this->Day2Button->Size = System::Drawing::Size(50, 44);
				 this->Day2Button->TabIndex = 1;
				 this->Day2Button->Text = L"2";
				 this->Day2Button->UseVisualStyleBackColor = false;
				 this->Day2Button->Click += gcnew System::EventHandler(this, &MainScreen::button2_Click);
				 // 
				 // Day3Button
				 // 
				 this->Day3Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day3Button->Location = System::Drawing::Point(243, 103);
				 this->Day3Button->Name = L"Day3Button";
				 this->Day3Button->Size = System::Drawing::Size(50, 44);
				 this->Day3Button->TabIndex = 2;
				 this->Day3Button->Text = L"3";
				 this->Day3Button->UseVisualStyleBackColor = false;
				 this->Day3Button->Click += gcnew System::EventHandler(this, &MainScreen::button3_Click);
				 // 
				 // Day4Button
				 // 
				 this->Day4Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day4Button->Location = System::Drawing::Point(289, 103);
				 this->Day4Button->Name = L"Day4Button";
				 this->Day4Button->Size = System::Drawing::Size(50, 44);
				 this->Day4Button->TabIndex = 3;
				 this->Day4Button->Text = L"4";
				 this->Day4Button->UseVisualStyleBackColor = false;
				 this->Day4Button->Click += gcnew System::EventHandler(this, &MainScreen::button4_Click);
				 // 
				 // Day5Button
				 // 
				 this->Day5Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day5Button->Location = System::Drawing::Point(336, 103);
				 this->Day5Button->Name = L"Day5Button";
				 this->Day5Button->Size = System::Drawing::Size(50, 44);
				 this->Day5Button->TabIndex = 4;
				 this->Day5Button->Text = L"5";
				 this->Day5Button->UseVisualStyleBackColor = false;
				 this->Day5Button->Click += gcnew System::EventHandler(this, &MainScreen::button5_Click);
				 // 
				 // Day6Button
				 // 
				 this->Day6Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day6Button->Location = System::Drawing::Point(383, 103);
				 this->Day6Button->Name = L"Day6Button";
				 this->Day6Button->Size = System::Drawing::Size(50, 44);
				 this->Day6Button->TabIndex = 5;
				 this->Day6Button->Text = L"6";
				 this->Day6Button->UseVisualStyleBackColor = false;
				 this->Day6Button->Click += gcnew System::EventHandler(this, &MainScreen::button6_Click);
				 // 
				 // Day7Button
				 // 
				 this->Day7Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day7Button->Location = System::Drawing::Point(149, 144);
				 this->Day7Button->Name = L"Day7Button";
				 this->Day7Button->Size = System::Drawing::Size(50, 44);
				 this->Day7Button->TabIndex = 6;
				 this->Day7Button->Text = L"7";
				 this->Day7Button->UseVisualStyleBackColor = false;
				 this->Day7Button->Click += gcnew System::EventHandler(this, &MainScreen::button7_Click);
				 // 
				 // Day8Button
				 // 
				 this->Day8Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day8Button->Location = System::Drawing::Point(196, 144);
				 this->Day8Button->Name = L"Day8Button";
				 this->Day8Button->Size = System::Drawing::Size(50, 44);
				 this->Day8Button->TabIndex = 7;
				 this->Day8Button->Text = L"8";
				 this->Day8Button->UseVisualStyleBackColor = false;
				 this->Day8Button->Click += gcnew System::EventHandler(this, &MainScreen::button8_Click);
				 // 
				 // Day9Button
				 // 
				 this->Day9Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day9Button->Location = System::Drawing::Point(243, 144);
				 this->Day9Button->Name = L"Day9Button";
				 this->Day9Button->Size = System::Drawing::Size(50, 44);
				 this->Day9Button->TabIndex = 8;
				 this->Day9Button->Text = L"9";
				 this->Day9Button->UseVisualStyleBackColor = false;
				 this->Day9Button->Click += gcnew System::EventHandler(this, &MainScreen::button9_Click);
				 // 
				 // Day10Button
				 // 
				 this->Day10Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day10Button->Location = System::Drawing::Point(289, 144);
				 this->Day10Button->Name = L"Day10Button";
				 this->Day10Button->Size = System::Drawing::Size(50, 44);
				 this->Day10Button->TabIndex = 9;
				 this->Day10Button->Text = L"10";
				 this->Day10Button->UseVisualStyleBackColor = false;
				 this->Day10Button->Click += gcnew System::EventHandler(this, &MainScreen::button10_Click);
				 // 
				 // Day11Button
				 // 
				 this->Day11Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day11Button->Location = System::Drawing::Point(336, 144);
				 this->Day11Button->Name = L"Day11Button";
				 this->Day11Button->Size = System::Drawing::Size(50, 44);
				 this->Day11Button->TabIndex = 10;
				 this->Day11Button->Text = L"11";
				 this->Day11Button->UseVisualStyleBackColor = false;
				 this->Day11Button->Click += gcnew System::EventHandler(this, &MainScreen::button11_Click);
				 // 
				 // Day12Button
				 // 
				 this->Day12Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day12Button->Location = System::Drawing::Point(383, 144);
				 this->Day12Button->Name = L"Day12Button";
				 this->Day12Button->Size = System::Drawing::Size(50, 44);
				 this->Day12Button->TabIndex = 11;
				 this->Day12Button->Text = L"12";
				 this->Day12Button->UseVisualStyleBackColor = false;
				 this->Day12Button->Click += gcnew System::EventHandler(this, &MainScreen::button12_Click);
				 // 
				 // Day13Button
				 // 
				 this->Day13Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day13Button->Location = System::Drawing::Point(149, 185);
				 this->Day13Button->Name = L"Day13Button";
				 this->Day13Button->Size = System::Drawing::Size(50, 44);
				 this->Day13Button->TabIndex = 12;
				 this->Day13Button->Text = L"13";
				 this->Day13Button->UseVisualStyleBackColor = false;
				 this->Day13Button->Click += gcnew System::EventHandler(this, &MainScreen::button13_Click);
				 // 
				 // Day14Button
				 // 
				 this->Day14Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day14Button->Location = System::Drawing::Point(196, 185);
				 this->Day14Button->Name = L"Day14Button";
				 this->Day14Button->Size = System::Drawing::Size(50, 44);
				 this->Day14Button->TabIndex = 13;
				 this->Day14Button->Text = L"14";
				 this->Day14Button->UseVisualStyleBackColor = false;
				 this->Day14Button->Click += gcnew System::EventHandler(this, &MainScreen::button14_Click);
				 // 
				 // Day15Button
				 // 
				 this->Day15Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day15Button->Location = System::Drawing::Point(243, 185);
				 this->Day15Button->Name = L"Day15Button";
				 this->Day15Button->Size = System::Drawing::Size(50, 44);
				 this->Day15Button->TabIndex = 14;
				 this->Day15Button->Text = L"15";
				 this->Day15Button->UseVisualStyleBackColor = false;
				 this->Day15Button->Click += gcnew System::EventHandler(this, &MainScreen::button15_Click);
				 // 
				 // Day16Button
				 // 
				 this->Day16Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day16Button->Location = System::Drawing::Point(289, 185);
				 this->Day16Button->Name = L"Day16Button";
				 this->Day16Button->Size = System::Drawing::Size(50, 44);
				 this->Day16Button->TabIndex = 15;
				 this->Day16Button->Text = L"16";
				 this->Day16Button->UseVisualStyleBackColor = false;
				 this->Day16Button->Click += gcnew System::EventHandler(this, &MainScreen::button16_Click);
				 // 
				 // Day17Button
				 // 
				 this->Day17Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day17Button->Location = System::Drawing::Point(336, 185);
				 this->Day17Button->Name = L"Day17Button";
				 this->Day17Button->Size = System::Drawing::Size(50, 44);
				 this->Day17Button->TabIndex = 16;
				 this->Day17Button->Text = L"17";
				 this->Day17Button->UseVisualStyleBackColor = false;
				 this->Day17Button->Click += gcnew System::EventHandler(this, &MainScreen::button17_Click);
				 // 
				 // Day18Button
				 // 
				 this->Day18Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day18Button->Location = System::Drawing::Point(383, 185);
				 this->Day18Button->Name = L"Day18Button";
				 this->Day18Button->Size = System::Drawing::Size(50, 44);
				 this->Day18Button->TabIndex = 17;
				 this->Day18Button->Text = L"18";
				 this->Day18Button->UseVisualStyleBackColor = false;
				 this->Day18Button->Click += gcnew System::EventHandler(this, &MainScreen::button18_Click);
				 // 
				 // Day19Button
				 // 
				 this->Day19Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day19Button->Location = System::Drawing::Point(149, 226);
				 this->Day19Button->Name = L"Day19Button";
				 this->Day19Button->Size = System::Drawing::Size(50, 44);
				 this->Day19Button->TabIndex = 18;
				 this->Day19Button->Text = L"19";
				 this->Day19Button->UseVisualStyleBackColor = false;
				 this->Day19Button->Click += gcnew System::EventHandler(this, &MainScreen::button19_Click);
				 // 
				 // Day20Button
				 // 
				 this->Day20Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day20Button->Location = System::Drawing::Point(196, 226);
				 this->Day20Button->Name = L"Day20Button";
				 this->Day20Button->Size = System::Drawing::Size(50, 44);
				 this->Day20Button->TabIndex = 19;
				 this->Day20Button->Text = L"20";
				 this->Day20Button->UseVisualStyleBackColor = false;
				 this->Day20Button->Click += gcnew System::EventHandler(this, &MainScreen::button20_Click);
				 // 
				 // Day21Button
				 // 
				 this->Day21Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day21Button->Location = System::Drawing::Point(243, 226);
				 this->Day21Button->Name = L"Day21Button";
				 this->Day21Button->Size = System::Drawing::Size(50, 44);
				 this->Day21Button->TabIndex = 20;
				 this->Day21Button->Text = L"21";
				 this->Day21Button->UseVisualStyleBackColor = false;
				 this->Day21Button->Click += gcnew System::EventHandler(this, &MainScreen::button21_Click);
				 // 
				 // Day22Button
				 // 
				 this->Day22Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day22Button->Location = System::Drawing::Point(289, 226);
				 this->Day22Button->Name = L"Day22Button";
				 this->Day22Button->Size = System::Drawing::Size(50, 44);
				 this->Day22Button->TabIndex = 21;
				 this->Day22Button->Text = L"22";
				 this->Day22Button->UseVisualStyleBackColor = false;
				 this->Day22Button->Click += gcnew System::EventHandler(this, &MainScreen::button22_Click);
				 // 
				 // Day23Button
				 // 
				 this->Day23Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day23Button->Location = System::Drawing::Point(336, 226);
				 this->Day23Button->Name = L"Day23Button";
				 this->Day23Button->Size = System::Drawing::Size(50, 44);
				 this->Day23Button->TabIndex = 22;
				 this->Day23Button->Text = L"23";
				 this->Day23Button->UseVisualStyleBackColor = false;
				 this->Day23Button->Click += gcnew System::EventHandler(this, &MainScreen::button23_Click);
				 // 
				 // Day24Button
				 // 
				 this->Day24Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day24Button->Location = System::Drawing::Point(383, 226);
				 this->Day24Button->Name = L"Day24Button";
				 this->Day24Button->Size = System::Drawing::Size(50, 44);
				 this->Day24Button->TabIndex = 23;
				 this->Day24Button->Text = L"24";
				 this->Day24Button->UseVisualStyleBackColor = false;
				 this->Day24Button->Click += gcnew System::EventHandler(this, &MainScreen::button24_Click);
				 // 
				 // Day25Button
				 // 
				 this->Day25Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day25Button->Location = System::Drawing::Point(149, 267);
				 this->Day25Button->Name = L"Day25Button";
				 this->Day25Button->Size = System::Drawing::Size(50, 44);
				 this->Day25Button->TabIndex = 24;
				 this->Day25Button->Text = L"25";
				 this->Day25Button->UseVisualStyleBackColor = false;
				 this->Day25Button->Click += gcnew System::EventHandler(this, &MainScreen::button25_Click);
				 // 
				 // Day26Button
				 // 
				 this->Day26Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day26Button->Location = System::Drawing::Point(196, 267);
				 this->Day26Button->Name = L"Day26Button";
				 this->Day26Button->Size = System::Drawing::Size(50, 44);
				 this->Day26Button->TabIndex = 25;
				 this->Day26Button->Text = L"26";
				 this->Day26Button->UseVisualStyleBackColor = false;
				 this->Day26Button->Click += gcnew System::EventHandler(this, &MainScreen::button26_Click);
				 // 
				 // Day27Button
				 // 
				 this->Day27Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day27Button->Location = System::Drawing::Point(243, 267);
				 this->Day27Button->Name = L"Day27Button";
				 this->Day27Button->Size = System::Drawing::Size(50, 44);
				 this->Day27Button->TabIndex = 26;
				 this->Day27Button->Text = L"27";
				 this->Day27Button->UseVisualStyleBackColor = false;
				 this->Day27Button->Click += gcnew System::EventHandler(this, &MainScreen::button27_Click);
				 // 
				 // Day28Button
				 // 
				 this->Day28Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day28Button->Location = System::Drawing::Point(289, 267);
				 this->Day28Button->Name = L"Day28Button";
				 this->Day28Button->Size = System::Drawing::Size(50, 44);
				 this->Day28Button->TabIndex = 27;
				 this->Day28Button->Text = L"28";
				 this->Day28Button->UseVisualStyleBackColor = false;
				 this->Day28Button->Click += gcnew System::EventHandler(this, &MainScreen::button28_Click);
				 // 
				 // Day29Button
				 // 
				 this->Day29Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day29Button->Location = System::Drawing::Point(336, 267);
				 this->Day29Button->Name = L"Day29Button";
				 this->Day29Button->Size = System::Drawing::Size(50, 44);
				 this->Day29Button->TabIndex = 28;
				 this->Day29Button->Text = L"29";
				 this->Day29Button->UseVisualStyleBackColor = false;
				 this->Day29Button->Click += gcnew System::EventHandler(this, &MainScreen::button29_Click);
				 // 
				 // Day30Button
				 // 
				 this->Day30Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day30Button->Location = System::Drawing::Point(383, 267);
				 this->Day30Button->Name = L"Day30Button";
				 this->Day30Button->Size = System::Drawing::Size(50, 44);
				 this->Day30Button->TabIndex = 29;
				 this->Day30Button->Text = L"30";
				 this->Day30Button->UseVisualStyleBackColor = false;
				 this->Day30Button->Click += gcnew System::EventHandler(this, &MainScreen::button30_Click);
				 // 
				 // Day31Button
				 // 
				 this->Day31Button->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->Day31Button->Location = System::Drawing::Point(149, 308);
				 this->Day31Button->Name = L"Day31Button";
				 this->Day31Button->Size = System::Drawing::Size(50, 44);
				 this->Day31Button->TabIndex = 30;
				 this->Day31Button->Text = L"31";
				 this->Day31Button->UseVisualStyleBackColor = false;
				 this->Day31Button->Click += gcnew System::EventHandler(this, &MainScreen::button31_Click);
				 // 
				 // QuickSearchButton
				 // 
				 this->QuickSearchButton->AutoSize = true;
				 this->QuickSearchButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->QuickSearchButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->QuickSearchButton->ForeColor = System::Drawing::SystemColors::HotTrack;
				 this->QuickSearchButton->Location = System::Drawing::Point(9, 79);
				 this->QuickSearchButton->Name = L"QuickSearchButton";
				 this->QuickSearchButton->Size = System::Drawing::Size(179, 30);
				 this->QuickSearchButton->TabIndex = 32;
				 this->QuickSearchButton->Text = L"Quick Search";
				 this->QuickSearchButton->Click += gcnew System::EventHandler(this, &MainScreen::label1_Click);
				 // 
				 // QuickSearchMonthLabel
				 // 
				 this->QuickSearchMonthLabel->AutoSize = true;
				 this->QuickSearchMonthLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->QuickSearchMonthLabel->Location = System::Drawing::Point(9, 100);
				 this->QuickSearchMonthLabel->Name = L"QuickSearchMonthLabel";
				 this->QuickSearchMonthLabel->Size = System::Drawing::Size(84, 29);
				 this->QuickSearchMonthLabel->TabIndex = 33;
				 this->QuickSearchMonthLabel->Text = L"Month";
				 this->QuickSearchMonthLabel->Click += gcnew System::EventHandler(this, &MainScreen::label2_Click);
				 // 
				 // QuickSearchYearButton
				 // 
				 this->QuickSearchYearButton->AutoSize = true;
				 this->QuickSearchYearButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->QuickSearchYearButton->Location = System::Drawing::Point(70, 100);
				 this->QuickSearchYearButton->Name = L"QuickSearchYearButton";
				 this->QuickSearchYearButton->Size = System::Drawing::Size(68, 29);
				 this->QuickSearchYearButton->TabIndex = 34;
				 this->QuickSearchYearButton->Text = L"Year";
				 // 
				 // ActivateQuickSearchButton
				 // 
				 this->ActivateQuickSearchButton->Location = System::Drawing::Point(12, 146);
				 this->ActivateQuickSearchButton->Name = L"ActivateQuickSearchButton";
				 this->ActivateQuickSearchButton->Size = System::Drawing::Size(107, 24);
				 this->ActivateQuickSearchButton->TabIndex = 36;
				 this->ActivateQuickSearchButton->Text = L"Enter";
				 this->ActivateQuickSearchButton->UseVisualStyleBackColor = true;
				 this->ActivateQuickSearchButton->Click += gcnew System::EventHandler(this, &MainScreen::button32_Click);
				 // 
				 // PrevMonthButton
				 // 
				 this->PrevMonthButton->Location = System::Drawing::Point(149, 74);
				 this->PrevMonthButton->Name = L"PrevMonthButton";
				 this->PrevMonthButton->Size = System::Drawing::Size(73, 23);
				 this->PrevMonthButton->TabIndex = 37;
				 this->PrevMonthButton->Text = L"Prev";
				 this->PrevMonthButton->UseVisualStyleBackColor = true;
				 this->PrevMonthButton->Click += gcnew System::EventHandler(this, &MainScreen::button33_Click);
				 // 
				 // NextMonthButton
				 // 
				 this->NextMonthButton->Location = System::Drawing::Point(359, 74);
				 this->NextMonthButton->Name = L"NextMonthButton";
				 this->NextMonthButton->Size = System::Drawing::Size(73, 23);
				 this->NextMonthButton->TabIndex = 38;
				 this->NextMonthButton->Text = L"Next";
				 this->NextMonthButton->UseVisualStyleBackColor = true;
				 this->NextMonthButton->Click += gcnew System::EventHandler(this, &MainScreen::button34_Click);
				 // 
				 // ShowCurrentMonthButton
				 // 
				 this->ShowCurrentMonthButton->BackColor = System::Drawing::SystemColors::InactiveCaption;
				 this->ShowCurrentMonthButton->Location = System::Drawing::Point(230, 74);
				 this->ShowCurrentMonthButton->Name = L"ShowCurrentMonthButton";
				 this->ShowCurrentMonthButton->Size = System::Drawing::Size(124, 23);
				 this->ShowCurrentMonthButton->TabIndex = 39;
				 this->ShowCurrentMonthButton->UseVisualStyleBackColor = false;
				 this->ShowCurrentMonthButton->Click += gcnew System::EventHandler(this, &MainScreen::button35_Click);
				 // 
				 // PrevYearButton
				 // 
				 this->PrevYearButton->Location = System::Drawing::Point(149, 45);
				 this->PrevYearButton->Name = L"PrevYearButton";
				 this->PrevYearButton->Size = System::Drawing::Size(73, 23);
				 this->PrevYearButton->TabIndex = 40;
				 this->PrevYearButton->Text = L"Prev";
				 this->PrevYearButton->UseVisualStyleBackColor = true;
				 this->PrevYearButton->Click += gcnew System::EventHandler(this, &MainScreen::button36_Click);
				 // 
				 // NextYearButton
				 // 
				 this->NextYearButton->Location = System::Drawing::Point(359, 45);
				 this->NextYearButton->Name = L"NextYearButton";
				 this->NextYearButton->Size = System::Drawing::Size(73, 23);
				 this->NextYearButton->TabIndex = 41;
				 this->NextYearButton->Text = L"Next";
				 this->NextYearButton->UseVisualStyleBackColor = true;
				 this->NextYearButton->Click += gcnew System::EventHandler(this, &MainScreen::button37_Click);
				 // 
				 // ShowCurrentYearButton
				 // 
				 this->ShowCurrentYearButton->BackColor = System::Drawing::SystemColors::InactiveCaption;
				 this->ShowCurrentYearButton->Location = System::Drawing::Point(230, 45);
				 this->ShowCurrentYearButton->Name = L"ShowCurrentYearButton";
				 this->ShowCurrentYearButton->Size = System::Drawing::Size(124, 23);
				 this->ShowCurrentYearButton->TabIndex = 42;
				 this->ShowCurrentYearButton->UseVisualStyleBackColor = false;
				 this->ShowCurrentYearButton->Click += gcnew System::EventHandler(this, &MainScreen::button38_Click);
				 // 
				 // TODAYButton
				 // 
				 this->TODAYButton->BackColor = System::Drawing::SystemColors::MenuHighlight;
				 this->TODAYButton->Font = (gcnew System::Drawing::Font(L"Broadway", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->TODAYButton->ForeColor = System::Drawing::Color::White;
				 this->TODAYButton->Location = System::Drawing::Point(149, 12);
				 this->TODAYButton->Name = L"TODAYButton";
				 this->TODAYButton->Size = System::Drawing::Size(283, 27);
				 this->TODAYButton->TabIndex = 43;
				 this->TODAYButton->Text = L"TODAY";
				 this->TODAYButton->UseVisualStyleBackColor = false;
				 this->TODAYButton->Click += gcnew System::EventHandler(this, &MainScreen::button39_Click);
				 // 
				 // QSMonthCombobox
				 // 
				 this->QSMonthCombobox->FormattingEnabled = true;
				 this->QSMonthCombobox->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
					 L"1", L"2", L"3", L"4", L"5", L"6", L"7",
						 L"8", L"9", L"10", L"11", L"12"
				 });
				 this->QSMonthCombobox->Location = System::Drawing::Point(12, 119);
				 this->QSMonthCombobox->Name = L"QSMonthCombobox";
				 this->QSMonthCombobox->Size = System::Drawing::Size(46, 32);
				 this->QSMonthCombobox->TabIndex = 44;
				 this->QSMonthCombobox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainScreen::comboBox1_SelectedIndexChanged_1);
				 // 
				 // QSYearTextbox
				 // 
				 this->QSYearTextbox->Location = System::Drawing::Point(73, 120);
				 this->QSYearTextbox->Name = L"QSYearTextbox";
				 this->QSYearTextbox->Size = System::Drawing::Size(46, 29);
				 this->QSYearTextbox->TabIndex = 35;
				 // 
				 // ViewDayEventsButton
				 // 
				 this->ViewDayEventsButton->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
				 this->ViewDayEventsButton->Location = System::Drawing::Point(196, 308);
				 this->ViewDayEventsButton->Name = L"ViewDayEventsButton";
				 this->ViewDayEventsButton->Size = System::Drawing::Size(236, 44);
				 this->ViewDayEventsButton->TabIndex = 45;
				 this->ViewDayEventsButton->UseVisualStyleBackColor = false;
				 this->ViewDayEventsButton->Click += gcnew System::EventHandler(this, &MainScreen::ViewDayEventsButton_Click);
				 // 
				 // SettingsButton
				 // 
				 this->SettingsButton->Location = System::Drawing::Point(12, 288);
				 this->SettingsButton->Name = L"SettingsButton";
				 this->SettingsButton->Size = System::Drawing::Size(119, 30);
				 this->SettingsButton->TabIndex = 46;
				 this->SettingsButton->Text = L"Settings";
				 this->SettingsButton->UseVisualStyleBackColor = true;
				 this->SettingsButton->Click += gcnew System::EventHandler(this, &MainScreen::SettingsButton_Click);
				 // 
				 // LogOutButton
				 // 
				 this->LogOutButton->Location = System::Drawing::Point(12, 322);
				 this->LogOutButton->Name = L"LogOutButton";
				 this->LogOutButton->Size = System::Drawing::Size(119, 30);
				 this->LogOutButton->TabIndex = 47;
				 this->LogOutButton->Text = L"Log Out";
				 this->LogOutButton->UseVisualStyleBackColor = true;
				 this->LogOutButton->Click += gcnew System::EventHandler(this, &MainScreen::button42_Click);
				 // 
				 // AddLocalEventButton
				 // 
				 this->AddLocalEventButton->Location = System::Drawing::Point(12, 240);
				 this->AddLocalEventButton->Name = L"AddLocalEventButton";
				 this->AddLocalEventButton->Size = System::Drawing::Size(119, 42);
				 this->AddLocalEventButton->TabIndex = 48;
				 this->AddLocalEventButton->Text = L"Add personal event";
				 this->AddLocalEventButton->UseVisualStyleBackColor = true;
				 this->AddLocalEventButton->Click += gcnew System::EventHandler(this, &MainScreen::AddLocalEventButton_Click);
				 // 
				 // AddTeamGlobalEventButton
				 // 
				 this->AddTeamGlobalEventButton->Location = System::Drawing::Point(12, 192);
				 this->AddTeamGlobalEventButton->Name = L"AddTeamGlobalEventButton";
				 this->AddTeamGlobalEventButton->Size = System::Drawing::Size(119, 42);
				 this->AddTeamGlobalEventButton->TabIndex = 49;
				 this->AddTeamGlobalEventButton->Text = L"Add team/global event";
				 this->AddTeamGlobalEventButton->UseVisualStyleBackColor = true;
				 this->AddTeamGlobalEventButton->Click += gcnew System::EventHandler(this, &MainScreen::AddTeamGlobalEventButton_Click);
				 // 
				 // HelloUserLabel
				 // 
				 this->HelloUserLabel->AutoSize = true;
				 this->HelloUserLabel->BackColor = System::Drawing::Color::Beige;
				 this->HelloUserLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				 this->HelloUserLabel->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->HelloUserLabel->ForeColor = System::Drawing::Color::MediumAquamarine;
				 this->HelloUserLabel->Location = System::Drawing::Point(12, 17);
				 this->HelloUserLabel->Name = L"HelloUserLabel";
				 this->HelloUserLabel->Size = System::Drawing::Size(153, 33);
				 this->HelloUserLabel->TabIndex = 50;
				 this->HelloUserLabel->Text = L"Hello User!";
				 this->HelloUserLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // DayEventsViewPanel
				 // 
				 this->DayEventsViewPanel->BackColor = System::Drawing::Color::Transparent;
				 this->DayEventsViewPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->DayEventsViewPanel->Controls->Add(this->ViewMonthLabel);
				 this->DayEventsViewPanel->Controls->Add(this->ViewYearLabel);
				 this->DayEventsViewPanel->Controls->Add(this->ViewDayLabel);
				 this->DayEventsViewPanel->Controls->Add(this->DeleteEventButton);
				 this->DayEventsViewPanel->Controls->Add(this->EditEventButton);
				 this->DayEventsViewPanel->Controls->Add(this->TypeFillLabel);
				 this->DayEventsViewPanel->Controls->Add(this->TypeStaticLabel);
				 this->DayEventsViewPanel->Controls->Add(this->ListOfGlobalEvents);
				 this->DayEventsViewPanel->Controls->Add(this->ViewGlobalEventsLabel);
				 this->DayEventsViewPanel->Controls->Add(this->ListOfTeamEvents);
				 this->DayEventsViewPanel->Controls->Add(this->ViewTeamEventsLabel);
				 this->DayEventsViewPanel->Controls->Add(this->PriorityFillLabel);
				 this->DayEventsViewPanel->Controls->Add(this->PriorityStaticLabel);
				 this->DayEventsViewPanel->Controls->Add(this->TimeFillLabel);
				 this->DayEventsViewPanel->Controls->Add(this->TimeStaticLabel);
				 this->DayEventsViewPanel->Controls->Add(this->DescriptionTextBox);
				 this->DayEventsViewPanel->Controls->Add(this->NameStaticLabel);
				 this->DayEventsViewPanel->Controls->Add(this->ViewPersonalEventsLabel);
				 this->DayEventsViewPanel->Controls->Add(this->ListOfDayEvents);
				 this->DayEventsViewPanel->Controls->Add(this->ViewEventsPanelBackButton);
				 this->DayEventsViewPanel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
				 this->DayEventsViewPanel->Location = System::Drawing::Point(5, 9);
				 this->DayEventsViewPanel->Name = L"DayEventsViewPanel";
				 this->DayEventsViewPanel->Size = System::Drawing::Size(477, 358);
				 this->DayEventsViewPanel->TabIndex = 51;
				 this->DayEventsViewPanel->Visible = false;
				 this->DayEventsViewPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainScreen::panel1_Paint_1);
				 // 
				 // ViewMonthLabel
				 // 
				 this->ViewMonthLabel->AutoSize = true;
				 this->ViewMonthLabel->BackColor = System::Drawing::Color::SteelBlue;
				 this->ViewMonthLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				 this->ViewMonthLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ViewMonthLabel->Location = System::Drawing::Point(246, 146);
				 this->ViewMonthLabel->Name = L"ViewMonthLabel";
				 this->ViewMonthLabel->Size = System::Drawing::Size(200, 44);
				 this->ViewMonthLabel->TabIndex = 19;
				 this->ViewMonthLabel->Text = L"December";
				 this->ViewMonthLabel->Click += gcnew System::EventHandler(this, &MainScreen::ViewMonthLabel_Click);
				 // 
				 // ViewYearLabel
				 // 
				 this->ViewYearLabel->AutoSize = true;
				 this->ViewYearLabel->BackColor = System::Drawing::Color::SkyBlue;
				 this->ViewYearLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				 this->ViewYearLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ViewYearLabel->Location = System::Drawing::Point(246, 117);
				 this->ViewYearLabel->Name = L"ViewYearLabel";
				 this->ViewYearLabel->Size = System::Drawing::Size(108, 44);
				 this->ViewYearLabel->TabIndex = 18;
				 this->ViewYearLabel->Text = L"2018";
				 this->ViewYearLabel->Click += gcnew System::EventHandler(this, &MainScreen::ViewYearLabel_Click);
				 // 
				 // ViewDayLabel
				 // 
				 this->ViewDayLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->ViewDayLabel->AutoSize = true;
				 this->ViewDayLabel->BackColor = System::Drawing::Color::PaleTurquoise;
				 this->ViewDayLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				 this->ViewDayLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ViewDayLabel->ImageAlign = System::Drawing::ContentAlignment::TopCenter;
				 this->ViewDayLabel->Location = System::Drawing::Point(246, 35);
				 this->ViewDayLabel->Name = L"ViewDayLabel";
				 this->ViewDayLabel->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
				 this->ViewDayLabel->Size = System::Drawing::Size(106, 147);
				 this->ViewDayLabel->TabIndex = 17;
				 this->ViewDayLabel->Text = L"7";
				 this->ViewDayLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
				 this->ViewDayLabel->UseCompatibleTextRendering = true;
				 // 
				 // DeleteEventButton
				 // 
				 this->DeleteEventButton->Location = System::Drawing::Point(335, 300);
				 this->DeleteEventButton->Name = L"DeleteEventButton";
				 this->DeleteEventButton->Size = System::Drawing::Size(83, 22);
				 this->DeleteEventButton->TabIndex = 16;
				 this->DeleteEventButton->Text = L"Delete";
				 this->DeleteEventButton->UseVisualStyleBackColor = true;
				 this->DeleteEventButton->Click += gcnew System::EventHandler(this, &MainScreen::DeleteEventButton_Click);
				 // 
				 // EditEventButton
				 // 
				 this->EditEventButton->Location = System::Drawing::Point(246, 300);
				 this->EditEventButton->Name = L"EditEventButton";
				 this->EditEventButton->Size = System::Drawing::Size(83, 22);
				 this->EditEventButton->TabIndex = 15;
				 this->EditEventButton->Text = L"Edit";
				 this->EditEventButton->UseVisualStyleBackColor = true;
				 this->EditEventButton->Click += gcnew System::EventHandler(this, &MainScreen::EditEventButton_Click);
				 // 
				 // TypeFillLabel
				 // 
				 this->TypeFillLabel->AutoSize = true;
				 this->TypeFillLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->TypeFillLabel->Location = System::Drawing::Point(296, 243);
				 this->TypeFillLabel->Name = L"TypeFillLabel";
				 this->TypeFillLabel->Size = System::Drawing::Size(0, 31);
				 this->TypeFillLabel->TabIndex = 14;
				 this->TypeFillLabel->Click += gcnew System::EventHandler(this, &MainScreen::TypeFillLabel_Click);
				 // 
				 // TypeStaticLabel
				 // 
				 this->TypeStaticLabel->AutoSize = true;
				 this->TypeStaticLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->TypeStaticLabel->Location = System::Drawing::Point(246, 242);
				 this->TypeStaticLabel->Name = L"TypeStaticLabel";
				 this->TypeStaticLabel->Size = System::Drawing::Size(90, 31);
				 this->TypeStaticLabel->TabIndex = 13;
				 this->TypeStaticLabel->Text = L"Type:";
				 this->TypeStaticLabel->Click += gcnew System::EventHandler(this, &MainScreen::TypeStaticLabel_Click);
				 // 
				 // ListOfGlobalEvents
				 // 
				 this->ListOfGlobalEvents->BackColor = System::Drawing::Color::LightSkyBlue;
				 this->ListOfGlobalEvents->FormattingEnabled = true;
				 this->ListOfGlobalEvents->ItemHeight = 24;
				 this->ListOfGlobalEvents->Location = System::Drawing::Point(15, 253);
				 this->ListOfGlobalEvents->Name = L"ListOfGlobalEvents";
				 this->ListOfGlobalEvents->ScrollAlwaysVisible = true;
				 this->ListOfGlobalEvents->Size = System::Drawing::Size(187, 52);
				 this->ListOfGlobalEvents->TabIndex = 12;
				 this->ListOfGlobalEvents->SelectedIndexChanged += gcnew System::EventHandler(this, &MainScreen::ListOfGlobalEvents_SelectedIndexChanged);
				 // 
				 // ViewGlobalEventsLabel
				 // 
				 this->ViewGlobalEventsLabel->AutoSize = true;
				 this->ViewGlobalEventsLabel->Location = System::Drawing::Point(15, 237);
				 this->ViewGlobalEventsLabel->Name = L"ViewGlobalEventsLabel";
				 this->ViewGlobalEventsLabel->Size = System::Drawing::Size(153, 25);
				 this->ViewGlobalEventsLabel->TabIndex = 11;
				 this->ViewGlobalEventsLabel->Text = L"Global Events:";
				 // 
				 // ListOfTeamEvents
				 // 
				 this->ListOfTeamEvents->BackColor = System::Drawing::Color::MediumTurquoise;
				 this->ListOfTeamEvents->FormattingEnabled = true;
				 this->ListOfTeamEvents->ItemHeight = 24;
				 this->ListOfTeamEvents->Location = System::Drawing::Point(15, 154);
				 this->ListOfTeamEvents->Name = L"ListOfTeamEvents";
				 this->ListOfTeamEvents->ScrollAlwaysVisible = true;
				 this->ListOfTeamEvents->Size = System::Drawing::Size(187, 52);
				 this->ListOfTeamEvents->TabIndex = 10;
				 this->ListOfTeamEvents->SelectedIndexChanged += gcnew System::EventHandler(this, &MainScreen::ListOfTeamEvents_SelectedIndexChanged);
				 // 
				 // ViewTeamEventsLabel
				 // 
				 this->ViewTeamEventsLabel->AutoSize = true;
				 this->ViewTeamEventsLabel->Location = System::Drawing::Point(15, 138);
				 this->ViewTeamEventsLabel->Name = L"ViewTeamEventsLabel";
				 this->ViewTeamEventsLabel->Size = System::Drawing::Size(144, 25);
				 this->ViewTeamEventsLabel->TabIndex = 9;
				 this->ViewTeamEventsLabel->Text = L"Team events:";
				 // 
				 // PriorityFillLabel
				 // 
				 this->PriorityFillLabel->AutoSize = true;
				 this->PriorityFillLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->PriorityFillLabel->Location = System::Drawing::Point(316, 277);
				 this->PriorityFillLabel->Name = L"PriorityFillLabel";
				 this->PriorityFillLabel->Size = System::Drawing::Size(0, 31);
				 this->PriorityFillLabel->TabIndex = 8;
				 this->PriorityFillLabel->Click += gcnew System::EventHandler(this, &MainScreen::PriorityFillLabel_Click);
				 // 
				 // PriorityStaticLabel
				 // 
				 this->PriorityStaticLabel->AutoSize = true;
				 this->PriorityStaticLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->PriorityStaticLabel->Location = System::Drawing::Point(245, 277);
				 this->PriorityStaticLabel->Name = L"PriorityStaticLabel";
				 this->PriorityStaticLabel->Size = System::Drawing::Size(134, 31);
				 this->PriorityStaticLabel->TabIndex = 7;
				 this->PriorityStaticLabel->Text = L"Priority:";
				 // 
				 // TimeFillLabel
				 // 
				 this->TimeFillLabel->AutoSize = true;
				 this->TimeFillLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->TimeFillLabel->Location = System::Drawing::Point(295, 260);
				 this->TimeFillLabel->Name = L"TimeFillLabel";
				 this->TimeFillLabel->Size = System::Drawing::Size(0, 31);
				 this->TimeFillLabel->TabIndex = 6;
				 this->TimeFillLabel->Click += gcnew System::EventHandler(this, &MainScreen::TimeFillLabel_Click);
				 // 
				 // TimeStaticLabel
				 // 
				 this->TimeStaticLabel->AutoSize = true;
				 this->TimeStaticLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->TimeStaticLabel->Location = System::Drawing::Point(245, 260);
				 this->TimeStaticLabel->Name = L"TimeStaticLabel";
				 this->TimeStaticLabel->Size = System::Drawing::Size(91, 31);
				 this->TimeStaticLabel->TabIndex = 5;
				 this->TimeStaticLabel->Text = L"Time:";
				 // 
				 // DescriptionTextBox
				 // 
				 this->DescriptionTextBox->BackColor = System::Drawing::Color::White;
				 this->DescriptionTextBox->Location = System::Drawing::Point(246, 200);
				 this->DescriptionTextBox->Multiline = true;
				 this->DescriptionTextBox->Name = L"DescriptionTextBox";
				 this->DescriptionTextBox->ReadOnly = true;
				 this->DescriptionTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
				 this->DescriptionTextBox->Size = System::Drawing::Size(172, 39);
				 this->DescriptionTextBox->TabIndex = 4;
				 // 
				 // NameStaticLabel
				 // 
				 this->NameStaticLabel->AutoSize = true;
				 this->NameStaticLabel->Font = (gcnew System::Drawing::Font(L"Cooper Black", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->NameStaticLabel->Location = System::Drawing::Point(246, 180);
				 this->NameStaticLabel->Name = L"NameStaticLabel";
				 this->NameStaticLabel->Size = System::Drawing::Size(290, 31);
				 this->NameStaticLabel->TabIndex = 3;
				 this->NameStaticLabel->Text = L"Name (description):";
				 // 
				 // ViewPersonalEventsLabel
				 // 
				 this->ViewPersonalEventsLabel->AutoSize = true;
				 this->ViewPersonalEventsLabel->Location = System::Drawing::Point(15, 40);
				 this->ViewPersonalEventsLabel->Name = L"ViewPersonalEventsLabel";
				 this->ViewPersonalEventsLabel->Size = System::Drawing::Size(174, 25);
				 this->ViewPersonalEventsLabel->TabIndex = 2;
				 this->ViewPersonalEventsLabel->Text = L"Personal events:";
				 // 
				 // ListOfDayEvents
				 // 
				 this->ListOfDayEvents->BackColor = System::Drawing::Color::Silver;
				 this->ListOfDayEvents->FormattingEnabled = true;
				 this->ListOfDayEvents->ItemHeight = 24;
				 this->ListOfDayEvents->Location = System::Drawing::Point(15, 56);
				 this->ListOfDayEvents->Name = L"ListOfDayEvents";
				 this->ListOfDayEvents->ScrollAlwaysVisible = true;
				 this->ListOfDayEvents->Size = System::Drawing::Size(187, 52);
				 this->ListOfDayEvents->TabIndex = 1;
				 this->ListOfDayEvents->SelectedIndexChanged += gcnew System::EventHandler(this, &MainScreen::listBox1_SelectedIndexChanged);
				 // 
				 // ViewEventsPanelBackButton
				 // 
				 this->ViewEventsPanelBackButton->Location = System::Drawing::Point(15, 7);
				 this->ViewEventsPanelBackButton->Name = L"ViewEventsPanelBackButton";
				 this->ViewEventsPanelBackButton->Size = System::Drawing::Size(79, 29);
				 this->ViewEventsPanelBackButton->TabIndex = 0;
				 this->ViewEventsPanelBackButton->Text = L"Back";
				 this->ViewEventsPanelBackButton->UseVisualStyleBackColor = true;
				 this->ViewEventsPanelBackButton->Click += gcnew System::EventHandler(this, &MainScreen::button1_Click_1);
				 // 
				 // SysInfoPanel
				 // 
				 this->SysInfoPanel->Controls->Add(this->InfoEmailLinkLabel);
				 this->SysInfoPanel->Controls->Add(this->InfoEmailLabel);
				 this->SysInfoPanel->Controls->Add(this->InfoPhoneLabel);
				 this->SysInfoPanel->Controls->Add(this->InfoDevList);
				 this->SysInfoPanel->Controls->Add(this->InfoDevLabel);
				 this->SysInfoPanel->Controls->Add(this->label2);
				 this->SysInfoPanel->Controls->Add(this->InfoHDDLabel);
				 this->SysInfoPanel->Controls->Add(this->InfoRamLabel);
				 this->SysInfoPanel->Controls->Add(this->InfoWindowsLabel);
				 this->SysInfoPanel->Controls->Add(this->nfoSysReqLabel);
				 this->SysInfoPanel->Controls->Add(this->label1);
				 this->SysInfoPanel->Controls->Add(this->InfoVersionLabel);
				 this->SysInfoPanel->Controls->Add(this->InfoNameLabel);
				 this->SysInfoPanel->Controls->Add(this->SysInfoBackButton);
				 this->SysInfoPanel->Location = System::Drawing::Point(3, 12);
				 this->SysInfoPanel->Name = L"SysInfoPanel";
				 this->SysInfoPanel->Size = System::Drawing::Size(434, 346);
				 this->SysInfoPanel->TabIndex = 20;
				 // 
				 // InfoEmailLinkLabel
				 // 
				 this->InfoEmailLinkLabel->AutoSize = true;
				 this->InfoEmailLinkLabel->Location = System::Drawing::Point(63, 288);
				 this->InfoEmailLinkLabel->Name = L"InfoEmailLinkLabel";
				 this->InfoEmailLinkLabel->Size = System::Drawing::Size(110, 25);
				 this->InfoEmailLinkLabel->TabIndex = 15;
				 this->InfoEmailLinkLabel->TabStop = true;
				 this->InfoEmailLinkLabel->Text = L"linkLabel1";
				 // 
				 // InfoEmailLabel
				 // 
				 this->InfoEmailLabel->AutoSize = true;
				 this->InfoEmailLabel->Location = System::Drawing::Point(11, 288);
				 this->InfoEmailLabel->Name = L"InfoEmailLabel";
				 this->InfoEmailLabel->Size = System::Drawing::Size(81, 25);
				 this->InfoEmailLabel->TabIndex = 14;
				 this->InfoEmailLabel->Text = L"E-Mail:";
				 // 
				 // InfoPhoneLabel
				 // 
				 this->InfoPhoneLabel->AutoSize = true;
				 this->InfoPhoneLabel->Location = System::Drawing::Point(10, 269);
				 this->InfoPhoneLabel->Name = L"InfoPhoneLabel";
				 this->InfoPhoneLabel->Size = System::Drawing::Size(81, 25);
				 this->InfoPhoneLabel->TabIndex = 13;
				 this->InfoPhoneLabel->Text = L"Phone:";
				 // 
				 // InfoDevList
				 // 
				 this->InfoDevList->FormattingEnabled = true;
				 this->InfoDevList->ItemHeight = 24;
				 this->InfoDevList->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
					 L"Vitaly Nechayuk", L"Adir Atia", L"Max Pokidaylo",
						 L"Doron Karavani"
				 });
				 this->InfoDevList->Location = System::Drawing::Point(13, 205);
				 this->InfoDevList->Name = L"InfoDevList";
				 this->InfoDevList->Size = System::Drawing::Size(133, 28);
				 this->InfoDevList->TabIndex = 12;
				 this->InfoDevList->SelectedIndexChanged += gcnew System::EventHandler(this, &MainScreen::InfoDevList_SelectedIndexChanged);
				 // 
				 // InfoDevLabel
				 // 
				 this->InfoDevLabel->AutoSize = true;
				 this->InfoDevLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->InfoDevLabel->Location = System::Drawing::Point(10, 181);
				 this->InfoDevLabel->Name = L"InfoDevLabel";
				 this->InfoDevLabel->Size = System::Drawing::Size(138, 25);
				 this->InfoDevLabel->TabIndex = 11;
				 this->InfoDevLabel->Text = L"Developers:";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(9, 90);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(192, 25);
				 this->label2->TabIndex = 10;
				 this->label2->Text = L"Language: English";
				 // 
				 // InfoHDDLabel
				 // 
				 this->InfoHDDLabel->AutoSize = true;
				 this->InfoHDDLabel->Location = System::Drawing::Point(9, 162);
				 this->InfoHDDLabel->Name = L"InfoHDDLabel";
				 this->InfoHDDLabel->Size = System::Drawing::Size(131, 25);
				 this->InfoHDDLabel->TabIndex = 9;
				 this->InfoHDDLabel->Text = L"400MB HDD";
				 // 
				 // InfoRamLabel
				 // 
				 this->InfoRamLabel->AutoSize = true;
				 this->InfoRamLabel->Location = System::Drawing::Point(9, 148);
				 this->InfoRamLabel->Name = L"InfoRamLabel";
				 this->InfoRamLabel->Size = System::Drawing::Size(133, 25);
				 this->InfoRamLabel->TabIndex = 8;
				 this->InfoRamLabel->Text = L"512MB RAM";
				 // 
				 // InfoWindowsLabel
				 // 
				 this->InfoWindowsLabel->AutoSize = true;
				 this->InfoWindowsLabel->Location = System::Drawing::Point(9, 132);
				 this->InfoWindowsLabel->Name = L"InfoWindowsLabel";
				 this->InfoWindowsLabel->Size = System::Drawing::Size(168, 25);
				 this->InfoWindowsLabel->TabIndex = 7;
				 this->InfoWindowsLabel->Text = L"Windows 7/8/10";
				 // 
				 // nfoSysReqLabel
				 // 
				 this->nfoSysReqLabel->AutoSize = true;
				 this->nfoSysReqLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->nfoSysReqLabel->Location = System::Drawing::Point(9, 114);
				 this->nfoSysReqLabel->Name = L"nfoSysReqLabel";
				 this->nfoSysReqLabel->Size = System::Drawing::Size(233, 25);
				 this->nfoSysReqLabel->TabIndex = 6;
				 this->nfoSysReqLabel->Text = L"System requirements";
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->label1->Location = System::Drawing::Point(9, 44);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(173, 25);
				 this->label1->TabIndex = 5;
				 this->label1->Text = L"System details:";
				 // 
				 // InfoVersionLabel
				 // 
				 this->InfoVersionLabel->AutoSize = true;
				 this->InfoVersionLabel->Location = System::Drawing::Point(9, 76);
				 this->InfoVersionLabel->Name = L"InfoVersionLabel";
				 this->InfoVersionLabel->Size = System::Drawing::Size(129, 25);
				 this->InfoVersionLabel->TabIndex = 4;
				 this->InfoVersionLabel->Text = L"Version: 1.7";
				 // 
				 // InfoNameLabel
				 // 
				 this->InfoNameLabel->AutoSize = true;
				 this->InfoNameLabel->Location = System::Drawing::Point(9, 61);
				 this->InfoNameLabel->Name = L"InfoNameLabel";
				 this->InfoNameLabel->Size = System::Drawing::Size(303, 25);
				 this->InfoNameLabel->TabIndex = 3;
				 this->InfoNameLabel->Text = L"Name of the system: Calendar";
				 // 
				 // SysInfoBackButton
				 // 
				 this->SysInfoBackButton->Location = System::Drawing::Point(9, 7);
				 this->SysInfoBackButton->Name = L"SysInfoBackButton";
				 this->SysInfoBackButton->Size = System::Drawing::Size(79, 29);
				 this->SysInfoBackButton->TabIndex = 2;
				 this->SysInfoBackButton->Text = L"Back";
				 this->SysInfoBackButton->UseVisualStyleBackColor = true;
				 this->SysInfoBackButton->Click += gcnew System::EventHandler(this, &MainScreen::SysInfoBackButton_Click);
				 // 
				 // SettingsPanel
				 // 
				 this->SettingsPanel->BackColor = System::Drawing::Color::Transparent;
				 this->SettingsPanel->Controls->Add(this->SysInfoPanel);
				 this->SettingsPanel->Controls->Add(this->PersonalTeamLabel);
				 this->SettingsPanel->Controls->Add(this->PersonalTeamStatusLabel);
				 this->SettingsPanel->Controls->Add(this->PersonalNameLabel);
				 this->SettingsPanel->Controls->Add(this->PersonaIDLabel);
				 this->SettingsPanel->Controls->Add(this->PersonalDetailsLabel);
				 this->SettingsPanel->Controls->Add(this->SysResetButton);
				 this->SettingsPanel->Controls->Add(this->EditUserButton);
				 this->SettingsPanel->Controls->Add(this->DeleteUserButton);
				 this->SettingsPanel->Controls->Add(this->UserSurnameTextBox);
				 this->SettingsPanel->Controls->Add(this->UserRankTextBox);
				 this->SettingsPanel->Controls->Add(this->UserTeamtextBox);
				 this->SettingsPanel->Controls->Add(this->UserNameTextBox);
				 this->SettingsPanel->Controls->Add(this->UserIDTextBox);
				 this->SettingsPanel->Controls->Add(this->UserRankLabel);
				 this->SettingsPanel->Controls->Add(this->UserTeamLabel);
				 this->SettingsPanel->Controls->Add(this->UserNameLabel);
				 this->SettingsPanel->Controls->Add(this->UserIDLabel);
				 this->SettingsPanel->Controls->Add(this->UserDetailsLabel);
				 this->SettingsPanel->Controls->Add(this->UserListLabel);
				 this->SettingsPanel->Controls->Add(this->UserList);
				 this->SettingsPanel->Controls->Add(this->SysInfoButton);
				 this->SettingsPanel->Controls->Add(this->AddNewUserButton);
				 this->SettingsPanel->Controls->Add(this->ChangePasswordButton);
				 this->SettingsPanel->Controls->Add(this->SecondBackButton);
				 this->SettingsPanel->Location = System::Drawing::Point(-1, 12);
				 this->SettingsPanel->Name = L"SettingsPanel";
				 this->SettingsPanel->Size = System::Drawing::Size(450, 372);
				 this->SettingsPanel->TabIndex = 20;
				 // 
				 // PersonalTeamLabel
				 // 
				 this->PersonalTeamLabel->AutoSize = true;
				 this->PersonalTeamLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->PersonalTeamLabel->Location = System::Drawing::Point(12, 286);
				 this->PersonalTeamLabel->Name = L"PersonalTeamLabel";
				 this->PersonalTeamLabel->Size = System::Drawing::Size(34, 25);
				 this->PersonalTeamLabel->TabIndex = 26;
				 this->PersonalTeamLabel->Text = L"ID";
				 // 
				 // PersonalTeamStatusLabel
				 // 
				 this->PersonalTeamStatusLabel->AutoSize = true;
				 this->PersonalTeamStatusLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold,
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->PersonalTeamStatusLabel->Location = System::Drawing::Point(12, 263);
				 this->PersonalTeamStatusLabel->Name = L"PersonalTeamStatusLabel";
				 this->PersonalTeamStatusLabel->Size = System::Drawing::Size(34, 25);
				 this->PersonalTeamStatusLabel->TabIndex = 25;
				 this->PersonalTeamStatusLabel->Text = L"ID";
				 // 
				 // PersonalNameLabel
				 // 
				 this->PersonalNameLabel->AutoSize = true;
				 this->PersonalNameLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->PersonalNameLabel->Location = System::Drawing::Point(12, 242);
				 this->PersonalNameLabel->Name = L"PersonalNameLabel";
				 this->PersonalNameLabel->Size = System::Drawing::Size(34, 25);
				 this->PersonalNameLabel->TabIndex = 24;
				 this->PersonalNameLabel->Text = L"ID";
				 // 
				 // PersonaIDLabel
				 // 
				 this->PersonaIDLabel->AutoSize = true;
				 this->PersonaIDLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->PersonaIDLabel->Location = System::Drawing::Point(12, 222);
				 this->PersonaIDLabel->Name = L"PersonaIDLabel";
				 this->PersonaIDLabel->Size = System::Drawing::Size(34, 25);
				 this->PersonaIDLabel->TabIndex = 23;
				 this->PersonaIDLabel->Text = L"ID";
				 // 
				 // PersonalDetailsLabel
				 // 
				 this->PersonalDetailsLabel->AutoSize = true;
				 this->PersonalDetailsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->PersonalDetailsLabel->Location = System::Drawing::Point(12, 197);
				 this->PersonalDetailsLabel->Name = L"PersonalDetailsLabel";
				 this->PersonalDetailsLabel->Size = System::Drawing::Size(298, 31);
				 this->PersonalDetailsLabel->TabIndex = 22;
				 this->PersonalDetailsLabel->Text = L"Your personal details:";
				 // 
				 // SysResetButton
				 // 
				 this->SysResetButton->Location = System::Drawing::Point(15, 161);
				 this->SysResetButton->Name = L"SysResetButton";
				 this->SysResetButton->Size = System::Drawing::Size(172, 24);
				 this->SysResetButton->TabIndex = 21;
				 this->SysResetButton->Text = L"System reset";
				 this->SysResetButton->UseVisualStyleBackColor = true;
				 this->SysResetButton->Click += gcnew System::EventHandler(this, &MainScreen::SysResetButton_Click);
				 // 
				 // EditUserButton
				 // 
				 this->EditUserButton->Location = System::Drawing::Point(228, 288);
				 this->EditUserButton->Name = L"EditUserButton";
				 this->EditUserButton->Size = System::Drawing::Size(93, 29);
				 this->EditUserButton->TabIndex = 20;
				 this->EditUserButton->Text = L"Edit";
				 this->EditUserButton->UseVisualStyleBackColor = true;
				 this->EditUserButton->Click += gcnew System::EventHandler(this, &MainScreen::EditUserButton_Click);
				 // 
				 // DeleteUserButton
				 // 
				 this->DeleteUserButton->Location = System::Drawing::Point(322, 288);
				 this->DeleteUserButton->Name = L"DeleteUserButton";
				 this->DeleteUserButton->Size = System::Drawing::Size(93, 29);
				 this->DeleteUserButton->TabIndex = 19;
				 this->DeleteUserButton->Text = L"Delete";
				 this->DeleteUserButton->UseVisualStyleBackColor = true;
				 this->DeleteUserButton->Click += gcnew System::EventHandler(this, &MainScreen::DeleteUserButton_Click_1);
				 // 
				 // UserSurnameTextBox
				 // 
				 this->UserSurnameTextBox->Location = System::Drawing::Point(270, 210);
				 this->UserSurnameTextBox->Name = L"UserSurnameTextBox";
				 this->UserSurnameTextBox->ReadOnly = true;
				 this->UserSurnameTextBox->Size = System::Drawing::Size(145, 29);
				 this->UserSurnameTextBox->TabIndex = 18;
				 // 
				 // UserRankTextBox
				 // 
				 this->UserRankTextBox->Location = System::Drawing::Point(270, 262);
				 this->UserRankTextBox->Name = L"UserRankTextBox";
				 this->UserRankTextBox->ReadOnly = true;
				 this->UserRankTextBox->Size = System::Drawing::Size(145, 29);
				 this->UserRankTextBox->TabIndex = 17;
				 // 
				 // UserTeamtextBox
				 // 
				 this->UserTeamtextBox->Location = System::Drawing::Point(270, 236);
				 this->UserTeamtextBox->Name = L"UserTeamtextBox";
				 this->UserTeamtextBox->ReadOnly = true;
				 this->UserTeamtextBox->Size = System::Drawing::Size(145, 29);
				 this->UserTeamtextBox->TabIndex = 16;
				 this->UserTeamtextBox->TextChanged += gcnew System::EventHandler(this, &MainScreen::textBox1_TextChanged);
				 // 
				 // UserNameTextBox
				 // 
				 this->UserNameTextBox->Location = System::Drawing::Point(270, 184);
				 this->UserNameTextBox->Name = L"UserNameTextBox";
				 this->UserNameTextBox->ReadOnly = true;
				 this->UserNameTextBox->Size = System::Drawing::Size(145, 29);
				 this->UserNameTextBox->TabIndex = 15;
				 // 
				 // UserIDTextBox
				 // 
				 this->UserIDTextBox->Location = System::Drawing::Point(270, 161);
				 this->UserIDTextBox->Name = L"UserIDTextBox";
				 this->UserIDTextBox->ReadOnly = true;
				 this->UserIDTextBox->Size = System::Drawing::Size(145, 29);
				 this->UserIDTextBox->TabIndex = 14;
				 // 
				 // UserRankLabel
				 // 
				 this->UserRankLabel->AutoSize = true;
				 this->UserRankLabel->Location = System::Drawing::Point(225, 265);
				 this->UserRankLabel->Name = L"UserRankLabel";
				 this->UserRankLabel->Size = System::Drawing::Size(68, 25);
				 this->UserRankLabel->TabIndex = 13;
				 this->UserRankLabel->Text = L"Rank:";
				 // 
				 // UserTeamLabel
				 // 
				 this->UserTeamLabel->AutoSize = true;
				 this->UserTeamLabel->Location = System::Drawing::Point(225, 240);
				 this->UserTeamLabel->Name = L"UserTeamLabel";
				 this->UserTeamLabel->Size = System::Drawing::Size(80, 25);
				 this->UserTeamLabel->TabIndex = 12;
				 this->UserTeamLabel->Text = L"Team: ";
				 // 
				 // UserNameLabel
				 // 
				 this->UserNameLabel->AutoSize = true;
				 this->UserNameLabel->Location = System::Drawing::Point(225, 187);
				 this->UserNameLabel->Name = L"UserNameLabel";
				 this->UserNameLabel->Size = System::Drawing::Size(75, 25);
				 this->UserNameLabel->TabIndex = 11;
				 this->UserNameLabel->Text = L"Name:";
				 this->UserNameLabel->Click += gcnew System::EventHandler(this, &MainScreen::UserNameLabel_Click);
				 // 
				 // UserIDLabel
				 // 
				 this->UserIDLabel->AutoSize = true;
				 this->UserIDLabel->Location = System::Drawing::Point(225, 164);
				 this->UserIDLabel->Name = L"UserIDLabel";
				 this->UserIDLabel->Size = System::Drawing::Size(40, 25);
				 this->UserIDLabel->TabIndex = 10;
				 this->UserIDLabel->Text = L"ID:";
				 this->UserIDLabel->Click += gcnew System::EventHandler(this, &MainScreen::UserIDLabel_Click);
				 // 
				 // UserDetailsLabel
				 // 
				 this->UserDetailsLabel->AutoSize = true;
				 this->UserDetailsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
				 this->UserDetailsLabel->Location = System::Drawing::Point(227, 144);
				 this->UserDetailsLabel->Name = L"UserDetailsLabel";
				 this->UserDetailsLabel->Size = System::Drawing::Size(133, 25);
				 this->UserDetailsLabel->TabIndex = 9;
				 this->UserDetailsLabel->Text = L"User details:";
				 // 
				 // UserListLabel
				 // 
				 this->UserListLabel->AutoSize = true;
				 this->UserListLabel->Location = System::Drawing::Point(228, 21);
				 this->UserListLabel->Name = L"UserListLabel";
				 this->UserListLabel->Size = System::Drawing::Size(75, 25);
				 this->UserListLabel->TabIndex = 8;
				 this->UserListLabel->Text = L"Users:";
				 // 
				 // UserList
				 // 
				 this->UserList->FormattingEnabled = true;
				 this->UserList->ItemHeight = 24;
				 this->UserList->Location = System::Drawing::Point(228, 40);
				 this->UserList->Name = L"UserList";
				 this->UserList->Size = System::Drawing::Size(187, 76);
				 this->UserList->TabIndex = 7;
				 this->UserList->SelectedIndexChanged += gcnew System::EventHandler(this, &MainScreen::UserList_SelectedIndexChanged);
				 // 
				 // SysInfoButton
				 // 
				 this->SysInfoButton->Location = System::Drawing::Point(15, 128);
				 this->SysInfoButton->Name = L"SysInfoButton";
				 this->SysInfoButton->Size = System::Drawing::Size(172, 24);
				 this->SysInfoButton->TabIndex = 6;
				 this->SysInfoButton->Text = L"System Information";
				 this->SysInfoButton->UseVisualStyleBackColor = true;
				 this->SysInfoButton->Click += gcnew System::EventHandler(this, &MainScreen::SysInfoButton_Click);
				 // 
				 // AddNewUserButton
				 // 
				 this->AddNewUserButton->Location = System::Drawing::Point(15, 98);
				 this->AddNewUserButton->Name = L"AddNewUserButton";
				 this->AddNewUserButton->Size = System::Drawing::Size(172, 24);
				 this->AddNewUserButton->TabIndex = 3;
				 this->AddNewUserButton->Text = L"Add New User (System) ";
				 this->AddNewUserButton->UseVisualStyleBackColor = true;
				 this->AddNewUserButton->Click += gcnew System::EventHandler(this, &MainScreen::AddNewUserbutton_Click);
				 // 
				 // ChangePasswordButton
				 // 
				 this->ChangePasswordButton->Location = System::Drawing::Point(15, 68);
				 this->ChangePasswordButton->Name = L"ChangePasswordButton";
				 this->ChangePasswordButton->Size = System::Drawing::Size(172, 24);
				 this->ChangePasswordButton->TabIndex = 2;
				 this->ChangePasswordButton->Text = L"Change password";
				 this->ChangePasswordButton->UseVisualStyleBackColor = true;
				 this->ChangePasswordButton->Click += gcnew System::EventHandler(this, &MainScreen::ChangePasswordButton_Click);
				 // 
				 // SecondBackButton
				 // 
				 this->SecondBackButton->Location = System::Drawing::Point(15, 12);
				 this->SecondBackButton->Name = L"SecondBackButton";
				 this->SecondBackButton->Size = System::Drawing::Size(79, 29);
				 this->SecondBackButton->TabIndex = 1;
				 this->SecondBackButton->Text = L"Back";
				 this->SecondBackButton->UseVisualStyleBackColor = true;
				 this->SecondBackButton->Click += gcnew System::EventHandler(this, &MainScreen::SecondBackButton_Click);
				 // 
				 // timer1
				 // 
				 this->timer1->Tick += gcnew System::EventHandler(this, &MainScreen::timer1_Tick);
				 // 
				 // TimeLabel
				 // 
				 this->TimeLabel->AutoSize = true;
				 this->TimeLabel->BackColor = System::Drawing::Color::Moccasin;
				 this->TimeLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
				 this->TimeLabel->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->TimeLabel->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
				 this->TimeLabel->Location = System::Drawing::Point(12, 45);
				 this->TimeLabel->Name = L"TimeLabel";
				 this->TimeLabel->Size = System::Drawing::Size(92, 39);
				 this->TimeLabel->TabIndex = 52;
				 this->TimeLabel->Text = L"Time";
				 // 
				 // MainScreen
				 // 
				 this->AccessibleRole = System::Windows::Forms::AccessibleRole::ScrollBar;
				 this->AutoScaleDimensions = System::Drawing::SizeF(12, 24);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::SystemColors::Control;
				 this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
				 this->ClientSize = System::Drawing::Size(485, 390);
				 this->Controls->Add(this->DayEventsViewPanel);
				 this->Controls->Add(this->SettingsPanel);
				 this->Controls->Add(this->TimeLabel);
				 this->Controls->Add(this->HelloUserLabel);
				 this->Controls->Add(this->AddTeamGlobalEventButton);
				 this->Controls->Add(this->AddLocalEventButton);
				 this->Controls->Add(this->LogOutButton);
				 this->Controls->Add(this->SettingsButton);
				 this->Controls->Add(this->ViewDayEventsButton);
				 this->Controls->Add(this->QSMonthCombobox);
				 this->Controls->Add(this->TODAYButton);
				 this->Controls->Add(this->ShowCurrentYearButton);
				 this->Controls->Add(this->NextYearButton);
				 this->Controls->Add(this->PrevYearButton);
				 this->Controls->Add(this->ShowCurrentMonthButton);
				 this->Controls->Add(this->NextMonthButton);
				 this->Controls->Add(this->PrevMonthButton);
				 this->Controls->Add(this->ActivateQuickSearchButton);
				 this->Controls->Add(this->QSYearTextbox);
				 this->Controls->Add(this->QuickSearchYearButton);
				 this->Controls->Add(this->QuickSearchMonthLabel);
				 this->Controls->Add(this->QuickSearchButton);
				 this->Controls->Add(this->Day31Button);
				 this->Controls->Add(this->Day30Button);
				 this->Controls->Add(this->Day29Button);
				 this->Controls->Add(this->Day28Button);
				 this->Controls->Add(this->Day27Button);
				 this->Controls->Add(this->Day26Button);
				 this->Controls->Add(this->Day25Button);
				 this->Controls->Add(this->Day24Button);
				 this->Controls->Add(this->Day23Button);
				 this->Controls->Add(this->Day22Button);
				 this->Controls->Add(this->Day21Button);
				 this->Controls->Add(this->Day20Button);
				 this->Controls->Add(this->Day19Button);
				 this->Controls->Add(this->Day18Button);
				 this->Controls->Add(this->Day17Button);
				 this->Controls->Add(this->Day16Button);
				 this->Controls->Add(this->Day15Button);
				 this->Controls->Add(this->Day14Button);
				 this->Controls->Add(this->Day13Button);
				 this->Controls->Add(this->Day12Button);
				 this->Controls->Add(this->Day11Button);
				 this->Controls->Add(this->Day10Button);
				 this->Controls->Add(this->Day9Button);
				 this->Controls->Add(this->Day8Button);
				 this->Controls->Add(this->Day7Button);
				 this->Controls->Add(this->Day6Button);
				 this->Controls->Add(this->Day5Button);
				 this->Controls->Add(this->Day4Button);
				 this->Controls->Add(this->Day3Button);
				 this->Controls->Add(this->Day2Button);
				 this->Controls->Add(this->Day1Button);
				 this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->MaximizeBox = false;
				 this->MinimizeBox = false;
				 this->Name = L"MainScreen";
				 this->Text = L"Calendar";
				 this->Load += gcnew System::EventHandler(this, &MainScreen::MainScreen_Load);
				 this->DayEventsViewPanel->ResumeLayout(false);
				 this->DayEventsViewPanel->PerformLayout();
				 this->SysInfoPanel->ResumeLayout(false);
				 this->SysInfoPanel->PerformLayout();
				 this->SettingsPanel->ResumeLayout(false);
				 this->SettingsPanel->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void monthCalendar1_DateChanged(System::Object^  sender, System::Windows::Forms::DateRangeEventArgs^  e) {
	}
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void MainScreen_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	//Day buttons
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		month_and_year_check(ShowMonth, ShowYear);
		GlobalClass::day = "1";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(1);
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "2";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(2);
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		GlobalClass::day = "3";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(3);
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "4";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(4);
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "5";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(5);
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "6";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(6);
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "7";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(7);
	}
	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "8";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(8);
	}
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "9";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(9);
	}
	private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "10";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(10);
	}
	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "11";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(11);
	}
	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "12";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(12);
	}
	private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "13";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(13);
	}
	private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "14";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(14);
	}
	private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "15";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(15);
	}
	private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "16";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(16);
	}
	private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "17";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(17);
	}
	private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "18";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(18);
	}
	private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "19";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(19);
	}
	private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "20";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(20);
	}
	private: System::Void button21_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "21";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(21);
	}
	private: System::Void button22_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "22";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(22);
	}
	private: System::Void button23_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "23";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(23);
	}
	private: System::Void button24_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "24";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(24);
	}
	private: System::Void button25_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "25";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(25);
	}
	private: System::Void button26_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "26";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(26);
	}
	private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "27";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(27);
	}
	private: System::Void button28_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "28";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(28);
	}
	private: System::Void button29_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "29";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(29);
	}
	private: System::Void button30_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "30";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(30);
	}
	private: System::Void button31_Click(System::Object^  sender, System::EventArgs^  e) {
		dateChosen = true;
		GlobalClass::day = "31";
		month_and_year_check(ShowMonth, ShowYear);
		show_date(31);
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	//Month "rotation" buttons
	private: System::Void button32_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowMonth = convertSpecialStringToInt(QSMonthCombobox->Text);
		ShowYear = convertSpecialStringToInt(QSYearTextbox->Text);
		ShowCurrentYearButton->Text = returnYear(ShowYear);
		ShowCurrentMonthButton->Text = returnCurrentMonth(ShowMonth);
		month_and_year_check(ShowMonth, ShowYear);
		ViewDayEventsButton->Text = "";
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
	}
	private: System::Void button34_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowMonth = nextMonth(ShowMonth);
		ShowCurrentMonthButton->Text = returnCurrentMonth(ShowMonth);
		month_and_year_check(ShowMonth, ShowYear);
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
		ViewDayEventsButton->Text = "";
	}
	private: System::Void button35_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowMonth = ShowCurrentMonth;
		ShowCurrentMonthButton->Text = returnCurrentMonth(ShowMonth);
		month_and_year_check(ShowMonth, ShowYear);
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
		ViewDayEventsButton->Text = "";
	}
	private: System::Void button33_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowMonth = prevMonth(ShowMonth);
		ShowCurrentMonthButton->Text = returnCurrentMonth(ShowMonth);
		month_and_year_check(ShowMonth, ShowYear);
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
		ViewDayEventsButton->Text = "";
	}
	private: System::Void button37_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowYear++;
		ShowCurrentYearButton->Text = returnYear(ShowYear);
		month_and_year_check(ShowMonth, ShowYear);
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
		ViewDayEventsButton->Text = "";
	}
	private: System::Void button38_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowYear = ShowCurrentYear;
		ShowCurrentYearButton->Text = returnYear(ShowYear);
		month_and_year_check(ShowMonth, ShowYear);
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
		ViewDayEventsButton->Text = "";
	}
	private: System::Void button36_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowYear--;
		ShowCurrentYearButton->Text = returnYear(ShowYear);
		month_and_year_check(ShowMonth, ShowYear);
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
		ViewDayEventsButton->Text = "";
	}
	private: System::Void button39_Click(System::Object^  sender, System::EventArgs^  e) {
		ShowMonth = ShowCurrentMonth;
		ShowYear = ShowCurrentYear;
		ShowCurrentMonthButton->Text = returnCurrentMonth(ShowMonth);
		ShowCurrentYearButton->Text = returnYear(ShowYear);
		month_and_year_check(ShowMonth, ShowYear);
		AddLocalEventButton->Visible = false;
		AddTeamGlobalEventButton->Visible = false;
		ViewDayEventsButton->Text = "";
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void comboBox1_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button42_Click(System::Object^  sender, System::EventArgs^  e) {
		//Log out
		Close();
	}
	//Day events screen (panel)
	private: System::Void AddTeamGlobalEventButton_Click(System::Object^  sender, System::EventArgs^  e) {
		GlobalClass::old_event_name = "";
		GlobalClass::old_priority = "";
		GlobalClass::old_eventType = "";
		GlobalClass::old_hour = "";
		GlobalClass::old_minute = "";
		if (currentUserRank == 2) {
			add_personal_event::add_personal_event form;
			add_personal_event::eventType = "TeamEvents.txt";
			add_personal_event::teamName = teamName;
			form.ShowDialog();
		}
		else if (currentUserRank == 3) {
			add_personal_event::add_personal_event form;
			add_personal_event::eventType = "GlobalEvents.txt";
			add_personal_event::teamName = "Global";
			form.ShowDialog();
		}
		this->Show();
	}
	private: System::Void AddLocalEventButton_Click(System::Object^  sender, System::EventArgs^  e) {
		GlobalClass::old_event_name = "";
		GlobalClass::old_priority = "";
		GlobalClass::old_eventType = "";
		GlobalClass::old_hour = "";
		GlobalClass::old_minute = "";
		add_personal_event::add_personal_event form;
		add_personal_event::eventType = "PersonalEvents.txt";
		add_personal_event::teamName = to_string(currentUserID);
		form.ShowDialog();
		this->Show();
	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		//Back button
		DayEventsViewPanel->Hide();
		ListOfDayEvents->Items->Clear();
		DescriptionTextBox->Clear();
		PriorityFillLabel->Text = "";
		TimeFillLabel->Text = "";
		TypeFillLabel->Text = "";
		ListOfTeamEvents->Items->Clear();
		ListOfGlobalEvents->Items->Clear();
		EditEventButton->Hide();
		DeleteEventButton->Hide();
		currentSelectedTypeOfEvent = 0;
	}
	private: System::Void panel1_Paint_1(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	}
	private: System::Void ViewDayEventsButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//Day events screen (panel) activation
		if (dateChosen == true) {
			ListOfDayEvents->Items->Clear();
			ListOfTeamEvents->Items->Clear();
			ListOfGlobalEvents->Items->Clear();
			currentSelectedTypeOfEvent = 0;
			DayEventsViewPanel->Show();
			int tempDay = convertSpecialStringToInt(GlobalClass::day);
			string currentDate = returnCurrentMonthString(ShowMonth) + " " + to_string(tempDay) + " " + to_string(ShowYear);
			string checkID, checkDate, ignore, newItem = "", checkTeam;
			fstream personalEvents, teamEvents, GlobalEvents;
			ViewDayLabel->Text = GlobalClass::day;
			ViewMonthLabel->Text = GlobalClass::month;
			ViewYearLabel->Text = GlobalClass::year;
			personalEvents.open("PersonalEvents.txt");
			teamEvents.open("TeamEvents.txt");
			GlobalEvents.open("GlobalEvents.txt");
			while (!personalEvents.eof()) {
				getline(personalEvents, checkID);
				getline(personalEvents, checkDate);
				getline(personalEvents, ignore);
				if (checkDate == currentDate && checkID == to_string(currentUserID)) {
					ListOfDayEvents->Items->Add(gcnew String(ignore.c_str()));
				}
				for (int i = 0; i < 3; i++) getline(personalEvents, ignore);
			}
			if (teamName != "None") {
				while (!teamEvents.eof()) {
					getline(teamEvents, checkTeam);
					getline(teamEvents, checkDate);
					getline(teamEvents, ignore);
					if (checkDate == currentDate && checkTeam == teamName) {
						ListOfTeamEvents->Items->Add(gcnew String(ignore.c_str()));
					}
					for (int i = 0; i < 3; i++) getline(teamEvents, ignore);
				}
			}
			while (!GlobalEvents.eof()) {
				getline(GlobalEvents, checkDate);
				getline(GlobalEvents, ignore);
				if (checkDate == currentDate) {
					ListOfGlobalEvents->Items->Add(gcnew String(ignore.c_str()));
				}
				for (int i = 0; i < 3; i++) getline(GlobalEvents, ignore);
			}
			personalEvents.close();
			teamEvents.close();
			GlobalEvents.close();
			if (ListOfDayEvents->Items->Count > 0) ListOfDayEvents->SelectedIndex = 0;
			if (ListOfTeamEvents->Items->Count > 0) ListOfTeamEvents->SelectedIndex = 0;
			if (ListOfGlobalEvents->Items->Count > 0) ListOfGlobalEvents->SelectedIndex = 0;
			PriorityFillLabel->Text = "";
			TimeFillLabel->Text = "";
			TypeFillLabel->Text = "";
			DescriptionTextBox->Clear();
			EditEventButton->Show();
			EditEventButton->Enabled = false;
			DeleteEventButton->Show();
			DeleteEventButton->Enabled = false;
		}
	}
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//Personal events list
		currentSelectedTypeOfEvent = 1;
		chosen_event = "PersonalEvents.txt";
		DescriptionTextBox->Text = ListOfDayEvents->SelectedItem->ToString();
		string temp = converSpecialStringToString(ListOfDayEvents->SelectedItem->ToString());
		PriorityFillLabel->Text = gcnew String((getPriorityOfEvent(temp, to_string(currentUserID), returnCurrentMonthString(ShowMonth) + " " + converSpecialStringToString(GlobalClass::day) + " " + to_string(ShowYear))).c_str());
		temp = getTimeOfEvent(temp, to_string(currentUserID), returnCurrentMonthString(ShowMonth) + " " + converSpecialStringToString(GlobalClass::day) + " " + to_string(ShowYear));
		TimeFillLabel->Text = gcnew String(temp.c_str());
		temp = converSpecialStringToString(ListOfDayEvents->SelectedItem->ToString());
		temp = getEventType(temp, to_string(currentUserID), returnCurrentMonthString(ShowMonth) + " " + converSpecialStringToString(GlobalClass::day) + " " + to_string(ShowYear));
		TypeFillLabel->Text = gcnew String(temp.c_str());
		EditEventButton->Enabled = true;
		DeleteEventButton->Enabled = true;
	}
	private: System::Void PriorityFillLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void ListOfTeamEvents_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//Team events list
		currentSelectedTypeOfEvent = 2;
		chosen_event = "TeamEvents.txt";
		DescriptionTextBox->Text = ListOfTeamEvents->SelectedItem->ToString();
		string temp = converSpecialStringToString(ListOfTeamEvents->SelectedItem->ToString());
		PriorityFillLabel->Text = gcnew String((getPriorityOfTeamEvent(temp, teamName, returnCurrentMonthString(ShowMonth) + " " + converSpecialStringToString(GlobalClass::day) + " " + to_string(ShowYear))).c_str());
		temp = getTimeOfTeamEvent(temp, teamName, returnCurrentMonthString(ShowMonth) + " " + converSpecialStringToString(GlobalClass::day) + " " + to_string(ShowYear));
		TimeFillLabel->Text = gcnew String(temp.c_str());
		temp = converSpecialStringToString(ListOfTeamEvents->SelectedItem->ToString());
		temp = getTeamEventType(temp, teamName, returnCurrentMonthString(ShowMonth) + " " + converSpecialStringToString(GlobalClass::day) + " " + to_string(ShowYear));
		TypeFillLabel->Text = gcnew String(temp.c_str());
		if (currentUserRank == 2) EditEventButton->Enabled = true;
		else EditEventButton->Enabled = false;
		if (currentUserRank == 2) DeleteEventButton->Enabled = true;
		else DeleteEventButton->Enabled = false;
	}
	private: System::Void ListOfGlobalEvents_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//Global events
		currentSelectedTypeOfEvent = 3;
		chosen_event = "GlobalEvents.txt";
		DescriptionTextBox->Text = ListOfGlobalEvents->SelectedItem->ToString();
		fstream GlobalEvents;
		string temp;
		if (currentUserRank == 3) EditEventButton->Enabled = true;
		else EditEventButton->Enabled = false;
		if (currentUserRank == 3) DeleteEventButton->Enabled = true;
		else DeleteEventButton->Enabled = false;
		DeleteEventButton->Show();
		GlobalEvents.open("GlobalEvents.txt");
		while (!GlobalEvents.eof()) {
			getline(GlobalEvents, temp);
			if (temp == (returnCurrentMonthString(ShowMonth) + " " + converSpecialStringToString(GlobalClass::day) + " " + to_string(ShowYear))) {
				getline(GlobalEvents, temp);
				if (converSpecialStringToString(ListOfGlobalEvents->SelectedItem->ToString()) == temp) {
					DescriptionTextBox->Text = gcnew String(temp.c_str());
					getline(GlobalEvents, temp);
					PriorityFillLabel->Text = gcnew String(temp.c_str());
					getline(GlobalEvents, temp);
					TimeFillLabel->Text = gcnew String(temp.c_str());
					getline(GlobalEvents, temp);
					TypeFillLabel->Text = gcnew String(temp.c_str());
				}
				for (int i = 0; i < 3; i++) getline(GlobalEvents, temp);
			}
		}
		GlobalEvents.close();
	}
	private: System::Void TypeFillLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void ViewYearLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void ViewMonthLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void TimeFillLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	//Settings screen (panel)
	private: System::Void SecondBackButton_Click(System::Object^  sender, System::EventArgs^  e) {
		SettingsPanel->Visible = false;
		AddNewUserButton->Visible = false;
		SysInfoButton->Visible = false;
		UserListLabel->Visible = false;
		UserList->Items->Clear();
		UserList->Visible = false;
		DeleteUserButton->Visible = false;
		EditUserButton->Visible = false;
		UserIDLabel->Visible = false;
		UserIDTextBox->Visible = false;
		UserNameLabel->Visible = false;
		UserNameTextBox->Visible = false;
		UserSurnameTextBox->Visible = false;
		UserRankLabel->Visible = false;
		UserRankTextBox->Visible = false;
		UserTeamLabel->Visible = false;
		UserTeamtextBox->Visible = false;
		UserDetailsLabel->Visible = false;
	}
	private: System::Void SettingsButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//Settings screen (panel) activation
		SettingsPanel->Visible = true;
		SysResetButton->Visible = false;
		if (currentUserRank == 2 || currentUserRank == 3) {
			AddNewUserButton->Visible = true;
			UserListLabel->Visible = true;
			UserList->Visible = true;
			DeleteUserButton->Visible = true;
			UserIDLabel->Visible = true;
			UserIDTextBox->Visible = true;
			UserNameLabel->Visible = true;
			UserNameTextBox->Visible = true;
			UserSurnameTextBox->Visible = true;
			UserRankLabel->Visible = true;
			UserRankTextBox->Visible = true;
			UserTeamLabel->Visible = true;
			UserTeamtextBox->Visible = true;
			UserDetailsLabel->Visible = true;
			if (currentUserRank == 2) {
				AddNewUserButton->Text = "Add New User (Team)";
				UserListLabel->Text = "Users of your team:";
				refreshTeamUserList();
			}
			else {
				refreshUserList();
				SysInfoButton->Visible = true;
				EditUserButton->Visible = true;
				SysResetButton->Visible = true;
			}
		}
		if (UserList->Items->Count > 0) UserList->SelectedIndex = 0;
	}
	private: System::Void TypeStaticLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void AddNewUserbutton_Click(System::Object^  sender, System::EventArgs^  e) {
		//Add user
		if (currentUserRank == 3) {
			AddUserScreen::AddUserSCR form;
			form.ShowDialog();
			refreshUserList();
		}
		else if (currentUserRank == 2 && teamName != "None") {
			AddUserToTeamScreenn::AddUserToTeamSCR form;
			AddUserToTeamScreenn::currentTeamName = teamName;
			form.ShowDialog();
			refreshTeamUserList();
		}
	}
	private: System::Void DeleteUserButton_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void UserList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//User list
		fstream personalDetails;
		string theID = converSpecialStringToString(UserList->SelectedItem->ToString()), temp1, temp2 = "";
		EditUserScreen::editedUserID = theID;
		personalDetails.open(theID + ".txt");
		UserIDTextBox->Text = UserList->SelectedItem->ToString();
		int intID = convertSpecialStringToInt(UserList->SelectedItem->ToString());
		EditUserScreen::editedUserRank = to_string(checkRank(intID));
		EditUserScreen::tempID = checkRank(intID);
		if (checkRank(intID) == 1) UserRankTextBox->Text = "Regular User";
		if (checkRank(intID) == 2) UserRankTextBox->Text = "Team Leader";
		if (checkRank(intID) == 3) UserRankTextBox->Text = "Admin";
		for (int i = 0; i < 3; i++) getline(personalDetails, temp1);
		for (int i = 11; i < (int)temp1.length(); i++) temp2 = temp2 + temp1[i];
		UserNameTextBox->Text = gcnew String(temp2.c_str());
		EditUserScreen::editedUserFirstName = temp2;
		getline(personalDetails, temp1);
		temp2 = "";
		for (int i = 10; i < (int)temp1.length(); i++) temp2 = temp2 + temp1[i];
		UserSurnameTextBox->Text = gcnew String(temp2.c_str());
		EditUserScreen::editedUserLastName = temp2;
		getline(personalDetails, temp1);
		temp2 = "";
		for (int i = 7; i < (int)temp1.length(); i++) temp2 = temp2 + temp1[i];
		UserTeamtextBox->Text = gcnew String(temp2.c_str());
		EditUserScreen::editedUserTeam = temp2;
	}
	private: System::Void UserIDLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void UserNameLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void DeleteUserButton_Click_1(System::Object^  sender, System::EventArgs^  e) {
		//Delete user
		if (currentUserRank == 3) {
			DeleteUserScreen::userID = converSpecialStringToString(UserList->SelectedItem->ToString());
			DeleteUserScreen::DeleteUserSCR form;
			form.ShowDialog();
			refreshUserList();
		}
		else if (currentUserRank == 2) {
			string temp = converSpecialStringToString(UserList->SelectedItem->ToString());
			ChangeGroup(temp, "None");
			refreshTeamUserList();
		}
	}
	private: System::Void EditUserButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//Edit user
		EditUserScreen::EditUserSCR form;
		form.ShowDialog();
	}
	private: System::Void ChangePasswordButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//Change password
		ChangePasswordScreen::userID = to_string(currentUserID);
		ChangePasswordScreen::ChangePasswordSCR form;
		form.ShowDialog();
	}
	//Sys info screen (panel)
	private: System::Void SysInfoBackButton_Click(System::Object^  sender, System::EventArgs^  e) {
		SysInfoPanel->Visible = false;
	}
	private: System::Void SysInfoButton_Click(System::Object^  sender, System::EventArgs^  e) {
		SysInfoPanel->Visible = true;
	}
	private: System::Void InfoDevList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//Developers list
		if (InfoDevList->SelectedIndex == 0) {
			InfoPhoneLabel->Text = "Phone: 054-3052882";
			InfoEmailLinkLabel->Text = "vitalne@ac.sce.ac.il";
		}
		else if (InfoDevList->SelectedIndex == 1) {
			InfoPhoneLabel->Text = "Phone: 050-2427470";
			InfoEmailLinkLabel->Text = "adirat@ac.sce.ac.il";
		}
		else if (InfoDevList->SelectedIndex == 2) {
			InfoPhoneLabel->Text = "Phone: 052-3546002";
			InfoEmailLinkLabel->Text = "maximpo@ac.sce.ac.il";
		}
		else if (InfoDevList->SelectedIndex == 3) {
			InfoPhoneLabel->Text = "Phone: 052-3144590";
			InfoEmailLinkLabel->Text = "doronk679@gmail.com";
		}
	}
	private: System::Void DeleteEventButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//Delete event
		GlobalClass::old_event_name = DescriptionTextBox->Text;
		if (chosen_event == "PersonalEvents.txt") {
			RemovePersonalTeamEvent("PersonalEvents.txt");
		}
		if (chosen_event == "TeamEvents.txt") {
			GlobalClass::team_name = gcnew String(getUserTeamName(currentUserID).c_str());
			delete_team_event("TeamEvents.txt");
		}
		if (chosen_event == "GlobalEvents.txt") {
			RemoveGlobalEvent();
		}
		RefreshDayEventsPanel();
	}
	private: System::Void EditEventButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//Edit event
		if (DescriptionTextBox->Text != "") {
			char hour[3];
			char minute[3];
			if (chosen_event == "PersonalEvents.txt") {
				add_personal_event::type = "edit personal";
				add_personal_event::eventTypeForEdit = "PersonalEvents.txt";
			}
			if (chosen_event == "TeamEvents.txt") {
				add_personal_event::currentUserID = currentUserID;
				add_personal_event::type = "edit team";
				add_personal_event::eventTypeForEdit = "TeamEvents.txt";
			}
			if (chosen_event == "GlobalEvents.txt") {
				add_personal_event::type = "edit global";
				add_personal_event::eventTypeForEdit = "GlobalEvents.txt";
			}
			GlobalClass::old_event_name = DescriptionTextBox->Text;
			GlobalClass::old_priority = PriorityFillLabel->Text;
			GlobalClass::old_eventType = TypeFillLabel->Text;
			int i = 0, index = 0;
			while (TimeFillLabel->Text[i] != ':') {
				hour[index++] = (char)TimeFillLabel->Text[i++];
			}
			hour[index] = '\0';
			GlobalClass::old_hour = gcnew String(hour);
			index = 0, i++;
			while (i < TimeFillLabel->Text->Length) {
				minute[index++] = (char)TimeFillLabel->Text[i++];
			}
			minute[index] = '\0';
			GlobalClass::old_minute = gcnew String(minute);
			add_personal_event::add_personal_event form;
			form.ShowDialog();
			this->Show();
			RefreshDayEventsPanel();
		}
	}
	private: System::Void SysResetButton_Click(System::Object^  sender, System::EventArgs^  e) {
		ResetScreen::ResetSCR form;
		form.ShowDialog();
		if (GlobalClass::resetActivation == true) {
			GlobalClass::resetActivation = false;
			this->Close();
		}
	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		TimeLabel->Text = gcnew String(currentTime().c_str());
	}
};
}

