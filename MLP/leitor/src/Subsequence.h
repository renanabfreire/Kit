#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#include <vector>
#include "Data.h"

typedef struct
{
    double T, C;
    int W;
    int first, last;
} Subsequence;

inline static Subsequence Concatenate(Subsequence& sigma1, Subsequence& sigma2, Data& t)
{
    Subsequence sigma;

    double temp = t.getDistance(sigma1.last, sigma2.first);

    sigma.W = sigma1.W + sigma2.W;
    sigma.T = sigma1.T + temp + sigma2.T;
    sigma.C = sigma1.C + sigma2.W*(sigma1.T + temp) + sigma2.C;
    sigma.first = sigma1.first;
    sigma.last = sigma2.last;

    return sigma;
}

#endif //SUBSEQUENCE_H