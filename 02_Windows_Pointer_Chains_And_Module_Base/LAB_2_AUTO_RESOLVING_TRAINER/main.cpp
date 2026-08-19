#include <iostream>
#include <windows.h>

int main() {
  DWORD pid;
  std::cout << "Enter Process ID: ";
  std::cin >> pid;

  uintptr_t g_GameManagerPtr_ptr;
  std::cout << "Enter &g_GameManager Staic Address: ";
  std::cin >> std::hex >> g_GameManagerPtr_ptr;

  std::cin >> std::dec;

  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  if (hProcess == NULL) {
    std::cout << "Can't Open Process With Error: " << GetLastError();
    return 0;
  }

  while (true) {
    system("cls");
    uintptr_t current_ptr;

    ReadProcessMemory(hProcess, (LPCVOID)g_GameManagerPtr_ptr, &current_ptr,
    sizeof(current_ptr), NULL);
    
    uintptr_t local_playerPtr_ptr = current_ptr + 0x08;
    ReadProcessMemory(hProcess, (LPCVOID)local_playerPtr_ptr, &current_ptr,
                      sizeof(current_ptr), NULL);

    uintptr_t statsPtr_ptr = current_ptr + 0x20;

    ReadProcessMemory(hProcess, (LPCVOID)statsPtr_ptr, &current_ptr,
                      sizeof(current_ptr), NULL);

    uintptr_t hp_ptr = current_ptr + 0x0;
    uintptr_t gold_ptr = current_ptr + 0x0C;
    int hp = 0;
    int gold = 0;

    ReadProcessMemory(hProcess, (LPCVOID)hp_ptr, &hp,
                      sizeof(hp), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)gold_ptr, &gold,
                      sizeof(gold), NULL);

    std::cout << "HP - 0x" << std::hex << hp_ptr << ": " << std::dec << hp << "\n";
    std::cout << "Gold - 0x" << std::hex << gold_ptr << ": " << std::dec << gold << "\n";

    Sleep(1000);
  }

  return 0;
}