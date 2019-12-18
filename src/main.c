/**
 * \brief Main file for Sensor Fusion Algorithm software
 * \author jaspalsingh@cmail.carleton.ca
 * \version 1.0
 * \date 2019-12-05
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "log_handling.h"
#include "sensor_fusion.h"
#include "test.h"

#define BUF_LEN 255
extern int errno ;

void get_curr_timestamp(char *time_now) {
    //Refer: http://zetcode.com/articles/cdatetime/
    time_t rawtime = time(NULL);
    if (rawtime == -1) {
        puts("The time() function failed");
        exit(EXIT_FAILURE);
    }
    struct tm *ptm = localtime(&rawtime);
    if (ptm == NULL) {
        puts("The localtime() function failed");
        exit(EXIT_FAILURE);
    }
    strftime(time_now, BUF_LEN, "%Y%m%d-%H%M%S", ptm);
}

int main(int argc, char *argv[]) {
    char *input_csv = NULL;
    char *output_csv = NULL;
    char log_path[BUF_LEN];
    char *proj_abs_path;
    FILE *fptr_log;
    FILE *fptr_csv_out;
    int err_num = 0;
    
    // get project absolute path
    char *temp_dir1 = realpath(argv[0], NULL);
    if(temp_dir1 == NULL) {
        printf("ERROR: cannot find file with name %s \n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        char *temp_dir2 = dirname(temp_dir1);
        proj_abs_path = dirname(temp_dir2);
        printf("DEBUG: Absolute path => %s\n", proj_abs_path);
    }
    
    // get current timestamp
    char time_now[BUF_LEN] = {0};
    get_curr_timestamp(time_now);
    printf("DEBUG: Current timestamp => %s\n", time_now);
    
    // set log path
    sprintf(log_path, "%s/logs/log_%s.txt", proj_abs_path, time_now );
    printf("DEBUG: Log Path => %s\n", log_path);
    fptr_log = fopen(log_path,"w");
    if(fptr_log == NULL) {
      fprintf(stderr, "Error opening log file: %s\n", strerror( err_num ));
      exit(EXIT_FAILURE);
    }
    
    // input csv
    char temp_csv1[255];
    sprintf(temp_csv1, "%s/data/input/input.csv", proj_abs_path);
    input_csv = malloc(sizeof(char) * 255);
    strncpy(input_csv, temp_csv1, sizeof(temp_csv1));
    printf("DEBUG: Input CSV Path => %s\n", input_csv);
  
    // output csv
    char temp_csv2[255];
    sprintf(temp_csv2, "%s/data/output/output.csv", proj_abs_path);
    output_csv = malloc(sizeof(char) * 255);
    strncpy(output_csv, temp_csv2, sizeof(temp_csv2));
    printf("DEBUG: Output CSV Path => %s\n", output_csv);
    fptr_csv_out = fopen(output_csv,"w");
    if(fptr_csv_out == NULL) {
      fprintf(stderr, "Error opening output csv file: %s\n", strerror( err_num ));
      exit(EXIT_FAILURE);
    }
    
    int LOOP_RESET = 0;
    int i, j;
    double sensor_values[10];
    char previous_timestamp[10];
    char current_timestamp[10];
    float current_sensor_val;
    FILE *fp = fopen(input_csv, "r");
    if(fp == NULL) {
        perror("Unable to open file!");
        exit(1);
     }
    char chunk[128];
    int ct_str_length;
    long cur_pos;
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
        ct_str_length=strlen(chunk);
        cur_pos = ftell(fp);
        chunk[strcspn(chunk, "\r\n")] = 0;
        i = 0;
        char *p = strtok(chunk, ",");
        char *array[3];
        while (p != NULL) {
          array[i++] = p;
          p = strtok(NULL, ",");
        }
        //
        if(LOOP_RESET == 0) {
          j = 0;
          for(i=0; i<10; i++) {
            sensor_values[i]=0.0;
          }
          strcpy(previous_timestamp, array[0]);
          strcpy(current_timestamp, array[0]);
          current_sensor_val = atof(array[2]);
          sensor_values[j] = current_sensor_val;
          LOOP_RESET = 1;
          continue;
        } else {
          j++;
          strcpy(previous_timestamp, current_timestamp);
          strcpy(current_timestamp, array[0]);
          current_sensor_val = atof(array[2]);
          if(strcmp(previous_timestamp, current_timestamp)==0) {
            sensor_values[j] = current_sensor_val;
            continue;
          } else {
            // Perform sensor fusion
            struct support_degree_matrix *spd = compute_support_degree_matrix(sensor_values);
            struct eigen_value_vector *eigen = compute_eigen(spd);
            double *contrib_rate = compute_contribution_rate(eigen, spd->sensor_count);
            int contrib_rate_count = compute_contrib_rate_count(contrib_rate, 0.5, spd->sensor_count);
            double **principal_components_matrix = compute_principal_component(spd, eigen->eigen_vector, contrib_rate_count);
            double *integrate_support_matrix = compute_integrated_support_degree(principal_components_matrix,
                                                   contrib_rate, contrib_rate_count, spd->sensor_count);
            int res = eliminate_incorrect_data(integrate_support_matrix, 0.7, spd->sensor_count);
            double *weight_coff = compute_weight_coefficient(integrate_support_matrix, spd->sensor_count);
            double fused_value = compute_fused_output(weight_coff, sensor_values, spd->sensor_count);
            printf("DEBUG: Time - %s, Fused Value: %f\n\n", previous_timestamp, fused_value);
            fprintf(fptr_csv_out, "Time: %s, Fused Value: %f\n", previous_timestamp, fused_value);
            fseek(fp,cur_pos-ct_str_length,SEEK_SET);
            LOOP_RESET = 0;
          }
        }
    }
    
    // Perform sensor fusion
    struct support_degree_matrix *spd = compute_support_degree_matrix(sensor_values);
    struct eigen_value_vector *eigen = compute_eigen(spd);
    double *contrib_rate = compute_contribution_rate(eigen, spd->sensor_count);
    int contrib_rate_count = compute_contrib_rate_count(contrib_rate, 0.5, spd->sensor_count);
    double **principal_components_matrix = compute_principal_component(spd, eigen->eigen_vector, contrib_rate_count);
    double *integrate_support_matrix = compute_integrated_support_degree(principal_components_matrix,
                                           contrib_rate, contrib_rate_count, spd->sensor_count);
    int res = eliminate_incorrect_data(integrate_support_matrix, 0.7, spd->sensor_count);
    double *weight_coff = compute_weight_coefficient(integrate_support_matrix, spd->sensor_count);
    double fused_value = compute_fused_output(weight_coff, sensor_values, spd->sensor_count);
    printf("DEBUG: Time - %s, Fused Value: %f\n\n", previous_timestamp, fused_value);
    fprintf(fptr_csv_out, "Time: %s, Fused Value: %f\n", previous_timestamp, fused_value);
    
    // free malloc space
    free(input_csv);
    free(output_csv);
	free(temp_dir1);
  
    // close log & csv out file handle
    fclose(fp);
    fclose(fptr_log);
    fclose(fptr_csv_out);
    
    // Testing APIs
    int opt;
    while ((opt = getopt(argc, argv, "t")) != -1) {
        switch (opt) {
            case 't':
                // perform automated testing
                printf("\n-----------------------------------\n");
                printf("Starting Automated APIs Testing\n");
                printf("-----------------------------------\n");
                test_all();
                printf("\n-----------------------------------\n");
                printf("Finished Automated APIs Testing\n");
                printf("-----------------------------------\n");
                break;
            default:
                printf("Usage: ./bin/main [-t]\n");
                break;
        }
    }
    
    return 0;
} // End of main()

