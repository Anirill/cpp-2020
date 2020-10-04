#pragma once
#include <vector>
#include <iostream>




namespace task {
    using std::vector;

    const double EPS_1 = 1e-7;

    vector<double> operator+ (const vector<double> &a, 
                              const vector<double> &b) { //+
        vector<double> out;
        for (size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] + b[i]);
        }
        return out;
    }

    vector<double> operator+ (const std::vector<double> &a) {//+
        return a;
    }
    
    vector<double> operator- (const vector<double> &a) { //+
        vector<double> out;
        for (size_t i = 0; i < a.size(); i++) {
           out.push_back(-a[i]);
        }
        return out;
    }

    vector<double> operator- (const vector<double> &a, 
                              const vector<double> &b) { //+
        vector<double> out;
        for (size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] - b[i]);
        }
        return out;
    }
    
    
    double operator* (const vector<double> &a, 
                      const vector<double> &b) { //+
        double out = 0.;
        for (size_t i = 0; i < a.size(); i++) {
            out += a[i] * b[i];
        }
        return out;
    }


    vector<double> operator% (const vector<double> &a, 
                              const vector<double> &b) {
        vector<double> out;
        out.push_back(a[1] * b[2] - a[2] * b[1]);
        out.push_back(- a[0] * b[2] +  a[2] * b[0]);
        out.push_back(a[0] * b[1] - a[1] * b[0]);
        return out;
    }

    //--------------------------------------------------------------------------------------------------

    bool operator|| (const vector<double> &a, 
                     const vector<double> &b) {
/*        vector<double> out;
        for (size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] - b[i]);
        } */
//        return a * b < EPS_1;
        double cos = 0.;
        double sqr_a = 0., sqr_b = 0.;
        for (size_t i = 0; i < a.size(); i++) {
            cos += a[i] * b[i];
            sqr_a += a[i] * a[i];
            sqr_b += b[i] * b[i];
        }
        cos /= sqrt(sqr_a) * sqrt(sqr_b);
        return !(1 - cos > EPS_1) || !(1 + cos > EPS_1) ;


    }

    bool operator&& (const vector<double> &a, 
                     const vector<double> &b) {
        double cos = 0.;
        double sqr_a = 0., sqr_b = 0.;
        for (size_t i = 0; i < a.size(); i++) {
            cos += a[i] * b[i];
            sqr_a += a[i] * a[i];
            sqr_b += b[i] * b[i];
        }
        cos /= sqrt(sqr_a) * sqrt(sqr_b);
        return !(1 - cos > EPS_1);
    }

    std::stringstream& operator<< (std::stringstream &s, 
                              vector<double> &a) { //+
        for(size_t i = 0; i < a.size(); i++) {
            s << a[i];
	    if(i != a.size() - 1) s << " "; 
        }
	s << "\n";
        return s;
    }

    std::stringstream& operator>> (std::stringstream &s, 
                              vector<double> &a) { //+
        unsigned long long n;
        double buf;
	vector<double> out = {};
	//a.clear(); 
	//while(!a.empty()) a.pop_back();
	s >> n;
	if(n == 0) {
	    if(a.empty()) printf("+");
	    //while(!a.empty()) a.pop_back();
	    //a.clear();
	    return s;
	}
        for (size_t i = 0; i < n; i++) {
            printf("-");
            s >> buf;
            out.push_back(buf);
        }
	a = out;
	//printf("%b ", a.empty());
        return s;
    }    

    vector<double> reverse (vector<double> &a) {  // +
        vector<double> out;
        for(size_t i = a.size() - 1; i >= 0; i--) {
            out.push_back(a[i]);
        }
        a = out;
        return a;
    }


    vector<int> operator| (const vector<int> &a, const vector<int> &b) {
        vector<int> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] | b[i]);
        }
        return out;
    }

    vector<int> operator& (const vector<int> &a, const vector<int> &b) {
        vector<int> out;
        for(size_t i = 0; i < a.size(); i++) {
            out.push_back(a[i] & b[i]);
        }
        return out;
    }
    

// Your code here...


}  // namespace task
