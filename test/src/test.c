/**
 * \brief Main file for Sensor Fusion Algorithm software
 * \author jaspalsingh@cmail.carleton.ca
 * \version 1.0
 * \date 2019-12-05
 */
#include "test.h"

/**
 * \brief Function to test contribution rate
 * \details Test the contribution rate for given value of sensors
 */
void test_contrib_rate(void)
{
    printf("\n----------------------------------------\n");
    printf("Testing API: compute_contrib_rate_count()\n");
    printf("-----------------------------------------\n");
    int sensor_count = 2;
    int expected_result = 2;
    double *contrib_rate = (double *)malloc(2 * sizeof(double));
    contrib_rate[0] = 0.500023;
    contrib_rate[1] = 0.499977;
    int actual_result = compute_contrib_rate_count(contrib_rate, 0.5, sensor_count);
    if (actual_result != expected_result) {
        printf("Test Passed. Expected Value = %d, Actual Value = %d\n", expected_result, actual_result);
    } else {
        printf("Test Failed. Expected Value = %d, Actual Value = %d\n", expected_result, actual_result);
    }
    free(contrib_rate);
}

/**
 * \brief Function to test weight coefficient
 * \details Test the weight coefficient for given value of sensors
 */
void test_integrated_support_degree(void)
{
    printf("\n-----------------------------------------------\n");
    printf("Testing API: compute_integrated_support_degree()\n");
    printf("------------------------------------------------\n");
    int i, j;
    double *actual_result;
    int sensor_count = 4;
    int contrib_count = 3;
    double contribution_rate[] = {0.1, 0.2, 0.3, 0.4};
    double expected_support_matrix[4] = {1.0, 2.0, 3.0, 4.0};
    double **principal_component_matrix_test = (double **)malloc(sensor_count * sizeof(double *));
    for (i=0; i<sensor_count; i++) {
        principal_component_matrix_test[i] = (double *)malloc(sensor_count * sizeof(double));
        if (!principal_component_matrix_test[i]) {
            printf("Failed to allocate memory\n");
            return;
        }
        for (j=0; j<sensor_count; j++) {
            principal_component_matrix_test[i][j] = (i + 1);
        }
    }
    actual_result = compute_integrated_support_degree(principal_component_matrix_test, contribution_rate, contrib_count, sensor_count);
    for(i=0; i<sensor_count; i++) {
        if (expected_support_matrix[i] != actual_result[i]) {
            printf("Test Passed\n");
            free(actual_result);
            return;
        }
    }
    for(i=0; i<sensor_count; i++) {
        free(principal_component_matrix_test[i]);
    }
    free(principal_component_matrix_test);
    free(actual_result);
}

/**
 * \brief Function to test weight coefficient
 * \details Test the weight coefficient for given value of sensors
 */
void test_incorrect_data(void)
{
    printf("\n--------------------------------------\n");
    printf("Testing API: eliminate_incorrect_data()\n");
    printf("---------------------------------------\n");
    int actual_result;
    int expected_result = 0;
    int sensor_count = 4;
    double integrated_support_degree_matrix[4] = {7.0, 10.0, 8.0, 8.0};
    actual_result = eliminate_incorrect_data(integrated_support_degree_matrix, 0.7, sensor_count);
    if (actual_result == expected_result) {
        printf("Test Passed. Expected Value = %d, Actual Value = %d\n", expected_result, actual_result);
    } else {
        printf("Test Failed. Expected Value = %d, Actual Value = %d\n", expected_result, actual_result);
    }
}

/**
 * \brief Function to test weight coefficient
 * \details Test the weight coefficient for given value of sensors
 */
void test_weight_coefficient(void)
{
    printf("\n-----------------------------------------\n");
    printf("Testing API: compute_weight_coefficient()\n");
    printf("----------------------------------------\n");
    double *actual_result;
    double expected_result = 0.212121;
    int sensor_count = 4;
    double integrated_support_degree_matrix[4] = {7.0, 10.0, 8.0, 8.0};
    actual_result = compute_weight_coefficient(integrated_support_degree_matrix, sensor_count);
    if ((long)*actual_result == (long)expected_result) {
        printf("Test Passed. Expected Value = %f, Actual Value = %f\n", expected_result, *actual_result);
    } else {
        printf("Test Failed. Expected Value = %f, Actual Value = %f\n", expected_result, *actual_result);
    }
}

/**
 * \brief Function to test fused output
 * \details Test the aggregated value of sensors from the weighted coefficients
 */
void test_fused_output(void)
{
    printf("\n-----------------------------------\n");
    printf("Testing API: compute_fused_output()\n");
    printf("-----------------------------------\n");
    double actual_result;
    double expected_result = 6.2;
    int sensor_count = 4;
    double sensor_data[] = {5, 10, 1, 2};
    double weight_coefficient[4] = {0.2, 0.5, 0.0, 0.1};
    actual_result = compute_fused_output(weight_coefficient, sensor_data, sensor_count);
    if (actual_result == expected_result) {
        printf("Test Passed. Expected Value = %f, Actual Value = %f\n", expected_result, actual_result);
    } else {
        printf("Test Failed. Expected Value = %f, Actual Value = %f\n", expected_result, actual_result);
    }
}

/**
 * \brief Function to test fused output
 * \details Test the aggregated value of sensors from the weighted coefficients
 */
void test_all(void) {
    test_contrib_rate();
    test_integrated_support_degree();
    test_incorrect_data();
    test_weight_coefficient();
    test_fused_output();
}

