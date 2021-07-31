#include <math.h>

#include "function_math.hpp"

int mathBinaryToNum(const std::vector<bool>& vector_in) {
  int value_out = 0;
  for (int i = 0; i < static_cast<int>(vector_in.size()); ++i) {
      value_out += vector_in.at(i) * std::pow(2, i);
    }
  return value_out;
}

double mathAverage(const std::vector<double>& vector_in) {
  double value_out = 0.0;
  for (const double value_in : vector_in) {
      value_out += value_in;
    }
  value_out /= static_cast<double>(vector_in.size());
  return value_out;
}

double mathDistanceAngular(const double pos_1, const double pos_2, const double modulus) {
  double value_out = (modulus * 1.5) + (pos_2 - pos_1);
  value_out = mathModulus(value_out, modulus, false) - (modulus / 2.0);
  return value_out;
}

double mathDistanceLinear(const std::vector<double>& pos_1, const std::vector<double>& pos_2) {
  double value_out = 0.0;
  if (pos_1.size() != pos_2.size()) {
      return value_out;
    }
  for (int i = 0; i < static_cast<int>(pos_1.size()); ++i) {
      value_out += std::pow(pos_2.at(i) - pos_1.at(i), 2.0);
    }
  return std::sqrt(value_out);
}

double mathModulus(const double value_in, const double modulus, const bool normalize) {
  double value_out = std::fmod(value_in, modulus);
  if (normalize && value_out < 0.0) {
      value_out += modulus;
    }
  return value_out;
}

double mathNearestAngle(double pos_target, const double pos_current, const double modulus) {
  pos_target = mathModulus(pos_target, modulus, false);
  while (pos_target - pos_current < -1.0 * modulus / 2.0) {
      pos_target += modulus;
    }
  while (pos_target - pos_current > modulus / 2.0) {
      pos_target -= modulus;
    }
  return pos_target;
}

double mathPi() {
  return static_cast<double>(atan(1.0) * 4.0);
}

double mathToDegree(const double radian_in) {
  return static_cast<double>(radian_in * 180.0 / mathPi());
}

double mathToRadian(const double degree_in) {
  return static_cast<double>(degree_in * mathPi() / 180.0);
}

std::vector<bool> mathNumToBinary(int value_in) {
  std::vector<bool> vector_out;
  while (value_in > 0.0) {
      vector_out.push_back(mathModulus(value_in, 2.0, true) > 0.0);
      if (vector_out.back()) {
          --value_in;
        }
      value_in /= 2.0;
    }
  return vector_out;
}
