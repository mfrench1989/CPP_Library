#ifndef FUNCTIONMATH2_HPP
#define FUNCTIONMATH2_HPP

#include <vector>

/**
 * @brief mathBinaryToNum - convert vector of bool binary value to integer (positive only), index 0 == least significant
 * @param vector<bool> - binary value in vector form
 * @return
 */
int mathBinaryToNum(const std::vector<bool>&);

/**
 * @brief mathAverage - calculate the average value of the vector
 * @param vector<double> - values to average
 * @return
 */
double mathAverage(const std::vector<double>&);

/**
 * @brief mathDistanceAngle - calculate the angular distance between two values with configurable repeatable distances
 * @param double - position 1
 * @param double - position 2
 * @param double - modulus value for repeating positions (0 == 360)
 * @return
 */
double mathDistanceAngular(const double, const double, const double);

/**
 * @brief mathDistanceLinear - N-dimensional distance calculation
 * @param vector<double> - position 1
 * @param vector<double> - position 2
 * @return
 */
double mathDistanceLinear(const std::vector<double>&, const std::vector<double>&);

/**
 * @brief mathModulus - calculate the modulus of a value, option to return as positive only
 * @param double - value to calculate
 * @param double - modulus
 * @param bool - flag to convert to positive modulus or not
 * @return
 */
double mathModulus(const double, const double, const bool);

/**
 * @brief mathNearestAngle - calculate the nearest equivalant target position to the current, given the modulus of repeating positions
 * @param double - target position to find nearest equivalant position
 * @param double - current position to base nearest equivalent position off of
 * @param double - modulus of repeating position values (0 == 360)
 * @return
 */
double mathNearestAngle(double, const double, const double);

/**
 * @brief mathPi - quick way to get double precision pi value
 * @return
 */
double mathPi();

/**
 * @brief mathStandardDeviation - calculate the standard deviation of the vector
 * @return
 */
double mathStandardDeviation(const std::vector<double>&);

/**
 * @brief mathToDegree - calculate degree from a radian
 * @param double - radian value to convert
 * @return
 */
double mathToDegree(const double);

/**
 * @brief mathToRadian - calculate radian from a degree
 * @param double - degree value to convert
 * @return
 */
double mathToRadian(const double);

/**
 * @brief mathNumToBinary - calculate a binary vector value from a passed integer (positive only), index 0 == least significant
 * @param int - positive integer value to convert
 * @return
 */
std::vector<bool> mathNumToBinary(int);

#endif // FUNCTIONMATH2_HPP
