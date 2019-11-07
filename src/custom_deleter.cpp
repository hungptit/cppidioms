#include <iostream>
#include <memory>
#include <spawn.h>

struct PosixFileActions {
    // PosixFileActions() {
    //     posix_spawn_file_actions_init(&fileActions);
    // }
    PosixFileActions() : fileActions() {}

    ~PosixFileActions() {
        posix_spawn_file_actions_destroy(&fileActions);
    }
    posix_spawn_file_actions_t fileActions;
};


int main() {
    PosixFileActions fileActions;
}
