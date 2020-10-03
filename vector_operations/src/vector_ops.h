#pragma once
#include <vector>
#include <iostream>




namespace task {
    using std::vector;

    vector<double> operator+ (const vector<double> &a, 
                              const vector<double> &b) { //+
        vector<double> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] + b[i]);
        }
        return out;
    }

    vector<double> operator+ (const vector<double> &a) {//+
        return a;
    }
    
    vector<double> operator- (const vector<double> &a) { //+
        vector<double> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(-a[i]);
        }
        return out;
    }

    vector<double> operator- (const vector<double> &a, 
                              const vector<double> &b) { //+
        vector<double> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] - b[i]);
        }
        return out;
    }
    
    
    double operator* (const vector<double> &a, 
                      const vector<double> &b) { //+
        double out;
        for(size_t i = 0; i < a.size(); i++) {
            out += a[i] * b[i];
        }
        return out;
    }

    //--------------------------------------------------------------------------------------------------

    vector<double> operator% (const vector<double> &a, 
                              const vector<double> &b) {
        vector<double> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] - b[i]);
        }
        return out;
    }

    vector<double> operator|| (const vector<double> &a, 
                               const vector<double> &b) {
        vector<double> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] - b[i]);
        }
        return out;
    }

    vector<double> operator&& (const vector<double> &a, 
                               const vector<double> &b) {
        vector<double> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] - b[i]);
        }
        return out;
    }

    std::ostream& operator<< (std::ostream &s, 
                              vector<double> &a) { //+
        for(size_t i = 0; i < a.size(); i++) {
            s << a[i];
        }
        return s;
    }

    std::istream& operator>> (std::istream &s, 
                              vector<double> &a) { //+
        size_t n;
        double buf;
        s >> n;
        for(size_t i = 0; i < n; i++) {
            s >> buf;
            a[i] = buf;
        }
        return s;
    }    

    vector<double> reverse (const vector<double> &a) {  // +
        vector<double> out;
        for(size_t i = a.size() - 1; i >= 0; i--) {
            out.push_back(a[i]);
        }
        return out;
    }


    vector<int> operator| (vector<int> &a, vector<int> &b) {
        vector<int> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] | b[i]);
        }
        return out;
    }

    vector<int> operator& (vector<int> &a, vector<int> &b) {
        vector<int> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] & b[i]);
        }
        return out;
    }
    

// Your code here...


}  // namespace task
