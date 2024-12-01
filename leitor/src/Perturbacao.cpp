#include "Ils.h"

Solution Perturbacao(Solution s, double **c)
{
    int tam = 2+rand()%int(((s.sequence.size()/10)-1));
    int indice = 1 +rand()%(s.sequence.size()-tam-1);

    int stam = 2+rand()%int((((s.sequence.size()/10)-1)));
    int sindice = 1 + rand()%(s.sequence.size()-stam-1);

    while (true)
    {
        if(sindice == indice)
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if (sindice < indice && (sindice+stam) > indice)
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if (sindice < (indice+tam) && (sindice+stam) >= (indice + tam))
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if (sindice > indice && (sindice+stam) <= (indice+tam))
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if(sindice < indice && (sindice+stam) >= (indice+tam))
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else
            break;
    }
    
    std::vector<int> inv(tam);
    std::vector<int> sinv(stam);
    
    for(int i=0; i<tam; i++)
    {
        inv[i] = s.sequence[indice];
        s.sequence.erase(s.sequence.begin()+indice);
    }
    if(indice < sindice)
    {
        for(int i=0; i<stam; i++)
        {
            sinv[i] = s.sequence[sindice-tam];
            s.sequence.erase(s.sequence.begin()+sindice-tam);
        }
        for(int i=0; i<tam; i++)
            s.sequence.insert(s.sequence.begin()+sindice-tam+i, inv[i]);
        for(int i=0; i<stam; i++)
            s.sequence.insert(s.sequence.begin()+indice+i, sinv[i]);
    }
    else
    {
        for(int i=0; i<stam; i++)
        {
            sinv[i] = s.sequence[sindice];
            s.sequence.erase(s.sequence.begin()+sindice);
        }
        for(int i=0; i<stam; i++)
            s.sequence.insert(s.sequence.begin()+indice-stam+i, sinv[i]);
        for(int i=0; i<tam; i++)
            s.sequence.insert(s.sequence.begin()+sindice+i, inv[i]);
    }

    int primeiro = s.sequence[indice];
    int prev_primeiro = s.sequence[indice-1];
    int end_primeiro = s.sequence[indice+tam-1];
    int next_primeiro = s.sequence[indice+tam];
    int segundo = s.sequence[sindice];
    int prev_segundo = s.sequence[sindice-1];
    int end_segundo = s.sequence[sindice+stam-1];
    int next_segundo = s.sequence[sindice+stam];

    double delta = -c[prev_primeiro-1][primeiro-1] + c[prev_primeiro-1][segundo-1] - c[end_primeiro-1][next_primeiro-1] + c[end_segundo-1][next_primeiro-1] - c[prev_segundo-1][segundo-1] + c[prev_segundo-1][primeiro-1] - c[end_segundo-1][next_segundo-1] + c[end_primeiro-1][next_segundo-1];
    s.value += delta;

    return s;
}