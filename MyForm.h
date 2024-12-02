#pragma once
#include "GameController.h"
#include "Shader.h"
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
		static bool mlight;
		static bool cPosition;
		static bool clickedL;
		static bool clickedO;
		static float sps;
	private: System::Windows::Forms::CheckBox^ MoveLight;
	private: System::Windows::Forms::Button^ ResetLight;
	private: System::Windows::Forms::TrackBar^ SPStrength;
	private: System::Windows::Forms::Label^ SpecularStrength;
	private: System::Windows::Forms::Label^ red;
	private: System::Windows::Forms::Label^ GREEN;
	private: System::Windows::Forms::Label^ blue;
	private: System::Windows::Forms::CheckBox^ colorByPosition;
	private: System::Windows::Forms::CheckBox^ moveCube;
	private: System::Windows::Forms::Button^ resetObj;
	private: System::Windows::Forms::TrackBar^ redtrackBar;
	private: System::Windows::Forms::TrackBar^ greentrackBar;
	private: System::Windows::Forms::TrackBar^ bluetrackBar;

	public:
		float specularStrengthValue = 4.0f;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	public:

	public:
		static bool mCube;
		MyForm(void)
		{
			InitializeComponent();
			mlight= MoveLight ->Checked;
			cPosition = colorByPosition ->Checked;
			mCube = moveCube ->Checked;
			clickedL = false;
			clickedO = false;
			redtrackBar->Value = 300;
			greentrackBar->Value = 300;
			bluetrackBar->Value = 300;
			
			textBox1->Text = redtrackBar->Value.ToString() + "%";
			textBox2->Text = greentrackBar->Value.ToString() + "%";
			textBox3->Text = bluetrackBar->Value.ToString() + "%";
			float sps = SPStrength->Value;
			
		}
		float Getsps() {
			return  sps = SPStrength->Value; // Normalize to -1.0 to 1.0
		}
		float GetG() {
			return (greentrackBar->Value - 100.0f) / 100.0f; // Normalize to -1.0 to 1.0
		}
		float GetB() {
			return (bluetrackBar->Value - 100.0f) / 100.0f; // Normalize to -1.0 to 1.0
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

	protected:



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
			this->MoveLight = (gcnew System::Windows::Forms::CheckBox());
			this->ResetLight = (gcnew System::Windows::Forms::Button());
			this->SPStrength = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularStrength = (gcnew System::Windows::Forms::Label());
			this->red = (gcnew System::Windows::Forms::Label());
			this->GREEN = (gcnew System::Windows::Forms::Label());
			this->blue = (gcnew System::Windows::Forms::Label());
			this->colorByPosition = (gcnew System::Windows::Forms::CheckBox());
			this->moveCube = (gcnew System::Windows::Forms::CheckBox());
			this->resetObj = (gcnew System::Windows::Forms::Button());
			this->redtrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->greentrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->bluetrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SPStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->redtrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->greentrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bluetrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// MoveLight
			// 
			this->MoveLight->AutoSize = true;
			this->MoveLight->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->MoveLight->Location = System::Drawing::Point(13, 13);
			this->MoveLight->Name = L"MoveLight";
			this->MoveLight->Size = System::Drawing::Size(94, 20);
			this->MoveLight->TabIndex = 0;
			this->MoveLight->Text = L"Move Light";
			this->MoveLight->UseVisualStyleBackColor = true;
			this->MoveLight->CheckedChanged += gcnew System::EventHandler(this, &MyForm::MoveLight_CheckedChanged);
			// 
			// ResetLight
			// 
			this->ResetLight->Location = System::Drawing::Point(42, 40);
			this->ResetLight->Name = L"ResetLight";
			this->ResetLight->Size = System::Drawing::Size(147, 23);
			this->ResetLight->TabIndex = 1;
			this->ResetLight->Text = L"Reset Light Position";
			this->ResetLight->UseVisualStyleBackColor = true;
			this->ResetLight->Click += gcnew System::EventHandler(this, &MyForm::ResetLight_Click);
			// 
			// SPStrength
			// 
			this->SPStrength->Location = System::Drawing::Point(129, 69);
			this->SPStrength->Maximum = 128;
			this->SPStrength->Minimum = 1;
			this->SPStrength->Name = L"SPStrength";
			this->SPStrength->Size = System::Drawing::Size(266, 56);
			this->SPStrength->TabIndex = 2;
			this->SPStrength->TickFrequency = 4;
			this->SPStrength->Value = 4;
			this->SPStrength->Scroll += gcnew System::EventHandler(this, &MyForm::SPStrength_Scroll);
			// 
			// SpecularStrength
			// 
			this->SpecularStrength->AutoSize = true;
			this->SpecularStrength->Location = System::Drawing::Point(10, 79);
			this->SpecularStrength->Name = L"SpecularStrength";
			this->SpecularStrength->Size = System::Drawing::Size(113, 16);
			this->SpecularStrength->TabIndex = 6;
			this->SpecularStrength->Text = L"Specular Strength";
			// 
			// red
			// 
			this->red->AutoSize = true;
			this->red->Location = System::Drawing::Point(10, 119);
			this->red->Name = L"red";
			this->red->Size = System::Drawing::Size(17, 16);
			this->red->TabIndex = 7;
			this->red->Text = L"R";
			this->red->Click += gcnew System::EventHandler(this, &MyForm::red_Click);
			// 
			// GREEN
			// 
			this->GREEN->AutoSize = true;
			this->GREEN->Location = System::Drawing::Point(9, 168);
			this->GREEN->Name = L"GREEN";
			this->GREEN->Size = System::Drawing::Size(17, 16);
			this->GREEN->TabIndex = 8;
			this->GREEN->Text = L"G";
			// 
			// blue
			// 
			this->blue->AutoSize = true;
			this->blue->Location = System::Drawing::Point(9, 213);
			this->blue->Name = L"blue";
			this->blue->Size = System::Drawing::Size(16, 16);
			this->blue->TabIndex = 9;
			this->blue->Text = L"B";
			// 
			// colorByPosition
			// 
			this->colorByPosition->AutoSize = true;
			this->colorByPosition->Location = System::Drawing::Point(13, 285);
			this->colorByPosition->Name = L"colorByPosition";
			this->colorByPosition->Size = System::Drawing::Size(131, 20);
			this->colorByPosition->TabIndex = 10;
			this->colorByPosition->Text = L"Color By Position";
			this->colorByPosition->UseVisualStyleBackColor = true;
			this->colorByPosition->CheckedChanged += gcnew System::EventHandler(this, &MyForm::colorByPosition_CheckedChanged);
			// 
			// moveCube
			// 
			this->moveCube->AutoSize = true;
			this->moveCube->Location = System::Drawing::Point(12, 365);
			this->moveCube->Name = L"moveCube";
			this->moveCube->Size = System::Drawing::Size(172, 20);
			this->moveCube->TabIndex = 11;
			this->moveCube->Text = L"Move Cubes To Sphere";
			this->moveCube->UseVisualStyleBackColor = true;
			this->moveCube->CheckedChanged += gcnew System::EventHandler(this, &MyForm::moveCube_CheckedChanged);
			// 
			// resetObj
			// 
			this->resetObj->Location = System::Drawing::Point(32, 326);
			this->resetObj->Name = L"resetObj";
			this->resetObj->Size = System::Drawing::Size(172, 23);
			this->resetObj->TabIndex = 12;
			this->resetObj->Text = L"Reset Suzzane Position";
			this->resetObj->UseVisualStyleBackColor = true;
			this->resetObj->Click += gcnew System::EventHandler(this, &MyForm::resetObj_Click);
			// 
			// redtrackBar
			// 
			this->redtrackBar->Location = System::Drawing::Point(33, 106);
			this->redtrackBar->Maximum = 300;
			this->redtrackBar->Name = L"redtrackBar";
			this->redtrackBar->Size = System::Drawing::Size(370, 56);
			this->redtrackBar->TabIndex = 13;
			this->redtrackBar->Value = 100;
			this->redtrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::redtrackBar_Scroll);
			// 
			// greentrackBar
			// 
			this->greentrackBar->Location = System::Drawing::Point(32, 151);
			this->greentrackBar->Maximum = 300;
			this->greentrackBar->Name = L"greentrackBar";
			this->greentrackBar->Size = System::Drawing::Size(370, 56);
			this->greentrackBar->TabIndex = 14;
			this->greentrackBar->Value = 100;
			this->greentrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::greentrackBar_Scroll);
			// 
			// bluetrackBar
			// 
			this->bluetrackBar->Location = System::Drawing::Point(31, 213);
			this->bluetrackBar->Maximum = 300;
			this->bluetrackBar->Name = L"bluetrackBar";
			this->bluetrackBar->Size = System::Drawing::Size(370, 56);
			this->bluetrackBar->TabIndex = 15;
			this->bluetrackBar->Value = 100;
			this->bluetrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::bluetrackBar_Scroll);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(401, 112);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(32, 22);
			this->textBox1->TabIndex = 16;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(401, 162);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(32, 22);
			this->textBox2->TabIndex = 17;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(401, 213);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(32, 22);
			this->textBox3->TabIndex = 18;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(401, 79);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(32, 22);
			this->textBox4->TabIndex = 19;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(466, 410);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->bluetrackBar);
			this->Controls->Add(this->greentrackBar);
			this->Controls->Add(this->redtrackBar);
			this->Controls->Add(this->resetObj);
			this->Controls->Add(this->moveCube);
			this->Controls->Add(this->colorByPosition);
			this->Controls->Add(this->blue);
			this->Controls->Add(this->GREEN);
			this->Controls->Add(this->red);
			this->Controls->Add(this->SpecularStrength);
			this->Controls->Add(this->SPStrength);
			this->Controls->Add(this->ResetLight);
			this->Controls->Add(this->MoveLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SPStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->redtrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->greentrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bluetrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			mlight = MoveLight ->Checked;
			GameController::GetInstance().moveLight = mlight;
}
private: System::Void ResetLight_Click(System::Object^ sender, System::EventArgs^ e) {
	clickedL = true;
	GameController::GetInstance().clickL = clickedL;
}
private: System::Void SPStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
	int trackBarValue = SPStrength->Value;
	
	// Map the trackbar value (1-128) to the specular strength (0.00-3.00)
	float specularStrength = (trackBarValue - 1) / 42.33f * 0.5f; // (128-1) maps to (0-3), 0.5 to make it less intense
	GameController::GetInstance().SetSpecularStrength(specularStrength);
	// Update the label to display the mapped value (0.00 to 3.00)
	textBox4->Text = specularStrength.ToString("F2");
}
private: System::Void redBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void greenBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void blueBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void colorByPosition_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	
	cPosition = colorByPosition->Checked;
	GameController::GetInstance().colorPosition = cPosition;
}
private: System::Void resetObj_Click(System::Object^ sender, System::EventArgs^ e) {
	clickedO = true;
	GameController::GetInstance().clickO = clickedO;
}
private: System::Void moveCube_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	mCube = moveCube->Checked;
	GameController::GetInstance().moveCube = mCube;
}
private: System::Void redtrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	textBox1->Text = redtrackBar->Value.ToString() + "%";
}
private: System::Void greentrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	textBox2->Text = greentrackBar->Value.ToString() + "%";
}
	private: System::Void bluetrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		textBox3->Text = bluetrackBar->Value.ToString() + "%";
	}
private: System::Void red_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
