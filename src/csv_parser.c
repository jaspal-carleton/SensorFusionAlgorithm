/* CSV Parserr: Reads csv file and returns a vector with all sensor readings for a particular time stamp where first element of array is the time stamp followed by readings */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("incorrect number of arguments, send csv file as argument and delimiter\n");
        return -1;
    }
    printf("filename=%s, delimiter=%s\n", argv[1], argv[2]);

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Can't open file\n");
        return 0;
    }

    char *delimiter = argv[2];
    printf("delimiter=%s\n", delimiter);

    char buf[1024];
    char *arr = (char*)calloc(1, 1024);
    char time_stamp_buf[1024] = { 0 };
    int row_count = 0;
    int field_count = 0;
    while (fgets(buf, 1024, fp)) {
        field_count = 0;
        row_count++;

        if (row_count == 1) {
            continue;
        }

        char *field = strtok(buf, delimiter);
        while (field) {
            if (field_count == 0) {
                if (strcmp(time_stamp_buf, "0")) {
                    printf("Time Stamp not 0\t");
                    if (!strcmp(field, time_stamp_buf)) {
                        printf("time stamp same, increase memory of row");
                        arr = realloc(arr, sizeof(arr)+sizeof(buf));
                        printf("array size %lu\n", sizeof(arr));
                    }
                }
                strcpy(time_stamp_buf, field);
            }
            if (field_count == 1) {
                //printf("Sensor:\t");
            }
            if (field_count == 2) {
                    //printf("Reading:\t");
            }
            if (field_count == 0) {
                printf("Time Stamp:\t");
                printf("%s\t", field);
            }
            //printf("%s\t", field);
            if (field_count == 0)
            	printf("Time Stamp buf:%s\t", time_stamp_buf);

            field = strtok(NULL, ",");
            field_count++;
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
