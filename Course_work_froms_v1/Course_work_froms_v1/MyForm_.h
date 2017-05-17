#pragma once
#include "Humori.hpp"
#include "Ford.hpp"
#include "stdafx.hpp"
#include "PictureForm.h"

#define OUTPUT_DIR "output"

static std::string ford_text;
static std::string humori_text;

namespace Course_work_froms_v1 {

	using namespace coursework;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for MyForm_
	/// </summary>
	public ref class MyForm_ : public System::Windows::Forms::Form
	{
	public:
		/**
		* @mode 0 - Ford, 1 - Humori, 2 - both
		* @gr pointer on graph
		*/
		MyForm_(int mode, graph *&gr, int vers[2], bool ss)
		{
			InitializeComponent();
			pbox1 = new char[40];
			pbox2 = new char[40];
			
			Remove_Directory();
			CreateDirectory(L"" OUTPUT_DIR, NULL);
			chdir(OUTPUT_DIR);
			FILE *f;
			long int file_size;
			char *tmp;
			clock_t t;
			try
			{
				switch (mode)
				{
				case 0:
				{
					this->radioButton2->Enabled = false;
					graphviz("Input.png", gr);
					strcpy(pbox1, "Input.png");
					pictureBox1->Image = Image::FromFile("Input.png");
					int iters;
					t = clock();
					if (ss)
						Ford("Ford.txt", gr, iters, vers[0] - 1, vers[1] - 1);
					else
						Ford("Ford.txt", gr, iters);
					t = clock() - t;
					time_ford = ((float)t)/CLOCKS_PER_SEC;

					if ((f = fopen("Ford.txt", "rb")) == NULL)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Ford.txt";
						e.solution = "Перезапустіть програму.";
						throw(e);
					}

					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					tmp = new char[file_size + 1];
					fread(tmp, file_size, 1, f);

					fclose(f);
					tmp[file_size] = '\0';
					richTextBox1->Text = gcnew String(tmp);
					ford_text = tmp;
					delete[] tmp;

					slides_ford = iters;
					c_slide = 1;
					chdir("../");
					delete_graph(gr);
					Change_Slide();

					break;
				}
				case 1:
				{

					if (gr->type)
					{
						gr->type = false;
						for (int i = 0; i < gr->n_edges; i++)
							gr->edges[i].orient = false;
					}

					graphviz("Input.png", gr);

					t = clock();
					Humori("Humori_result.txt", gr);
					t = clock() - t;
					time_humori = ((float)t) / CLOCKS_PER_SEC;

					if ((f = fopen("Humori_result.txt", "rb")) == NULL)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Humori_result.txt";
						throw(e);
					}
					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					tmp = new char[file_size + 1];
					fread(tmp, file_size, 1, f);

					if (fclose(f))
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо закрити файл Humori_result.txt";
						throw(e);
					}

					tmp[file_size] = '\0';
					this->richTextBox1->Text = gcnew String(tmp);
					humori_text = tmp;
					delete[] tmp;

					slides_humori = gr->n_vertexes - 1;
					c_slide = 1;
					half = -1;

					this->radioButton1->Checked = false;
					this->radioButton1->Enabled = false;
					this->radioButton2->Enabled = true;
					this->radioButton2->Checked = true;
					chdir("../");

					delete_graph(gr);
					Change_Slide();

					break;
				}
				case 2:
				{
					graphviz("Input.png", gr);
					int iters;

					t = clock();
					if (ss)
						Ford("Ford.txt", gr, iters, vers[0] - 1, vers[1] - 1);
					else
						Ford("Ford.txt", gr, iters);
					t = clock() - t;
					time_ford = ((float)t) / CLOCKS_PER_SEC;

					if ((f = fopen("Ford.txt", "rb")) == NULL)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Ford.txt";
						throw(e);
					}

					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					tmp = new char[file_size + 1];
					fread(tmp, file_size, 1, f);

					if (fclose(f))
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо закрити файл Ford.txt";
						throw(e);
					}

					tmp[file_size] = '\0';
					ford_text = tmp;
					delete[] tmp;

					slides_ford = iters;
					c_slide = 1;

					//
					// Humori
					//
					for (int i = 0; i < gr->n_edges; i++)
					{
						gr->edges[i].stream = 0;
						gr->edges[i].orient = false;
					}

					gr->type = false;

					t = clock();
					Humori("Humori_result.txt", gr);
					t = clock() - t;
					time_humori = ((float)t) / CLOCKS_PER_SEC;

					if ((f = fopen("Humori_result.txt", "rb")) == NULL)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Humori_result.txt";
						throw(e);
					}

					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					tmp = new char[file_size + 1];
					fread(tmp, file_size, 1, f);

					if (fclose(f))
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо закрити файл Humori_result.txt";
						throw(e);
					}

					tmp[file_size] = '\0';
					humori_text = tmp;
					delete[] tmp;

					slides_humori = gr->n_vertexes - 1;

					this->radioButton1->Checked = true;
					this->radioButton1->Enabled = true;
					this->radioButton2->Enabled = true;
					this->radioButton2->Checked = false;

					this->richTextBox1->Text = gcnew String(ford_text.c_str());
					chdir("../");
					delete_graph(gr);
					Change_Slide();
					break;
				}
				default:
				{
					T_exception e;
					e.code = 6;
					e.text = "Щось не так з вхідними параметрами.";
					throw(e);
					break;
				}
				}
			}
			catch (T_exception &e)
			{
				if(e.solution!="")
					MessageBox::Show(gcnew String(("Помилка: " + e.text + "\nМожливе рішення: " + e.solution).c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				else
					MessageBox::Show(gcnew String(("Помилка: " + e.text).c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				if (e.code != 5 && e.code != 7)
					delete_graph(gr);
				this->~MyForm_();
				chdir("../");
				return;
			}
			this->Show();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm_()
		{
			if (components)
			{
				delete components;
			}
			delete[] pbox1;
			delete[] pbox2;
		}


	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Label^  label4;

	private:
		/// <summary>
		/// </summary>
		int slides_ford;
		int slides_humori;
		int c_slide;
		int half;
		char *pbox1;
		char *pbox2;
		double time_ford;
		double time_humori;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton1->Location = System::Drawing::Point(17, 40);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(243, 24);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Алгоритм Форда-Фалкерсона";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->Click += gcnew System::EventHandler(this, &MyForm_::radioButton1_Click);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton2->Location = System::Drawing::Point(17, 65);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(174, 24);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->Text = L"Алгоритм Гуморі-Ху";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->Click += gcnew System::EventHandler(this, &MyForm_::radioButton2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Open Sans Light", 12));
			this->label1->Location = System::Drawing::Point(12, 10);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(298, 27);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Результати роботи алгоритмів";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->pictureBox1->Location = System::Drawing::Point(595, 59);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(414, 741);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm_::pictureBox1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(650, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(135, 20);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Введенний граф:";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Cursor = System::Windows::Forms::Cursors::SizeAll;
			this->pictureBox2->Location = System::Drawing::Point(12, 378);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(509, 422);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 6;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MyForm_::pictureBox2_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->richTextBox1->Location = System::Drawing::Point(12, 95);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(509, 203);
			this->richTextBox1->TabIndex = 7;
			this->richTextBox1->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(193, 352);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(51, 20);
			this->label3->TabIndex = 8;
			this->label3->Text = L"label3";
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(15, 339);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 33);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Назад";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm_::button1_Click);
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(96, 339);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 33);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Вперед";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm_::button2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(314, 44);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(51, 20);
			this->label4->TabIndex = 11;
			this->label4->Text = L"label4";
			// 
			// MyForm_
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1025, 812);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Font = (gcnew System::Drawing::Font(L"Open Sans", 9));
			this->Name = L"MyForm_";
			this->Text = L"Результати алгоритмів";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: bool Remove_Directory()
		{
			HANDLE hFind = INVALID_HANDLE_VALUE;
			WIN32_FIND_DATA f;
			
			hFind = FindFirstFile(OUTPUT_DIR L"/*", &f);
			if (hFind == INVALID_HANDLE_VALUE)
				return false;

			//_bstr_t b(f.cFileName);
			//char file_name[40];
			wstring ws;
			do
			{
				ws = f.cFileName;
				string tmp(ws.begin(), ws.end());
				tmp = OUTPUT_DIR "/" + tmp;
				remove(tmp.c_str());
				//DeleteFile(f.cFileName);
			}
			while ((FindNextFile(hFind, &f))!=0);

			FindClose(hFind);

			RemoveDirectory(L"" OUTPUT_DIR);

			return true;
		}
		private: System::Void radioButton1_Click(System::Object^  sender, System::EventArgs^  e) {
			half = -2;
			c_slide = 1;
			strcpy(pbox1, OUTPUT_DIR "/Input.png");
			this->pictureBox1->Image = Image::FromFile(OUTPUT_DIR "/Input.png");
			this->label2->Text = L"Введенний граф:";
			this->richTextBox1->Text = gcnew String(ford_text.c_str());

			char temp[100];
			char buf[10];

			sprintf(buf, "%f", time_ford);
			strcpy(temp, "Час роботи алгоритму: ");
			strcat(temp, buf);
			strcat(temp, "\nКількість ітерацій: ");
			itoa(slides_ford, buf, 10);
			strcat(temp, buf);
			this->label4->Text = gcnew String(temp);
			Change_Slide();
		}
		private: void Change_Slide()
		{
			char temp[100];
			char buf[4];
			if (this->radioButton1->Checked)
			{
				itoa(c_slide, buf, 10);
				strcpy(temp, OUTPUT_DIR "/Ford_Iteration_");
				strcat(temp, buf);
				strcat(temp, ".png");
				strcpy(pbox2, temp);
				this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
				strcpy(temp, buf);
				strcat(temp, " ітерація.");
				this->label3->Text = gcnew String(temp);
				return;
			}
			else
			{
				itoa(c_slide, buf, 10);
				strcpy(temp, OUTPUT_DIR "/Graph#");
				strcat(temp, buf);
				if (half == -1)
				{
					strcat(temp, ".png");
					strcpy(pbox2, temp);
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Граф на ");
					strcat(temp, buf);
					strcat(temp, " ітерації.");
					this->label3->Text = gcnew String(temp);
				}
				else if (half == 0)
				{
					strcat(temp, "_first_half.png");
					strcpy(pbox2, temp);
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Граф на ");
					strcat(temp, buf);
					strcat(temp, " ітерації. Перший сконденсований граф.");
					this->label3->Text = gcnew String(temp);
				}
				else if(half == 1)
				{
					strcat(temp, "_second_half.png");
					strcpy(pbox2, temp);
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Граф на ");
					strcat(temp, buf);
					strcat(temp, " ітерації. Другий сконденсований граф.");
					this->label3->Text = gcnew String(temp);
				}
				else if (half == 2)
				{
					strcpy(temp, OUTPUT_DIR "/Humori_result.png");
					strcpy(pbox2, temp);
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Кінцевий граф.");
					this->label3->Text = gcnew String(temp);
				}
				if (half != 2)
				{
					strcpy(temp, OUTPUT_DIR "/Humori_Graph_");
					strcat(temp, buf);
					strcat(temp, ".png");
					strcpy(pbox1, temp);
					this->pictureBox1->Image = Image::FromFile(gcnew String(temp));
					
					strcpy(temp, "Поточний вигляд результуючого графу:");
					this->label2->Text = gcnew String(temp);
				}
			}
		}
		private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			if (this->radioButton1->Checked)
			{
				c_slide++;
				if (c_slide > slides_ford)
					c_slide = 1;
			
				Change_Slide();
			}
			else
			{
				if (half == 2)
				{
					half = -1;
					c_slide = 1;
					Change_Slide();
					return;
				}

				half++;
				if (half > 1)
					half = -1;
				else
				{
					Change_Slide();
					return;
				}

				c_slide++;
				if (c_slide > slides_humori)
				{
					half = 2;
				}
			
				Change_Slide();
			}
		}
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			if (this->radioButton1->Checked)
			{
				c_slide--;
				if (c_slide < 1)
					c_slide = slides_ford;

				Change_Slide();
			}
			else
			{
				if (half == 2)
				{
					c_slide = slides_humori;
					half = 1;
					Change_Slide();
					return;
				}

				half--;
				if (half < -1)
					half = 1;
				else
				{
					Change_Slide();
					return;
				}

				c_slide--;
				if (c_slide < 1)
				{
					half = 2;
				}
			
				Change_Slide();
			}
		}
		private: System::Void radioButton2_Click(System::Object^  sender, System::EventArgs^  e) {
			half = -1;
			c_slide = 1;
			this->richTextBox1->Text = gcnew String(humori_text.c_str());

			char temp[100];
			char buf[10];

			sprintf(buf, "%f", time_humori);
			strcpy(temp, "Час роботи алгоритму: ");
			strcat(temp, buf);
			strcat(temp, "\nКількість ітерацій: ");
			itoa(slides_humori, buf, 10);
			strcat(temp, buf);
			this->label4->Text = gcnew String(temp);
			Change_Slide();
			
		}
		private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
			Course_work_froms_v1::PictureForm^ Pictform = gcnew PictureForm(pbox2);
			Pictform->Show();
		}
		private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			Course_work_froms_v1::PictureForm^ Pictform = gcnew PictureForm(pbox1);
			Pictform->Show();
		}
};
}
