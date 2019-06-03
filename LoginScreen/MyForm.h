#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include "LogSys.h"
#include "MainScreen.h"
#include "GlobalClass.h"
#include "LoginMSGSCR.h"
using namespace std;
namespace LoginScreen {
	void MScr();
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Globals;
	/// <summary>
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class LoginScreen : public System::Windows::Forms::Form
	{
	public:
		LoginScreen(void)
		{
			InitializeComponent();
			textBox2->PasswordChar = '*';
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoginScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::MonthCalendar^  monthCalendar1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->button1->Location = System::Drawing::Point(91, 254);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(154, 34);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Login!";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &LoginScreen::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(91, 202);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(154, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &LoginScreen::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(91, 228);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(154, 20);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &LoginScreen::textBox2_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(64, 205);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(21, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"ID:";
			this->label1->Click += gcnew System::EventHandler(this, &LoginScreen::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(29, 231);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Password:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(98, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"CALENDAR";
			this->label3->Click += gcnew System::EventHandler(this, &LoginScreen::label3_Click);
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->monthCalendar1->ForeColor = System::Drawing::SystemColors::InactiveCaption;
			this->monthCalendar1->Location = System::Drawing::Point(8, 31);
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->ShowWeekNumbers = true;
			this->monthCalendar1->TabIndex = 6;
			this->monthCalendar1->DateChanged += gcnew System::Windows::Forms::DateRangeEventHandler(this, &LoginScreen::monthCalendar1_DateChanged);
			// 
			// LoginScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(266, 303);
			this->Controls->Add(this->monthCalendar1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->Name = L"LoginScreen";
			this->Text = L"Calendar";
			this->Load += gcnew System::EventHandler(this, &LoginScreen::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	String ^ ID = textBox1->Text;
	String ^ PASS = textBox2->Text; 
	char id[10];
	char pass[10];
	int i;
	if (ID->Length != 0 && PASS->Length != 0) {
		for (i = 0; i < ID->Length; i++) id[i] = (char)ID[i];
		id[i] = '\0';
		for (i = 0; i < PASS->Length; i++) pass[i] = (char)PASS[i];
		pass[i] = '\0';
		int ret = LoginSys(id, pass);
		if (ret == 1) {
			GlobalClass::user_id = textBox1->Text;
			this->Hide();
			MainScreen::currentUserID = convertCharArrayToInt(id);
			MainScreen::currentUserRank = 1;
			MainScreen::teamName = getUserTeamName(convertCharArrayToInt(id));
			MScr();
			textBox1->Text = "";
			textBox2->Text = "";
			this->Show();
		}
		if (ret == 2) {
			GlobalClass::user_id = textBox1->Text;
			this->Hide();
			MainScreen::currentUserID = convertCharArrayToInt(id);
			MainScreen::currentUserRank = 2;
			MainScreen::teamName = getUserTeamName(convertCharArrayToInt(id));
			MScr();
			textBox1->Text = "";
			textBox2->Text = "";
			this->Show();
		}
		if (ret == 3) {
			GlobalClass::user_id = textBox1->Text;
			this->Hide();
			MainScreen::currentUserID = convertCharArrayToInt(id);
			MainScreen::currentUserRank = 3;
			MainScreen::teamName = getUserTeamName(convertCharArrayToInt(id));
			MScr();
			textBox1->Text = "";
			textBox2->Text = "";
			this->Show();
		}
		if (ret == 4) {
			LoginFailedScreen::warning = "Wrong password!";
			LoginFailedScreen::LoginMSGSCR form;
			form.ShowDialog();
			textBox2->Text = "";

		}
		if (ret == 5) {
			LoginFailedScreen::warning = "Wrong ID!";
			LoginFailedScreen::LoginMSGSCR form;
			form.ShowDialog();
			textBox1->Text = "";
			textBox2->Text = "";
		}
	}
	}
	private: System::Void monthCalendar1_DateChanged(System::Object^  sender, System::Windows::Forms::DateRangeEventArgs^  e) {
	}
};
	///MScr
	void MScr() {
		MainScreen::MainScreen form;
		form.ShowDialog();
		
	}
}
