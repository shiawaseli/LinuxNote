#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("./tmp.txt", "w+");
    if (fp == NULL) {
        perror("fopen error");
        return -1;
    }

    //char ptr[] = (char*)"冬天适合睡懒觉~";
    char *ptr = (char*)"冬天适合睡懒觉~";
    int ret = fwrite(ptr, 1, strlen(ptr), fp);
    if (ret <= 0) {
        perror("fwrite error");
        return -1;
    }
    printf("ret = %d\n", ret);

    fseek(fp, 0, SEEK_SET);

    char buf[1024] = { 0 };
    ret = fread(buf, 1, strlen(ptr), fp);
    if (ret < 0) {
        perror("fread error");
        return -1;
    }
    printf("read buf: [%s]-[%d]\n", buf, ret);

    fclose(fp);
    return 0;
}
