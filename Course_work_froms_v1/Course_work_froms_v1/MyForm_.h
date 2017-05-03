#pragma once
#include "Humori.hpp"
#include "Ford.hpp"
#include "stdafx.hpp"
#include "list.hpp"

#define OUTPUT_DIR "output"

static T_list *Ford_head;
static T_list *Ford_tail;
static T_list *Humori_head;
static T_list *Humori_tail;
static std::string ford_text;
static std::string humori_text;

namespace Course_work_froms_v1 {

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
		* @mode 0 - Ford, 1 - Humori, 2 - both
		* @gr pointer on graph
		*/
		MyForm_(int mode, graph *&gr, int vers[2], bool ss)
		{
			InitializeComponent();

			CreateDirectory(L"" OUTPUT_DIR, NULL);
			chdir(OUTPUT_DIR);
			

			switch (mode)
			{
			case 0:
			{
				this->radioButton2->Enabled = false;
				graphviz("Input.png", gr);
				pictureBox1->Image = Image::FromFile("Input.png");
				int iters;
				if (ss)
					Ford("Ford.txt", gr, iters, vers[0]-1, vers[1]-1);
				else
					Ford("Ford.txt", gr, iters);
				FILE *f;
				if ((f = fopen("Ford.txt", "rb")) == NULL)
				{
					exit(1);
				}
				long int file_size;
				fseek(f, 0, SEEK_END);
				file_size = ftell(f);
				rewind(f);

				char *tmp = new char[file_size+1];
				fread(tmp, file_size, 1, f);

				fclose(f);
				tmp[file_size] = '\0';
				this->richTextBox1->Text = gcnew String(tmp);
				delete[] tmp;

				slides_ford = iters;
				c_slide = 1;
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
				pictureBox1->Image = Image::FromFile("Input.png");

				Humori("Humori_result.txt", gr);

				slides_humori = gr->n_vertexes - 1;
				c_slide = 1;
				half = -1;

				this->radioButton1->Checked = false;
				this->radioButton1->Enabled = false;
				this->radioButton2->Enabled = true;
				this->radioButton2->Checked = true;
				Change_Slide();

				break;
			}
			case 2:
			{

				break;
			}
			default:
			{
				exit(1);
				break;
			}
			}
			delete_graph(gr);
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

			free_list(Ford_head, Ford_tail);
			free_list(Humori_head, Humori_tail);
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
	
	protected:

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// </summary>
		int slides_ford;
		int slides_humori;
		int c_slide;
		int half;


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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(12, 40);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(228, 21);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Алгоритм Форда-Фалкерсона";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->Click += gcnew System::EventHandler(this, &MyForm_::radioButton1_Click);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(12, 68);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(159, 21);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->Text = L"Алгоритм Гуморі-Ху";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->Click += gcnew System::EventHandler(this, &MyForm_::radioButton2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(210, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Результати роботи алгоритмів";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(595, 59);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(414, 741);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(650, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(120, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Введенний граф:";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(12, 378);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(509, 422);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 6;
			this->pictureBox2->TabStop = false;
			// 
			// richTextBox1
			// 
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
			this->label3->Size = System::Drawing::Size(46, 17);
			this->label3->TabIndex = 8;
			this->label3->Text = L"label3";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(15, 349);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 9;
			this->button1->Text = L"Назад";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm_::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(96, 349);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Вперед";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm_::button2_Click);
			// 
			// MyForm_
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1025, 812);
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
			this->Name = L"MyForm_";
			this->Text = L"Результати алгоритмів";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void radioButton1_Click(System::Object^  sender, System::EventArgs^  e) {
			half = -2;
			c_slide = 1;
			Change_Slide();
		}
		private: void Change_Slide()
		{
			char temp[100];
			char buf[4];
			if (this->radioButton1->Checked)
			{
				itoa(c_slide, buf, 10);
				strcpy(temp, "Ford_Iteration_");
				strcat(temp, buf);
				strcat(temp, ".png");
				this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
				strcpy(temp, buf);
				strcat(temp, " ітерація.");
				this->label3->Text = gcnew String(temp);
				return;
			}
			else
			{
				itoa(c_slide, buf, 10);
				strcpy(temp, "Graph#");
				strcat(temp, buf);
				if (half == -1)
				{
					strcat(temp, ".png");
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Граф на ");
					strcat(temp, buf);
					strcat(temp, " ітерації.");
					this->label3->Text = gcnew String(temp);
					return;
				}
				else if (half == 0)
				{
					strcat(temp, "_first_half.png");
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Граф на ");
					strcat(temp, buf);
					strcat(temp, " ітерації. Перший сконденсований граф.");
					this->label3->Text = gcnew String(temp);
					return;
				}
				else if(half == 1)
				{
					strcat(temp, "_second_half.png");
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Граф на ");
					strcat(temp, buf);
					strcat(temp, " ітерації. Другий сконденсований граф.");
					this->label3->Text = gcnew String(temp);
					return;
				}
				else if (half == 2)
				{
					strcpy(temp, "Humori_result.png");
					this->pictureBox2->Image = Image::FromFile(gcnew String(temp));
					strcpy(temp, "Кінцевий граф.");
					this->label3->Text = gcnew String(temp);
					return;
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
				c_slide = 0;
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
				c_slide = 1;
				half = 2;
			}
			
			Change_Slide();
		}
	}

	private: System::Void radioButton2_Click(System::Object^  sender, System::EventArgs^  e) {
		half = -1;
		c_slide = 1;
	}
};
}
