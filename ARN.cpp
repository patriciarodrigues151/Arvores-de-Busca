#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;


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
	int rank(string key);
	void destroiArvore();
	void inorder_print();
	void postorder_print();
	void preorder_print();
	//string select(int k);

private:
	noARN * vaiAteUltimoEsq(noARN * folha);
	noARN * vaiAteUltimoDir(noARN * folha);
	void tioVermelhoePaiVermelho(noARN *folha);
	void tioPretoouInexistente(noARN *folha);
    void rodaDireita(noARN *folha);
	void rodaEsquerda(noARN *folha);
    void verificaCasos(noARN *folha);
	//string selectp(int k, no * folha);
	int rankp(string key, noARN *folha);
	void destroiArvore(noARN *folha);
	void add(string key, noARN *folha);
	int value(string key, noARN *folha);
	void inorder_print(noARN *folha);
	void postorder_print(noARN *folha);
	void preorder_print(noARN *folha);

	noARN *root;
	int qntd;
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
	cout << "adicionando" << endl;
	cout << key << endl;
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
	cout << "verificando" << endl;
	cout << folha->valor << endl;

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

int ARN::rank(string key)
{
	return rankp(key, root);
}

int ARN::rankp(string key, noARN* folha)
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

/*
string ARN::select(int k)
{
	return selectp(k, root);
}

string ARN::selectp(int k, no * folha)
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

*/
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

void ARN::postorder_print(){
	postorder_print(root);
	cout << "\n";
}

void ARN::postorder_print(noARN *folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		inorder_print(folha->esq);
		cout << folha->valor << ",";
	}
}

void ARN::preorder_print(){
	preorder_print(root);
	cout << "\n";
}

void ARN::preorder_print(noARN*folha){
	if(folha!= NULL){
		cout << folha->valor << ",";
		inorder_print(folha->esq);
		inorder_print(folha->dir);
	}
}



int main(){
    int n = 10000000;
    //printf("digite a quantidade de palavras: \n");
    //cin >> n;

	ARN *tree = new ARN();
    string filename("bible_KJ.txt");
    vector<string> words;
    string word;
    
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Não pode abrir o arquivo - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file >> word) {
        words.push_back(word);
    }
    
    for (const auto &i : words) 
    {
		cout << "entrando: " << endl;
		cout << i << endl;
		tree->add(i);
    }

	string palavra("Jesus");
	string palavraSelected;
	int qntd;
	tree->inorder_print();

	qntd = tree->value(palavra);
	cout << "(value) a qntd de vezes que a palavra aparece: " << qntd << endl;
	qntd = tree->rank(palavra);
	cout << "(rank) o rank de jesus na arvore  é: " << qntd << endl;


	delete tree;

}




























