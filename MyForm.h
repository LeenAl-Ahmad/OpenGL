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

	private: System::Windows::Forms::Button^ ResetLight;
	private: System::Windows::Forms::TrackBar^ SPStrength;
	private: System::Windows::Forms::Label^ SpecularStrength;
	private: System::Windows::Forms::Label^ red;
	private: System::Windows::Forms::Label^ GREEN;
	private: System::Windows::Forms::Label^ blue;


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
	private: System::Windows::Forms::RadioButton^ check1;
	private: System::Windows::Forms::RadioButton^ check2;
	private: System::Windows::Forms::CheckBox^ Box1;
	private: System::Windows::Forms::CheckBox^ Box2;
	private: System::Windows::Forms::CheckBox^ Box3;
	private: System::Windows::Forms::RadioButton^ check3;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::TrackBar^ trackBar2;
	private: System::Windows::Forms::CheckBox^ Box4;
	private: System::Windows::Forms::CheckBox^ Box5;
	private: System::Windows::Forms::RadioButton^ check4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;




	public:

	public:
		static bool mCube;

		MyForm(void)
		{
			InitializeComponent();
			mlight= check1 ->Checked;
			//cPosition = colorByPosition ->Checked;
			//mCube = moveCube ->Checked;
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
			this->ResetLight = (gcnew System::Windows::Forms::Button());
			this->SPStrength = (gcnew System::Windows::Forms::TrackBar());
			this->SpecularStrength = (gcnew System::Windows::Forms::Label());
			this->red = (gcnew System::Windows::Forms::Label());
			this->GREEN = (gcnew System::Windows::Forms::Label());
			this->blue = (gcnew System::Windows::Forms::Label());
			this->resetObj = (gcnew System::Windows::Forms::Button());
			this->redtrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->greentrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->bluetrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->check1 = (gcnew System::Windows::Forms::RadioButton());
			this->check2 = (gcnew System::Windows::Forms::RadioButton());
			this->Box1 = (gcnew System::Windows::Forms::CheckBox());
			this->Box2 = (gcnew System::Windows::Forms::CheckBox());
			this->Box3 = (gcnew System::Windows::Forms::CheckBox());
			this->check3 = (gcnew System::Windows::Forms::RadioButton());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->Box4 = (gcnew System::Windows::Forms::CheckBox());
			this->Box5 = (gcnew System::Windows::Forms::CheckBox());
			this->check4 = (gcnew System::Windows::Forms::RadioButton());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SPStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->redtrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->greentrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bluetrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			this->SuspendLayout();
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
			// resetObj
			// 
			this->resetObj->Location = System::Drawing::Point(42, 289);
			this->resetObj->Name = L"resetObj";
			this->resetObj->Size = System::Drawing::Size(172, 23);
			this->resetObj->TabIndex = 12;
			this->resetObj->Text = L"Reset Transform";
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
			// check1
			// 
			this->check1->AutoSize = true;
			this->check1->Location = System::Drawing::Point(12, 12);
			this->check1->Name = L"check1";
			this->check1->Size = System::Drawing::Size(93, 20);
			this->check1->TabIndex = 20;
			this->check1->TabStop = true;
			this->check1->Text = L"Move Light";
			this->check1->UseVisualStyleBackColor = true;
			this->check1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::check1_CheckedChanged);
			// 
			// check2
			// 
			this->check2->AutoSize = true;
			this->check2->Location = System::Drawing::Point(13, 263);
			this->check2->Name = L"check2";
			this->check2->Size = System::Drawing::Size(89, 20);
			this->check2->TabIndex = 21;
			this->check2->TabStop = true;
			this->check2->Text = L"Transform";
			this->check2->UseVisualStyleBackColor = true;
			this->check2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::check2_CheckedChanged);
			// 
			// Box1
			// 
			this->Box1->AutoSize = true;
			this->Box1->Location = System::Drawing::Point(13, 318);
			this->Box1->Name = L"Box1";
			this->Box1->Size = System::Drawing::Size(86, 20);
			this->Box1->TabIndex = 22;
			this->Box1->Text = L"Translate";
			this->Box1->UseVisualStyleBackColor = true;
			this->Box1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Box1_CheckedChanged);
			// 
			// Box2
			// 
			this->Box2->AutoSize = true;
			this->Box2->Location = System::Drawing::Point(174, 318);
			this->Box2->Name = L"Box2";
			this->Box2->Size = System::Drawing::Size(69, 20);
			this->Box2->TabIndex = 23;
			this->Box2->Text = L"Rotate";
			this->Box2->UseVisualStyleBackColor = true;
			this->Box2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Box2_CheckedChanged);
			// 
			// Box3
			// 
			this->Box3->AutoSize = true;
			this->Box3->Location = System::Drawing::Point(338, 318);
			this->Box3->Name = L"Box3";
			this->Box3->Size = System::Drawing::Size(64, 20);
			this->Box3->TabIndex = 24;
			this->Box3->Text = L"Scale";
			this->Box3->UseVisualStyleBackColor = true;
			this->Box3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Box3_CheckedChanged);
			// 
			// check3
			// 
			this->check3->AutoSize = true;
			this->check3->Location = System::Drawing::Point(12, 344);
			this->check3->Name = L"check3";
			this->check3->Size = System::Drawing::Size(106, 20);
			this->check3->TabIndex = 25;
			this->check3->TabStop = true;
			this->check3->Text = L"Water Scene";
			this->check3->UseVisualStyleBackColor = true;
			this->check3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::check3_CheckedChanged);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(13, 392);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(404, 56);
			this->trackBar1->TabIndex = 26;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(13, 454);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(404, 56);
			this->trackBar2->TabIndex = 27;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar2_Scroll);
			// 
			// Box4
			// 
			this->Box4->AutoSize = true;
			this->Box4->Location = System::Drawing::Point(54, 505);
			this->Box4->Name = L"Box4";
			this->Box4->Size = System::Drawing::Size(139, 20);
			this->Box4->TabIndex = 28;
			this->Box4->Text = L"Wireframe Render";
			this->Box4->UseVisualStyleBackColor = true;
			this->Box4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Box4_CheckedChanged);
			// 
			// Box5
			// 
			this->Box5->AutoSize = true;
			this->Box5->Location = System::Drawing::Point(248, 505);
			this->Box5->Name = L"Box5";
			this->Box5->Size = System::Drawing::Size(81, 20);
			this->Box5->TabIndex = 29;
			this->Box5->Text = L"Tint Blue";
			this->Box5->UseVisualStyleBackColor = true;
			this->Box5->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Box5_CheckedChanged);
			// 
			// check4
			// 
			this->check4->AutoSize = true;
			this->check4->Location = System::Drawing::Point(17, 531);
			this->check4->Name = L"check4";
			this->check4->Size = System::Drawing::Size(110, 20);
			this->check4->TabIndex = 30;
			this->check4->TabStop = true;
			this->check4->Text = L"Space Scene";
			this->check4->UseVisualStyleBackColor = true;
			this->check4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::check4_CheckedChanged);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(422, 383);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(32, 22);
			this->textBox5->TabIndex = 31;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(423, 445);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(32, 22);
			this->textBox6->TabIndex = 32;
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox6_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(39, 373);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(71, 16);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Frequency";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(39, 432);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 16);
			this->label2->TabIndex = 34;
			this->label2->Text = L"Amplitude";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(466, 567);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->check4);
			this->Controls->Add(this->Box5);
			this->Controls->Add(this->Box4);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->check3);
			this->Controls->Add(this->Box3);
			this->Controls->Add(this->Box2);
			this->Controls->Add(this->Box1);
			this->Controls->Add(this->check2);
			this->Controls->Add(this->check1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->bluetrackBar);
			this->Controls->Add(this->greentrackBar);
			this->Controls->Add(this->redtrackBar);
			this->Controls->Add(this->resetObj);
			this->Controls->Add(this->blue);
			this->Controls->Add(this->GREEN);
			this->Controls->Add(this->red);
			this->Controls->Add(this->SpecularStrength);
			this->Controls->Add(this->SPStrength);
			this->Controls->Add(this->ResetLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SPStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->redtrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->greentrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bluetrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

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
/*private: System::Void colorByPosition_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	
	cPosition = colorByPosition->Checked;
	GameController::GetInstance().colorPosition = cPosition;
}*/
private: System::Void resetObj_Click(System::Object^ sender, System::EventArgs^ e) {
	clickedO = true;
	GameController::GetInstance().clickO = clickedO;
}
/*private: System::Void moveCube_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	mCube = moveCube->Checked;
	GameController::GetInstance().moveCube = mCube;
}*/
private: System::Void redtrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	float redBar = redtrackBar->Value;
	// Map the trackbar value (0 - 300) to the specular color component (0.00 - 3.00)
	float val = redBar / 100.0f;

	// Check if the new value differs from the previous value
	if (GameController::GetInstance().GetR() != val) {
		// Update the GameController and set UpdatedRed to true
		GameController::GetInstance().SetR(val);
		GameController::GetInstance().UpdatedRed = true;
	}

	// Update the text label
	textBox1->Text = val.ToString("F2");
}
private: System::Void greentrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	float greenBar = greentrackBar->Value;
	// Map the trackbar value (0 - 300) to the specular color component (0.00 - 3.00)
	float val = greenBar / 100.0f;

	// Check if the new value differs from the previous value
	if (GameController::GetInstance().GetG() != val) {
		// Update the GameController and set UpdatedGreen to true
		GameController::GetInstance().SetG(val);
		GameController::GetInstance().UpdatedGreen = true;
	}

	// Update the text label
	textBox2->Text = val.ToString("F2");
}
private: System::Void bluetrackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		float blueBar = bluetrackBar->Value;
		// Map the trackbar value (0 - 300) to the specular color component (0.00 - 3.00)
		float val = blueBar / 100.0f;

		// Check if the new value differs from the previous value
		if (GameController::GetInstance().GetB() != val) {
			// Update the GameController and set UpdatedBlue to true
			GameController::GetInstance().SetB(val);
			GameController::GetInstance().UpdatedBlue = true;
		}

		// Update the text label
		textBox3->Text = val.ToString("F2");
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
private: System::Void check1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	mlight = check1->Checked;
	GameController::GetInstance().moveLight = mlight;
}
private: System::Void check2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void Box1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Box2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Box3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void check3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox6_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Box4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Box5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void check4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
