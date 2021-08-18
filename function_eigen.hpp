#ifndef FUNCTIONEIGEN_HPP
#define FUNCTIONEIGEN_HPP

#include "Eigen/Eigen"

/**
 * @brief eigenQuaternion - calculate the quaternion of a 3x3 rotation matrix
 * @param Matrix3d - rotation matrix
 * @return
 */
Eigen::Quaterniond eigenQuaternion(const Eigen::Matrix3d&);

/**
 * @brief eigenCentroid - calculate the centroid of any number of xyz vectors
 * @param Matrix3Xd - matrix of vectors
 * @return
 */
Eigen::Vector3d eigenCentroid(const Eigen::Matrix3Xd&);

/**
 * @brief eigenCoordTransform - transform a coordinate from current to other coord frame
 * @param Matrix3d - rotation matrix of current -> other frame
 * @param Vector3d - translation vector of current -> other frame
 * @param Vector3d - coordinates in current frame
 * @return
 */
Eigen::Vector3d eigenCoordTransform(const Eigen::Matrix3d&, const Eigen::Vector3d&, const Eigen::Vector3d&);

/**
 * @brief eigenToCartesian - convert spherical Rho,Theta,Phi (angles) coordinates to cartesian X,Y,Z
 *        ISO 80000-2:2019 standard (X/Rho-radius, Y/Theta-Polar Angle, Z/Phi-Azimuth Angle)
 * @param Vector3d - spherical coordinates
 * @return
 */
Eigen::Vector3d eigenToCartesian(const Eigen::Vector3d&);

/**
 * @brief eigenToSpherical - convert catresian X,Y,Z coordinates to spherical Rho,Theta,Phi (angles)
 *        ISO 80000-2:2019 standard (X/Rho-radius, Y/Theta-Polar Angle, Z/Phi-Azimuth Angle)
 * @param Vector3d - cartesian coordinates
 * @return
 */
Eigen::Vector3d eigenToSpherical(const Eigen::Vector3d&);

/**
 * @brief eigenTranslation - calculate the coordinate frame translation
 * @param Matrix3Xd - matrix of xyz coordinate vectors in current coord frame
 * @param Matrix3Xd - matrix of xyz vectors of equivalent position in other coord frame
 * @param Matrix3d - current coord frame rotation matrix
 * @return
 */
Eigen::Vector3d eigenTranslation(const Eigen::Matrix3Xd&, const Eigen::Matrix3Xd&, const Eigen::Matrix3d&);

/**
 * @brief eigenTransposeTranslation - convert current coord frame transform to other coord frame transform
 * @param Matrix3d - current coord frame rotation matrix
 * @param Vector3d - current coord frame translation vector
 * @return
 */
Eigen::Vector3d eigenTransposeTranslation(const Eigen::Matrix3d&, const Eigen::Vector3d&);

/**
 * @brief eigenRotation - convert quaternion into rotation matrix
 * @param Quaterniond - quaternion to convert
 * @return
 */
Eigen::Matrix3d eigenRotation(const Eigen::Quaterniond&);

/**
 * @brief eigenRotation - calculate least squares fit rotation matrix for current coord frame to other coord frame
 * @param Matrix3Xd - matrix of XYZ vectors in current coord frame
 * @param Matrix3Xd - matrix of XYZ vectors in other coord frame
 * @return
 */
Eigen::Matrix3d eigenRotation(const Eigen::Matrix3Xd&, const Eigen::Matrix3Xd&);

#endif // FUNCTIONEIGEN_HPP
