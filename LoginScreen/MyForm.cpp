#include "MyForm.h"
#include "string.h"
#include "additionalFunc.h"
#include "UnitTest.h"
using namespace std;
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int LogScreen() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LoginScreen::LoginScreen form;
	Application::Run(%form);
	return 0;
}
int main() {
	UnitTest();
	LogScreen();
	return 0;
}
