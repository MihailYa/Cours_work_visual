#include "MyForm.h"
#include <string.h>
using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Course_work_froms_v1::MyForm form;

	Application::Run(%form);
}
