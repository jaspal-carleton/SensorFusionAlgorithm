/**
 * \brief Function Definition Library to implement Sensor Fusion Algorithm
 * \author jaspalsingh@cmail.carleton.ca
 * \version 1.0
 * \date 2019-12-01
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "sensor_fusion.h"

/**
 * \brief Structure pointer for computed support degree matrix
 * \details Structure pointer for calculating support degree matrix
 * \param[in] sensor_readings array of sensor readings
 * \return Success: pointer to the structure support_degree_matrix
 * \return Failure: NULL
 */
struct support_degree_matrix *compute_support_degree_matrix(float *sensor_readings) {
    struct support_degree_matrix *spd;
    spd = (struct support_degree_matrix *)malloc(sizeof(struct support_degree_matrix));
    // count the number of sensor readings
    int length = sizeof(sensor_readings) / sizeof(sensor_readings[0]);
    spd->sensor_count = length;
    double **arrptr = (double **)malloc(length * sizeof(double *));
    int count = 0;
    for (int i = 0; i < length; i++) {
        arrptr[i] = (double *)malloc(length * sizeof(double));
    }
    // allocate memory space for support degree matrix structure
    spd->sd_matrix = (double *)malloc(sizeof(double) * length * length);
    if (arrptr == NULL || spd == NULL || spd->sd_matrix == NULL) {
        printf("ERROR: Failed to allocate memory at %s\n", __func__);
        return NULL;
    }
    // compute support degree matrix
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            arrptr[i][j] = exp(-1 * fabs(sensor_readings[i] - sensor_readings[j]));
            spd->sd_matrix[count] = arrptr[i][j];
            count++;
        }
    }
    printf("INFO: Computed support degree matrix\n");
    for (int i = 0; i < length * length; i++) {
        printf("DEBUG: Value => %f\n", spd->sd_matrix[i]);
    }
    free(arrptr);
    return spd;
}

/**
 * \brief Structure pointer calculate eigen value and eigen vector
 * \details Structure pointer for calculating eigen value and eigen vector
 * \param[in] support_degree_matrix pointer to structure support degree matrix
 * \return Success: pointer to structure eigen_value_vector
 * \return Failure: NULL
 */
struct eigen_value_vector *compute_eigen(struct support_degree_matrix *spd) {
    if ((spd->sd_matrix == NULL) || (spd->sensor_count == 0)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return NULL;
    }
    int length = spd->sensor_count;
    struct eigen_value_vector *eigen;
    // allocation memory space for eigen value vector structure
    eigen = (struct eigen_value_vector *)malloc(sizeof(struct eigen_value_vector));
    eigen->eigen_value = (double *)malloc(sizeof(double) * length);
    eigen->eigen_vector = (double **)malloc(length * sizeof(double *));
    for (int i = 0; i < length; i++) {
        eigen->eigen_vector[i] = (double *)malloc(length * sizeof(double));
    }
    if (eigen == NULL || eigen->eigen_vector == NULL || eigen->eigen_value == NULL) {
        printf("ERROR: Failed to allocate memory at %s\n", __func__);
        return NULL;
    }
    //Refer: https://www.gnu.org/software/gsl/doc/html/eigen.html
    // compute eigen values
    gsl_matrix_view m = gsl_matrix_view_array(spd->sd_matrix, length, length);
    gsl_vector *eval = gsl_vector_alloc(length);
    gsl_matrix *evec = gsl_matrix_alloc(length, length);
    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(length);
    gsl_eigen_symmv(&m.matrix, eval, evec, w);
    gsl_eigen_symmv_free(w);
    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_DESC);
    {
        int i;
        for (i = 0; i < length; i++) {
            eigen->eigen_value[i] = gsl_vector_get(eval, i);
            gsl_vector_view evec_i = gsl_matrix_column(evec, i);
            for (int j = 0; j < length; j++) {
                eigen->eigen_vector[i][j] = *(*(&evec_i.vector.data) + j * length);
            }
        }
    }
    for (int i = 0; i < length; i++) {
        printf("DEBUG: Eigen Value => %g\n", eigen->eigen_value[i]);
        printf("DEBUG: Eigen Vector => \n");
        for (int j = 0; j < length; j++) {
            printf("%g\n", eigen->eigen_vector[i][j]);
        }
    }
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    return eigen;
}

/**
 * \brief Function to calculate the contribution rate of principal component
 * \details Compute the contribution rate of kth and mth principal components
 * \param[in] eigen_value_vector pointer to structure of eigen_value_vector
 * \param[in] sensor_count total count of sensors
 * \return Success: pointer to contribution_rate of type double
 * \return Failure: NULL
 */
double *compute_contribution_rate(struct eigen_value_vector *eigen,
                                  int sensor_count) {
    if ((sensor_count == 0) || (eigen->eigen_value == NULL) || (eigen->eigen_vector == NULL)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return NULL;
    }
    double *contribution_rate = (double *)malloc(sensor_count * sizeof(double));
    if (contribution_rate == NULL) {
        printf("ERROR: Failed to allocate memory at %s\n", __func__);
        return NULL;
    }
    double sum = 0;
    for (int i = 0; i < sensor_count; i++) {
        sum += eigen->eigen_value[i];
    }
    printf("INFO: Compute contribution rate\n");
    for (int j = 0; j < sensor_count; j++) {
        contribution_rate[j] = eigen->eigen_value[j] / sum;
        printf("DEBUG: Rate => %g\n", contribution_rate[j]);
    }
    return contribution_rate;
}

/**
 * \brief Function to compute contribution rate
 * \details Compute the count of contribution rates to be used for sensors
 * \param[in] contribution_rate
 * \param[in] threshold
 * \param[in] sensor_count number of sensors to be used
 * \return Success: contribution rate count, 
 * \return Failure: -1
 */
int compute_contrib_rate_count(double *contribution_rate,
                               float threshold,
                               int sensor_count) {
    if ((contribution_rate == NULL) || (threshold == 0) || (sensor_count == 0)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return -1;
    }
    double sum = 0;
    int m;
    for (int k = 0; k < sensor_count; k++) {
        for (int j = 0; j <= k; j++) {
            sum += contribution_rate[j];
        }
        if (sum <= threshold) {
            m = k - 1;
            printf("DEBUG: Contribution rate to use %d\n", m);
            return m;
        }
    }
    printf("DEBUG: Count of Contribution rates => %d\n", sensor_count);
    return sensor_count;
}

/**
 * \brief Function to compute principal component
 * \details Computed principal component for each of eigen vector
 * \param[in] support_degree_matrix pointer to structure support degree matrix
 * \param[in] eigen_vector pointer to pointer of eigen vector of type double
 * \param[in] contrib_rate_count number of contribution rate to be used
 * \return Success: principal of support degree matrix, 
 * \return Failure: NULL
 */
double **compute_principal_component(struct support_degree_matrix *spd,
                                     double **eigen_vector,
                                     int contrib_rate_count) {
    if ((spd->sensor_count == 0) || (contrib_rate_count == 0) || (spd->sd_matrix == NULL) || (eigen_vector == NULL)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return NULL;
    }
    int n = spd->sensor_count;
    int m = contrib_rate_count;
    int count = 0;
    double **arrptr = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        arrptr[i] = (double *)malloc(n * sizeof(double));
    }
    if (arrptr == NULL) {
        printf("ERROR: Failed to allocate memory at %s\n", __func__);
        return NULL;
    }
    printf("INFO: Compute support degree matrix\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arrptr[i][j] = spd->sd_matrix[count];
            printf("%f\n", arrptr[i][j]);
            count++;
        }
    }
    double **principal_components_matrix = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < n; i++) {
        principal_components_matrix[i] = (double *)malloc(n * sizeof(double));
    }
    if (principal_components_matrix == NULL) {
        printf("ERROR: Failed to allocate memory at %s\n", __func__);
        return NULL;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            principal_components_matrix[i][j] = 0;
            for (int k = 0; k < n; k++) {
                principal_components_matrix[i][j] += eigen_vector[i][k] * arrptr[k][j];
            }
        }
    }
    free(arrptr);
    return principal_components_matrix;
}

/**
 * \brief Function to compute integrated support degree
 * \details Computed support degree matrix for each of the sensors
 * \param[in] principle_components pointer to pointer of principle component of type double
 * \param[in] contribution_rate pointer to contribution rate of type double
 * \param[in] contrib_rate_count number of contribution rate to be used
 * \param[in] sensor_count number of sensors
 * \return Success: array of support degree matrix, 
 * \return Failure: NULL
 */
double *compute_integrated_support_degree(double **principle_components,
                                          double *contribution_rate,
                                          int contrib_rate_count,
                                          int sensor_count) {
    if ((sensor_count == 0) || (contrib_rate_count == 0) || (principle_components == NULL) || (contribution_rate == NULL)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return NULL;
    }
    double *arr = (double *)malloc(sensor_count * sizeof(double));
    if (arr == NULL) {
        printf("ERROR: Failed to allocate memory at %s\n", __func__);
        return NULL;
    }
    // Calculate integrated support degree matrix
    for (int i = 0; i < sensor_count; i++) {
        for (int j = 0; j < contrib_rate_count; j++) {
            printf("INFO: Principal Component => %d-%f, Contribution Rate => %d-%f\n", i, principle_components[i][j], j, contribution_rate[i]);
            arr[i] += principle_components[i][j] * contribution_rate[i];
        }
    }
    return arr;
}

/**
 * \brief Function to eliminate invalid sensor readings
 * \details Discard the faulty sensor readings from the support degree matrix
 * \param[in,out] integrated_support_degree_matrix pointer to integrated support degree matrix
 * \param[in] fault_tolerance_threshold threshold value to cut off invalid readings
 * \param[in] sensor_count total count of sensors
 * \return Success: 0, 
 * \return Failure: -1
 */
int eliminate_incorrect_data(double *integrated_support_degree_matrix,
                             double fault_tolerance_threshold,
                             int sensor_count) {
    int i;
    double mean = 0;
    double sum = 0;
    double *arr = integrated_support_degree_matrix;
    if ((sensor_count == 0) || (arr == NULL)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return -1;
    }
    for (i = 0; i < sensor_count; i++) {
        sum += arr[i];
    }
    mean = sum / (i + 1);
    for (i = 0; i < sensor_count; i++) {
        if (fabs(arr[i]) < fabs(fault_tolerance_threshold * mean)) {
            arr[i] = 0;
        }
    }
    return 0;
}

/**
 * \brief Function to compute weight coefficient for each sensor
 * \details Compute weighted coefficients for each sensors from the support degree matrix
 * \param[in] integrated_support_degree_matrix pointer to integrated support degree matrix
 * \param[in] sensor_count total count of sensors
 * \return Success: array of weighted coefficients, 
 * \return Failure: NULL
 */
double *compute_weight_coefficient(double *integrated_support_degree_matrix,
                                   int sensor_count) {
    double sum_weight_coefficient = 0;
    if ((sensor_count == 0) || (integrated_support_degree_matrix == NULL)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return NULL;
    }
    double *arr = (double *)malloc(sensor_count * sizeof(double));
    if (arr == NULL) {
        printf("ERROR: Failed to allocate memory at %s\n", __func__);
        return NULL;
    }
    memset(arr, 0, sensor_count * sizeof(double));
    for (int i = 0; i < sensor_count; i++) {
        sum_weight_coefficient += integrated_support_degree_matrix[i];
    }
    for (int i = 0; i < sensor_count; i++) {
        arr[i] = integrated_support_degree_matrix[i] / sum_weight_coefficient;
    }
    return arr;
}

/**
 * \brief Function to compute fused output
 * \details Compute the aggregated value of sensors from the weighted coefficients
 * \param[in] weight_coefficient pointer to weighted coefficient of sensors
 * \param[in] sensor_data pointer to data of sensors
 * \param[in] sensor_count total count of sensors
 * \return Success: fused value of sensor data
 * \return Failure: -1
 */
double compute_fused_output(double *weight_coefficient,
                            double *sensor_data,
                            int sensor_count) {
    double fused_output = 0;
    if ((sensor_count == 0) || (weight_coefficient == NULL) || (sensor_data == NULL)) {
        printf("ERROR: Invalid param passed at %s\n", __func__);
        return -1;
    }
    for (int i = 0; i < sensor_count; i++) {
        fused_output += weight_coefficient[i] * sensor_data[i];
    }
    return fused_output;
}