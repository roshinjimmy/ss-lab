#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    int i, startAddress, currentAddress;
    char programName[10], line[50], extractedName[10], addressStr[10];

    printf("Enter Program Name: ");
    scanf("%s", programName);

    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    fscanf(inputFile, "%s", line);
    for (i = 2; i < 8; i++) {
        extractedName[i - 2] = line[i];
    }
    extractedName[6] = '\0';

    printf("Name from Input File: %s\n", extractedName);

    if (strcmp(programName, extractedName) == 0) {
        while (fscanf(inputFile, "%s", line) != EOF) {
            if (line[0] == 'T') {
                for (i = 2; i < 8; i++) {
                    addressStr[i - 2] = line[i];
                }
                addressStr[6] = '\0';
                currentAddress = atoi(addressStr);

                i = 12;
                while (line[i] != '$') {
                    if (line[i] != '^') {
                        printf("00%d \t %c%c\n", currentAddress, line[i], line[i + 1]);
                        fprintf(outputFile, "00%d \t %c%c\n", currentAddress, line[i], line[i + 1]);
                        currentAddress++;
                        i += 2;
                    } else {
                        i++;
                    }
                }
            } else if (line[0] == 'E') {
                break;
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
