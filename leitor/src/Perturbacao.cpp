#include "Ils.h"

Solution Perturbacao(Solution s, Data &d)
{
    // Gerando aleatoriamente blocos para troca
    int tam = 2+rand()%int(((s.sequence.size()/10)-1));
    int indice = 1 +rand()%int((s.sequence.size()-tam-2));

    int stam = 2+rand()%int((((s.sequence.size()/10)-1)));
    int sindice = 1 + rand()%int((s.sequence.size()-stam-2));

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

    // Obtendo arestas que isolam os blocos a serem trocados
    int primeiro = s.sequence[indice];
    int prev_primeiro = s.sequence[indice-1];
    int end_primeiro = s.sequence[indice+tam-1];
    int next_primeiro = s.sequence[indice+tam];
    int segundo = s.sequence[sindice];
    int prev_segundo = s.sequence[sindice-1];
    int end_segundo = s.sequence[sindice+stam-1];
    int next_segundo = s.sequence[sindice+stam];

    //calculando variação de custo
    double delta = -d.getDistance(prev_primeiro, primeiro) + d.getDistance(prev_primeiro, segundo) - d.getDistance(end_primeiro, next_primeiro) + d.getDistance(end_segundo, next_primeiro) - d.getDistance(prev_segundo, segundo) + d.getDistance(prev_segundo, primeiro) - d.getDistance(end_segundo, next_segundo) + d.getDistance(end_primeiro, next_segundo);
    
    // Corrigindo variação para casos específicos
    if(next_primeiro == segundo)
    {
        delta += d.getDistance(end_segundo, primeiro) + d.getDistance(end_primeiro, next_primeiro) - d.getDistance(end_segundo, next_primeiro) - d.getDistance(prev_segundo, primeiro);
    }
    else if (next_segundo == primeiro)
    {
        delta +=  d.getDistance(end_primeiro, segundo) + d.getDistance(end_segundo, next_segundo) - d.getDistance(end_primeiro, next_segundo) - d.getDistance(prev_primeiro, segundo);
    }
    
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

    s.value += delta;

    return s;
}