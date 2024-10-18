#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/wait.h>

void ema_search_str(const char *filename, const char *pattern, int repetitions);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <pattern> <repetitions>" << std::endl;
        return EXIT_FAILURE;
    }
    const char *filename = argv[1];
    const char *pattern = argv[2];
    char *endptr;
    errno = 0;
    long repetitions_long = strtol(argv[3], &endptr, 10);
    if (endptr == argv[3] || *endptr != '\0' || errno == ERANGE || repetitions_long < 0) {
        std::cerr << "Invalid number of repetitions: " << argv[3] << std::endl;
        return EXIT_FAILURE;
    }
    int repetitions = static_cast<int>(repetitions_long);
    pid_t pid = vfork();
    if (pid < 0) {
        perror("vfork failed");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        ema_search_str(filename, pattern, repetitions);
        _exit(0);
    } else {
        wait(nullptr);
    }
    return EXIT_SUCCESS;
}
