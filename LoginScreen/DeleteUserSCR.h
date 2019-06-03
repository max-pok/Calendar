#pragma once
#include <string>
#include "RemoveUser.h"
namespace DeleteUserScreen {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for DeleteUserSCR
	/// </summary>
	string userID;
	public ref class DeleteUserSCR : public System::Windows::Forms::Form
	{
	public:
		DeleteUserSCR(void)
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
		~DeleteUserSCR()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  NoButton;
	protected:
	private: System::Windows::Forms::Button^  YesButton;
	private: System::Windows::Forms::Label^  label1;

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
			this->NoButton = (gcnew System::Windows::Forms::Button());
			this->YesButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// NoButton
			// 
			this->NoButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->NoButton->Location = System::Drawing::Point(249, 85);
			this->NoButton->Margin = System::Windows::Forms::Padding(6);
			this->NoButton->Name = L"NoButton";
			this->NoButton->Size = System::Drawing::Size(117, 39);
			this->NoButton->TabIndex = 5;
			this->NoButton->Text = L"No";
			this->NoButton->UseVisualStyleBackColor = true;
			this->NoButton->Click += gcnew System::EventHandler(this, &DeleteUserSCR::NoButton_Click);
			// 
			// YesButton
			// 
			this->YesButton->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->YesButton->Location = System::Drawing::Point(120, 85);
			this->YesButton->Margin = System::Windows::Forms::Padding(6);
			this->YesButton->Name = L"YesButton";
			this->YesButton->Size = System::Drawing::Size(117, 39);
			this->YesButton->TabIndex = 4;
			this->YesButton->Text = L"Yes";
			this->YesButton->UseVisualStyleBackColor = true;
			this->YesButton->Click += gcnew System::EventHandler(this, &DeleteUserSCR::YesButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F));
			this->label1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label1->Location = System::Drawing::Point(22, 17);
			this->label1->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(228, 39);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Are you sure\?";
			// 
			// DeleteUserSCR
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(381, 140);
			this->Controls->Add(this->NoButton);
			this->Controls->Add(this->YesButton);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(6);
			this->MaximizeBox = false;
			this->Name = L"DeleteUserSCR";
			this->Text = L"Delete user";
			this->Load += gcnew System::EventHandler(this, &DeleteUserSCR::DeleteUserSCR_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void DeleteUserSCR_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void YesButton_Click(System::Object^  sender, System::EventArgs^  e) {
		RemoveUser(userID);
		this->Close();
	}
	private: System::Void NoButton_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	};
}

