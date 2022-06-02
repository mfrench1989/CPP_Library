#include "object_kalman.hpp"


ObjectKalman::ObjectKalman(const double noise_reduction, const double map_scalar, const double estimated_covariance) {
  /*Set initial values*/
  Noise_Reduction = noise_reduction;
  Map_Scalar = map_scalar;
  Estimated_Covariance = estimated_covariance;

  /*Reset calculated values*/
  Error_Value = 0.0;
  Gain_Value = 0.0;
  Kalman_Out = 0.0;
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
void ObjectKalman::kalmanFilter(const double value_in) {
  Gain_Value = kalmanCalc_Gain();
  Error_Value = kalmanCalc_Error();
  Kalman_Out = kalmanCalc_Out(value_in);
}

double ObjectKalman::kalmanCalc_Error() {
  return Error_Value * (1 - Gain_Value * Map_Scalar) + Estimated_Covariance;
}

double ObjectKalman::kalmanCalc_Gain() {
  return (Error_Value * Map_Scalar) / (Map_Scalar * Error_Value * Map_Scalar + Noise_Reduction);
}

double ObjectKalman::kalmanCalc_Out(const double value_in) {
  return Kalman_Out + Gain_Value * (value_in - Map_Scalar * Kalman_Out);
}

double ObjectKalman::kalmanGet_Error() {
  return Error_Value;
}

double ObjectKalman::kalmanGet_Gain() {
  return Gain_Value;
}

double ObjectKalman::kalmanGet_Out() {
  return Kalman_Out;
}
