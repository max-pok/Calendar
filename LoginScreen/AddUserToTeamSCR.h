#pragma once
#include <fstream>
#include <string>
#include "EditUserForManger.h"
#include "additionalFunc.h"
namespace AddUserToTeamScreenn {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AddUserToTeamSCR
	/// </summary>
	string currentTeamName;
	public ref class AddUserToTeamSCR : public System::Windows::Forms::Form
	{
	public:
		AddUserToTeamSCR(void)
		{
			InitializeComponent();
			refreshUserWithoutTeamList();
			//
			//TODO: Add the constructor code here
			//
		}
		void refreshUserWithoutTeamList() {
			fstream base;
			string IDString, temp;
			int IDint;
			base.open("base.txt");
			UsersWithoutTeamList->Items->Clear();
			while (!base.eof()) {
				getline(base, IDString);
				IDint = convertStringToInt(IDString);
				if ("None" == getUserTeamName(IDint)) UsersWithoutTeamList->Items->Add(gcnew String(IDString.c_str()));
				getline(base, temp);
			}
			if (UsersWithoutTeamList->SelectedItems->Count > 0) UsersWithoutTeamList->SelectedIndex = 0;
			base.close();
		}
		string converSpecialStringToString(String ^ oldOne) {
			string newOne = "";
			for (int i = 0; i < oldOne->Length; i++) newOne = newOne + (char)oldOne[i];
			return newOne;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AddUserToTeamSCR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::TextBox^  UserSurnameTextBox;
	private: System::Windows::Forms::TextBox^  UserNameTextBox;
	private: System::Windows::Forms::TextBox^  UserIDTextBox;
	private: System::Windows::Forms::Label^  UserNameLabel;
	private: System::Windows::Forms::Label^  UserIDLabel;
	private: System::Windows::Forms::Label^  UserDetailsLabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ListBox^  UsersWithoutTeamList;

	private:
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
			this->UserSurnameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UserNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UserIDTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UserNameLabel = (gcnew System::Windows::Forms::Label());
			this->UserIDLabel = (gcnew System::Windows::Forms::Label());
			this->UserDetailsLabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->UsersWithoutTeamList = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->button1->Location = System::Drawing::Point(201, 195);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(68, 40);
			this->button1->TabIndex = 38;
			this->button1->Text = L"Add";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AddUserToTeamSCR::button1_Click);
			// 
			// UserSurnameTextBox
			// 
			this->UserSurnameTextBox->Location = System::Drawing::Point(56, 232);
			this->UserSurnameTextBox->Name = L"UserSurnameTextBox";
			this->UserSurnameTextBox->ReadOnly = true;
			this->UserSurnameTextBox->Size = System::Drawing::Size(126, 20);
			this->UserSurnameTextBox->TabIndex = 37;
			// 
			// UserNameTextBox
			// 
			this->UserNameTextBox->Location = System::Drawing::Point(56, 206);
			this->UserNameTextBox->Name = L"UserNameTextBox";
			this->UserNameTextBox->ReadOnly = true;
			this->UserNameTextBox->Size = System::Drawing::Size(126, 20);
			this->UserNameTextBox->TabIndex = 36;
			// 
			// UserIDTextBox
			// 
			this->UserIDTextBox->Location = System::Drawing::Point(43, 180);
			this->UserIDTextBox->Name = L"UserIDTextBox";
			this->UserIDTextBox->ReadOnly = true;
			this->UserIDTextBox->Size = System::Drawing::Size(139, 20);
			this->UserIDTextBox->TabIndex = 35;
			// 
			// UserNameLabel
			// 
			this->UserNameLabel->AutoSize = true;
			this->UserNameLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->UserNameLabel->Location = System::Drawing::Point(12, 209);
			this->UserNameLabel->Name = L"UserNameLabel";
			this->UserNameLabel->Size = System::Drawing::Size(38, 13);
			this->UserNameLabel->TabIndex = 34;
			this->UserNameLabel->Text = L"Name:";
			// 
			// UserIDLabel
			// 
			this->UserIDLabel->AutoSize = true;
			this->UserIDLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->UserIDLabel->Location = System::Drawing::Point(12, 183);
			this->UserIDLabel->Name = L"UserIDLabel";
			this->UserIDLabel->Size = System::Drawing::Size(21, 13);
			this->UserIDLabel->TabIndex = 33;
			this->UserIDLabel->Text = L"ID:";
			// 
			// UserDetailsLabel
			// 
			this->UserDetailsLabel->AutoSize = true;
			this->UserDetailsLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->UserDetailsLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->UserDetailsLabel->Location = System::Drawing::Point(12, 164);
			this->UserDetailsLabel->Name = L"UserDetailsLabel";
			this->UserDetailsLabel->Size = System::Drawing::Size(78, 13);
			this->UserDetailsLabel->TabIndex = 32;
			this->UserDetailsLabel->Text = L"User details:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline))));
			this->label1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(146, 15);
			this->label1->TabIndex = 31;
			this->label1->Text = L"Users without a team:";
			// 
			// UsersWithoutTeamList
			// 
			this->UsersWithoutTeamList->FormattingEnabled = true;
			this->UsersWithoutTeamList->Location = System::Drawing::Point(15, 27);
			this->UsersWithoutTeamList->Name = L"UsersWithoutTeamList";
			this->UsersWithoutTeamList->ScrollAlwaysVisible = true;
			this->UsersWithoutTeamList->Size = System::Drawing::Size(167, 134);
			this->UsersWithoutTeamList->TabIndex = 30;
			this->UsersWithoutTeamList->SelectedIndexChanged += gcnew System::EventHandler(this, &AddUserToTeamSCR::UsersWithoutTeamList_SelectedIndexChanged);
			// 
			// AddUserToTeamSCR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->UserSurnameTextBox);
			this->Controls->Add(this->UserNameTextBox);
			this->Controls->Add(this->UserIDTextBox);
			this->Controls->Add(this->UserNameLabel);
			this->Controls->Add(this->UserIDLabel);
			this->Controls->Add(this->UserDetailsLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->UsersWithoutTeamList);
			this->MaximizeBox = false;
			this->Name = L"AddUserToTeamSCR";
			this->Text = L"Add user to your team";
			this->Load += gcnew System::EventHandler(this, &AddUserToTeamSCR::AddUserToTeamSCR_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AddUserToTeamSCR_Load(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void UserIDLabel_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void UserNameTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void UserSurnameTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void UserIDTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void UserNameLabel_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void UsersWithoutTeamList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	fstream personalDetails;
	string theID = converSpecialStringToString(UsersWithoutTeamList->SelectedItem->ToString()), temp1, temp2 = "";
	personalDetails.open(theID + ".txt");
	UserIDTextBox->Text = UsersWithoutTeamList->SelectedItem->ToString();
	for (int i = 0; i < 3; i++) getline(personalDetails, temp1);
	for (int i = 11; i < (int)temp1.length(); i++) temp2 = temp2 + temp1[i];
	UserNameTextBox->Text = gcnew String(temp2.c_str());
	getline(personalDetails, temp1);
	temp2 = "";
	for (int i = 10; i < (int)temp1.length(); i++) temp2 = temp2 + temp1[i];
	UserSurnameTextBox->Text = gcnew String(temp2.c_str());
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	string temp = converSpecialStringToString(UsersWithoutTeamList->SelectedItem->ToString());
	ChangeGroup(temp, currentTeamName);
	this->Close();
}
};
}
