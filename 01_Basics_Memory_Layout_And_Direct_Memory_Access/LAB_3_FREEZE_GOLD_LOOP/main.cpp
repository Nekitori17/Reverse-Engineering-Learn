#include <iostream>
#include <windows.h>

int main() {
  DWORD pid;
  uintptr_t gold_address;
  
  std::cout << "Enter Process ID:";
  std::cin >> pid;

  std::cout << "Enter Gold Adress:";
  std::cin >> std::hex >> gold_address;

  std::cin >> std::dec;

  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

  if (hProcess != NULL) {
    int newGold = 999999;

    while (true) {
      WriteProcessMemory(hProcess, (LPVOID)gold_address, &newGold,
                         sizeof(newGold), NULL);

      Sleep(100);
    }
  }

  return 0;
}