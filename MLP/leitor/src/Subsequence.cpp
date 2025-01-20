#include "Ils.h"

// Função para atualização de subsequências
void UpdateAllSubseq(Solution s, vector<vector<Subsequence>> &subseqMatrix, Data &t)
{
    int n = s.sequence.size();
    subseqMatrix[0][0].W = 0;
    // Atualiza diagonal principal
    for(int i = 0; i<n; i++)
    {
        if(i != 0)
            subseqMatrix[i][i].W = 1;
        subseqMatrix[i][i].C = 0;
        subseqMatrix[i][i].T = 0;
        subseqMatrix[i][i].first = s.sequence[i];
        subseqMatrix[i][i].last = s.sequence[i];
    }
    
    // Atualizando resto da matriz
    for (int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            subseqMatrix[i][j] = Concatenate(subseqMatrix[i][j-1], subseqMatrix[j][j], t);
    for (int i=n-1; i>=0; i--) // Subsequências para trechos invertidos
        for (int j=i-1; j>=0; j--)
            subseqMatrix[i][j] = Concatenate(subseqMatrix[i][j+1], subseqMatrix[j][j], t);

}