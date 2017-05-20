#pragma once
#include "Gomory.hpp"
#include "Ford.hpp"
#include "stdafx.hpp"
#include "PictureForm.h"

// Directory for output
#define OUTPUT_DIR "output"

static std::string ford_text;	// Result text of Ford-Fulkerson algorithm
static std::string Gomory_text;	// Result text of Gomory-Hu algorithm

namespace coursework {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm_
	/// </summary>
	public ref class MyForm_ : public System::Windows::Forms::Form
	{
	public:
		/**
		* Constructor
		* @param mode 0 - Ford, 1 - Gomory, 2 - both
		* @param gr pointer on graph
		*/
		MyForm_(int mode, graph *&gr, int vers[2], bool ss)
		{
			InitializeComponent();
			pbox1 = new char[100];
			pbox2 = new char[100];
			
			try
			{
				Remove_Directory();
				if (!CreateDirectory(L"" OUTPUT_DIR, NULL))
				{
					T_exception e;
					e.text = "Не можливо створити директорію " OUTPUT_DIR;
					e.code = 9;
					throw(e);
				}

				chdir(OUTPUT_DIR);
				FILE *f = nullptr;
				long int file_size;
				char *tmp = nullptr;
				clock_t t;
			
				switch (mode)
				{
				case 0:
				{
					// Draw input graph
					graphviz("Input.png", gr);

					int iters;

					// Start Ford-Fulkerson algorithm
					t = clock();
					if (ss)
						Ford("Ford.txt", gr, iters, vers[0] - 1, vers[1] - 1);
					else
						Ford("Ford.txt", gr, iters);

					t = clock() - t;
					time_ford = ((float)t)/CLOCKS_PER_SEC;

					if ((f = fopen("Ford.txt", "rb")) == nullptr)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Ford.txt";
						e.solution = "Перезапустіть програму.";
						throw(e);
					}

					// Get size of file
					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					// Read
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

					// Free memory
					delete_graph(gr);

					// Change slider
					strcpy(pbox1, OUTPUT_DIR "/Input.png");
					this->pictureBox1->Image = Image::FromFile(OUTPUT_DIR "/Input.png");
					this->radioButton2->Enabled = false;
					this->radioButton1->Checked = true;
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

					// Draw graph
					graphviz("Input.png", gr);

					// Start Gomory-Hu algorithm
					t = clock();
					Gomory("Gomory_result.txt", gr);
					t = clock() - t;
					time_Gomory = ((float)t) / CLOCKS_PER_SEC;

					if ((f = fopen("Gomory_result.txt", "rb")) == nullptr)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Gomory_result.txt";
						throw(e);
					}

					// Get size of file
					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					tmp = new char[file_size + 1];
					fread(tmp, file_size, 1, f);

					if (fclose(f))
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо закрити файл Gomory_result.txt";
						throw(e);
					}

					tmp[file_size] = '\0';
					this->richTextBox1->Text = gcnew String(tmp);
					Gomory_text = tmp;
					delete[] tmp;

					// Calculate number of slides
					slides_Gomory = gr->n_vertexes - 1;
					c_slide = 1;
					half = -1;

					this->radioButton1->Enabled = false;
					this->radioButton2->Checked = true;
					chdir("../");

					// Free memory from graph
					delete_graph(gr);

					// Change slide
					Change_Slide();

					break;
				}
				case 2:
				{
					// Draw graph
					graphviz("Input.png", gr);
					int iters;

					//
					// Start Ford-Fulkerson algorithm
					//
					t = clock();
					if (ss)
						Ford("Ford.txt", gr, iters, vers[0] - 1, vers[1] - 1);
					else
						Ford("Ford.txt", gr, iters);
					t = clock() - t;
					time_ford = ((float)t) / CLOCKS_PER_SEC;

					if ((f = fopen("Ford.txt", "rb")) == nullptr)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Ford.txt";
						throw(e);
					}

					// Get size of file
					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					// Read file
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

					// Calculate number of slides
					slides_ford = iters;
					c_slide = 1;

					//
					// Gomory-Hu algorithm
					//

					// Rewind graph
					for (int i = 0; i < gr->n_edges; i++)
					{
						gr->edges[i].stream = 0;
						gr->edges[i].orient = false;
					}

					gr->type = false;

					// Start Gomory-Hu algorithm
					t = clock();
					Gomory("Gomory_result.txt", gr);
					t = clock() - t;
					time_Gomory = ((float)t) / CLOCKS_PER_SEC;

					if ((f = fopen("Gomory_result.txt", "rb")) == nullptr)
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо відкрити файл Gomory_result.txt";
						throw(e);
					}

					// Get size of file
					fseek(f, 0, SEEK_END);
					file_size = ftell(f);
					rewind(f);

					// Read file
					tmp = new char[file_size + 1];
					fread(tmp, file_size, 1, f);

					if (fclose(f))
					{
						T_exception e;
						e.code = 1;
						e.text = "Не можливо закрити файл Gomory_result.txt";
						throw(e);
					}

					tmp[file_size] = '\0';
					Gomory_text = tmp;
					delete[] tmp;

					// Calculate number of slides
					slides_Gomory = gr->n_vertexes - 1;

					this->radioButton1->Checked = true;

					this->richTextBox1->Text = gcnew String(ford_text.c_str());
					chdir("../");

					// Free memory
					delete_graph(gr);

					// Change slide
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
				delete_graph(gr);
				this->~MyForm_();
				if (e.code != 9)
					chdir("../");
				return;
			}
			this->Show();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm_()
		{
			
			if (this->pictureBox2->Image != nullptr)
			{
				img = this->pictureBox2->Image;
				this->pictureBox2->Image = nullptr;
				delete img;
				img = nullptr;
			}
			if (this->pictureBox1->Image != nullptr)
			{
				img = this->pictureBox1->Image;
				this->pictureBox1->Image = nullptr;
				delete img;
				img = nullptr;
			}
			
			if (pbox1 != nullptr)
			{
				delete[] pbox1;
				pbox1 = nullptr;
			}
			if (pbox2 != nullptr)
			{
				delete[] pbox2;
				pbox2 = nullptr;
			}
			if (components)
			{
				delete components;
			}
			
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
		System::Drawing::Image^ img;
		int slides_ford;	// Number of slides of Ford-Fulkerson algorithm
		int slides_Gomory;	// Number of slides of Gomory-Hu algorithm 
		int c_slide;		// Current slide
		int half;			// Condensed half (for Gomory-Hu slider)
		char *pbox1;		// Way to image of picturebox1
		char *pbox2;		// Way to image of picturebox2
		double time_ford;	// Time of Ford-Fulkerson algorithm
		double time_Gomory;	// Time of Gomory-Hu algorithm

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
			this->radioButton1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton1->Location = System::Drawing::Point(17, 40);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(243, 24);
			this->radioButton1->TabIndex = 0;
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
		// Delete directory function
		private: bool Remove_Directory()
		{
			HANDLE hFind = INVALID_HANDLE_VALUE;
			WIN32_FIND_DATAW f;
			
			hFind = FindFirstFileW(OUTPUT_DIR L"/*.*", &f);
			if (hFind == INVALID_HANDLE_VALUE)
				return false;

			FILE *file_;

			std::wstring ws;
			do
			{
				ws = f.cFileName;
				if (!DeleteFileW((std::wstring(L"" OUTPUT_DIR "/") + f.cFileName).c_str()) && _wcsicmp(f.cFileName, L".") && _wcsicmp(f.cFileName, L".."))
				{
					T_exception e;
					e.code = 9;
					e.text = "Не можливо видалити файл з дерикторії " OUTPUT_DIR;
					throw(e);
				}
				
			}
			while ((FindNextFileW(hFind, &f))!=0);

			FindClose(hFind);

			RemoveDirectoryW(L"" OUTPUT_DIR);

			return true;
		}

		// Gomory-Hu
		private: System::Void radioButton1_Click(System::Object^  sender, System::EventArgs^  e) {
			
			strcpy(pbox1, OUTPUT_DIR "/Input.png");
			if (this->pictureBox1->Image != nullptr)
			{
				img = this->pictureBox1->Image;
				this->pictureBox1->Image = nullptr;
				delete img;
				img = nullptr;
			}
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

			if (slides_ford == 0)
			{
				this->label3->Text = L"";
				if (this->pictureBox2->Image != nullptr)
				{
					img = this->pictureBox2->Image;
					this->pictureBox2->Image = nullptr;
					delete img;
					img = nullptr;
				}
				return;
			}

			half = -2;
			c_slide = 1;
			Change_Slide();
		}

		// Change slide function
		private: void Change_Slide()
		{
			char temp[100];
			try
			{
				if (this->radioButton1->Checked)
				{
					if (slides_ford == 0)
						return;
					// Ford slide
					sprintf(temp, OUTPUT_DIR "/Ford_Iteration_%d.png", c_slide);
					strcpy(pbox2, temp);
					if (this->pictureBox2->Image != nullptr)
					{
						img = this->pictureBox2->Image;
						this->pictureBox2->Image = nullptr;
						delete img;
						img = nullptr;
					}
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					sprintf(temp, "%d ітерація.", c_slide);
					this->label3->Text = gcnew String(temp);
					return;
				}
				else
				{
					if (slides_Gomory == 0)
						return;
					// Humori slide
					sprintf(temp, OUTPUT_DIR "/Graph#%d", c_slide);
					if (half == -1)
					{
						strcat(temp, ".png");
						strcpy(pbox2, temp);
						if (this->pictureBox2->Image != nullptr)
						{
							img = this->pictureBox2->Image;
							this->pictureBox2->Image = nullptr;
							delete img;
							img = nullptr;
						}
						this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
						sprintf(temp, "Граф на %d ітерації.", c_slide);
						this->label3->Text = gcnew String(temp);
					}
					else if (half == 0)
					{
						strcat(temp, "_first_half.png");
						strcpy(pbox2, temp);
						if (this->pictureBox2->Image != nullptr)
						{
							img = this->pictureBox2->Image;
							this->pictureBox2->Image = nullptr;
							delete img;
							img = nullptr;
						}
						this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
						sprintf(temp, "Граф на %d ітерації. Перший сконденсований граф.", c_slide);
						this->label3->Text = gcnew String(temp);
					}
					else if (half == 1)
					{
						strcat(temp, "_second_half.png");
						strcpy(pbox2, temp);
						if (this->pictureBox2->Image != nullptr)
						{
							img = this->pictureBox2->Image;
							this->pictureBox2->Image = nullptr;
							delete img;
							img = nullptr;
						}
						this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
						sprintf(temp, "Граф на %d ітерації. Другий сконденсований граф.", c_slide);
						this->label3->Text = gcnew String(temp);
					}
					else if (half == 2)
					{
						strcpy(temp, OUTPUT_DIR "/Gomory_result.png");
						strcpy(pbox2, temp);
						if (this->pictureBox2->Image !=nullptr)
						{
							img = this->pictureBox2->Image;
							this->pictureBox2->Image = nullptr;
							delete img;
							img = nullptr;
						}
						this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
						strcpy(temp, "Кінцевий граф.");
						this->label3->Text = gcnew String(temp);
					}
					if (half != 2)
					{
						sprintf(temp, OUTPUT_DIR "/Gomory_Graph_%d.png", c_slide);
						strcpy(pbox1, temp);
						if (this->pictureBox1->Image != nullptr)
						{
							img = this->pictureBox1->Image;
							this->pictureBox1->Image = nullptr;
							delete img;
							img = nullptr;
						}
						this->pictureBox1->Image = Image::FromFile(gcnew String(temp));

						strcpy(temp, "Поточний вигляд результуючого графу:");
						this->label2->Text = gcnew String(temp);
					}
				}
			}
			catch (System::IO::FileNotFoundException^ e)
			{
				MessageBox::Show(gcnew String("Помилка: не можливо відкрити зображення.\nМожливе рішення: перезапустіть программу."), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				this->~MyForm_();
				chdir("../");
				return;
			}
		}

		// Next slide function
		private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			if (this->radioButton1->Checked)
			{
				if (slides_ford == 0)
					return;

				c_slide++;
				if (c_slide > slides_ford)
					c_slide = 1;
			
				Change_Slide();
			}
			else
			{
				if (slides_Gomory == 0)
					return;

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
				if (c_slide > slides_Gomory)
				{
					half = 2;
				}
			
				Change_Slide();
			}
		}

		// Previous slide function
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
					c_slide = slides_Gomory;
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

		// Ford-Fulkerson
		private: System::Void radioButton2_Click(System::Object^  sender, System::EventArgs^  e) {
			if (slides_Gomory == 0)
			{
				this->label3->Text = L"";
				return;
			}
			half = -1;
			c_slide = 1;
			this->richTextBox1->Text = gcnew String(Gomory_text.c_str());

			char temp[100];
			char buf[10];

			sprintf(buf, "%f", time_Gomory);
			sprintf(temp, "Час роботи алгоритму: %f\nКількість ітерацій: %d", time_Gomory, slides_Gomory);
			this->label4->Text = gcnew String(temp);
			Change_Slide();
			
		}

		// Show maximized image
		private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
			coursework::PictureForm^ Pictform = gcnew PictureForm(pbox2);
			Pictform->Show();
		}
		private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			coursework::PictureForm^ Pictform = gcnew PictureForm(pbox1);
			Pictform->Show();
		}
};
}
