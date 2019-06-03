#pragma once
#include "GlobalClass.h"
#include <fstream>
#include <iostream>
#include <string>
#include "additionalFunc.h"
namespace add_personal_event {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace Globals;

	int tempint;
	/// <summary>
	/// Summary for add_personal_event
	/// </summary>
	///static info
	string eventType, teamName;
	string type;
	string event_name, priority, EventMeetingTask, hour, minute, eventTypeForEdit;
	int currentUserID;
	public ref class add_personal_event : public System::Windows::Forms::Form
	{
	public:
		add_personal_event(void)
		{
			InitializeComponent();
			if (type == "edit personal" || type == "edit team" || type == "edit global") {
				event_name_textBox->Text = GlobalClass::old_event_name;
				priority_textBox->Text = GlobalClass::old_priority;
				eventTypeBox->Text = GlobalClass::old_eventType;
				hour_textBox->Text = GlobalClass::old_hour;
				minute_textBox->Text = GlobalClass::old_minute;
			}

			//
			//TODO: Add the constructor code here
			//
		}
		void edit_personal_event() {
			string temp2, day, month, year;
			char new_event_name[50], new_priority[5], new_hour[3], new_minute[3], new_type[6];
			int index = 0;
			fstream Pevent(eventTypeForEdit);
			fstream temp("temp.txt", ios::app);
			while (!Pevent.eof()) {
				getline(Pevent, temp2);
				if (Pevent.eof()) break;
				temp << temp2 << endl; //ID
				String^ tempS1 = gcnew String(temp2.c_str());
				String^ tempteam = gcnew String(getUserTeamName(currentUserID).c_str());
				if (tempS1 == GlobalClass::user_id || tempS1 == GlobalClass::team_name) {
					Pevent >> month;
					Pevent >> day;
					Pevent >> year;
					temp << month << " " << day << " " << year << endl; //Date to file
					String^ tempS2 = gcnew String(month.c_str());
					String^ tempS3 = gcnew String(day.c_str());
					String^ tempS4 = gcnew String(year.c_str());
					getline(Pevent, temp2);
					getline(Pevent, temp2);
					if (tempS2 == GlobalClass::month && tempS3 == GlobalClass::day && tempS4 == GlobalClass::year) {
						String^ tempS5 = gcnew String(temp2.c_str());
						if (tempS5 == GlobalClass::old_event_name) {
							for (int i = 0; i < GlobalClass::event_name->Length; i++) new_event_name[index++] = (char)GlobalClass::event_name[i];
							new_event_name[index] = '\0';
							index = 0;
							temp << new_event_name << endl; //New event name
							getline(Pevent, temp2);
							for (int i = 0; i < GlobalClass::priority->Length; i++) new_priority[index++] = (char)GlobalClass::priority[i];
							new_priority[index] = '\0';
							index = 0;
							temp << new_priority << endl; //New priority
							getline(Pevent, temp2);
							for (int i = 0; i < GlobalClass::hour->Length; i++) new_hour[index++] = (char)GlobalClass::hour[i];
							new_hour[index] = '\0';
							index = 0;
							temp << new_hour << ':';
							for (int i = 0; i < GlobalClass::minute->Length; i++) new_minute[index++] = (char)GlobalClass::minute[i];
							new_minute[index] = '\0';
							index = 0;
							temp << new_minute << endl;
							getline(Pevent, temp2);
							for (int i = 0; i < GlobalClass::eventType->Length; i++) new_type[index++] = (char)GlobalClass::eventType[i];
							new_type[index] = '\0';
							temp << new_type;
							if (!Pevent.eof()) {
								temp << endl;
							}
						}
						else {
							if (Pevent.eof()) break;
							temp << temp2 << endl;
							getline(Pevent, temp2);
							temp << temp2 << endl;
							getline(Pevent, temp2);
							temp << temp2 << endl;
							getline(Pevent, temp2);
							temp << temp2;
							if (!Pevent.eof()) {
								temp << endl;
							}
						}
					}
					else {
						if (Pevent.eof()) break;
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2;
						if (!Pevent.eof()) {
							temp << endl;
						}
					}
				}
				else {
					if (Pevent.eof()) break;
					Pevent >> month;
					Pevent >> day;
					Pevent >> year;
					temp << month << " " << day << " " << year << endl;
					getline(Pevent, temp2);
					getline(Pevent, temp2);
					temp << temp2 << endl;
					getline(Pevent, temp2);
					temp << temp2 << endl;
					getline(Pevent, temp2);
					temp << temp2 << endl;
					getline(Pevent, temp2);
					temp << temp2;
					if (!Pevent.eof()) {
						temp << endl;
					}
				}
			}
			type = "";
			Pevent.close();
			Pevent.open(eventTypeForEdit, ios::out | ios::trunc);
			Pevent.close();
			temp.close();
			ifstream infile("temp.txt");
			fstream outfile(eventTypeForEdit, ios::app);
			string content;
			while (!infile.eof()) {
				getline(infile, content);
				if (!content.size()) break;
				outfile << content << endl;
			}
			infile.close();
			outfile.close();
			Pevent.open("temp.txt", ios::out | ios::trunc);
			Pevent.close();
		}
		void edit_global_event() {
			string temp2, day, month, year;
			char new_event_name[50], new_priority[5], new_hour[3], new_minute[3], new_type[6];
			int index = 0;
			fstream Pevent(eventTypeForEdit);
			fstream temp("temp.txt", ios::app);
			while (!Pevent.eof()) {
				if (Pevent.eof()) break;
				Pevent >> month;
				Pevent >> day;
				Pevent >> year;
				temp << month << " " << day << " " << year << endl; //Date to file
				String^ tempS2 = gcnew String(month.c_str());
				String^ tempS3 = gcnew String(day.c_str());
				String^ tempS4 = gcnew String(year.c_str());
				getline(Pevent, temp2);
				getline(Pevent, temp2); //event name
				if (tempS2 == GlobalClass::month && tempS3 == GlobalClass::day && tempS4 == GlobalClass::year) {
					String^ tempS5 = gcnew String(temp2.c_str());
					if (tempS5 == GlobalClass::old_event_name) {
						for (int i = 0; i < GlobalClass::event_name->Length; i++) new_event_name[index++] = (char)GlobalClass::event_name[i];
						new_event_name[index] = '\0';
						index = 0;
						temp << new_event_name << endl; //New event name
						getline(Pevent, temp2);
						for (int i = 0; i < GlobalClass::priority->Length; i++) new_priority[index++] = (char)GlobalClass::priority[i];
						new_priority[index] = '\0';
						index = 0;
						temp << new_priority << endl; //New priority
						getline(Pevent, temp2);
						for (int i = 0; i < GlobalClass::hour->Length; i++) new_hour[index++] = (char)GlobalClass::hour[i];
						new_hour[index] = '\0';
						index = 0;
						temp << new_hour << ':';
						for (int i = 0; i < GlobalClass::minute->Length; i++) new_minute[index++] = (char)GlobalClass::minute[i];
						new_minute[index] = '\0';
						index = 0;
						temp << new_minute << endl;
						getline(Pevent, temp2);
						for (int i = 0; i < GlobalClass::eventType->Length; i++) new_type[index++] = (char)GlobalClass::eventType[i];
						new_type[index] = '\0';
						temp << new_type;
						if (!Pevent.eof()) {
							temp << endl;
						}
					}
					else {
						if (Pevent.eof()) break;
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2;
						if (!Pevent.eof()) {
							temp << endl;
						}
					}
				}
				else {
					if (Pevent.eof()) break;
					temp << temp2 << endl;//event name to file
					getline(Pevent, temp2);
					temp << temp2 << endl; //priority to file
					getline(Pevent, temp2);
					temp << temp2 << endl; // time to file
					getline(Pevent, temp2);
					temp << temp2; //type to file
					if (!Pevent.eof()) {
						temp << endl;
					}
				}
			}
			type = "";
			Pevent.close();
			Pevent.open(eventTypeForEdit, ios::out | ios::trunc);
			Pevent.close();
			temp.close();
			ifstream infile("temp.txt");
			fstream outfile(eventTypeForEdit, ios::app);
			string content;
			while (!infile.eof()) {
				getline(infile, content);
				if (!content.size()) break;
				outfile << content << endl;
			}
			infile.close();
			outfile.close();
			Pevent.open("temp.txt", ios::out | ios::trunc);
			Pevent.close();
		}
		void edit_team_event() {
			string temp2, day, month, year;
			char new_event_name[50], new_priority[5], new_hour[3], new_minute[3], new_type[6];
			int index = 0;
			fstream Pevent(eventTypeForEdit);
			fstream temp("temp.txt", ios::app);
			while (!Pevent.eof()) {
				getline(Pevent, temp2); //Team name
				if (Pevent.eof()) break;
				temp << temp2 << endl; //Team name to file
				String^ tempS1 = gcnew String(temp2.c_str());
				String^ teamTemp = gcnew String(getUserTeamName(currentUserID).c_str());
				if (tempS1 == teamTemp) {
					Pevent >> month;
					Pevent >> day;
					Pevent >> year;
					temp << month << " " << day << " " << year << endl; //Date to file
					String^ tempS2 = gcnew String(month.c_str());
					String^ tempS3 = gcnew String(day.c_str());
					String^ tempS4 = gcnew String(year.c_str());
					getline(Pevent, temp2);
					getline(Pevent, temp2);
					if (tempS2 == GlobalClass::month && tempS3 == GlobalClass::day && tempS4 == GlobalClass::year) {
						String^ tempS5 = gcnew String(temp2.c_str());
						if (tempS5 == GlobalClass::old_event_name) {
							for (int i = 0; i < GlobalClass::event_name->Length; i++) new_event_name[index++] = (char)GlobalClass::event_name[i];
							new_event_name[index] = '\0';
							index = 0;
							temp << new_event_name << endl; //New event name
							getline(Pevent, temp2);
							for (int i = 0; i < GlobalClass::priority->Length; i++) new_priority[index++] = (char)GlobalClass::priority[i];
							new_priority[index] = '\0';
							index = 0;
							temp << new_priority << endl; //New priority
							getline(Pevent, temp2);
							for (int i = 0; i < GlobalClass::hour->Length; i++) new_hour[index++] = (char)GlobalClass::hour[i];
							new_hour[index] = '\0';
							index = 0;
							temp << new_hour << ':';
							for (int i = 0; i < GlobalClass::minute->Length; i++) new_minute[index++] = (char)GlobalClass::minute[i];
							new_minute[index] = '\0';
							index = 0;
							temp << new_minute << endl;
							getline(Pevent, temp2);
							for (int i = 0; i < GlobalClass::eventType->Length; i++) new_type[index++] = (char)GlobalClass::eventType[i];
							new_type[index] = '\0';
							temp << new_type;
							if (!Pevent.eof()) {
								temp << endl;
							}
						}
						else {
							if (Pevent.eof()) break;
							temp << temp2 << endl;
							getline(Pevent, temp2);
							temp << temp2 << endl;
							getline(Pevent, temp2);
							temp << temp2 << endl;
							getline(Pevent, temp2);
							temp << temp2;
							if (!Pevent.eof()) {
								temp << endl;
							}
						}
					}
					else {
						if (Pevent.eof()) break;
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2 << endl;
						getline(Pevent, temp2);
						temp << temp2;
						if (!Pevent.eof()) {
							temp << endl;
						}
					}
				}
				else {
					if (Pevent.eof()) break;
					Pevent >> month;
					Pevent >> day;
					Pevent >> year;
					temp << month << " " << day << " " << year << endl;
					getline(Pevent, temp2);
					getline(Pevent, temp2);
					temp << temp2 << endl;
					getline(Pevent, temp2);
					temp << temp2 << endl;
					getline(Pevent, temp2);
					temp << temp2 << endl;
					getline(Pevent, temp2);
					temp << temp2;
					if (!Pevent.eof()) {
						temp << endl;
					}
				}
			}
			type = "";
			Pevent.close();
			Pevent.open(eventTypeForEdit, ios::out | ios::trunc);
			Pevent.close();
			temp.close();
			ifstream infile("temp.txt");
			fstream outfile(eventTypeForEdit, ios::app);
			string content;
			while (!infile.eof()) {
				getline(infile, content);
				if (!content.size()) break;
				outfile << content << endl;
			}
			infile.close();
			outfile.close();
			Pevent.open("temp.txt", ios::out | ios::trunc);
			Pevent.close();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~add_personal_event()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  event_name_label;


	private: System::Windows::Forms::TextBox^  event_name_textBox;
	private: System::Windows::Forms::Label^  priority_label;





	private: System::Windows::Forms::TextBox^  hour_textBox;

	private: System::Windows::Forms::Label^  hour_label;

	private: System::Windows::Forms::TextBox^  minute_textBox;
	private: System::Windows::Forms::Button^  add_event_button;
	private: System::Windows::Forms::Button^  clear_button;


	private: System::Windows::Forms::Label^  add_event_update;
	private: System::Windows::Forms::Label^  minute_error;
	private: System::Windows::Forms::Label^  hour_error;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  EventTypeLabel;
	private: System::Windows::Forms::ComboBox^  eventTypeBox;


	private: System::Windows::Forms::ComboBox^  priority_textBox;
	private: System::Windows::Forms::Button^  button1;

	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
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
			this->event_name_label = (gcnew System::Windows::Forms::Label());
			this->event_name_textBox = (gcnew System::Windows::Forms::TextBox());
			this->priority_label = (gcnew System::Windows::Forms::Label());
			this->hour_textBox = (gcnew System::Windows::Forms::TextBox());
			this->hour_label = (gcnew System::Windows::Forms::Label());
			this->minute_textBox = (gcnew System::Windows::Forms::TextBox());
			this->add_event_button = (gcnew System::Windows::Forms::Button());
			this->clear_button = (gcnew System::Windows::Forms::Button());
			this->add_event_update = (gcnew System::Windows::Forms::Label());
			this->minute_error = (gcnew System::Windows::Forms::Label());
			this->hour_error = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->EventTypeLabel = (gcnew System::Windows::Forms::Label());
			this->eventTypeBox = (gcnew System::Windows::Forms::ComboBox());
			this->priority_textBox = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// event_name_label
			// 
			this->event_name_label->AutoSize = true;
			this->event_name_label->BackColor = System::Drawing::Color::Transparent;
			this->event_name_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->event_name_label->Location = System::Drawing::Point(59, 95);
			this->event_name_label->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->event_name_label->Name = L"event_name_label";
			this->event_name_label->Size = System::Drawing::Size(78, 15);
			this->event_name_label->TabIndex = 0;
			this->event_name_label->Text = L"Event name: ";
			// 
			// event_name_textBox
			// 
			this->event_name_textBox->Location = System::Drawing::Point(141, 94);
			this->event_name_textBox->Margin = System::Windows::Forms::Padding(2);
			this->event_name_textBox->Name = L"event_name_textBox";
			this->event_name_textBox->Size = System::Drawing::Size(144, 20);
			this->event_name_textBox->TabIndex = 1;
			this->event_name_textBox->TextChanged += gcnew System::EventHandler(this, &add_personal_event::event_name_textBox_TextChanged);
			// 
			// priority_label
			// 
			this->priority_label->AutoSize = true;
			this->priority_label->BackColor = System::Drawing::Color::Transparent;
			this->priority_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->priority_label->Location = System::Drawing::Point(62, 139);
			this->priority_label->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->priority_label->Name = L"priority_label";
			this->priority_label->Size = System::Drawing::Size(50, 15);
			this->priority_label->TabIndex = 2;
			this->priority_label->Text = L"Priority: ";
			// 
			// hour_textBox
			// 
			this->hour_textBox->Location = System::Drawing::Point(141, 180);
			this->hour_textBox->Margin = System::Windows::Forms::Padding(2);
			this->hour_textBox->Name = L"hour_textBox";
			this->hour_textBox->Size = System::Drawing::Size(64, 20);
			this->hour_textBox->TabIndex = 4;
			this->hour_textBox->TextChanged += gcnew System::EventHandler(this, &add_personal_event::hour_textBox_TextChanged);
			// 
			// hour_label
			// 
			this->hour_label->AutoSize = true;
			this->hour_label->BackColor = System::Drawing::Color::Transparent;
			this->hour_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hour_label->Location = System::Drawing::Point(59, 181);
			this->hour_label->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->hour_label->Name = L"hour_label";
			this->hour_label->Size = System::Drawing::Size(41, 15);
			this->hour_label->TabIndex = 5;
			this->hour_label->Text = L"Time: ";
			// 
			// minute_textBox
			// 
			this->minute_textBox->Location = System::Drawing::Point(222, 180);
			this->minute_textBox->Margin = System::Windows::Forms::Padding(2);
			this->minute_textBox->Name = L"minute_textBox";
			this->minute_textBox->Size = System::Drawing::Size(63, 20);
			this->minute_textBox->TabIndex = 7;
			this->minute_textBox->TextChanged += gcnew System::EventHandler(this, &add_personal_event::minute_textBox_TextChanged);
			// 
			// add_event_button
			// 
			this->add_event_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->add_event_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->add_event_button->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->add_event_button->Location = System::Drawing::Point(244, 290);
			this->add_event_button->Margin = System::Windows::Forms::Padding(2);
			this->add_event_button->Name = L"add_event_button";
			this->add_event_button->Size = System::Drawing::Size(70, 28);
			this->add_event_button->TabIndex = 8;
			this->add_event_button->Text = L"Add";
			this->add_event_button->UseVisualStyleBackColor = false;
			this->add_event_button->Click += gcnew System::EventHandler(this, &add_personal_event::add_event_bottom_Click);
			// 
			// clear_button
			// 
			this->clear_button->Location = System::Drawing::Point(317, 290);
			this->clear_button->Margin = System::Windows::Forms::Padding(2);
			this->clear_button->Name = L"clear_button";
			this->clear_button->Size = System::Drawing::Size(76, 28);
			this->clear_button->TabIndex = 9;
			this->clear_button->Text = L"Clear";
			this->clear_button->UseVisualStyleBackColor = true;
			this->clear_button->Click += gcnew System::EventHandler(this, &add_personal_event::clear_bottom_Click);
			// 
			// add_event_update
			// 
			this->add_event_update->AutoSize = true;
			this->add_event_update->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->add_event_update->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->add_event_update->ForeColor = System::Drawing::Color::Red;
			this->add_event_update->Location = System::Drawing::Point(20, 298);
			this->add_event_update->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->add_event_update->Name = L"add_event_update";
			this->add_event_update->Size = System::Drawing::Size(0, 12);
			this->add_event_update->TabIndex = 10;
			// 
			// minute_error
			// 
			this->minute_error->AutoSize = true;
			this->minute_error->ForeColor = System::Drawing::Color::Red;
			this->minute_error->Location = System::Drawing::Point(241, 199);
			this->minute_error->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->minute_error->Name = L"minute_error";
			this->minute_error->Size = System::Drawing::Size(0, 13);
			this->minute_error->TabIndex = 11;
			// 
			// hour_error
			// 
			this->hour_error->AutoSize = true;
			this->hour_error->ForeColor = System::Drawing::Color::Red;
			this->hour_error->Location = System::Drawing::Point(163, 199);
			this->hour_error->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->hour_error->Name = L"hour_error";
			this->hour_error->Size = System::Drawing::Size(0, 13);
			this->hour_error->TabIndex = 12;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Yi Baiti", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(17, 27);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(376, 33);
			this->label1->TabIndex = 14;
			this->label1->Text = L"New Event/Task/Meeting/Other";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(207, 183);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(10, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L":";
			// 
			// EventTypeLabel
			// 
			this->EventTypeLabel->AutoSize = true;
			this->EventTypeLabel->Location = System::Drawing::Point(62, 226);
			this->EventTypeLabel->Name = L"EventTypeLabel";
			this->EventTypeLabel->Size = System::Drawing::Size(65, 13);
			this->EventTypeLabel->TabIndex = 16;
			this->EventTypeLabel->Text = L"Event Type:";
			// 
			// eventTypeBox
			// 
			this->eventTypeBox->FormattingEnabled = true;
			this->eventTypeBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Event", L"Task", L"Meeting", L"Other" });
			this->eventTypeBox->Location = System::Drawing::Point(141, 226);
			this->eventTypeBox->Name = L"eventTypeBox";
			this->eventTypeBox->Size = System::Drawing::Size(144, 21);
			this->eventTypeBox->TabIndex = 17;
			this->eventTypeBox->SelectedIndexChanged += gcnew System::EventHandler(this, &add_personal_event::comboBox1_SelectedIndexChanged);
			// 
			// priority_textBox
			// 
			this->priority_textBox->FormattingEnabled = true;
			this->priority_textBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"High", L"Medium", L"Low" });
			this->priority_textBox->Location = System::Drawing::Point(141, 135);
			this->priority_textBox->Name = L"priority_textBox";
			this->priority_textBox->Size = System::Drawing::Size(144, 21);
			this->priority_textBox->TabIndex = 19;
			this->priority_textBox->SelectedIndexChanged += gcnew System::EventHandler(this, &add_personal_event::priority_textBox_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(386, 1);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(23, 23);
			this->button1->TabIndex = 20;
			this->button1->Text = L"X";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &add_personal_event::button1_Click);
			// 
			// add_personal_event
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(411, 333);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->priority_textBox);
			this->Controls->Add(this->eventTypeBox);
			this->Controls->Add(this->EventTypeLabel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->hour_error);
			this->Controls->Add(this->minute_error);
			this->Controls->Add(this->add_event_update);
			this->Controls->Add(this->clear_button);
			this->Controls->Add(this->add_event_button);
			this->Controls->Add(this->minute_textBox);
			this->Controls->Add(this->hour_label);
			this->Controls->Add(this->hour_textBox);
			this->Controls->Add(this->priority_label);
			this->Controls->Add(this->event_name_textBox);
			this->Controls->Add(this->event_name_label);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"add_personal_event";
			this->Text = L"add_personal_event";
			this->Load += gcnew System::EventHandler(this, &add_personal_event::add_personal_event_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void event_name_textBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		add_event_update->Text = "";
		if (event_name_textBox->Text != "") GlobalClass::event_name = event_name_textBox->Text;
		if (event_name_textBox->Text == "") GlobalClass::event_name = nullptr;
	}

	private: System::Void hour_textBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		add_event_update->Text = "";
		if (hour_textBox->Text != "") {
			int hour = 0, next_digit = 1;
			for (int i = hour_textBox->Text->Length - 1; i >= 0; i--) {
				hour = hour + ((hour_textBox->Text[i] - 48) * next_digit);
				next_digit *= 10;
			}
			if (hour >= 0 && hour < 24) {
				GlobalClass::hour = hour_textBox->Text;
				hour_error->Text = "";
			}
			else {
				GlobalClass::hour = nullptr;
				hour_error->Text = "*Error";
			}
		}
		else {
			GlobalClass::hour = nullptr;
			hour_error->Text = "";
		}
	}

	private: System::Void minute_textBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		add_event_update->Text = "";
		if (minute_textBox->Text != "") {
			int minute = 0, next_digit = 1;
			for (int i = minute_textBox->Text->Length - 1; i >= 0; i--) {
				minute = minute + ((minute_textBox->Text[i] - 48) * next_digit);
				next_digit *= 10;
			}
			if (minute >= 0 && minute < 60) {
				GlobalClass::minute = minute_textBox->Text;
				minute_error->Text = "";
			}
			else {
				GlobalClass::minute = nullptr;
				minute_error->Text = "*Error";
			}
		}
		else {
			GlobalClass::minute = nullptr;
			minute_error->Text = "";
		}
	}

	private: System::Void clear_bottom_Click(System::Object^  sender, System::EventArgs^  e) {
		GlobalClass::event_name = nullptr;
		event_name_textBox->Text = "";
		GlobalClass::priority = nullptr;
		priority_textBox->Text = "";
		GlobalClass::hour = nullptr;
		hour_textBox->Text = "";
		GlobalClass::minute = nullptr;
		minute_textBox->Text = "";
		add_event_update->Text = "";
		GlobalClass::eventType = nullptr;
		eventTypeBox->Text = "";
		label1->Text = "New Event/Task/Meeting/Other";
	}

	private: System::Void add_event_bottom_Click(System::Object^  sender, System::EventArgs^  e) {
		if (type == "edit personal") {
			edit_personal_event();
			clear_bottom_Click(sender, e);
			this->Hide();
		}
		else if (type == "edit global") {
			edit_global_event();
			clear_bottom_Click(sender, e);
			this->Hide();
		}
		else if (type == "edit team") {
			edit_team_event();
			clear_bottom_Click(sender, e);
			this->Hide();
		}
		else {
			fstream myfile(eventType, ios::app);
			char id[10];
			char day[3];
			char month[10];
			char year[5];
			char event_name[15];
			char priority[3];
			char hour[3];
			char minute[3];
			char type[6];
			int index = 0;
			add_event_update->Text = "";
			if (GlobalClass::event_name != nullptr && GlobalClass::priority != nullptr && GlobalClass::hour != nullptr && GlobalClass::minute != nullptr && GlobalClass::eventType != nullptr) {
				if (teamName == "") {
					for (int i = 0; i < GlobalClass::user_id->Length; i++) {
						id[index++] = (char)GlobalClass::user_id[i];
					}
					id[index] = '\0';
					index = 0;
					myfile << id << endl;
				}
				else if (teamName != "" && teamName != "Global") {
					for (int i = 0; i < (int)teamName.length(); i++) {
						id[index++] = teamName[i];
					}
					id[index] = '\0';
					index = 0;
					myfile << id << endl;
				}
				for (int i = 0; i < GlobalClass::month->Length; i++) {
					month[index++] = (char)GlobalClass::month[i];
				}
				month[index] = '\0';
				index = 0;
				myfile << month << " ";
				for (int i = 0; i < GlobalClass::day->Length; i++) {
					day[index++] = (char)GlobalClass::day[i];
				}
				day[index] = '\0';
				index = 0;
				myfile << day << " ";
				for (int i = 0; i < GlobalClass::year->Length; i++) {
					year[index++] = (char)GlobalClass::year[i];
				}
				year[index] = '\0';
				index = 0;
				myfile << year << endl;
				for (int i = 0; i < GlobalClass::event_name->Length; i++) {
					event_name[index++] = (char)GlobalClass::event_name[i];
				}
				event_name[index] = '\0';
				index = 0;
				myfile << event_name << endl;
				for (int i = 0; i < GlobalClass::priority->Length; i++) {
					priority[index++] = (char)GlobalClass::priority[i];
				}
				priority[index] = '\0';
				index = 0;
				myfile << priority << endl;
				for (int i = 0; i < GlobalClass::hour->Length; i++) {
					hour[index++] = (char)GlobalClass::hour[i];
				}
				hour[index] = '\0';
				index = 0;
				myfile << hour << ":";
				for (int i = 0; i < GlobalClass::minute->Length; i++) {
					minute[index++] = (char)GlobalClass::minute[i];
				}
				minute[index] = '\0';
				index = 0;
				myfile << minute << endl;
				for (int i = 0; i < eventTypeBox->Text->Length; i++) {
					type[index++] = (char)eventTypeBox->Text[i];
				}
				type[index] = '\0';
				myfile << type << endl;
				clear_bottom_Click(sender, e);
				this->Hide();
			}
			else {
				if (GlobalClass::event_name == nullptr || GlobalClass::priority == nullptr || GlobalClass::hour == nullptr || GlobalClass::minute == nullptr || GlobalClass::eventType == nullptr) {
					if (hour_error->Text != "" || minute_error->Text != "") {
						add_event_update->Text = "*Fill All The Information and Fix The Errors";
					}
					else add_event_update->Text = "*Fill All The Information";
				}
				else add_event_update->Text = "*Fix The Errors";
			}
			myfile.close();
		}
	}

	private: System::Void add_personal_event_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (eventTypeBox->Text == "Event") {
			label1->Text = "New Event";
		}
		else if (eventTypeBox->Text == "Task") {
			label1->Text = "New Task";
		}
		else if (eventTypeBox->Text == "Meeting") {
			label1->Text = "New Meeting";
		}
		else {
			label1->Text = "New Event/Task/Meeting/Other";
		}
		GlobalClass::eventType = eventTypeBox->Text;
	}

	private: System::Void priority_textBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		GlobalClass::priority = priority_textBox->Text;
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		GlobalClass::event_name = nullptr;
		event_name_textBox->Text = "";
		GlobalClass::priority = nullptr;
		priority_textBox->Text = "";
		GlobalClass::hour = nullptr;
		hour_textBox->Text = "";
		GlobalClass::minute = nullptr;
		eventTypeBox->Text = "";
		GlobalClass::eventType = nullptr;
		this->Close();
	}
	};
}


