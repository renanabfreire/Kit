#include "LagrangianRelaxation.h"

void subgradientMethod(SolutionLambda& xselect,int dimension, double** costMatrix, double epsilon, double UB, int kMax, double epsilonMin){
    std::vector<double> lambda(dimension-1, 0);
    std::vector<double> lambdaselect(dimension-1, 0);
    int k=0;
    SolutionLambda x;
    xselect.cost = 0;

    while(1)
    {
        solveLambda(dimension, costMatrix, x, lambda);

        if(x.cost > xselect.cost){
            xselect = x;
            lambdaselect = lambda;
            k=0;
        }else{
            k++;
            epsilon /= 2;
            if(k >= kMax)
                k=0;
        }
        for(int i=0; i<lambda.size(); i++){
            int cont = 0;
            for(const auto& edge : x.edges) {
                if(edge.first == i || edge.second == i)
                    cont++;
            }
            if(cont != 2)
                lambda[i] = lambdaselect[i] + epsilon * (UB - xselect.cost) / (2 - cont);
            else
                lambda[i] = lambdaselect[i];
        }

        if(x.cost > UB || epsilon < epsilonMin){
            break;
        }
    }
}