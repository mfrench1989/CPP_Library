#ifndef OBJECTKALMAN_HPP
#define OBJECTKALMAN_HPP

class ObjectKalman {

public:
   ObjectKalman(const double = 10.0, const double = 1.0, const double = 10.0);
   void kalmanFilter(const double);
   double kalmanCalc_Error();
   double kalmanCalc_Gain();
   double kalmanCalc_Out(const double);
   double kalmanGet_Error();
   double kalmanGet_Gain();
   double kalmanGet_Out();

private:
    double Gain_Value;
    double Kalman_Out;
    double Error_Value;
    double Estimated_Covariance;
    double Map_Scalar;
    double Noise_Reduction;
};

#endif // OBJECTKALMAN_HPP
