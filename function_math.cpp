#include <algorithm>
#include <math.h>
#include <numeric>

#include "function_math.hpp"

int mathBinaryToNum(const std::vector<bool>& vector_in) {
  int value_out = 0;
  for (int i = 0; i < static_cast<int>(vector_in.size()); ++i) {
      value_out += vector_in.at(i) * std::pow(2, i);
    }
  return value_out;
}

double mathAverage(const std::vector<double>& vector_in) {
  return std::accumulate(vector_in.begin(), vector_in.end(), 0.0) / static_cast<double>(vector_in.size());
}

double mathDistanceAngular(const double pos_1, const double pos_2, const double modulus) {
  double value_out = (modulus * 1.5) + (pos_2 - pos_1);
  value_out = mathModulus(value_out, modulus, true) - (modulus / 2.0);
  return value_out;
}

double mathDistanceLinear(const std::vector<double>& pos_1, const std::vector<double>& pos_2) {
  if (pos_1.size() != pos_2.size()) {
      return std::numeric_limits<double>::quiet_NaN();
    }
  double value_out = 0.0;
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
  /*Get pos_target close to pos_current, this limits while loops for large numbers*/
  pos_target = mathModulus(pos_target, modulus, false) + (modulus * std::round(pos_current / modulus));
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

double mathStandardDeviation(const std::vector<double>& vector_in) {
  if (vector_in.empty()) {
      return 0.0;
    }

  double sample_mean = mathAverage(vector_in);

  std::vector<double> vector_diff(vector_in.size());
  std::transform(vector_in.begin(), vector_in.end(), vector_diff.begin(), [sample_mean](double x) {return x - sample_mean;});

  double square_sum = std::inner_product(vector_diff.begin(), vector_diff.end(), vector_diff.begin(), 0.0);
  return std::sqrt(square_sum / (vector_in.size() - (vector_in.size() >= 2 ? 1 : 0)));
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
