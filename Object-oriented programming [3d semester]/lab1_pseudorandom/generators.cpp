#include "generators.h"
using namespace std;

const double    PI = acos(-1),
                E = exp(1);




LCG::LCG(int a, int c, int m, int x) {
    maxInt = m;
    this -> a = a;
    this -> c = c;
    this -> m = m;
    this -> x = x;        
}

int LCG::genInt() {
    return x = ((long long) a*x + c) % m;
}


SCG::SCG(int d, int a, int c, int m, int x) {
    maxInt = m;
    this -> d = d;          
    this -> a = a;
    this -> m = m;
    this -> c = c;
    this -> x = x;        
}

int SCG::genInt() {
    return x = ((long long) d*(x*x)%m + a*x + c) % m;
}


LFG::LFG(int m, int x1, int x2) {
    maxInt = m;
    this -> m = m;
    this -> x1 = x1;        
    this -> x2 = x2;        
}

int LFG::genInt() {
    int t = (x1 + x2) % m;
    x2 = x1;
    x1 = t;
    return t;
}



int ICG::inverse(long long x) {
    long long res = 1;
    for (int st=m-2; st; st/=2) {
        if (st%2)
            res = (res * x) % m;
        x = (x*x)%m;                                                  
    }
    return res;
}
ICG::ICG(int a, int c, int m, int x) {
    maxInt = m;
    this -> a = a;
    this -> c = c;
    this -> m = m;
    this -> x = x;
}

int ICG::genInt() {
    return x = ((long long) a * inverse(x) + c) % m;
}



MMG::MMG(int a, int b, int c, int m, int x0) {
    maxInt = m;
    this -> a = a;          
    this -> b = b;
    this -> c = c;
    this -> m = m;
    this -> x0 = x0;
    this -> y = 1;
}

int MMG::genInt() {
    int A = (x0*b + c) % m;
    int x = (A*y + x0) % m;
    y = (a * y) % m;
    return (x-y+m)%m;
}


TSL::TSL(double m, double sig) {
    this -> sig = sig;          
    this -> m = m;
    this -> g = new LFG();
}

double TSL::genReal() {
    double sum = 0;
    for (int i=0; i<12; ++i)
        sum += g -> genReal();
    return m + (sum - 6)*sig;
}


MPM::MPM() {
    this -> g = new LFG();
}

double MPM::genReal() {
    double sum = 1;
    double u1,u2;

    while (sum >= 1) {
        u1 = 2*(g -> genReal())-1;
        u2 = 2*(g -> genReal())-1;

        sum = u1*u1 + u2*u2;
    }

    double x = u1 * sqrt( -2*log(sum)/sum );
    return x;
}


RMG::RMG() {
    g = new LFG();
}

double RMG::genReal() {
    while (1) {
        double u,v;
        u = g -> genReal();
        v = g -> genReal();
        
        if (!u)
            continue;

        double x = sqrt(8/E) * (v - 0.5) / u;

        // if (x*x <= 5-4*exp(0.25)*u)
        //     continue;

        // if (x*x >= 4*exp(-1.35)/u+1.4)
        //     continue;

        if (x*x >= -4*log(u))
            continue;

        return x;
    }
}



LMDG::LMDG(double mu) {
    this -> mu = mu;
    this -> g = new LFG();
}

double LMDG::genReal() {
    return -mu * log(g -> genReal());
}



AGDM::AGDM(double a) {
    this -> a = a;
    this -> g = new LFG();
}

double AGDM::genReal() {
    while (1) {
        double y,x,v,tmp;

        y = tan(PI*(g -> genReal()));
        x = sqrt(2*a - 1)*y + a - 1;
        if (x <= 0)
            continue;

        v = g -> genReal();
        tmp = (1+y*y)*exp((a-1)*log(x/(a-1))-sqrt(2*a-1)*y);
        if (v > tmp)
            continue;

        return x;
    }
}
