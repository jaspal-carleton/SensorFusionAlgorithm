/**
 * \brief Function Definition Library to implement log functionality
 * \author jaspalsingh@cmail.carleton.ca
 * \version 1.0
 * \date 2019-12-05
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log_handling.h"

/**
 * \brief Initialize log info
 * \details Initialize the log base path, name and other details
 * \param[in] ptr log file pointer
 * \param[in] path log file path
 * \return Success: 0
 * \return Failure: 1
 */
struct log_info_t *init_log(char *proj_abs_path, char *time_now) {
    struct log_info_t log_info;
    log_info.fptr = NULL;
    
    char temp[255];
    sprintf(temp, "log_%s.txt", time_now);
    log_info.log_filename = malloc(sizeof(char) * 255);
    strncpy(log_info.log_filename, temp, sizeof(temp));
    
    log_info.log_basefolder = malloc(sizeof(char) * 255);
    strncpy(log_info.log_basefolder, "/logs", sizeof("/logs"));
    
    char temp2[255];
    sprintf(temp2, "%s/logs/log_%s.txt", proj_abs_path, time_now );
    log_info.log_path = malloc(sizeof(char) * 255);
    strncpy(log_info.log_path, temp2, sizeof(temp2));
  
    printf("DEBUG: Log Path => %s\n", log_info.log_path);
    return &log_info;
}

/**
 * \brief Open log
 * \details Open log file
 * \param[in] ptr log file pointer
 * \param[in] path log file path
 * \return Success: 0
 * \return Failure: 1
 */
int open_log(struct log_info_t *log_info) {
    log_info->fptr = fopen(log_info->log_path, "w");
    if(log_info->fptr == NULL) {
        puts("fail");
        return 1;
    } else {
        puts("pass");
        return 0;
    }
}

/**
 * \brief Close log
 * \details Close log file
 * \param[in] ptr log file pointer
 * \return Success: 0
 * \return Failure: 1
 */
int close_log(struct log_info_t *log_info) {
    if (fclose(log_info->fptr) == 0) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * \brief Write to log
 * \details Write to log file 
 * \param[in] ptr log file pointer
 * \param[in] str string message to write to log file
 * \return Success: 0
 * \return Failure: 1
 */
void write_log(struct log_info_t *log_info, char *str) {
    puts(str);
    log_info->fptr = malloc(sizeof(char) * 255);
    fprintf(log_info->fptr, "%s\n", str);
}