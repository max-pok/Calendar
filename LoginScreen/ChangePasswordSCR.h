#pragma once
#include "changepass.h"
#include <string>
namespace ChangePasswordScreen {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for ChangePasswordSCR
	/// </summary>
	string userID;
	public ref class ChangePasswordSCR : public System::Windows::Forms::Form
	{
	public:
		ChangePasswordSCR(void)
		{
			InitializeComponent();
			NewPassTextBox->PasswordChar = '*';
			RepeatPassTextBox->PasswordChar = '*';
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ChangePasswordSCR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  SavePassButton;
	protected:
	private: System::Windows::Forms::TextBox^  RepeatPassTextBox;
	private: System::Windows::Forms::TextBox^  NewPassTextBox;
	private: System::Windows::Forms::Label^  RepeatPassLabel;
	private: System::Windows::Forms::Label^  NewPassLabel;

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
			this->SavePassButton = (gcnew System::Windows::Forms::Button());
			this->RepeatPassTextBox = (gcnew System::Windows::Forms::TextBox());
			this->NewPassTextBox = (gcnew System::Windows::Forms::TextBox());
			this->RepeatPassLabel = (gcnew System::Windows::Forms::Label());
			this->NewPassLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// SavePassButton
			// 
			this->SavePassButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->SavePassButton->Location = System::Drawing::Point(480, 42);
			this->SavePassButton->Margin = System::Windows::Forms::Padding(6, 6, 6, 6);
			this->SavePassButton->Name = L"SavePassButton";
			this->SavePassButton->Size = System::Drawing::Size(110, 63);
			this->SavePassButton->TabIndex = 9;
			this->SavePassButton->Text = L"Save";
			this->SavePassButton->UseVisualStyleBackColor = true;
			this->SavePassButton->Click += gcnew System::EventHandler(this, &ChangePasswordSCR::button1_Click);
			// 
			// RepeatPassTextBox
			// 
			this->RepeatPassTextBox->Location = System::Drawing::Point(248, 76);
			this->RepeatPassTextBox->Margin = System::Windows::Forms::Padding(6, 6, 6, 6);
			this->RepeatPassTextBox->Name = L"RepeatPassTextBox";
			this->RepeatPassTextBox->Size = System::Drawing::Size(219, 29);
			this->RepeatPassTextBox->TabIndex = 8;
			// 
			// NewPassTextBox
			// 
			this->NewPassTextBox->Location = System::Drawing::Point(248, 28);
			this->NewPassTextBox->Margin = System::Windows::Forms::Padding(6, 6, 6, 6);
			this->NewPassTextBox->Name = L"NewPassTextBox";
			this->NewPassTextBox->Size = System::Drawing::Size(219, 29);
			this->NewPassTextBox->TabIndex = 7;
			// 
			// RepeatPassLabel
			// 
			this->RepeatPassLabel->AutoSize = true;
			this->RepeatPassLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			this->RepeatPassLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->RepeatPassLabel->Location = System::Drawing::Point(18, 78);
			this->RepeatPassLabel->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->RepeatPassLabel->Name = L"RepeatPassLabel";
			this->RepeatPassLabel->Size = System::Drawing::Size(201, 25);
			this->RepeatPassLabel->TabIndex = 6;
			this->RepeatPassLabel->Text = L"Repeat password:";
			// 
			// NewPassLabel
			// 
			this->NewPassLabel->AutoSize = true;
			this->NewPassLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			this->NewPassLabel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->NewPassLabel->Location = System::Drawing::Point(18, 30);
			this->NewPassLabel->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->NewPassLabel->Name = L"NewPassLabel";
			this->NewPassLabel->Size = System::Drawing::Size(171, 25);
			this->NewPassLabel->TabIndex = 5;
			this->NewPassLabel->Text = L"New password:";
			// 
			// ChangePasswordSCR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(609, 140);
			this->Controls->Add(this->SavePassButton);
			this->Controls->Add(this->RepeatPassTextBox);
			this->Controls->Add(this->NewPassTextBox);
			this->Controls->Add(this->RepeatPassLabel);
			this->Controls->Add(this->NewPassLabel);
			this->Margin = System::Windows::Forms::Padding(6, 6, 6, 6);
			this->Name = L"ChangePasswordSCR";
			this->Text = L"Change password";
			this->Load += gcnew System::EventHandler(this, &ChangePasswordSCR::ChangePasswordSCR_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ChangePasswordSCR_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void RepeatPassLabel_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void NewPassTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (NewPassTextBox->Text->ToString() == RepeatPassTextBox->Text->ToString() && RepeatPassTextBox->Text->ToString() != "") {
		int i;
		char temp[15], tempID[10];
		for (i = 0; i < (int)NewPassTextBox->Text->ToString()->Length; i++) temp[i] = (char)NewPassTextBox->Text->ToString()[i];
		temp[i] = '\0';
		for (i = 0; i < (int)userID.length(); i++) tempID[i] = userID[i];
		tempID[i] = '\0';
		changepass(tempID, temp);
		this->Close();
	}
	else MessageBox::Show("New password entered incorrectly.\nPlease enter repeat it again...");
}
};
}
