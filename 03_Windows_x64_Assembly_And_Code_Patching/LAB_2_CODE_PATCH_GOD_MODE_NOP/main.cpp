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
  unsigned char newByteCode[3] = {0x90, 0x90, 0x90};

  DWORD oldProtect;
  VirtualProtectEx(hProcess, (LPVOID)subAddress, sizeof(newByteCode),
                   PAGE_EXECUTE_READWRITE, &oldProtect);

  WriteProcessMemory(hProcess, (LPVOID)subAddress, &newByteCode,
                     sizeof(newByteCode), NULL);

  VirtualProtectEx(hProcess, (LPVOID)subAddress, sizeof(newByteCode),
                   oldProtect, &oldProtect);

  CloseHandle(hProcess);
  return 0;
}