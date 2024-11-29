#ifndef INSERTION_INFO_H
#define INSERTION_INFO_H

/* Struct possui informações sobre determinada inserção de algum nó à solução*/
typedef struct
{
    int noInserido;
    int arestaRemovida;
    double custo;
}InsertionInfo;

#endif // INSERTION_INFO_H