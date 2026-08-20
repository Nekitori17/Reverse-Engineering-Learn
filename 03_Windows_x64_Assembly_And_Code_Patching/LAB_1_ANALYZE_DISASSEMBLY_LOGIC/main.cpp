#include <windows.h>

int main() {
  unsigned char byteCode[64] = {
    0x55,                               // push rbp
    0x48, 0x89, 0xE5,                   // mov rbp, rsp
    0x48, 0x89, 0x4D, 0x10,             // mov [rbp+10h], rcx
    0x89, 0x55, 0x18,                   // mov [rbp+18h], edx
    0x48, 0x8B, 0x45, 0x10,             // mov rax, [rbp+10h]
    0x8B, 0x00,                         // mov eax, [rax]
    0x2B, 0x45, 0x18,                   // sub eax, [rbp+18h]
    0x89, 0xC2,                         // mov edx, eax
    0x48, 0x8B, 0x45, 0x10,             // mov rax, [rbp+10h]
    0x89, 0x10,                         // mov [rax], edx
    0x48, 0x8B, 0x45, 0x10,             // mov rax, [rbp+10h]
    0x8B, 0x00,                         // mov eax, [rax]
    0x85, 0xC0,                         // test eax, eax
    0x79, 0x0A,                         // jns (nhảy nếu kết quả không âm)
    0x48, 0x8B, 0x45, 0x10,             // mov rax, [rbp+10h]
    0xC7, 0x00, 0x00, 0x00, 0x00, 0x00, // mov dword ptr [rax], 0
    0x90,                               // nop
    0x5D,                               // pop rbp
    0xC3,                               // ret
    0x55,                               // push rbp (bắt đầu hàm tiếp theo)
    0x48, 0x89, 0xE5,                   // mov rbp, rsp
    0x48, 0x83, 0xEC, 0x50,             // sub rsp, 50h
    0xE8, 0xC0, 0xC6, 0x00, 0x00        // call (gọi một hàm khác)
  };

  // Vậy là lệnh trừ máu là: sub eax, [rbp+18h]
  // Đếm số byte lên ta được là cách 17byte tương ứng 0x11
  uintptr_t subAdressOffset = 0x11;
}