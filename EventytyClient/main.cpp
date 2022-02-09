#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <conio.h>
using namespace std;

HWND hwnd;
DWORD procID;
HANDLE hProcess;

uintptr_t ModuleBase;
uintptr_t PlayerBase;

uintptr_t GetModuleBaseAddress(const char* modName) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, modName)) {
                    CloseHandle(hSnap);
                    return (uintptr_t)modEntry.modBaseAddr;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}

float speed = 4;
bool speedd = false;

int main() {
	SetConsoleTitle("Eventyty Client");

    hwnd = FindWindow(0, "doom.exe");
    string appname = "doom.exe";
	
    if (hwnd == NULL) {
        cout << "[-] Please Open DOOM" << endl;
        Sleep(1000);
        return 0;
    }
    
    cout << "[+] Process doom.exe is Opened\n" << endl;

    procID = 0;
    GetWindowThreadProcessId(hwnd, &procID);

    if (procID == 0) {
        cout << "\n\n [-] Process ID not Found" << endl;
        return 0;
    }
    
    ModuleBase = GetModuleBaseAddress("GameAssembly.dll");
    
    int choice;
    do {
		system("color C");
		cout << "[1] Speed Hack" << endl;
		cout << "Enter Value\n";
		cin >> choice;
	
		//Functions
		switch(choice) {
		case 1:
			speedd = !speedd;
				if (speedd) {
					system("cls");
					cout << "\n\n[+] Speed Hack Enabled\n\n";
					
					uintptr_t dynamicptrbaseaddr = ModuleBase + 0x2C616F8;
    				std::vector<unsigned int> offset (0x534);

  					uintptr_t myAddr = FindDMAAddy(hProcess, dynamicptrbaseaddr, offset);

   					 WriteProcessMemory(hProcess, (LPVOID)myAddr, &speed, sizeof(speed), 0);
				} else {
					system("cls");
					cout << "\n\n[-] Speed Hack Disabled\n\n";
				}
			break;
		 }
	  } while (choice != 2); // you max value on last case ( add for you value +1)
}
