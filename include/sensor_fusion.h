/**
 * \brief Function Prototype Library to implement Sensor Fusion Algorithm
 * \author jaspalsingh@cmail.carleton.ca
 * \version 1.0
 * \date 2019-12-01
 */

#ifndef SENSOR_FUSION_H
#define SENSOR_FUSION_H

/**
 * \brief Structure for storing support degree matrix
 * \details For the given number of sensors the structure will store support degree matrix
 */
typedef struct support_degree_matrix {
    int sensor_count;
    double *sd_matrix;
} support_degree_matrix_t;

/**
 * \brief Structure for storing eigen value and eigen vector
 * \details For a given support degree matrix of
 * sensors the corresponding eigen values and vectors are stored in structure
 */
typedef struct eigen_value_vector {
    double *eigen_value;
    double **eigen_vector;
}eigen_value_vector_t;

/**
 * \brief Structure to store computed support degree matrix
 * \details Structure pointer for calculating support degree matrix
 * \param[in] sensor_readings array of sensor readings
 * \return Success: pointer to the structure support_degree_matrix
 * \return Failure: NULL
 */
struct support_degree_matrix *compute_support_degree_matrix(double *sensor_readings);

/**
 * \brief Structure to store computed eigen value and eigen vector
 * \details Structure pointer for calculating eigen value and eigen vector
 * \param[in] support_degree_matrix pointer to structure support degree matrix
 * \return Success: pointer to structure eigen_value_vector
 * \return Failure: NULL
 */
struct eigen_value_vector *compute_eigen(struct support_degree_matrix *spd);

/**
 * \brief Function to calculate the contribution rate of principal component
 * \details Compute the contribution rate of kth and mth principal components
 */
double *compute_contribution_rate(struct eigen_value_vector *eigen,
                                  int sensor_count);

/**
 * \brief Function to compute contribution rate
 * \details Compute the count of contribution rates to be used for sensors
 */
int compute_contrib_rate_count(double *contribution_rate,
                               float parameter,
                               int sensor_count);

/**
 * \brief Function to compute principal component
 * \details Computed principal component for each of eigen vector
 */
double **compute_principal_component(struct support_degree_matrix *spd,
                                     double **eigen_vector,
                                     int contrib_rate_count);

/**
 * \brief Function to compute integrated support degree
 * \details Computed support degree matrix for each of the sensors
 */
double *compute_integrated_support_degree(double **principle_components,
                                          double *contribution_rate,
                                          int contrib_rate_count,
                                          int sensor_count);

/**
 * \brief Function to eliminate invalid sensor readings
 * \details Discard the faulty sensor readings from the support degree matrix
 */
int eliminate_incorrect_data(double *integrated_support_degree_matrix,
                             double fault_tolerance,
                             int sensor_count);

/**
 * \brief Function to compute weight coefficient for each sensor
 * \details Compute weighted coefficients for each sensors from the support degree matrix
 */
double *compute_weight_coefficient(double *integrated_support_degree_matrix,
                                   int sensor_count);

/**
 * \brief Function to compute fused output
 * \details Compute the aggregated value of sensors from the weighted coefficients
 */
double compute_fused_output(double *weight_coefficient,
                            double *sensor_data,
                            int sensor_count);

#endif // SENSOR_FUSION_H