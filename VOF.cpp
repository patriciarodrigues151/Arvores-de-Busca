#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "math.h"

using namespace std;


struct palavra{
	string valor;
	int ocorrencia;
};

class VO{ 
public:
	VO(int n);
	~VO();

	void add(string key);
	int value(string key);
    int rank(string key);
    string select(int k);
    void printVetor();
    void ordena();
private:
    int tam;
    int credito;
    vector<string> arrayChar(string texto[], int n);
    void resize(palavra *v);
	void addp(string key);
	int valueP(string key);
    void ordena(palavra *vetor, int n);
    int rankp(palavra *v, string key, int n);
    string selectp(int k);
    palavra * v;
    int numero;
};

VO::VO(int n)
{
    numero = n;
    credito = 0;
    tam = n;
    v = (palavra*)malloc(tam * sizeof(palavra));
    
    for(int i = 0; i < n; i++)
    {
        v[i].valor = ' ';
        v[i].ocorrencia = 0;
    }
}

VO::~VO()
{
    delete(v);
}

void VO::resize(palavra *v)
{
    palavra * novoV = (palavra*)malloc((2 * tam) * sizeof(palavra));
    for(int i = 0; i < 2 * tam; i++)
    {
        novoV[i].ocorrencia = 0;
    }
    for(int i = 0; i < tam ; i++)
    {
        novoV[i] = v[i];
    }

    //simulando uma deleção
    for(int i = 0; i < tam; i++)
    {
        v->valor = ' ';
        v->ocorrencia = 0;
    }
    //delete v;
    v = novoV;
    tam = 2 * tam;
}

void VO::add(string key)
{
    addp(key);
}

void VO::addp(string key)
{
    int tem = 0;
    for(int i = 0; i < tam; i++)
    {
        if(v[i].valor == key)
        {
            v[i].ocorrencia = v[i].ocorrencia +1;
            tem = 1;
            break;
        }
    }
    
    if(tem == 0)
    {
        for(int i = 0; i < tam; i++)
        {
            if(v[i].ocorrencia == 0)
            {
                v[i].valor = key;
                v[i].ocorrencia = 1;
                break;
            }
        }
    }
    ordena(v,tam);
}

void VO::ordena()
{
    ordena(v, tam);
}

void VO::ordena(palavra *vetor, int n)
{
    int k, j;
    palavra aux;

    for (k = 1; k < n; k++) {

        for (j = 0; j < n - 1; j++) {

            if (vetor[j].valor > vetor[j + 1].valor) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

int VO::rankp(palavra * v, string key, int n)
{
    int comeco = 0;
    int fim = n - 1;
    while(comeco <= fim)
    {
        int meio = (comeco+ fim)/2;
        if(v[meio].valor == key)
            return meio + 1;
        if(v[meio].valor < key)
            comeco = meio + 1;
        else
            fim = meio - 1;
    }
    if(v[0].valor == key)
        return 1;
    return -1;
}

int VO::rank(string key)
{
    return rankp(v, key, tam);
}

int VO::value(string key)
{
    return valueP(key);
}

int VO::valueP(string key)
{
    for(int i = 0; i < int(sizeof(v)); i++)
    {
        if(v[i].valor == key)
        {
            return(v[i].ocorrencia);
        }
    }
    return 0;
}

string VO::selectp(int k)
{
    cout << v[k-1].valor << endl;
    return(v[k-1].valor);
}

string VO::select(int k)
{
    return selectp(k);
}

void VO::printVetor()
{
    for(int i = 0; i < numero; i++)
    cout << v[i].valor << "("<<v[i].ocorrencia <<")" << endl;

}

bool sep(char c)
{
    if(c == ' ' || c == '.' || c == ';' || c == '?'|| c == '!' || c == ':' || c == '_' || c == '\n' || c == ',')
        return true;
    return false;
}

vector<string> arrayChar(string texto[], int n)
{
    vector<string> palavras;
    for(int i = 0; i < n; i ++)
    {
        string palavra= texto[i];
        int n = palavra.length();
        char char_array[n + 1];
        strcpy(char_array, palavra.c_str());

        char *pch;
        pch = strtok(char_array, ",.-!?()[]{}*|;");
        while(pch != NULL)
        {
            string str = pch;
            palavras.push_back(str);
            pch = strtok(NULL, ",.-!?()[]{}*|;");
        }
    }
    return palavras;
}



int main ()
{
    int n = 10000000;
    //printf("digite a quantidade de palavras: \n");
    //cin >> n;

    VO* vetor = new VO(n);

    bool jaCol = false;
    int i = 0;
    FILE* arquivo = fopen("bible_KJ.txt", "r");

    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.txt.");
        return 1;
    }

    char *palavra = (char*)malloc(50 * sizeof(char));
    while (true)
    {
        char c = fgetc(arquivo);
        if(c == EOF)
            break;
    
        if(!sep(c))
        {
            palavra[i] = c;
            palavra[i+1] = '\0';
            jaCol = false;
            i++;
        }else
        {
            //aqui coloca o add das estruturas
            if(!jaCol)
                vetor->add(palavra);
            jaCol = true;
            i = 0;
        }
    }

    vetor->ordena();
    vetor->printVetor();

    free(palavra);
    

    return 0;
}

