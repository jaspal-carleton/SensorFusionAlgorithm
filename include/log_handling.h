/**
 * \brief Function Prototype Library to implement log handling
 * \author jaspalsingh@cmail.carleton.ca
 * \version 1.0
 * \date 2019-12-05
 */

#ifndef LOG_HANDLING_H
#define LOG_HANDLING_H

/**
 * \brief Structure for storing log details
 * \details Store log info such as log file pointer, log path, and log name
 */
struct log_info_t {
    FILE *fptr;
    char *log_filename;
    char *log_basefolder;
    char *log_path;
};

/**
 * \brief Initialize log info
 * \details Initialize the log base path, name and other details
 */
struct log_info_t *init_log(char *proj_abs_path, char *time_now);

/**
 * \brief Open log
 * \details Open log file
 */
int open_log(struct log_info_t *log_info);

/**
 * \brief Close log
 * \details Close log file
 */
int close_log(struct log_info_t *log_info);

/**
 * \brief Write to log
 * \details Write to log file
 */
void write_log(struct log_info_t *log_info, char *str);

#endif // LOG_HANDLING_H