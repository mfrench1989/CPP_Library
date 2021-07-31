#include "function_math.hpp"

#include "function_eigen.hpp"

Eigen::Quaterniond eigenQuaternion(const Eigen::Matrix3d& rotation_in) {
  return Eigen::Quaterniond(rotation_in);
}

Eigen::Vector3d eigenCentroid(const Eigen::Matrix3Xd& matrix_in) {
  return Eigen::Vector3d(matrix_in.rowwise().mean());
}

Eigen::Vector3d eigenCoordTransform(const Eigen::Matrix3d& rot_in, const Eigen::Vector3d& trans_in, const Eigen::Vector3d& coord_in) {
  return Eigen::Vector3d(rot_in * coord_in + trans_in);
}

Eigen::Vector3d eigenToCartesian(const Eigen::Vector3d& spherical_in) {
  /*ISO 80000-2:2019 standard (X/R-radius, Y/Theta-Polar Angle, Z/Phi-Azimuth Angle)*/
  Eigen::Vector3d cartesian_out;
  cartesian_out(0) = spherical_in.x() * std::sin(mathToRadian(spherical_in.y())) * std::cos(mathToRadian(spherical_in.z()));
  cartesian_out(1) = spherical_in.x() * std::sin(mathToRadian(spherical_in.y())) * std::sin(mathToRadian(spherical_in.z()));
  cartesian_out(2) = spherical_in.x() * std::cos(mathToRadian(spherical_in.y()));
  return cartesian_out;
}

Eigen::Vector3d eigenToSpherical(const Eigen::Vector3d& cartesian_in) {
  /*ISO 80000-2:2019 standard (X/R-radius, Y/Theta-Polar Angle, Z/Phi-Azimuth Angle)*/
  Eigen::Vector3d spherical_out;

  /*Radius distance*/
  spherical_out(0) = std::sqrt(std::pow(cartesian_in.x(), 2) + std::pow(cartesian_in.y(), 2) + std::pow(cartesian_in.z(), 2));

  /*Polar angle*/
  spherical_out(1) = mathToDegree(std::atan2(std::sqrt(std::pow(cartesian_in.x(), 2) + std::pow(cartesian_in.y(), 2)), cartesian_in.z()));

  /*Azimuth angle*/
  spherical_out(2) = mathToDegree(std::atan2(cartesian_in.y(), cartesian_in.x()));
  return spherical_out;
}

Eigen::Vector3d eigenTranslation(const Eigen::Matrix3Xd& matrix_1, const Eigen::Matrix3Xd& matrix_2, const Eigen::Matrix3d& rot_in) {
  return Eigen::Vector3d(eigenCentroid(matrix_2) - rot_in * eigenCentroid(matrix_1));
}

Eigen::Vector3d eigenTransposeTranslation(const Eigen::Matrix3d& rot_in, const Eigen::Vector3d& trans_in) {
  return Eigen::Vector3d(rot_in.transpose() * trans_in * -1.0);
}

Eigen::Matrix3d eigenRotation(const Eigen::Quaterniond& quat_in) {
  return Eigen::Matrix3d(quat_in.toRotationMatrix());
}

Eigen::Matrix3d eigenRotation(const Eigen::Matrix3Xd& matrix_1, const Eigen::Matrix3Xd& matrix_2) {
  /*Calculate symmetric matrix ABt such that both matrices are re-centered on the origin*/
  Eigen::Matrix3d matrix_sym = (matrix_1.colwise() - eigenCentroid(matrix_1)) * (matrix_2.colwise() - eigenCentroid(matrix_2)).transpose();

  /*Perform SVD calculation of matrix_sym*/
  Eigen::JacobiSVD<Eigen::MatrixXd> eigen_svd(matrix_sym, Eigen::ComputeFullU | Eigen::ComputeFullV);

  /*Calculate rotation matrix*/
  Eigen::Matrix3d rotation_out = eigen_svd.matrixV() * eigen_svd.matrixU().transpose();

  /*Check special reflection case, which happens when determinant of matrix_rotation < 0*/
  if (rotation_out.determinant() < 0) {
      /*If reflection multiply 3rd column of V by -1*/
      Eigen::Matrix3d matrix_v = eigen_svd.matrixV();
      matrix_v.col(2) *= -1;
      rotation_out = matrix_v * eigen_svd.matrixU().transpose();
    }

  return rotation_out;
}
