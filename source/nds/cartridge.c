#include <nds/cartridge.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

unsigned char *nds_cartridge_read(const char *path) {
    FILE *fp;
    if ((fp = fopen(path, "rb+")) == NULL) return NULL;

    struct stat st;
    if (stat(path, &st) == -1) return NULL;

    unsigned char *buf = malloc(st.st_size);
    fread(buf, st.st_size, 1, fp);
    return buf;
}