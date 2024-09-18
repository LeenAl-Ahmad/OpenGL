#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		static bool rendRed;
		static bool rendGreen;
		static bool rendBlue;
		MyForm(void)
		{
			InitializeComponent();
			rendRed = checkBoxRed ->Checked;
			rendGreen = checkBoxGreen->Checked;
			rendBlue = checkBoxBlue->Checked;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ checkBoxRed;
	protected:
	private: System::Windows::Forms::CheckBox^ checkBoxGreen;
	private: System::Windows::Forms::CheckBox^ checkBoxBlue;

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
			this->checkBoxRed = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxGreen = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxBlue = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// checkBoxRed
			// 
			this->checkBoxRed->AutoSize = true;
			this->checkBoxRed->Location = System::Drawing::Point(13, 13);
			this->checkBoxRed->Name = L"checkBoxRed";
			this->checkBoxRed->Size = System::Drawing::Size(55, 20);
			this->checkBoxRed->TabIndex = 0;
			this->checkBoxRed->Text = L"Red";
			this->checkBoxRed->UseVisualStyleBackColor = true;
			this->checkBoxRed->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxRed_CheckedChanged);
			// 
			// checkBoxGreen
			// 
			this->checkBoxGreen->AutoSize = true;
			this->checkBoxGreen->Location = System::Drawing::Point(13, 40);
			this->checkBoxGreen->Name = L"checkBoxGreen";
			this->checkBoxGreen->Size = System::Drawing::Size(66, 20);
			this->checkBoxGreen->TabIndex = 1;
			this->checkBoxGreen->Text = L"Green";
			this->checkBoxGreen->UseVisualStyleBackColor = true;
			this->checkBoxGreen->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxGreen_CheckedChanged);
			// 
			// checkBoxBlue
			// 
			this->checkBoxBlue->AutoSize = true;
			this->checkBoxBlue->Location = System::Drawing::Point(13, 67);
			this->checkBoxBlue->Name = L"checkBoxBlue";
			this->checkBoxBlue->Size = System::Drawing::Size(56, 20);
			this->checkBoxBlue->TabIndex = 2;
			this->checkBoxBlue->Text = L"Blue";
			this->checkBoxBlue->UseVisualStyleBackColor = true;
			this->checkBoxBlue->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxBlue_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(226, 204);
			this->Controls->Add(this->checkBoxBlue);
			this->Controls->Add(this->checkBoxGreen);
			this->Controls->Add(this->checkBoxRed);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->TopMost = true;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void checkBoxRed_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		rendRed = checkBoxRed->Checked;
	}
	private: System::Void checkBoxGreen_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		rendGreen = checkBoxGreen->Checked;
	}
	private: System::Void checkBoxBlue_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		rendBlue = checkBoxBlue->Checked;
	}
	};
}
