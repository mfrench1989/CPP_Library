#ifndef FUNCTIONEIGEN_HPP
#define FUNCTIONEIGEN_HPP

#include "Eigen/Eigen"

/*================ NOTES ================*/
/*The current frame is base*/
/*The other frame is object*/
/*=======================================*/

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
 * @brief eigenCoordTransform - transform a coordinate from base frame to object frame
 * @param Matrix3d - rotation matrix of base -> object frame
 * @param Vector3d - translation vector of base -> object frame
 * @param Vector3d - coordinates in base frame
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
 * @param Matrix3Xd - matrix of xyz coordinate vectors in base coordinate frame
 * @param Matrix3Xd - matrix of xyz vectors of equivalent position in coordinate frame
 * @param Matrix3d - rotation matrix of coordinate frame
 * @return
 */
Eigen::Vector3d eigenTranslation(const Eigen::Matrix3Xd&, const Eigen::Matrix3Xd&, const Eigen::Matrix3d&);

/**
 * @brief eigenTransposeTranslation - convert translation for opposite direction transformation
 * @param Matrix3d - rotation matrix of original transformation
 * @param Vector3d - translation vector of original transformation
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
 * @brief eigenRotation - calculate least squares fit rotation matrix to convert from one matrix to the other using any number of XYZ vectors
 * @param Matrix3Xd - matrix of XYZ vectors in original base coordinate frame
 * @param Matrix3Xd - matrix of XYZ vectors in equivalent object coordinate frame
 * @return
 */
Eigen::Matrix3d eigenRotation(const Eigen::Matrix3Xd&, const Eigen::Matrix3Xd&);

#endif // FUNCTIONEIGEN_HPP
