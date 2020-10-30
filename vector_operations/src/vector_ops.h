#pragma once
#include <iostream>
#include <vector>

namespace task {
using std::vector;

const double EPS_1 = 1e-7;

vector<double> operator+(const vector<double> &a, const vector<double> &b) {
  vector<double> out;
  out.reserve(a.size());    
  for (size_t i = 0; i < a.size(); i++) {
    out.push_back(a[i] + b[i]);
  }
  return out;
}

vector<double> operator+(const std::vector<double> &a) { return a; }

vector<double> operator-(const vector<double> &a) {
  vector<double> out;
  out.reserve(a.size());  
  for (size_t i = 0; i < a.size(); i++) {
    out.push_back(-a[i]);
  }
  return out;
}

vector<double> operator-(const vector<double> &a, const vector<double> &b) {
  vector<double> out;
  out.reserve(a.size());  
  for (size_t i = 0; i < a.size(); i++) {
    out.push_back(a[i] - b[i]);
  }
  return out;
}

double operator*(const vector<double> &a, const vector<double> &b) {
  double out = 0.;
  for (size_t i = 0; i < a.size(); i++) {
    out += a[i] * b[i];
  }
  return out;
}

vector<double> operator%(const vector<double> &a, const vector<double> &b) {
  vector<double> out;
  out.push_back(a[1] * b[2] - a[2] * b[1]);
  out.push_back(-a[0] * b[2] + a[2] * b[0]);
  out.push_back(a[0] * b[1] - a[1] * b[0]);
  return out;
}

double vector_cos(const vector<double> &a, const vector<double> &b) {
  double cos = 0.;
  double sqr_a = 0., sqr_b = 0.;
  for (size_t i = 0; i < a.size(); i++) {
    cos += a[i] * b[i];
    sqr_a += a[i] * a[i];
    sqr_b += b[i] * b[i];
  }
  if (sqr_a < EPS_1 || sqr_b < EPS_1) return 1.; // assuming here we're not checking orthogonality
  cos /= sqrt(sqr_a) * sqrt(sqr_b);
  return cos;
}

bool operator||(const vector<double> &a, const vector<double> &b) {
  double cos = vector_cos(a, b);
  return !(1 - cos > EPS_1) || !(1 + cos > EPS_1);
}

bool operator&&(const vector<double> &a, const vector<double> &b) {
  double cos = vector_cos(a, b);;
  return !(1 - cos > EPS_1);
}

std::ostream &operator<<(std::ostream &s, vector<double> &a) {
  for (size_t i = 0; i < a.size(); i++) {
    s << a[i];
    if (i != a.size() - 1) s << " ";
  }
  s << "\n";
  return s;
}

std::istream &operator>>(std::istream &s, vector<double> &a) {
  unsigned long long n;
  double buf;
  a.clear();
  s >> n;
  for (size_t i = 0; i < n; i++) {
    s >> buf;
    a.push_back(buf);
  }
  return s;
}

vector<double> reverse(vector<double> &a) {
  vector<double> out;
  out.reserve(a.size());  
  size_t size_of_a = a.size();

  for (size_t i = 0; i < size_of_a; i++) {
    out.push_back(a.back());
    a.pop_back();
  }
  a = out;
  return a;
}

vector<int> operator|(const vector<int> &a, const vector<int> &b) {
  vector<int> out;
  out.reserve(a.size());  
  for (size_t i = 0; i < a.size(); i++) {
    out.push_back(a[i] | b[i]);
  }
  return out;
}

vector<int> operator&(const vector<int> &a, const vector<int> &b) {
  vector<int> out;
  out.reserve(a.size());  
  for (size_t i = 0; i < a.size(); i++) {
    out.push_back(a[i] & b[i]);
  }
  return out;
}

}  // namespace task
