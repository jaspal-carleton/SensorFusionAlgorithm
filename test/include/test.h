/**
 * \brief Function Prototype Library to implement Sensor Fusion Algorithm
 * \author jaspalsingh@cmail.carleton.ca
 * \version 1.0
 * \date 2019-12-01
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sensor_fusion.h"

/**
 * \brief Function to test support degree matrix
 * \details Test the support degree matrix for given value of sensors
 */
void test_support_degree_matrix(void);

/**
 * \brief Function to test eigen
 * \details Test the eigne vector and value for given value of sensors
 */
void test_eigen(void);

/**
 * \brief Function to test contribution rate
 * \details Test the contribution rate for given value of sensors
 */
void test_contrib_rate(void);

/**
 * \brief Function to test contribution rate count
 * \details Test the contribution rate count for given value of sensors
 */
void test_contrib_rate_count(void);

/**
 * \brief Function to test principal components
 * \details Test the principal components for given value of sensors
 */
void test_principal_component(void);

/**
 * \brief Function to test integrated support degree matrix
 * \details Test the integrated support degree matrix for given value of sensors
 */
void test_integrated_support_degree(void);

/**
 * \brief Function to test incorrect data
 * \details Test the incorrect data for given value of sensors
 */
void test_incorrect_data(void);

/**
 * \brief Function to test weight coefficient
 * \details Test the weight coefficient for given value of sensors
 */
void test_weight_coefficient(void);

/**
 * \brief Function to test fused output
 * \details Test the aggregated value of sensors from the weighted coefficients
 */
void test_fused_output(void);

/**
 * \brief Function to test all test cases
 * \details Automatically Test all the test cases for sensor fusion
 */
void test_all(void);

#endif // TEST_H