#include <iostream>
#include <windows.h>

int main() {
  DWORD pid;
  std::cout << "Enter Process ID:";
  std::cin >> pid;

  std::cout << "Enter Player HP Address:";
  uintptr_t hp_address;
  std::cin >> std::hex >> hp_address;

  std::cin >> std::dec;

  HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  if (process != NULL) {
    int currentHP = 0;

    ReadProcessMemory(process, (LPCVOID)hp_address, &currentHP,
                      sizeof(currentHP), NULL);

    int newHP = 0;
    std::cout << "Enter Player HP:";
    std::cin >> newHP;

    WriteProcessMemory(process, (LPVOID)hp_address, &newHP, sizeof(newHP), NULL);

    std::cout << currentHP;
  }

  CloseHandle(process);

  return 0;
}