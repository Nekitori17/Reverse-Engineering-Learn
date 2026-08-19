#include <iostream>
#include <windows.h>

struct Stats {
  int hp;
  int max_hp;
  int mp;
  int gold;
};

struct Player {
  char name[32];
  Stats *stats; // Pointer cấp 2
};

struct GameManager {
  int game_state;
  Player *local_player; // Pointer cấp 1
};

// Biến toàn cục tĩnh nằm trên Data Segment
// relative offset của biến này so với Base Address của exe là CỐ ĐỊNH!
GameManager *g_GameManager = nullptr;

void InitGame() {
  if (g_GameManager == nullptr) {
    g_GameManager = new GameManager();
  }
  if (g_GameManager->local_player) {
    delete g_GameManager->local_player->stats;
    delete g_GameManager->local_player;
  }

  // Cấp phát động mới
  g_GameManager->game_state = 1; // 1 = In Game
  g_GameManager->local_player = new Player();
  strcpy_s(g_GameManager->local_player->name, "Hero");
  g_GameManager->local_player->stats = new Stats{100, 100, 50, 0};
}

int main() {
  SetConsoleTitleA("TargetDummy_CLI_v2");
  InitGame();
  DWORD pid = GetCurrentProcessId();
  uintptr_t baseAddress = (uintptr_t)GetModuleHandle(NULL);

  while (true) {
    system("cls");
    std::cout << "=== DUMMY TARGET GAME v2 (POINTER CHAINS) ===\n";
    std::cout << "PID: " << pid << " | Module Base: 0x" << std::hex
              << baseAddress << "\n\n";

    std::cout << "[POINTER ARCHITECTURE]:\n";
    std::cout << "1. Base Address              : 0x" << baseAddress << "\n";
    std::cout << "2. Static Pointer &g_Manager : 0x"
              << (uintptr_t)&g_GameManager << " (Offset from Base: +0x"
              << ((uintptr_t)&g_GameManager - baseAddress) << ")\n";
    std::cout << "3. g_GameManager Points to   : 0x" << (uintptr_t)g_GameManager
              << "\n";
    std::cout << "4. local_player Points to    : 0x"
              << (uintptr_t)g_GameManager->local_player << "\n";
    std::cout << "5. stats Points to           : 0x"
              << (uintptr_t)g_GameManager->local_player->stats << "\n";
    std::cout << std::dec;

    std::cout << "\n[STATUS]:\n";
    std::cout << "  Name: " << g_GameManager->local_player->name << "\n";
    std::cout << "  HP  : " << g_GameManager->local_player->stats->hp << "\n";
    std::cout << "  Gold: " << g_GameManager->local_player->stats->gold << "\n";

    std::cout << "\n[1] Nhan sat thuong (-20 HP)\n";
    std::cout << "[2] Restart Match (Cap phat lai bo nho Heap moi)\n";
    std::cout << "[0] Thoat\n";
    std::cout << "Lua chon: ";

    int choice;
    if (!(std::cin >> choice))
      break;
    if (choice == 0)
      break;
    if (choice == 1) {
      g_GameManager->local_player->stats->hp -= 20;
    } else if (choice == 2) {
      InitGame();
      std::cout << "Da cap phat lai bo nho!\n";
      Sleep(1000);
    }
  }

  return 0;
}