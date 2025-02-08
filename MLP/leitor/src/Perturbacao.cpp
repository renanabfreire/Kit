#include "Ils.h"

Solution Perturbacao(Solution s, Data &d, vector<vector<Subsequence>> &SubsequenceMatriz)
{
    // Gerando aleatoriamente blocos para troca
    int tam, stam;
    if(s.sequence.size() <20 && s.sequence.size()>=10)
    {
        tam =2;
        stam =2;
    }
    else
    {
        tam = 2+rand()%(int)(((s.sequence.size()/10)-1));
        stam = 2+rand()%int((((s.sequence.size()/10)-1)));
    }

    int indice = 1 +rand()%int((s.sequence.size()-tam-2));
    int sindice = 1 + rand()%int((s.sequence.size()-stam-1));

    // impedindo que blocos fiquem sobrepostos
    while (true)
    {
        if(sindice < indice) // escolhendo um anterior a fim de organização
        {
            std::swap(indice, sindice);
            std::swap(tam, stam);
        }
        else if(sindice == indice || (indice + tam) > sindice) // verificando sobreposição
            sindice = 1 + rand()%int((s.sequence.size()-stam-2)); // corrigindo segundo indice
        else
            break;
    }

    //calculando Custo de nova solução
    Subsequence sigma_1 = Concatenate(SubsequenceMatriz[0][indice-1], SubsequenceMatriz[sindice][sindice+stam-1], d);
    if(indice+tam != sindice)
        sigma_1 = Concatenate(sigma_1, SubsequenceMatriz[indice+tam][sindice-1], d);
    Subsequence sigma_2 = Concatenate(sigma_1, SubsequenceMatriz[indice][indice+tam-1], d);
    Subsequence delta = Concatenate(sigma_2, SubsequenceMatriz[sindice+stam][s.sequence.size()-1], d);

    // Efetuando troca
    std::vector<int> inv(tam); // primeiro bloco
    std::vector<int> sinv(stam); // segundo bloco
    for(int i=0; i<tam; i++) // Guardando primeiro bloco
    {
        inv[i] = s.sequence[indice];
        s.sequence.erase(s.sequence.begin()+indice);
    }
    for(int i=0; i<stam; i++) // guardando segundo bloco
    {
        sinv[i] = s.sequence[sindice-tam];
        s.sequence.erase(s.sequence.begin()+sindice-tam);
    }
    for(int i=0; i<tam; i++) // repondo primeiro bloco na posição do segundo
        s.sequence.insert(s.sequence.begin()+sindice-tam+i, inv[i]);
    for(int i=0; i<stam; i++) // repondo segundo bloco na posição do primeiro
        s.sequence.insert(s.sequence.begin()+indice+i, sinv[i]);

    s.value = delta.C; // Atualizando custo

    return s;
}