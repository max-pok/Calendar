#pragma once
#include "additionalFunc.h"
#include "EditUserForManger.h"
namespace EditUserScreen {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EditUserSCR
	/// </summary>
	string editedUserID, editedUserFirstName, editedUserLastName, editedUserTeam, editedUserRank;
	int tempID;
	public ref class EditUserSCR : public System::Windows::Forms::Form
	{
	public:
		EditUserSCR(void)
		{
			InitializeComponent();
			UserIDTextBox->Text = gcnew String(editedUserID.c_str());
			UserFirstNameTextBox->Text = gcnew String(editedUserFirstName.c_str());
			UserLastNameTextBox->Text = gcnew String(editedUserLastName.c_str());
			UserRankComboBox->SelectedIndex = tempID - 1;
			UserTeamTextBox->Text = gcnew String(editedUserTeam.c_str());
			//
			//TODO: Add the constructor code here
			//
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
		~EditUserSCR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  UserRankComboBox;
	protected:
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  UserTeamTextBox;
	private: System::Windows::Forms::TextBox^  UserLastNameTextBox;
	private: System::Windows::Forms::TextBox^  UserFirstNameTextBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  UserIDTextBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  SaveChangesButton;

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
			this->UserRankComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->UserTeamTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UserLastNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UserFirstNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->UserIDTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SaveChangesButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// UserRankComboBox
			// 
			this->UserRankComboBox->FormattingEnabled = true;
			this->UserRankComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"1 - Regular", L"2 - Team Leader", L"3 - Admin" });
			this->UserRankComboBox->Location = System::Drawing::Point(81, 91);
			this->UserRankComboBox->Name = L"UserRankComboBox";
			this->UserRankComboBox->Size = System::Drawing::Size(111, 21);
			this->UserRankComboBox->TabIndex = 22;
			this->UserRankComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &EditUserSCR::comboBox1_SelectedIndexChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label5->Location = System::Drawing::Point(15, 121);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(37, 13);
			this->label5->TabIndex = 21;
			this->label5->Text = L"Team:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label4->Location = System::Drawing::Point(15, 95);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(36, 13);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Rank:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label3->Location = System::Drawing::Point(15, 69);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 13);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Last Name";
			// 
			// UserTeamTextBox
			// 
			this->UserTeamTextBox->Location = System::Drawing::Point(81, 118);
			this->UserTeamTextBox->Name = L"UserTeamTextBox";
			this->UserTeamTextBox->Size = System::Drawing::Size(111, 20);
			this->UserTeamTextBox->TabIndex = 18;
			// 
			// UserLastNameTextBox
			// 
			this->UserLastNameTextBox->Location = System::Drawing::Point(81, 66);
			this->UserLastNameTextBox->Name = L"UserLastNameTextBox";
			this->UserLastNameTextBox->Size = System::Drawing::Size(111, 20);
			this->UserLastNameTextBox->TabIndex = 17;
			// 
			// UserFirstNameTextBox
			// 
			this->UserFirstNameTextBox->Location = System::Drawing::Point(81, 40);
			this->UserFirstNameTextBox->Name = L"UserFirstNameTextBox";
			this->UserFirstNameTextBox->Size = System::Drawing::Size(111, 20);
			this->UserFirstNameTextBox->TabIndex = 16;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label2->Location = System::Drawing::Point(15, 43);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L"First Name:";
			// 
			// UserIDTextBox
			// 
			this->UserIDTextBox->Location = System::Drawing::Point(81, 14);
			this->UserIDTextBox->Name = L"UserIDTextBox";
			this->UserIDTextBox->ReadOnly = true;
			this->UserIDTextBox->Size = System::Drawing::Size(111, 20);
			this->UserIDTextBox->TabIndex = 14;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label1->Location = System::Drawing::Point(15, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(21, 13);
			this->label1->TabIndex = 13;
			this->label1->Text = L"ID:";
			// 
			// SaveChangesButton
			// 
			this->SaveChangesButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->SaveChangesButton->Location = System::Drawing::Point(106, 144);
			this->SaveChangesButton->Name = L"SaveChangesButton";
			this->SaveChangesButton->Size = System::Drawing::Size(86, 38);
			this->SaveChangesButton->TabIndex = 12;
			this->SaveChangesButton->Text = L"Save changes";
			this->SaveChangesButton->UseVisualStyleBackColor = true;
			this->SaveChangesButton->Click += gcnew System::EventHandler(this, &EditUserSCR::button1_Click);
			// 
			// EditUserSCR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(209, 192);
			this->Controls->Add(this->UserRankComboBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->UserTeamTextBox);
			this->Controls->Add(this->UserLastNameTextBox);
			this->Controls->Add(this->UserFirstNameTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->UserIDTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->SaveChangesButton);
			this->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->MaximizeBox = false;
			this->Name = L"EditUserSCR";
			this->Text = L"Edit user";
			this->Load += gcnew System::EventHandler(this, &EditUserSCR::EditUserSCR_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		string newUserFirstName = converSpecialStringToString(UserFirstNameTextBox->Text->ToString());
		string newUserLastName = converSpecialStringToString(UserLastNameTextBox->Text->ToString());
		string newUserTeamName = converSpecialStringToString(UserTeamTextBox->Text->ToString());
		string newUserRank = converSpecialStringToString(UserRankComboBox->SelectedItem->ToString());
		if (newUserFirstName != editedUserFirstName) ChangeFirstName(editedUserID, newUserFirstName);
		if (newUserLastName != editedUserLastName) ChangeLastName(editedUserID, newUserLastName);
		if (newUserRank != editedUserRank) ChangeRank(editedUserID, newUserRank);
		if (newUserTeamName != editedUserTeam) ChangeGroup(editedUserID, newUserTeamName);
		this->Close();
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void AddUserSCR_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void EditUserSCR_Load(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
