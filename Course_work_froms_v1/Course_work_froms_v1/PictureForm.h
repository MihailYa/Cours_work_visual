#pragma once

namespace coursework {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PictureForm
	/// </summary>
	public ref class PictureForm : public System::Windows::Forms::Form
	{
	public:
		PictureForm(char *picture_name)
		{
			InitializeComponent();
			try
			{
				this->pictureBox1->Image = Image::FromFile(gcnew String(picture_name));
			}
			catch (System::IO::FileNotFoundException^ e)
			{
				MessageBox::Show(gcnew String("Помилка: не можливо відкрити зображення.\nМожливе рішення: перезапустіть программу."), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				this->~PictureForm();
				return;
			}
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PictureForm()
		{
			if (components)
			{
				delete components;
			}

			if (this->pictureBox1->Image != nullptr)
			{
				delete this->pictureBox1->Image;
				this->pictureBox1->Image = nullptr;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(938, 697);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// PictureForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(962, 721);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"PictureForm";
			this->Text = L"Picture";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
