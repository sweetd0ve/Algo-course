#include <asm/unistd.h>

struct FileWriteState
{
    int fd;
    unsigned char *buf;
    int bufsize;
    int cur_buf;
};

unsigned char buf[4096];

struct FileWriteState currect_struct = 
{
        1, buf, 4096, 0
};

struct FileWriteState *stout = &currect_struct;

__attribute__((fastcall)) void flush(struct FileWriteState *out)
{
    volatile int result = 0;
    asm volatile (
        "int    $0x80\n\t"
        :
        : "a"(__NR_write), "b"(out->fd), "c"(out->buf), "d"(out->cur_buf)
        : "memory"
    );
}

__attribute__((fastcall)) void writechar(int c, struct FileWriteState *out)
{
    if (out->cur_buf == out->bufsize)
    {
        flush(out);
        out->cur_buf = 0;
    }
    out->buf[out->cur_buf] = c;
    ++(out->cur_buf);
}