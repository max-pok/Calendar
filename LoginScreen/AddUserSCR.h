#pragma once
#include "AddUser.h"
#include "GlobalClass.h"
namespace AddUserScreen {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Globals;
	/// <summary>
	/// Summary for AddUserSCR
	/// </summary>
	public ref class AddUserSCR : public System::Windows::Forms::Form
	{
	public:
		AddUserSCR(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AddUserSCR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  comboBox1;
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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->button1->Location = System::Drawing::Point(146, 177);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(86, 38);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Add new user";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AddUserSCR::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label1->Location = System::Drawing::Point(26, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(21, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"ID:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(92, 29);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(111, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &AddUserSCR::textBox1_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label2->Location = System::Drawing::Point(26, 58);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"First Name:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(92, 55);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(111, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &AddUserSCR::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(92, 81);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(111, 20);
			this->textBox3->TabIndex = 5;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(92, 133);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(111, 20);
			this->textBox5->TabIndex = 7;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label3->Location = System::Drawing::Point(26, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(58, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Last Name";
			this->label3->Click += gcnew System::EventHandler(this, &AddUserSCR::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label4->Location = System::Drawing::Point(26, 110);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(36, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Rank:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label5->Location = System::Drawing::Point(26, 136);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(37, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Team:";
			this->label5->Click += gcnew System::EventHandler(this, &AddUserSCR::label5_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"1 - Regular", L"2 - Team Leader", L"3 - Admin" });
			this->comboBox1->Location = System::Drawing::Point(92, 106);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(111, 21);
			this->comboBox1->TabIndex = 11;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &AddUserSCR::comboBox1_SelectedIndexChanged);
			// 
			// AddUserSCR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(244, 227);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->Name = L"AddUserSCR";
			this->Text = L"Add User";
			this->Load += gcnew System::EventHandler(this, &AddUserSCR::AddUserSCR_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^ tempSTR = textBox1->Text;
		string FNAME = "", LNAME = "",GNAME = "", *fName, *lName, *gName;
		char id[10];
		int i = 0, rank = 1;
		for (i = 0; i < (int)tempSTR->Length; i++) id[i] = (char)tempSTR[i];
		id[i] = '\0';
		fName = new string[textBox2->Text->Length];
		lName = new string[textBox3->Text->Length];
		gName = new string[textBox5->Text->Length];
		for (i = 0; i < textBox2->Text->Length; i++) fName[i] = (char)(textBox2->Text)[i];
		for (i = 0; i < textBox2->Text->Length; i++) FNAME = FNAME + fName[i];
		for (i = 0; i < textBox3->Text->Length; i++) lName[i] = (char)(textBox3->Text)[i];
		for (i = 0; i < textBox3->Text->Length; i++) LNAME = LNAME + lName[i];
		for (i = 0; i < textBox5->Text->Length; i++) gName[i] = (char)(textBox5->Text)[i];
		for (i = 0; i < textBox5->Text->Length; i++) GNAME = GNAME + gName[i];
		if (comboBox1->Text == "1 - Regular") rank = 1;
		if (comboBox1->Text == "2 - Team Leader") rank = 2;
		if (comboBox1->Text == "3 - Admin") rank = 3;
		AddUserToSystem(id,FNAME,LNAME,rank,GNAME);
		this->Close();
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (comboBox1->Text == "3 - Admin") {
		textBox5->Enabled = false;
		textBox5->Text = "Admin";
	}
	else {
		textBox5->Enabled = true;
		textBox5->Text = "";
	}
}
private: System::Void AddUserSCR_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
