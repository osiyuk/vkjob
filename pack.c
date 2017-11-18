#pragma pack(push,1)
struct s {
  int field;
  char data[0];
};
#pragma pack(pop)

#include <stdio.h>

#define byte (char *)
#define width(s) ( byte &s.data[0] - byte &s)

int main() {
  struct s ss;
  printf("size of s %d\n", sizeof(ss));
  printf("%u %u %u\n", &ss, &ss.data, &ss.data[0]);
  printf("offset of data[0] is %d\n", width(ss));

  return 0;
}
