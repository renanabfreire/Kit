#include "LagrangianRelaxation.h"

bool subgradientMethod(SolutionLambda& xselect,int dimension, double** costMatrix, double epsilon, double UB, int kMax, double epsilonMin, vector<double>& lambdaselect){
    // starting lambda vector
    std::vector<double> lambda(dimension-1, 0);
    // starting used variable
    int k=0;
    SolutionLambda x;
    xselect.cost = 0;
    
    while(epsilon > epsilonMin)
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
            if(k >= kMax){
                epsilon /= 2;
                k=0;
            }
        }

        // Getting next lambda
        vector<int> cont(lambda.size(), 0);
        double mi=0;
        double sum=0;
        for(const auto& edge : x.edges) {
                cont[edge.first]++;
                cont[edge.second]++;
        }
        for(int i=0; i<lambda.size(); i++){
            sum += (2 - cont[i])*(2-cont[i]);
        }
        if(sum == 0){ // if is feasible, just return the solution
            xselect = x;
            lambdaselect = lambda;
            return true;
        }
        mi = epsilon*(UB - x.cost)/sum;
        for(int i=0; i<lambda.size(); i++){
            lambda[i] = lambda[i] + mi*(2-cont[i]);
        }
    }

    return false;
}