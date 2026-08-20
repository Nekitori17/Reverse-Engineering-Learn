#include <iostream>
#include <windows.h>

int main() {
  DWORD pid;
  std::cout << "Enter Process ID:";
  std::cin >> pid;

  uintptr_t funcAddr;
  std::cout << "Enter Function Address:";
  std::cin >> std::hex >> funcAddr;

  std::cin >> std::dec;

  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  if (hProcess == NULL) {
    std::cout << "Fail to open process: " << GetLastError();
    return 0;
  }

  uintptr_t subAddress = funcAddr + 0x11;
  unsigned char oldByteCode[3];
  unsigned char newByteCode[3] = {0x90, 0x90, 0x90};

  DWORD oldProtect;

  ReadProcessMemory(hProcess, (LPVOID)subAddress, &oldByteCode,
                    sizeof(oldByteCode), NULL);

  bool godMode = false;
  while (true) {
    system("cls");
    std::cout << "- God Mode -" << "\n";
    std::cout << "Active: " << (godMode ? "On" : "Off") << "\n";
    std::cout << "[E] Enable GodMode" << "\n";
    std::cout << "[D] Disable GodMode" << "\n";
    std::cout << "[0] Exit" << "\n";
    std::cout << "Choice: ";

    char choice;
    if (!(std::cin >> choice)) {
      continue;
    }

    if (choice == '0')
      break;

    VirtualProtectEx(hProcess, (LPVOID)subAddress, sizeof(newByteCode),
                     PAGE_EXECUTE_READWRITE, &oldProtect);

    if (choice == 'E' || choice == 'e') {
      godMode = true;
      WriteProcessMemory(hProcess, (LPVOID)subAddress, &newByteCode,
                         sizeof(newByteCode), NULL);
    }

    if (choice == 'D' || choice == 'd') {
      godMode = false;
      WriteProcessMemory(hProcess, (LPVOID)subAddress, &oldByteCode,
                         sizeof(oldByteCode), NULL);
    }

    VirtualProtectEx(hProcess, (LPVOID)subAddress, sizeof(newByteCode),
                     oldProtect, &oldProtect);
  }

  CloseHandle(hProcess);
  return 0;
}