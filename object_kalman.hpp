#ifndef OBJECTKALMAN_HPP
#define OBJECTKALMAN_HPP

class ObjectKalman {

public:
   ObjectKalman(const double = 10.0, const double = 1.0, const double = 10.0);
   double kalmanFilter(const double);

private:
    double Kalman_Gain;
    double Kalman_Out;
    double Error_Covariance;
    double Estimated_Covariance;
    double Map_Scalar;
    double Noise_Covariance; /*Smaller = more reactive/less filtering, Larger = slower/more filtering*/
};

#endif // OBJECTKALMAN_HPP