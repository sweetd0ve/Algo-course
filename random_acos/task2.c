#include <fcntl.h>
#include <unistd.h>
#include <endian.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

struct Data
{
    int16_t x;
    int64_t y;
};

void marshall(unsigned char *out, const struct Data *in) {

    int16_t s_x = htole16(in->x);
    int64_t s_y = htole64(in->y);

    memcpy(out, &s_x, 2);
    memcpy(out + 2, &s_y, 8);
}


void unmarshall(struct Data *out, const unsigned char *in) {
    int16_t s_x;
    int64_t s_y;

    memcpy(&s_x, in, 2);
    memcpy(&s_y, in + 2, 8);

    out->x = htole16(s_x);
    out->y = htole64(s_y);
}


void file_to_data(int fd, int i, struct Data *out) {

    unsigned char buf[10]; 

    lseek(fd, i * 10, SEEK_SET);
    int read_res = 0;

    while(read_res != 10) {

        int c_read = read(fd, buf + read_res, 10 - read_res);

        if (c_read <= 0)
            exit(2);

        read_res += c_read;
    }

    unmarshall(out, buf);
}


int64_t of_process(int16_t x, int64_t y, int A) {

    int64_t x_64 = (int64_t)x;
    int64_t A_64 = (int64_t)A;

    int64_t mul_res;

    if (__builtin_mul_overflow(x_64, A_64, &mul_res) || __builtin_add_overflow(mul_res, y, &y))
        exit(3);

    return y;
}


void data_to_file(struct Data *from, int fd, int i) {

    lseek(fd, i * 10, SEEK_SET);
    unsigned char buf[10];

    marshall(buf, from);

    int write_res = 0;

    while (write_res != 10) {

        int c_write = write(fd, buf + write_res, 10 - write_res);

        if (c_write <= 0)
            exit(2);

        write_res += c_write;
    }
}

int main(int argc, char **argv) {

    int fd = open(argv[1], O_RDWR);
    int A = atoi(argv[2]);

    int n = lseek(fd, 0, SEEK_END) / 10;

    for (int i = 0; i < (n / 2 + n % 2); i++) {
             
        struct Data a;
        struct Data b;

        file_to_data(fd, i, &a);
        file_to_data(fd, n - 1 - i, &b);

        a.y = of_process(a.x, a.y, A);
        b. y = of_process(b.x, b.y, A);

        data_to_file(&a, fd, n - 1 - i);
        data_to_file(&b, fd, i);        
    }

    return 0;
}