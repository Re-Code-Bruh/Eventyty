#include <cstdlib>
#include <windows.h>
using namespace std;

int choice;


void AddButton(string text)
{
	cout << "      " << text << endl;
}

void AddInput(string text)
{
	cout << "      " << text << ": ";
	cin >> choice;
}

void AddText(string text)
{
	system("cls");
	cout << endl << "      "  << text << endl << endl;
}
