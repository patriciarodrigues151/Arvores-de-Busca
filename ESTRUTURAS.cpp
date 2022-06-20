//estruturas

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "math.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;




//******************************ARVORE DE BUSCA BINARIA******************************

struct noABB{
	string valor;
	int ocorrencia;
	noABB*esq;
	noABB*dir;
};

class ABB{ 
public:
	ABB();
	~ABB();

	void add(string key);
	int value(string key);
	int rank(string key, ABB* &treeR);
	void destroiArvore();
	void inorder_print();
	void postorder_print();
	void preorder_print();
	int qntd;
	string select(int k);

private:
	string selectp(int k, noABB* folha);
	int rankp(string key, noABB*folha, ABB* &treeR);
	void destroiArvore(noABB*folha);
	void add(string key, noABB*folha);
	int value(string key, noABB*folha);
	void inorder_print(noABB*folha);
	void postorder_print(noABB*folha);
	void preorder_print(noABB*folha);

	noABB*root;
	int quantas;
};

ABB::ABB()
{
	root = NULL;
	qntd = 0;
	quantas  = 0;
}

ABB::~ABB()
{
	destroiArvore();
}

void ABB::add(string key, noABB*folha)
{
	//caso a chave que eu queira inserir seja menor que o nó que estou comparando
	if(key < folha->valor)
	{
		if(folha->esq != NULL){
			add(key, folha->esq);
		}else{//caso seja menor e o nó que estou seja uma folha (pimeira ocorrencia)
			folha->esq = new noABB;
			folha->esq->valor = key;
			folha->esq->esq = NULL;
			folha->esq->dir = NULL;
			folha->esq->ocorrencia = 1;
		}
	//caso a chave que estou querendo inserir seja maior que o nó que estou comparando
	}else if(key > folha->valor){
		if(folha->dir!= NULL){
			add(key, folha->dir);
		}else{ //caso o nó seja menor que o nó que estou e o nó que estou seja uma folha (primeira ocorrencia)
			folha->dir = new noABB;
			folha->dir->valor = key;
			folha->dir->dir = NULL;
			folha->dir->esq = NULL;
			folha->dir->ocorrencia = 1;
		}
	//caso o nó que eu estea tentando inserir seja igual ao nó em que estou (mais de uma ocorrencia), o contador de ocorrencia daquele nó será incrementado para sinalizar que há mais de um ali.
	}else if(key == folha->valor){
			folha->ocorrencia = folha->ocorrencia + 1;
		}

}

void ABB::add(string key)
{
	if(root != NULL){
		add(key, root);
	}else{ //caso não exista uma arvore um nó será criado e a ocorrencia será um
		root = new noABB;
		root->valor = key;
		root->esq = NULL;
		root->dir = NULL;
		root->ocorrencia = 1;
	}
}

int ABB::value(string key, noABB*folha)
{
	if(folha != NULL){
		if(key == folha->valor){//se ele achou o valor que é igual a chave que estou procurando, retornarei esse nó e a quantidade de ocorrencias.
			return folha->ocorrencia;
		}
		if(key < folha->valor){
			return value(key, folha->esq);
		}else{
			return value(key, folha->dir);
		}
	}else{
		return NULL;
	}
}

int ABB::value(string key)
{
	return(value(key, root));
}

int ABB::rank(string key,ABB* &treeR)
{
	return rankp(key, root, treeR);
}

int ABB::rankp(string key, noABB* folha, ABB* &treeR)
{

	if(folha != NULL){
	rankp(key ,folha->esq, treeR);
		treeR->qntd = treeR->qntd + 1;
		if(folha->valor == key)
			return treeR->qntd;
	rankp(key,folha->dir, treeR);
	}
}

string ABB::select(int k)
{
	return selectp(k, root);
}

string ABB::selectp(int k, noABB* folha)
{
	//continuar fazend o select
	if(folha != NULL){
	selectp(k ,folha->esq);
	quantas = quantas + 1;
		if(quantas == k)
		{
			quantas = 0;
			return folha->valor;
		}
	selectp(k,folha->dir);
	}
	
}

void ABB::destroiArvore(){
	destroiArvore(root);
}

void ABB::destroiArvore(noABB*folha){
	if(folha != NULL){
		destroiArvore(folha->esq);
		destroiArvore(folha->dir);
		delete folha;
	}
}

void ABB::inorder_print(){
	inorder_print(root);
	cout << "\n";
}

void ABB::inorder_print(noABB*folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		cout << folha->valor << "(" << folha->ocorrencia << ")" <<  ",";
		inorder_print(folha->dir);
	}
}




//********************************TREAP*********************************************

struct noTREAP{
    //cor vermelha: 1; cor preta: 0
    int prior;
	string valor;
	int ocorrencia;
    noTREAP* pai;
	noTREAP*esq;
	noTREAP*dir;

};

class TREAP{ 
public:
	TREAP();
	~TREAP();

	void add(string key, int prior);
	int value(string key);
	int rank(string key, TREAP* &treeR);
	void destroiArvore();
	void inorder_print();
	void postorder_print();
	void preorder_print();
	int qntd;
	//string select(int k);

private:
    void rodaDireita(noTREAP*folha);
	void rodaEsquerda(noTREAP*folha);
    void verificaCasos(noTREAP*folha);
	//string selectp(int k, noTREAP* folha);
	int rankp(string key, noTREAP*folha, TREAP* &treeR);
	void destroiArvore(noTREAP*folha);
	void add(string key, noTREAP*folha, int prior);
	int value(string key, noTREAP*folha);
	void inorder_print(noTREAP*folha);
	void postorder_print(noTREAP*folha);
	void preorder_print(noTREAP*folha);

	noTREAP*root;
};

TREAP::TREAP()
{
	root = NULL;
	qntd = 0;
}

TREAP::~TREAP()
{
	destroiArvore();
}

void TREAP::add(string key, int prior)
{
	if(root != NULL){
		add(key, root, prior);
	}else{ //caso não exista uma arvore um nó será criado e a ocorrencia será um
		root = new noTREAP;
		root->valor = key;
		root->esq = NULL;
		root->dir = NULL;
		root->pai = NULL;
        root->prior = prior;
		root->ocorrencia = 1;
	}
}

void TREAP::add(string key, noTREAP*folha, int prior)
{
	//caso a chave que eu queira inserir seja menor que o nó que estou comparando
	if(key < folha->valor)
	{
		if(folha->esq != NULL){
			add(key, folha->esq, prior);
		}else{//caso seja menor e o nó que estou seja uma folha (pimeira ocorrencia)
			folha->esq = new noTREAP;
			folha->esq->valor = key;
			folha->esq->esq = NULL;
			folha->esq->dir = NULL;
			folha->esq->pai = folha;
			folha->esq->ocorrencia = 1;
            folha->esq->prior = prior;
			verificaCasos(folha->esq);
		}
	//caso a chave que estou querendo inserir seja maior que o nó que estou comparando
	}else if(key > folha->valor){
		if(folha->dir!= NULL){
			add(key, folha->dir, prior);
		}else{ //caso o nó seja menor que o nó que estou e o nó que estou seja uma folha (primeira ocorrencia)
			folha->dir = new noTREAP;
			folha->dir->valor = key;
			folha->dir->dir = NULL;
			folha->dir->esq = NULL;
			folha->dir->pai = folha;
			folha->dir->ocorrencia = 1;
            folha->dir->prior = prior;
			verificaCasos(folha->dir);
		}
	//caso o nó que eu estea tentando inserir seja igual ao nó em que estou (mais de uma ocorrencia), o contador de ocorrencia daquele nó será incrementado para sinalizar que há mais de um ali.
	}else if(key == folha->valor){
			folha->ocorrencia = folha->ocorrencia + 1;
		}
}

void TREAP::verificaCasos(noTREAP*folha)
{

	while(true)
	{
		//se é raiz
		if(folha->pai == NULL)
		{
			break;
		}

		//se é filho de um preto
		if(folha->pai->prior > folha->prior)
		{
			break;
		}

		//se não tem avô

		if(folha->pai->pai == NULL)
		{
			//se o pai é esquerdo
			if(folha->pai->esq == folha)
			{
                rodaDireita(folha);
                break;
			}
			//se o pai é direito
			if(folha->pai->dir == folha)
			{
                rodaEsquerda(folha);
                break;
            }
		}


		if(folha->pai->prior < folha->prior)
		{
			//se o pai é esquerdo
			if(folha->pai->esq == folha)
			{
                rodaDireita(folha);
                verificaCasos(folha);
                break;

			}
			//se o pai é direito
			if(folha->pai->dir == folha)
			{
                rodaEsquerda(folha);
                verificaCasos(folha);
                break;
            }

		}
		break;
	}

}

void TREAP::rodaEsquerda(noTREAP*folha)
{
    int qual;

	noTREAP* aux;
	aux = (noTREAP*)malloc(sizeof(noTREAP));

	if(folha->pai->pai != NULL)
	{
		if(folha->pai->pai->esq == folha->pai)
			qual = 1;
		if(folha->pai->pai->dir == folha->pai)
			qual = 0;
	}

    aux = folha->esq;
    folha->esq = folha->pai;
    folha->pai = folha->pai->pai;
    folha->esq->pai = folha;
    folha->esq->dir= aux;

    if(folha->pai != NULL)
    {
        if(qual == 1)
            folha->pai->esq = folha;
        if(qual == 0)
            folha->pai->dir = folha;
    }


    if(aux != NULL)
        folha->esq->dir->pai = folha->esq;

    if(folha->pai == NULL)
        root = folha;  
}

void TREAP::rodaDireita(noTREAP* folha)
{
    int qual;
	noTREAP* aux;
	aux = (noTREAP*)malloc(sizeof(noTREAP));

	if(folha->pai->pai != NULL)
	{
		if(folha->pai->pai->esq == folha->pai)
			qual = 1;
		if(folha->pai->pai->dir == folha->pai)
			qual = 0;
	}

    aux = folha->dir;
    folha->dir = folha->pai;
    folha->pai = folha->pai->pai;
    folha->dir->pai = folha;
    folha->dir->esq = aux;

    
    if(folha->pai != NULL)
    {
        if(qual == 1)
            folha->pai->esq = folha;
        if(qual == 0)
            folha->pai->dir = folha;
    }

    if(aux != NULL)
        folha->dir->esq->pai = folha->dir;

    if(folha->pai == NULL)
        root = folha;
}

int TREAP::rank(string key,TREAP* &treeR)
{
	return rankp(key, root, treeR);
}

int TREAP::rankp(string key, noTREAP* folha, TREAP* &treeR)
{

	if(folha != NULL){
	rankp(key ,folha->esq, treeR);
		treeR->qntd = treeR->qntd + 1;
		if(folha->valor == key)
			return treeR->qntd;
	rankp(key,folha->dir, treeR);
	}
}

int TREAP::value(string key, noTREAP *folha)
{
	if(folha != NULL){
		if(key == folha->valor){//se ele achou o valor que é igual a chave que estou procurando, retornarei esse nó e a quantidade de ocorrencias.
			return folha->ocorrencia;
		}
		if(key < folha->valor){
			return value(key, folha->esq);
		}else{
			return value(key, folha->dir);
		}
	}else{
		return NULL;
	}
}

int TREAP::value(string key)
{
	return(value(key, root));
}

void TREAP::destroiArvore(){
	destroiArvore(root);
}

void TREAP::destroiArvore(noTREAP*folha){
	if(folha != NULL){
		destroiArvore(folha->esq);
		destroiArvore(folha->dir);
		delete folha;
	}
}

void TREAP::inorder_print(){
	cout << "*****************A impressão é feita na ordem 'inorder', de maneira a planiicar (achatar) a árvore*****************" << endl;
	inorder_print(root);
	cout << "\n";
}

void TREAP::inorder_print(noTREAP*folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		cout << folha->valor << "(" << folha->ocorrencia << ")" << ",";
		inorder_print(folha->dir);
	}
}




// ********************************** ARVORE RUBRO NEGRA **********************************************
struct noARN{
    //cor vermelha: 1; cor preta: 0
    int cor;
	string valor;
	int ocorrencia;
    noARN * pai;
	noARN *esq;
	noARN *dir;

};

class ARN{ 
public:
	ARN();
	~ARN();

	void add(string key);
	int value(string key);
	int rank(string key, ARN* &treeR);
	void destroiArvore();
	void inorder_print();
	void postorder_print();
	void preorder_print();
	//string select(int k);
    int qntd;

private:
	noARN * vaiAteUltimoEsq(noARN * folha);
	noARN * vaiAteUltimoDir(noARN * folha);
	void tioVermelhoePaiVermelho(noARN *folha);
	void tioPretoouInexistente(noARN *folha);
    void rodaDireita(noARN *folha);
	void rodaEsquerda(noARN *folha);
    void verificaCasos(noARN *folha);
	//string selectp(int k, no * folha);
    int rankp(string key, noARN* folha, ARN* &treeR);
	void destroiArvore(noARN *folha);
	void add(string key, noARN *folha);
	int value(string key, noARN *folha);
	void inorder_print(noARN *folha);
	void postorder_print(noARN *folha);
	void preorder_print(noARN *folha);

	noARN *root;

};


ARN::ARN()
{
	root = NULL;
    qntd = 0;
}

ARN::~ARN()
{
	destroiArvore();
}

void ARN::add(string key, noARN *folha)
{
	//caso a chave que eu queira inserir seja menor que o nó que estou comparando
	if(key < folha->valor)
	{
		if(folha->esq != NULL){
			add(key, folha->esq);
		}else{//caso seja menor e o nó que estou seja uma folha (pimeira ocorrencia)
			folha->esq = new noARN;
			folha->esq->valor = key;
			folha->esq->esq = NULL;
			folha->esq->dir = NULL;
			folha->esq->cor = 1;
			folha->esq->pai = folha;
			folha->esq->ocorrencia = 1;
			verificaCasos(folha->esq);
		}
	//caso a chave que estou querendo inserir seja maior que o nó que estou comparando
	}else if(key > folha->valor){
		if(folha->dir!= NULL){
			add(key, folha->dir);
		}else{ //caso o nó seja menor que o nó que estou e o nó que estou seja uma folha (primeira ocorrencia)
			folha->dir = new noARN;
			folha->dir->valor = key;
			folha->dir->dir = NULL;
			folha->dir->esq = NULL;
			folha->dir->cor = 1;
			folha->dir->pai = folha;
			folha->dir->ocorrencia = 1;
			verificaCasos(folha->dir);
		}
	//caso o nó que eu estea tentando inserir seja igual ao nó em que estou (mais de uma ocorrencia), o contador de ocorrencia daquele nó será incrementado para sinalizar que há mais de um ali.
	}else if(key == folha->valor){
			folha->ocorrencia = folha->ocorrencia + 1;
		}
}

noARN * ARN::vaiAteUltimoEsq(noARN * folha)
{
	if(folha->esq == NULL)
		return(folha);
	vaiAteUltimoEsq(folha->esq);
}

noARN * ARN::vaiAteUltimoDir(noARN * folha)
{
	if(folha->dir == NULL)
		return(folha);
	vaiAteUltimoDir(folha->dir);
}

void ARN::rodaEsquerda(noARN *folha)
{
    int qual;
    cout << "rodando para a esquerda ... " << endl;

	noARN * aux;
	aux = (noARN*)malloc(sizeof(noARN));

	if(folha->pai->pai != NULL)
	{
		if(folha->pai->pai->esq == folha->pai)
			qual = 1;
		if(folha->pai->pai->dir == folha->pai)
			qual = 0;
	}

    aux = folha->esq;
    folha->esq = folha->pai;
    folha->pai = folha->pai->pai;
    folha->esq->pai = folha;
    folha->esq->dir= aux;

    if(folha->pai != NULL)
    {
        if(qual == 1)
            folha->pai->esq = folha;
        if(qual == 0)
            folha->pai->dir = folha;
    }


    if(aux != NULL)
        folha->esq->dir->pai = folha->esq;

    if(folha->pai == NULL)
        root = folha;  

	folha->cor = 0;
	folha->esq->cor = 1;
}

void ARN::rodaDireita(noARN * folha)
{
    int qual;
    cout << "rodando para a direita ... " << endl;
	noARN * aux;
	aux = (noARN*)malloc(sizeof(noARN));

	if(folha->pai->pai != NULL)
	{
		if(folha->pai->pai->esq == folha->pai)
			qual = 1;
		if(folha->pai->pai->dir == folha->pai)
			qual = 0;
	}

    aux = folha->dir;
    folha->dir = folha->pai;
    folha->pai = folha->pai->pai;
    folha->dir->pai = folha;
    folha->dir->esq = aux;

    
    if(folha->pai != NULL)
    {
        if(qual == 1)
            folha->pai->esq = folha;
        if(qual == 0)
            folha->pai->dir = folha;
    }

    if(aux != NULL)
        folha->dir->esq->pai = folha->dir;

    if(folha->pai == NULL)
        root = folha;

	folha->cor = 0;
	folha->dir->cor = 1;

}

void ARN::tioPretoouInexistente(noARN *folha)
{
	//quando roda pode gerar vermelho vermelho então se rodar para a direita, chamamr resursivamente desde a ponta direita e vice versa
	if(folha != NULL)
	{
		if(folha->pai->cor == 0)
		{
			if(folha->pai->dir == folha)
			{
				rodaEsquerda(folha);
			}
			else if(folha->pai->pai->esq == folha)
			{
				rodaDireita(folha);
			}
		}else
		{
			tioPretoouInexistente(folha->pai);
		}
	}
}

void ARN::tioVermelhoePaiVermelho(noARN *folha)
{
	cout << "aqui" << endl;
	if(folha->pai != NULL)
	{
		if(folha != NULL)
		{
			folha->pai->cor = 0;
			if(folha->pai->pai->esq != NULL)
			{
				folha->pai->pai->esq->cor = 0;
			}
			else if(folha->pai->pai->dir != NULL)
			{
				folha->pai->pai->esq->cor = 0;
			}
			folha->pai->pai->cor = 1;
		}
	}
}

void ARN::verificaCasos(noARN *folha)
{

	while(true)
	{
		//se é raiz
		if(folha->pai == NULL)
		{
			break;
		}

		//se é filho de um preto
		if(folha->pai->cor == 0)
		{
			break;
		}

		//se não tem avô
		if(folha->pai->pai == NULL)
		{
			if(folha->cor == 1)
			{
				if(folha->pai->cor == 1)
				{
					folha->pai->cor = 0;
					break;
				}
			}
		}

		if(folha->pai->pai != NULL)
		{
			//se o pai é esquerdo
			if(folha->pai->pai->esq == folha)
			{
				//se o pai é esquerdo, mexeremos noo tio esquerdo, caso haja
				if(folha->pai->cor == 1 && folha->pai->pai->dir->cor == 1)
				{
					tioVermelhoePaiVermelho(folha);
					if(folha->pai->pai != NULL)
						verificaCasos(folha->pai);
				}

				if(folha->pai->pai->dir == NULL)
				{
					tioPretoouInexistente(folha);
						if(folha->dir != NULL)
						{
						folha = vaiAteUltimoDir(folha);
						verificaCasos(folha);
						}
				}

				if(folha->pai->pai->dir->cor == 0)
				{
					tioPretoouInexistente(folha);
						if(folha->esq != NULL)
						{
						folha = vaiAteUltimoEsq(folha);
						verificaCasos(folha);
						}

				}

			}
			//se o pai é direito
			if(folha->pai->pai->dir == folha)
			{
				if(folha->pai->cor == 1 && folha->pai->pai->esq->cor == 1)
				{
					tioVermelhoePaiVermelho(folha);
				}

				if(folha->pai->pai->esq == NULL)
				{
					tioPretoouInexistente(folha);
				}

				if(folha->pai->pai->esq->cor == 0)
				{
					tioPretoouInexistente(folha);
				}

			}

		}
		break;
	}
}

void ARN::add(string key)
{
	if(root != NULL){
		add(key, root);
	}else{ //caso não exista uma arvore um nó será criado e a ocorrencia será um
		root = new noARN;
		root->valor = key;
		root->esq = NULL;
		root->dir = NULL;
		root->cor = 1;
		root->pai = NULL;
		root->ocorrencia = 1;
	}
}

int ARN::value(string key, noARN *folha)
{
	if(folha != NULL){
		if(key == folha->valor){//se ele achou o valor que é igual a chave que estou procurando, retornarei esse nó e a quantidade de ocorrencias.
			return folha->ocorrencia;
		}
		if(key < folha->valor){
			return value(key, folha->esq);
		}else{
			return value(key, folha->dir);
		}
	}else{
		return NULL;
	}
}

int ARN::value(string key)
{
	return(value(key, root));
}

int ARN::rank(string key,ARN* &treeR)
{
	return rankp(key, root, treeR);
}

int ARN::rankp(string key, noARN* folha, ARN* &treeR)
{

	if(folha != NULL){
	rankp(key ,folha->esq, treeR);
		treeR->qntd = treeR->qntd + 1;
		if(folha->valor == key)
			return treeR->qntd;
	rankp(key,folha->dir, treeR);
	}
}

void ARN::destroiArvore(){
	destroiArvore(root);
}

void ARN::destroiArvore(noARN *folha){
	if(folha != NULL){
		destroiArvore(folha->esq);
		destroiArvore(folha->dir);
		delete folha;
	}
}

void ARN::inorder_print(){
	cout << "*****************A impressão é feita na ordem 'inorder', de maneira a planiicar (achatar) a árvore*****************" << endl;
	inorder_print(root);
	cout << "\n";
}

void ARN::inorder_print(noARN *folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		cout << folha->valor << "(" << folha->ocorrencia << ")" << ",";
		inorder_print(folha->dir);
	}
}


// ********************************** VETOR ORDENADO *************************************************8
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
    void printVetor(int n);
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

void VO::printVetor(int n)
{
    for(int i = 0; i < n; i++)
    cout << v[i].valor << "("<<v[i].ocorrencia <<")" << endl;

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




int main()
{
    vector<string> palavras;
    string estrutura;
    int num;
    int q;


    cout << "Qual é a estrutura a ser testada: " << endl;
    cin >> estrutura;

    cout << "digite a quantidade de palavras: \n" << endl;
    cin >> num;

    string meuVetor[num];
    cout << "Digite o texto: \n" << endl;

    for(int i = 0; i < num; i++)
    {
        cin >> meuVetor[i];
    }


    palavras = arrayChar(meuVetor, num);


    int tem = 0;     

    cout << "Digite o número de operações a serem realizadas na tabela de símbulos: \n" << endl;
    cin >> q;

    int funcaoTeste[q];
    string coisaTeste[q];

    if(estrutura == "VO" || estrutura == "vo")
    {
        cout << "operações" << q << endl;
        VO* vetor = new VO(num);  
        int itera = q;
        //le operacoes
        for(int i = 0; i < itera; i++)
        {
            cout<< "Digite a "<< i+1  << "° operação: \n" << endl;
            cin >> funcaoTeste[i];
            cin >> coisaTeste[i];
        }

        for(int i = 0; i < itera; i++)
        {
            if(funcaoTeste[0] != 1)
            {
                cout << "Não adicionou!" << endl;
                break;
            }

            //add
            if(funcaoTeste[i] == 1)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }

                for(int j = 0; j < inA; j++)
                {
                    vetor->add(palavras[j]);
                }
                
            }
            //value
            if(funcaoTeste[i] == 2)
            {
                int qntd = 0;

                qntd = vetor->value(coisaTeste[i]);
                cout << "value: " << qntd << endl;
            }

            if(funcaoTeste[i] == 3)
            {
                int ra;
                cout << coisaTeste[i] << endl;
                ra = vetor->rank(coisaTeste[i]);
                cout << "rank: " << ra << endl;
            }

            if(funcaoTeste[i] == 4)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }

                string aux;
                aux = vetor->select(inA);
                cout << "select: " << aux << endl;
            }
        }
    }


    if(estrutura == "ARN" || estrutura == "arn")
    {
        ARN* treeR = new ARN();  
        int itera = q;
        //le operacoes
        for(int i = 0; i < itera; i++)
        {
            cout<< "Digite a "<< i+1  << "° operação: \n" << endl;
            cin >> funcaoTeste[i];
            cin >> coisaTeste[i];
        }

        for(int i = 0; i < itera; i++)
        {
            if(funcaoTeste[0] != 1)
            {
                cout << "Não adicionou!" << endl;
                break;
            }

            //add
            if(funcaoTeste[i] == 1)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }

                for(int j = 0; j < inA; j++)
                {
                    treeR->add(palavras[j]);
                }
                
            }
            //value
            if(funcaoTeste[i] == 2)
            {
                int qntd = 0;

                qntd = treeR->value(coisaTeste[i]);
                cout << "value: " << qntd << endl;
            }

            if(funcaoTeste[i] == 3)
            {

                treeR->qntd = 0;
                int ra;
                cout << coisaTeste[i] << endl;
                ra = treeR->rank(coisaTeste[i], treeR);
                cout << "rank: " << ra << endl;
            }

            if(funcaoTeste[i] == 4)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }

                string aux;
                //aux = treeR->select(inA);
                //cout << "select: " << aux << endl;
            }
        }

    }
   
   
    if(estrutura == "TR" || estrutura == "tr")
    {
        TREAP* treeR = new TREAP();  
        int itera = q;
        //le operacoes
        for(int i = 0; i < itera; i++)
        {
            cout<< "Digite a "<< i+1  << "° operação: \n" << endl;
            cin >> funcaoTeste[i];
            cin >> coisaTeste[i];
        }

        for(int i = 0; i < itera; i++)
        {
            if(funcaoTeste[0] != 1)
            {
                cout << "Não adicionou!" << endl;
                break;
            }

            //add
            if(funcaoTeste[i] == 1)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }
                int prior = 0;
                for(int j = 0; j < inA; j++)
                {
                    cout << "qual é a prioridade da primeira palavra?:" << endl;
                    cin >> prior;
                    treeR->add(palavras[j], prior);
                }
                
            }
            //value
            if(funcaoTeste[i] == 2)
            {
                int qntd = 0;

                qntd = treeR->value(coisaTeste[i]);
                cout << "value: " << qntd << endl;
            }

            if(funcaoTeste[i] == 3)
            {

                treeR->qntd = 0;
                int ra;
                cout << coisaTeste[i] << endl;
                ra = treeR->rank(coisaTeste[i], treeR);
                cout << "rank: " << ra << endl;
            }

            if(funcaoTeste[i] == 4)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }

                string aux;
                //aux = treeR->select(inA);
                //cout << "select: " << aux << endl;
            }
        }

    }
   
   
    if(estrutura == "ABB" || estrutura == "abb")
    {
        ABB* treeR = new ABB();  
        int itera = q;
        //le operacoes
        for(int i = 0; i < itera; i++)
        {
            cout<< "Digite a "<< i+1  << "° operação: \n" << endl;
            cin >> funcaoTeste[i];
            cin >> coisaTeste[i];
        }

        for(int i = 0; i < itera; i++)
        {
            if(funcaoTeste[0] != 1)
            {
                cout << "Não adicionou!" << endl;
                break;
            }

            //add
            if(funcaoTeste[i] == 1)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }
                int prior = 0;
                for(int j = 0; j < inA; j++)
                {
                    treeR->add(palavras[j]);
                }
                
            }
            //value
            if(funcaoTeste[i] == 2)
            {
                int qntd = 0;

                qntd = treeR->value(coisaTeste[i]);
                cout << "value: " << qntd << endl;
            }

            if(funcaoTeste[i] == 3)
            {

                treeR->qntd = 0;
                int ra;
                cout << coisaTeste[i] << endl;
                ra = treeR->rank(coisaTeste[i], treeR);
                cout << "rank: " << ra << endl;
            }

            if(funcaoTeste[i] == 4)
            {
                int n = coisaTeste[i].length();
                int cint[n];
                int inA = 0;
                char char_array[n + 1];
                strcpy(char_array, coisaTeste[i].c_str());

                for(int a = 0; a < n; a++)
                {
                    cint[a] = char_array[a] - '0';
                }
                
                for(int a = 0; a < n; a ++)
                {
                    inA = inA + cint[a] * pow(10,a);
                }

                string aux;
                //aux = treeR->select(inA);
                //cout << "select: " << aux << endl;
            }
        }

    }
   
    

    //input_file.close();
    return EXIT_SUCCESS;
}