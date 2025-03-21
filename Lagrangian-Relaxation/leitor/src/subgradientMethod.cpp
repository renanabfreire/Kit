#include "LagrangianRelaxation.h"

vector<double> subgradientMethod(SolutionLambda& xselect,int dimension, double** costMatrix, double epsilon, double UB, int kMax, double epsilonMin, vector<double>& lambdaselect){
    // starting lambda vector
    std::vector<double> lambda(dimension-1, 0);
    // starting used variable
    int k=0;
    SolutionLambda x;
    xselect.cost = 0;

    while(1)
    {
        // solving the relaxed solution with the Lagrangian Multiplier
        solveLambda(dimension, costMatrix, x, lambda);

        // Updating variables
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

        // Getting next lambda
        vector<int> cont(lambda.size(), 0);
        for(const auto& edge : x.edges) {
                cont[edge.first]++;
                cont[edge.second]++;
        }
        for(int i=0; i<lambda.size(); i++){
            if(cont[i] != 2)
                lambda[i] = lambdaselect[i] + epsilon * (UB - xselect.cost) / (2 - cont[i]);
            else
                lambda[i] = lambdaselect[i];
        }

        if(x.cost > UB || epsilon < epsilonMin){
            break;
        }
    }

    return lambdaselect;
}