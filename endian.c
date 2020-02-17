#include <stdio.h>
#include <arpa/inet.h>

int main() {
    int a = 0x12345678;
    a = ntohl(a);
    unsigned char *c = (unsigned char*)(&a);
    if (*c == 0x78) {
       printf("little-endian\n");
    } else {
       printf("big-endian\n");
    }
    return 0;
}