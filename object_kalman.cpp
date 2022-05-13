#include "object_kalman.hpp"


ObjectKalman::ObjectKalman(const double noise_covariance, const double map_scalar, const double estimated_covariance) {
    Noise_Covariance = noise_covariance;
    Map_Scalar = map_scalar;
    Estimated_Covariance = estimated_covariance;
    Error_Covariance = 0.0;
    Kalman_Gain = 0.0;
    Kalman_Out = 0.0;
}

/*================================================================*/
/*Public Methods*/
/*================================================================*/
double ObjectKalman::kalmanFilter(const double value_in) {
    /*Update Kalman_Gain*/
    Kalman_Gain = (Error_Covariance * Map_Scalar) / (Map_Scalar * Error_Covariance * Map_Scalar + Noise_Covariance);
    
    /*Update Error_Covariance*/
    Error_Covariance = Error_Covariance * (1 - Kalman_Gain * Map_Scalar) + Estimated_Covariance;

    /*Update estimated Kalman_Out*/
    Kalman_Out = Kalman_Out + Kalman_Gain * (value_in - Map_Scalar * Kalman_Out);

    return Kalman_Out;
}