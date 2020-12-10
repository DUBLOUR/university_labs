/// Nikitenko Max, K-22

const int   N = 2,  
            M = 1,
            N_c = 2,
            N_s = 2,
            N_e_start = 2,
            N_l_start = 2,
            N_e = N_e_start,
            N_l = N_l_start,
            // N_e = (N_e_start - N_l_start >= 0 ? N_e_start - N_l_start : 0),
            // N_l = (N_e_start - N_l_start >= 0 ? 0 : N_l_start - N_e_start),
            DEPTH = 9;



namespace mt
{
    template <int N> 
    struct fact {
        static const long double value;
    };

    template <int N> 
    const long double fact<N>::value = N * (fact<N-1>::value);

    template <> 
    struct fact<0> {
        static const long double value;
    };

    const long double fact<0>::value = 1;


    template <class X, int N> 
    struct power {
        static const long double value;
    };

    template <class X, int N> 
    const long double power<X, N>::value = X::value * power<X, N-1>::value;

    template <class X>
    struct power<X, 0> {
        static const long double value;
    };

    template <class X> 
    const long double power<X, 0>::value = 1.0;


    // COSH ===================================================================
    template<class X, int D>
    struct _cosh {
        static const long double value;
    };
    template<class X, int D>
    const long double _cosh<X, D>::value = 
        (power<X, 2*D>::value) / (fact<2*D>::value) + (_cosh<X, D-1>::value);

    
    template<class X>
    struct _cosh<X, -1> {
        static const long double value;
    };
    template<class X>
    const long double _cosh<X, -1>::value = 0;


    template<class X>
    struct cosh {
        static const long double value;
    };
    template<class X>
    const long double cosh<X>::value = _cosh<X, DEPTH-1>::value;


    template<class X, int N>
    struct cosh_it {
        static const long double value;
    };
    template<class X, int N>
    const long double cosh_it<X, N>::value = cosh < cosh_it<X, N-1> >::value;

    template<class X>
    struct cosh_it<X, 0> {
        static const long double value;
    };
    template<class X>
    const long double cosh_it<X, 0>::value = X::value;


    // SINH ===================================================================
    template<class X, int D>
    struct _sinh {
        static const long double value;
    };
    template<class X, int D>
    const long double _sinh<X, D>::value = 
        (power<X, 2*D+1>::value) / (fact<2*D+1>::value) + (_sinh<X, D-1>::value);

    
    template<class X>
    struct _sinh<X, -1> {
        static const long double value;
    };
    template<class X>
    const long double _sinh<X, -1>::value = 0;


    template<class X>
    struct sinh {
        static const long double value;
    };
    template<class X>
    const long double sinh<X>::value = _sinh<X, DEPTH-1>::value;


    template<class X, int N>
    struct sinh_it {
        static const long double value;
    };
    template<class X, int N>
    const long double sinh_it<X, N>::value = sinh < sinh_it<X, N-1> >::value;

    template<class X>
    struct sinh_it<X, 0> {
        static const long double value;
    };
    template<class X>
    const long double sinh_it<X, 0>::value = X::value;


    // EXP ===================================================================
    template<class X, int D>
    struct _exp {
        static const long double value;
    };
    template<class X, int D>
    const long double _exp<X, D>::value = 
        (power<X, D>::value) / (fact<D>::value) + (_exp<X, D-1>::value);

    
    template<class X>
    struct _exp<X, -1> {
        static const long double value;
    };
    template<class X>
    const long double _exp<X, -1>::value = 0;


    template<class X>
    struct exp {
        static const long double value;
    };
    template<class X>
    const long double exp<X>::value = _exp<X, DEPTH-1>::value;


    template<class X, int N>
    struct exp_it {
        static const long double value;
    };
    template<class X, int N>
    const long double exp_it<X, N>::value = exp < exp_it<X, N-1> >::value;

    template<class X>
    struct exp_it<X, 0> {
        static const long double value;
    };
    template<class X>
    const long double exp_it<X, 0>::value = X::value;


    // LOG ===================================================================
    

    template<class X, int D>
    struct _log {
        static const long double value;
    };
    template<class X, int D>
    const long double _log<X, D>::value = 
        (power<X, D*2-1>::value) / (2*D-1) + (_log<X, D-1>::value);

    
    template<class X>
    struct _log<X, 0> {
        static const long double value;
    };
    template<class X>
    const long double _log<X, 0>::value = 0;

    template<class X>
    struct log {
        static const long double value;
        struct x {
            static const long double value;
        };
    };
    template<class X>
    const long double log<X>::x::value = (long double) (X::value - 1)/(X::value + 1);
    
    template<class X>
    const long double log<X>::value = 2 * _log<log<X>::x, DEPTH-1>::value;


    template<class X, int N>
    struct log_it {
        static const long double value;
    };
    template<class X, int N>
    const long double log_it<X, N>::value = log < log_it<X, N-1> >::value;

    template<class X>
    struct log_it<X, 0> {
        static const long double value;
    };
    template<class X>
    const long double log_it<X, 0>::value = X::value;


    template<template<class> class FUNC, class X, int N>
    struct iter_func {
        static const long double value;
    };

    template<template<class> class FUNC, class X, int N>
    const long double iter_func<template<class> class FUNC, class X, int N>::value = 
        FUNC< iter_func<FUNC, X, N-1> >::value;

    // template<class FUNC, class X>
    // struct iter_func<FUNC, X, 0> {
    //     static const long double value;
    // };

    // template<class FUNC, class X>
    // const long double iter_func<class FUNC, class X, 0>::value = X::value;


}



#include<bits/stdc++.h>


struct var {
    static const long double value;
};

const long double var::value = (long double) M/N;


long long fact(int n) {
    if (!n) return 1;
    return n*fact(n-1);
}

long double my_cosh(long double x) {
    long double res = 0;
    for (int i=0; i<DEPTH; ++i)
        res += pow(x, 2*i) / fact(2*i);
    return res;
}

long double my_sinh(long double x) {
    long double res = 0;
    for (int i=0; i<DEPTH; ++i)
        res += pow(x, 2*i+1) / fact(2*i+1);
    return res;
}


long double my_exp(long double x) {
    long double res = 0;
    for (int i=0; i<DEPTH; ++i)
        res += pow(x, i) / fact(i);
    return res;
}

long double my_log(long double z) {
    long double x = (z-1)/(z+1),
                res = 0;
    for (int i=1; i<DEPTH; ++i)
        res += pow(x, i*2-1) / (i*2-1);
    return 2*res;
}

long double  ch_it(int it, long double x) {while (it--) x = my_cosh(x); return x;}
long double  sh_it(int it, long double x) {while (it--) x = my_sinh(x); return x;}
long double log_it(int it, long double x) {while (it--) x = my_log(x);  return x;}
long double exp_it(int it, long double x) {while (it--) x = my_exp(x);  return x;}

int main()
{    
    std::cout << std::fixed << std::setprecision(20) << '\n';

    std::cout << ch_it(N_c, sh_it(N_s, log_it(N_l, exp_it(N_e, var::value)))) << '\n';
    std::cout << mt::cosh_it< mt::sinh_it<var, N_s>, N_c>::value << '\n';
    std::cout << 1.7405810099741901268656597979426887081374700276298478143021 << '\n';

    // Debug:
    // std::cout << my_log(var::value) << '\n';
    // std::cout << log(var::value) << '\n';
    // std::cout << mt::log<var>::value << "\n\n";

    // std::cout << my_cosh(my_cosh(var::value)) << '\n';
    // std::cout << mt::cosh<mt::cosh<var>>::value << "\n";
    // std::cout << mt::cosh_it<var, 2>::value << "\n\n";

    // std::cout << exp(exp(var::value)) << '\n';
    // std::cout << exp_it(2, var::value) << '\n';
    // std::cout << mt::exp_it<var, 2>::value << "\n\n";

    // std::cout << log(var::value) << '\n';
    // std::cout << my_log(var::value) << '\n';
    // std::cout << mt::log_it<var, 1>::value << "\n\n";

    // std::cout << log(log(exp(exp(var::value)))) << '\n';
    // std::cout << log_it(2, exp_it(1, var::value)) << '\n';
    // std::cout << mt::log_it<mt::exp_it<var, 1>, 2>::value << "\n\n";

    // std::cout << log(exp(var::value)) << '\n';
    // std::cout << log_it(2, exp_it(1, var::value)) << '\n';
    // std::cout << mt::log_it<mt::exp_it<var, 1>, 2>::value << "\n\n";



}
