#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int input_fd, output_fd;
    char buffer[1024];

    input_fd = open("input.txt", O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open input.txt");
        return 1;
    }

    output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        perror("Failed to open output.txt");
        return 1;
    }

    dup2(input_fd, STDIN_FILENO);
    dup2(output_fd, STDOUT_FILENO);

    close(input_fd);
    close(output_fd);

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("%s", buffer);
    }

    return 0;
}
