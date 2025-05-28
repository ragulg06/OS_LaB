#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SharedMemSize 50

int main() {
    int shmid;
    key_t key = 5677;
    char *shared_memory;

    // Access existing shared memory
    if ((shmid = shmget(key, SharedMemSize, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    if ((shared_memory = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Convert to uppercase
    for (int i = 0; shared_memory[i]; i++) {
        shared_memory[i] = toupper(shared_memory[i]);
    }

    printf("Uppercase Name from Shared Memory: %s\n", shared_memory);

    // Detach and remove shared memory
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL); // Clean up

    return 0;
}
