#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;


struct noTREAP{
	string valor;
	int ocorrencia;
    noTREAP * pai;
    int prior;
	noTREAP *esq;
	noTREAP *dir;
};

class TREAP{ 
public:
	TREAP();
	~TREAP();

	void add(string key, int prior);
	int value(string key);
	int rank(string key);
	void destroiArvore();
	void inorder_print();
	void postorder_print();
	void preorder_print();
	string select(int k);

private:
    void verificaCasos(noTREAP *folha);
    void rodaEsquerda(noTREAP *folha);
    void rodaDireita(noTREAP *folha);
	string selectp(int k, noTREAP * folha);
	int rankp(string key, noTREAP *folha);
	void destroiArvore(noTREAP *folha);
	void add(string key, int prior, noTREAP *folha);
	int value(string key, noTREAP *folha);
	void inorder_print(noTREAP *folha);
	void postorder_print(noTREAP *folha);
	void preorder_print(noTREAP *folha);

	no *root;
	int qntd;
    int quantas;
};


TREAP::TREAP()
{
	root = NULL;
	qntd = 0;
    quantas = 0;
}

TREAP::~TREAP()
{
	destroiArvore();
}



void TREAP::rodaEsquerda(noTREAP *folha)
{

	//CONTINUAR AQUI
	noTREAP * aux;
	aux = (no*)malloc(sizeof(noTREAP));

	aux->esq = folha->esq;
	folha->esq = folha->pai;
	folha->pai = folha->pai->pai;
	folha->esq->dir= aux->esq;
	folha->esq->pai = folha;
	folha->pai->dir = folha;

	free(aux);	

    if(folha->pai == NULL)
        root = folha;

}

void TREAP::rodaDireita(noTREAP * folha)
{
	noTREAP * aux;
	aux = (noTREAP*)malloc(sizeof(noTREAP));

	aux->dir = folha->esq;
	folha->dir = folha->pai;
	folha->pai = folha->pai->pai;
	folha->dir->esq= aux->dir;
	folha->dir->pai = folha;
	folha->pai->esq = folha;

	free(aux);
    if(folha->pai == NULL)
        root = folha;


    
}

void TREAP::verificaCasos(noTREAP *folha)
{
    cout << folha->valor << ":" <<folha->prior << endl;
    cout << "verificando ..." << endl;
    if(folha->pai != NULL)
    {
        if(folha->prior > folha->pai->prior)
        {
            if(folha->pai->esq == folha)
            {
                rodaDireita(folha);

            }else if(folha->pai->dir = folha)
            {
                cout << "ufa" << endl;
                rodaEsquerda(folha);
                cout << "saiu" << endl;
                cout << folha->valor << endl;
            }
        }
    }
    if(folha->pai != NULL)
    {
        cout << "ok" << endl;
        verificaCasos(folha);
    }
    
}

void TREAP::add(string key, int prior, noTREAP *folha)
{
    cout << key << ":" << prior << endl;

    cout << "adicionando" << endl;
	//caso a chave que eu queira inserir seja menor que o nó que estou comparando
	if(key < folha->valor)
	{
		if(folha->esq != NULL){
			add(key, prior, folha->esq);
		}else{//caso seja menor e o nó que estou seja uma folha (pimeira ocorrencia)
            folha->esq = new noTREAP;
			folha->esq->valor = key;
			folha->esq->esq = NULL;
			folha->esq->dir = NULL;
			folha->esq->ocorrencia = 1;
            folha->esq->pai = folha;
            folha->esq->prior = prior;
            verificaCasos(folha->esq);
		}
	//caso a chave que estou querendo inserir seja maior que o nó que estou comparando
	}else if(key > folha->valor){
		if(folha->dir!= NULL){
			add(key, prior, folha->dir);
		}else{ //caso o nó seja menor que o nó que estou e o nó que estou seja uma folha (primeira ocorrencia)
			folha->dir = new noTREAP;
			folha->dir->valor = key;
			folha->dir->dir = NULL;
			folha->dir->esq = NULL;
			folha->dir->ocorrencia = 1;
            folha->dir->pai = folha;
            folha->dir->prior = prior;
            verificaCasos(folha->dir);
		}
	//caso o nó que eu estea tentando inserir seja igual ao nó em que estou (mais de uma ocorrencia), o contador de ocorrencia daquele nó será incrementado para sinalizar que há mais de um ali.
	}else if(key == folha->valor){
			folha->ocorrencia = folha->ocorrencia + 1;
		}
}

void TREAP::add(string key, int prior)
{
    cout << "nova palavra: " << key << endl;
    if(root != NULL)
        cout << "raiz root: " << root->valor << endl;
	if(root != NULL){
		add(key, prior, root);
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

int TREAP::rank(string key)
{
	return rankp(key, root);
}

int TREAP::rankp(string key, noTREAP* folha)
{
	int qntd = 0;
	if(folha != NULL){
	rankp(key ,folha->esq);
		qntd = qntd + 1;
		if(folha->valor == key)
			return qntd;
	rankp(key,folha->dir);
	}
}

string TREAP::select(int k)
{
	return selectp(k, root);
}

string TREAP::selectp(int k, noTREAP * folha)
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

void TREAP::destroiArvore(){
	destroiArvore(root);
}

void TREAP::destroiArvore(noTREAP *folha){
	if(folha != NULL){
		destroiArvore(folha->esq);
		destroiArvore(folha->dir);
		delete folha;
	}
}

void TREAP::inorder_print(){
	inorder_print(root);
	cout << "\n";
}

void TREAP::inorder_print(noTREAP *folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		cout << folha->valor << ",";
		inorder_print(folha->dir);
	}
}

void TREAP::postorder_print(){
	postorder_print(root);
	cout << "\n";
}

void TREAP::postorder_print(noTREAP *folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		inorder_print(folha->esq);
		cout << folha->valor << ",";
	}
}

void TREAP::preorder_print(){
	preorder_print(root);
	cout << "\n";
}

void TREAP::preorder_print(noTREAP *folha){
	if(folha!= NULL){
		cout << folha->valor << ",";
		inorder_print(folha->esq);
		inorder_print(folha->dir);
	}
}



int main(){
    int n = 0;
    int indice = 0;
    int qual;
    int prior;
    printf("digite a quantidade de palavras: \n");
    cin >> n;
    string *vetorPalavras;
    vetorPalavras = (string*)malloc(n * sizeof(string)); 

	TREAP *tree = new TREAP();
    string filename("palavras.txt");
    vector<string> words;
    string word;
    
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Não pode abrir o arquivo- '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file >> word) {
        words.push_back(word);
    }

    for (const auto &i : words) 
    {
		vetorPalavras[indice] = i;
        indice = indice + 1;
        
    }

    indice = 0;
    int na = 0;
    for (const auto &i : words) 
    {
        na = na + 1;
		tree->add(vetorPalavras[indice],na);
        indice = indice + 1;
        
    }

	delete tree;

}