#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 

int writeMem();
int readMem();

int main() {
    if (writeMem() != 0) {
        fprintf(stderr, "Write operation failed.\n");
        return 1;
    }

    if (readMem() != 0) {
        fprintf(stderr, "Read operation failed.\n");
        return 1;
    }

    return 0;
}

int writeMem() {
    key_t key = 1234;  // Shared memory key
    int shmid;
    char *shm_ptr;

    // Step 1: Create shared memory
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Step 2: Attach shared memory
    shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    // Step 3: Write to shared memory
    printf("Writer Process: Writing data to shared memory...\n");
    strcpy(shm_ptr, "Hello from the Writer Process!");

    // Step 4: Simulate some delay
    sleep(2);

    // Step 5: Detach from shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
        return 1;
    }

    printf("Writer Process: Detached from shared memory.\n");
    return 0;
}

int readMem() {
    key_t key = 1234;  // Shared memory key
    int shmid;
    char *shm_ptr;

    // Step 1: Get shared memory
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Step 2: Attach shared memory
    shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    // Step 3: Read from shared memory
    printf("Reader Process: Read data = %s\n", shm_ptr);

    // Step 4: Detach from shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
        return 1;
    }

    printf("Reader Process: Detached from shared memory.\n");
    return 0;
}
