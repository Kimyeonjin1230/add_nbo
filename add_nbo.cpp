#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h> 

uint32_t read_nbo(FILE *fp) {
    uint32_t num = 0;
    if (fread(&num, sizeof(uint32_t), 1, fp) != 1) {
        fprintf(stderr, "Error reading\n");
        exit(1);
    }
    return ntohl(num); // Convert network byte order to host byte order
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "syntax : add-nbo <file1> <file2>\n");
        fprintf(stderr, "sample : add-nbo a.bin b.bin\n");
        return 1;
    }

    FILE *file1 = fopen(argv[1], "rb");
    FILE *file2 = fopen(argv[2], "rb");

    if (!file1 || !file2) {
        fprintf(stderr, "Cannot open file.\n");
        return 1;
    }

    // Check file size
    fseek(file1, 0, SEEK_END);
    fseek(file2, 0, SEEK_END);
    if (ftell(file1) < sizeof(uint32_t) || ftell(file2) < sizeof(uint32_t)) {
        fprintf(stderr, "File size is smaller than 4 bytes.\n");
        return 1;
    }
    rewind(file1);
    rewind(file2);

    uint32_t num1 = read_nbo(file1);
    uint32_t num2 = read_nbo(file2);

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, num1 + num2, num1 + num2);

    fclose(file1);
    fclose(file2);

    return 0;
}

