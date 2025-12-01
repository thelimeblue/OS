#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;
    char buffer[100];

    // 1. open()
    fd = open("demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        perror("open failed");
        return 1;
    }

    // 2. write()
    char *text = "This is written using write() system call.\n";
    write(fd, text, 45);

    // Move pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // 3. read()
    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';

    printf("Data read from file: %s\n", buffer);

    // 4. close()
    close(fd);

    return 0;
}
