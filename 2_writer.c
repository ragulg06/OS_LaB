#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SharedMemSize 50

int main() {
    int shmid;
    key_t key = 5677;
    char *shared_memory;

    // Create shared memory
    if ((shmid = shmget(key, SharedMemSize, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    if ((shared_memory = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Get input from user
    char name[SharedMemSize];
    printf("Enter a name: ");
    fgets(name, SharedMemSize, stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline

    // Write to shared memory
    strcpy(shared_memory, name);

    printf("Name written to shared memory. Run the reader now.\n");

    return 0;
}
