#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: newcat <filename>\n", 25);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    int bytesRead, lineNumber = 1;
    char lineHeader[20];
    int headerLength = snprintf(lineHeader, sizeof(lineHeader), "%d: ", lineNumber++);
    write(STDOUT_FILENO, lineHeader, headerLength);

    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            write(STDOUT_FILENO, &buffer[i], 1);
            if (buffer[i] == '\n' && i + 1 < bytesRead) {
                headerLength = snprintf(lineHeader, sizeof(lineHeader), "%d: ", lineNumber++);
                write(STDOUT_FILENO, lineHeader, headerLength);
            }
        }
    }

    close(fd);
    return 0;
}

