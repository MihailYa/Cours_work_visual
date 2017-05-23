#pragma once

#include "input.hpp"
#include "MyForm_.h"


namespace coursework {

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
		MyForm(void)
		{
			InitializeComponent();
			form_ = nullptr;
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::Label^  header;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::HelpProvider^  helpProvider1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		bool first = true;	// First click on richTextBox
		MyForm_ ^form_;		// Window with algorithms

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->header = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// header
			// 
			this->header->AutoSize = true;
			this->header->Font = (gcnew System::Drawing::Font(L"Open Sans Light", 12));
			this->header->Location = System::Drawing::Point(13, 13);
			this->header->Name = L"header";
			this->helpProvider1->SetShowHelp(this->header, true);
			this->header->Size = System::Drawing::Size(377, 27);
			this->header->TabIndex = 0;
			this->header->Text = L"Пошук максимального потоку в мережі";
			// 
			// richTextBox1
			// 
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Open Sans", 9));
			this->helpProvider1->SetHelpString(this->richTextBox1, L"Input view:\nType_of_graph\nnumber_of_vertex number_of_edges\nedge_beign edge_end ed"
				L"ge_pass_able\n...");
			this->richTextBox1->Location = System::Drawing::Point(30, 385);
			this->richTextBox1->Name = L"richTextBox1";
			this->helpProvider1->SetShowHelp(this->richTextBox1, true);
			this->richTextBox1->Size = System::Drawing::Size(261, 132);
			this->richTextBox1->TabIndex = 20;
			this->richTextBox1->Text = L"// Приклад:\n0 // Не орієнтований граф\n2 1 // 2 вершини, 1 ребро\n1 2 // 1 - почато"
				L"к, 2 - кінець ребра";
			this->richTextBox1->Click += gcnew System::EventHandler(this, &MyForm::richTextBox1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Open Sans", 9));
			this->label1->Location = System::Drawing::Point(27, 44);
			this->label1->Name = L"label1";
			this->helpProvider1->SetShowHelp(this->label1, true);
			this->label1->Size = System::Drawing::Size(154, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Оберіть алгоритми:";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox2->Font = (gcnew System::Drawing::Font(L"Open Sans", 9));
			this->checkBox2->Location = System::Drawing::Point(30, 233);
			this->checkBox2->Name = L"checkBox2";
			this->helpProvider1->SetShowHelp(this->checkBox2, true);
			this->checkBox2->Size = System::Drawing::Size(173, 24);
			this->checkBox2->TabIndex = 4;
			this->checkBox2->Text = L"Алгоритм Гоморі-Ху";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Open Sans", 9));
			this->helpProvider1->SetHelpString(this->label2, L"Input view:\nnumber_of_vertex number_of_edges\nedge_beign edge_end edge_pass_able\n."
				L"..");
			this->label2->Location = System::Drawing::Point(27, 362);
			this->label2->Name = L"label2";
			this->helpProvider1->SetShowHelp(this->label2, true);
			this->label2->Size = System::Drawing::Size(107, 20);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Введіть граф:";
			// 
			// helpProvider1
			// 
			this->helpProvider1->HelpNamespace = L"help.chm";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Open Sans", 9));
			this->label3->Location = System::Drawing::Point(27, 362);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(172, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Зчитати граф з файлу:";
			this->label3->Visible = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(26, 273);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(205, 20);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Оберіть варіант введення:";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton1->Location = System::Drawing::Point(30, 296);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(83, 24);
			this->radioButton1->TabIndex = 8;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Вручну";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->Click += gcnew System::EventHandler(this, &MyForm::radioButton1_Click);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton2->Location = System::Drawing::Point(30, 326);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(88, 24);
			this->radioButton2->TabIndex = 9;
			this->radioButton2->Text = L"З файла";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->Click += gcnew System::EventHandler(this, &MyForm::radioButton2_Click);
			// 
			// textBox1
			// 
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Open Sans", 9));
			this->textBox1->Location = System::Drawing::Point(31, 386);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 28);
			this->textBox1->TabIndex = 10;
			this->textBox1->Visible = false;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox3->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox3->Location = System::Drawing::Point(30, 534);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(131, 24);
			this->checkBox3->TabIndex = 11;
			this->checkBox3->Text = L"Зберегти граф";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox3_CheckedChanged);
			// 
			// textBox2
			// 
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Enabled = false;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(30, 581);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 28);
			this->textBox2->TabIndex = 12;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Enabled = false;
			this->label5->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(27, 558);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(106, 20);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Назва файлу:";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Window;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(30, 615);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(183, 34);
			this->button1->TabIndex = 14;
			this->button1->Text = L"Отримати результат";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Enabled = false;
			this->label6->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(47, 122);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(77, 20);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Джерело:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Enabled = false;
			this->label7->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(49, 176);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(41, 20);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Стік:";
			// 
			// textBox3
			// 
			this->textBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox3->Enabled = false;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->ForeColor = System::Drawing::SystemColors::WindowText;
			this->textBox3->Location = System::Drawing::Point(51, 145);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 28);
			this->textBox3->TabIndex = 17;
			// 
			// textBox4
			// 
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox4->Enabled = false;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox4->Location = System::Drawing::Point(51, 199);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 28);
			this->textBox4->TabIndex = 18;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Enabled = false;
			this->checkBox4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox4->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox4->Location = System::Drawing::Point(51, 95);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(306, 24);
			this->checkBox4->TabIndex = 19;
			this->checkBox4->Text = L"Визначити джерело та стік власноруч";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox4_CheckedChanged);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Open Sans", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBox1->Location = System::Drawing::Point(30, 68);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(241, 24);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->Text = L"Алгоритм Форда-Фалкерсона";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->Focused;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(425, 656);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->header);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->helpProvider1->SetShowHelp(this, true);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Coursework";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	// By hand
	private: System::Void radioButton1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->label3->Visible = false;
		this->textBox1->Visible = false;
		this->ClientSize = System::Drawing::Size(425, 656);
		this->button1->Location = System::Drawing::Point(30, 615);
		this->label2->Visible = true;
		this->richTextBox1->Visible = true;
		this->checkBox3->Visible = true;
		this->label5->Visible = true;
		this->textBox2->Visible = true;
	}

	// From file
	private: System::Void radioButton2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->label2->Visible = false;
		this->richTextBox1->Visible = false;
		this->checkBox3->Visible = false;
		this->label5->Visible = false;
		this->textBox2->Visible = false;
		this->ClientSize = System::Drawing::Size(425, 459);
		this->button1->Location = System::Drawing::Point(30, 420);
		this->label3->Visible = true;
		this->textBox1->Visible = true;
	}

	private: System::Void checkBox3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->checkBox3->Checked)
		{
			this->label5->Enabled = true;
			this->textBox2->Enabled = true;
		}
		else
		{
			this->label5->Enabled = false;
			this->textBox2->Enabled = false;
		}
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			if (form_ != nullptr && !form_->IsDisposed)
			{
				T_exception e;
				e.code = 4;
				e.text = "Не можна одночасно створювати декілька графів.";
				e.solution = "Закрийте вікно з попереднім графом.";
				throw(e);
			}
			int mode;
			int vers[2];
			bool ss = false;
			std::string temp, temp_;
		
			if (this->checkBox1->Checked || this->checkBox2->Checked)
			{
				// Define mode
				if (this->checkBox1->Checked && this->checkBox2->Checked)
				{
					mode = 2;
					if (this->checkBox4->Checked)
					{
						if (this->textBox4->Text == "" || this->textBox3->Text == "")
						{
							T_exception e;
							e.code = 4;
							e.text = "Не вказано джерело або стік.";
							throw(e);
						}
						temp = msclr::interop::marshal_as<std::string>(this->textBox3->Text);
						vers[0] = atoi(temp.c_str());
						temp = msclr::interop::marshal_as<std::string>(this->textBox4->Text);
						vers[1] = atoi(temp.c_str());
						if (vers[0] <= 0 || vers[1] <= 0)
						{
							T_exception e;
							e.code = 4;
							e.text = "Не вірно вказано джерело або стік.";
							e.solution = "Джерело та стік повинні бути більші за одиницю.";
							throw(e);
						}
						ss = true;
					}
				}
				else if (this->checkBox1->Checked)
				{
					mode = 0;
					if (this->checkBox4->Checked)
					{
						if (this->textBox4->Text == "" || this->textBox3->Text == "")
						{
							T_exception e;
							e.code = 4;
							e.text = "Не вказано джерело або стік.";
							throw(e);
						}
						temp = msclr::interop::marshal_as<std::string>(this->textBox3->Text);
						vers[0] = atoi(temp.c_str());
						temp = msclr::interop::marshal_as<std::string>(this->textBox4->Text);
						vers[1] = atoi(temp.c_str());
						if (vers[0] <= 0 || vers[1] <= 0)
						{
							T_exception e;
							e.code = 4;
							e.text = "Не вірно вказано джерело або стік.";
							e.solution = "Джерело та стік повинні бути більші за одиницю.";
							throw(e);
						}
						ss = true;
					}
				}
				else
					mode = 1;
			}
			else
			{
				T_exception e;
				e.code = 4;
				e.text = "Не обрано алгоритм.";
				throw(e);
			}

			// Read graph
			graph *gr = NULL;
			if (this->radioButton1->Checked)
			{
				if (this->richTextBox1->Text == "")
				{
					T_exception e;
					e.code = 4;
					e.text = "Не введено граф.";
					throw(e);
				}
				temp = msclr::interop::marshal_as<std::string>(this->richTextBox1->Text);
				// Read graph from richTextBox
				input_char(temp.c_str(), gr);

				// Save graph
				if (this->checkBox3->Checked)
				{
					if (this->textBox2->Text == "")
					{
						T_exception e;
						e.code = 4;
						e.text = "Не вказана назва файлу, в якому потрібно зберегти граф.";
						throw(e);
					}
					else
					{
						temp_ = msclr::interop::marshal_as<std::string>(this->textBox2->Text);
						FILE *f;
						if ((f = fopen(temp_.c_str(), "wt")) == NULL)
						{
							T_exception e;
							e.code = 1;
							e.text = "Не можливо відкрити файл для збереження графу.";
							e.solution = "Закрийте вказаний файл.";
							throw(e);
						}
						int n = temp.length();
						for (int i = 0; i < n; i++)
							fprintf(f, "%c", (temp.c_str())[i]);
						fclose(f);
					}
				}

				// Create new window
				form_ = gcnew MyForm_(mode, gr, vers, ss);
			}
			else
			{
				temp = msclr::interop::marshal_as<std::string>(this->textBox1->Text);
				// Read graph from file
				input(temp.c_str(), gr);

				// Create new window
				form_ = gcnew MyForm_(mode, gr, vers, ss);
			}
		}
		catch (T_exception &e)
		{
			if(e.solution != "")
				MessageBox::Show(gcnew String(("Помилка: " + e.text + "\nМожливе рішення: " + e.solution).c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			else
				MessageBox::Show(gcnew String(("Помилка: " + e.text).c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
	}

	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->checkBox1->Checked)
		{
			this->checkBox4->Checked = false;
			this->checkBox4->Enabled = true;
		}
		else
		{
			this->checkBox4->Checked = false;
			this->checkBox4->Enabled = false;
			this->textBox4->Enabled = false;
			this->textBox3->Enabled = false;
			this->label6->Enabled = false;
			this->label7->Enabled = false;
		}
	}

	private: System::Void checkBox4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->checkBox4->Checked)
		{
			this->textBox4->Enabled = true;
			this->textBox3->Enabled = true;
			this->label6->Enabled = true;
			this->label7->Enabled = true;
		}
		else
		{
			this->textBox4->Enabled = false;
			this->textBox3->Enabled = false;
			this->label6->Enabled = false;
			this->label7->Enabled = false;
		}
	}

	private: System::Void checkBox1_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e) {
		if (this->checkBox1->Checked)
			this->checkBox4->Enabled = true;
		else
		{
			this->checkBox4->Checked = false;
			this->checkBox4->Enabled = false;
		}
	}

	private: System::Void richTextBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (first)
		{
			first = false;
			this->richTextBox1->Text = "";
		}
	}
};

}
