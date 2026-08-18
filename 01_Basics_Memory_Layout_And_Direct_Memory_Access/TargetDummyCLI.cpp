#include <iostream>
#include <windows.h>


// Struct đại diện cho thực thể trong game (Nằm trên Heap)
struct PlayerEntity {
  int hp;
  int max_hp;
  int mp;
  int gold;
};

// Biến toàn cục nằm trên .data segment (Static Memory)
int g_GameTick = 0;
int g_ServerDifficulty = 1;

void PrintMenu() {
  std::cout << "\n========================================\n";
  std::cout << "[1] Nhan sat thuong (-15 HP)\n";
  std::cout << "[2] Nhat tien (+50 Gold)\n";
  std::cout << "[3] Su dung ky nang (-10 MP)\n";
  std::cout << "[0] Thoat Game\n";
  std::cout << "Lua chon: ";
}

int main() {
  // Đặt tiêu đề console
  SetConsoleTitleA("TargetDummy_CLI_v1");

  DWORD pid = GetCurrentProcessId();

  // Khởi tạo Player trên Heap
  PlayerEntity *player = new PlayerEntity{100, 100, 50, 0};

  while (true) {
    system("cls");
    g_GameTick++;

    std::cout << "=== DUMMY TARGET GAME CLI (RE LAB 01) ===\n";
    std::cout << "Process ID (PID)      : " << pid << "\n\n";

    std::cout << "[!] THONG TIN DIA CHI (DEBUG HINT):\n";
    std::cout << "  - [Static Global] &g_GameTick : 0x" << std::hex
              << (uintptr_t)&g_GameTick << "\n";
    std::cout << "  - [Heap Pointer]  player      : 0x" << std::hex
              << (uintptr_t)player << "\n";
    std::cout << "  - [Heap Offset]   &player->hp : 0x" << std::hex
              << (uintptr_t)&(player->hp) << "\n";
    std::cout << "  - [Heap Offset]   &player->gold: 0x" << std::hex
              << (uintptr_t)&(player->gold) << "\n";
    std::cout << std::dec; // Trả về định dạng thập phân

    std::cout << "\n[STATUS NGUOI CHOI]:\n";
    std::cout << "  Tick       : " << g_GameTick << "\n";
    std::cout << "  HP         : " << player->hp << " / " << player->max_hp
              << "\n";
    std::cout << "  MP         : " << player->mp << "\n";
    std::cout << "  Gold       : " << player->gold << "\n";

    PrintMenu();
    int choice;
    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    if (choice == 0)
      break;
    switch (choice) {
    case 1:
      player->hp -= 15;
      if (player->hp < 0)
        player->hp = 0;
      break;
    case 2:
      player->gold += 50;
      break;
    case 3:
      if (player->mp >= 10)
        player->mp -= 10;
      break;
    default:
      break;
    }
  }

  delete player;
  return 0;
}