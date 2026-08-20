#include <iostream>
#include <windows.h>

struct Player {
  int hp;
  int max_hp;
};

// Tắt tối ưu hóa inline để đảm bảo hàm tồn tại độc lập trong .text
#pragma optimize("", off)
void TakeDamage(Player *p, int damage) {
  p->hp -= damage;
  if (p->hp < 0)
    p->hp = 0;
}
#pragma optimize("", on)

int main() {
  SetConsoleTitleA("TargetDummy_CLI_v3");
  DWORD pid = GetCurrentProcessId();

  Player hero{100, 100};
  uintptr_t funcAddr = (uintptr_t)&TakeDamage;

  while (true) {
    system("cls");
    std::cout << "=== DUMMY TARGET GAME v3 (ASSEMBLY & CODE PATCHING) ===\n";
    std::cout << "PID: " << pid << "\n";
    std::cout << "Address of TakeDamage(): 0x" << std::hex << funcAddr
              << "\n\n";

    std::cout << "[TakeDamage() First 16 Machine Bytes]:\n";
    unsigned char *codeBytes = (unsigned char *)funcAddr;
    for (int i = 0; i < 64; i++) {
      printf("%02X ", codeBytes[i]);
    }
    std::cout << std::dec << "\n\n";

    std::cout << "[STATUS]:\n";
    std::cout << "  Player HP: " << hero.hp << " / " << hero.max_hp << "\n\n";

    std::cout << "[1] Goi TakeDamage(&hero, 20)\n";
    std::cout << "[2] Hoi day mau (+100 HP)\n";
    std::cout << "[0] Thoat\n";
    std::cout << "Lua chon: ";

    int choice;
    if (!(std::cin >> choice))
      break;
    if (choice == 0)
      break;

    if (choice == 1) {
      TakeDamage(&hero, 20);
    } else if (choice == 2) {
      hero.hp = hero.max_hp;
    }
  }

  return 0;
}