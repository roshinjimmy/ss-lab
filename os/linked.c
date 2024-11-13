#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main() {
    int f[MAX], n, val, choice, blocks, start;

    for (int i = 0; i < MAX; i++)
        f[i] = 0;

    printf("Enter the number of blocks already allocated: ");
    scanf("%d", &n);
    printf("Enter the allocated block numbers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        f[val] = 1;
    }

    while (1) {
        printf("1. Add file\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:   
                printf("Enter the number of blocks and the starting block: ");
                scanf("%d %d", &blocks, &start);

                if (f[start] == 1) {
                    printf("Block %d is already allocated.\n", start);
                    break;
                }

                for (int i = start; i < start + blocks; i++) {
                    if (f[i] == 0) {
                        f[i] = 1;
                        printf("Block %d allocated.\n", i);
                    } else {
                        printf("Block %d is already allocated.\n", i);
                        blocks++;
                    }
                }
                break;

            case 2:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}