#include "MyForm.h"
#include <string.h>

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	coursework::MyForm form;

	Application::Run(%form);
}
