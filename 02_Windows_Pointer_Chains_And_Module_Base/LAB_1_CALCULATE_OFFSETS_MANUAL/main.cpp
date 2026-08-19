#include <vector>

int main() {
  uintptr_t baseModulePtr;

  // Địa chỉ tĩnh của biến chứa địa chỉ của object g_Manager (*g_Manager) có
  // offset là: +0xf7030
  uintptr_t g_ManagerPtr_ptr_offset = 0xf7030;

  // Từ Base Address cộng thêm offset của biến chứa địa chỉ của g_Manager
  // (*g_Manager) +0xf7030 ta sẽ truy cập được giá trị của biến đó là địa chỉ
  // của g_Manager được cập nhật sau mỗi lần gán lại
  uintptr_t g_ManagerPtr_ptr = baseModulePtr + g_ManagerPtr_ptr_offset;
  uintptr_t g_ManagerPtr = *(uintptr_t*)g_ManagerPtr_ptr;

  // Từ địa chỉ của g_Manager ta có thể thêm các offset để truy cập hai biến:
  std::vector<uintptr_t> hp_offsets = std::vector<uintptr_t>({
    0x00, // 4byte    int      game_state
    0x08, // 8byte    Player*  local_player
    // Truy cập giá trị của local_player để lấy địa chỉ của dữ liệu
    // local_player sau đó tiếp tục công pffset
    0x20, // 32byte   Stats*   stats
    // Truy cập giá trị của stats để lấy địa chỉ của dữ liệu
    // stats sau đó tiếp tục công pffset
    0x00  // 4byte    int      hp
  });

  std::vector<uintptr_t> gold_offsets = std::vector<uintptr_t>({
    0x00, // 4byte    int      game_state
    0x08, // 8byte    Player*  local_player
    // Truy cập giá trị của local_player để lấy địa chỉ của dữ liệu
    // local_player sau đó tiếp tục công pffset
    0x20, // 32byte   Stats*   stats
    // Truy cập giá trị của stats để lấy địa chỉ của dữ liệu
    // stats sau đó tiếp tục công pffset
    0x00, // 4byte    int      hp
    0x0C  // 12byte   int      gold
  });

  // 1. Player* và Stats* là biến chứa địa chỉ của hai object đó chứ k phải chứa giá trị. Luôn có độ dài là 8 byte
  // 2. Mỗi biến/thuộc tính có ví trí bộ nhớ luôn là vị trí % kích thước của biến/thuộc tính == 0
  // local_player có kích thước là 8byte và int có kích thước là 4byte 
  // nên phải đệm thêm 4byte để local_player ở vị trí 8byte 
}