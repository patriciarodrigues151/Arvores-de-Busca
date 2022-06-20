#include <iostream>

using namespace std;


struct no{
	int valor;
	no *esq;
	no *dir;
};

class arvoreBi{
public:
	arvoreBi();
	~arvoreBi();

	void inserir(int chave);
	no *buscar(int chave);
	void destroiArvore();
	void inorder_print();
	void postorder_print();
	void preorder_print();
    void deletaNo(int chave);
    int rank(int chave);

private:
	no *insereMaisAesq(no* folha, no* subA);
    void deletaNo(int chave, no *folha);
	void destroiArvore(no *folha);
	void inserir(int chave, no *folha);
	no *buscar(int chave, no *folha);
	void inorder_print(no *folha);
	void postorder_print(no *folha);
	void preorder_print(no *folha);

	no *root;
};


arvoreBi::arvoreBi()
{
	root = NULL;
}

arvoreBi::~arvoreBi()
{
	destroiArvore();
}

void arvoreBi::inserir(int chave, no *folha)
{
	if(chave < folha->valor){
		if(folha->esq != NULL){
			inserir(chave, folha->esq);
		}else{
			folha->esq = new no;
			folha->esq->valor = chave;
			folha->esq->esq = NULL;
			folha->esq->dir = NULL;
		}
	}else if(chave >= folha->valor){
		if(folha->dir!= NULL){
			inserir(chave, folha->dir);
		}else{
			folha->dir = new no;
			folha->dir->valor = chave;
			folha->dir->dir = NULL;
			folha->dir->esq = NULL;
		}
	}

}

void arvoreBi::inserir(int chave)
{
	if(root != NULL){
		inserir(chave, root);
	}else{
		root = new no;
		root->valor = chave;
		root->esq = NULL;
		root->dir = NULL;
	}
}

no *arvoreBi::buscar(int chave, no *folha)
{
	if(folha != NULL){
		if(chave == folha->valor){
			return folha;
		}
		if(chave < folha->valor){
			return buscar(chave, folha->esq);
		}else{
			return buscar(chave, folha->dir);
		}
	}else{
		return NULL;
	}
}

no *arvoreBi::buscar(int chave)
{
	return buscar(chave, root);
}

void arvoreBi::deletaNo(int chave)
{
	printf("entrei");
    deletaNo(chave, root);
}

no *arvoreBi::insereMaisAesq(no *folha, no *subA)
{
	if(subA->esq == NULL)
	{
		subA->esq = folha;
		return subA;
	}
	else
	{
		insereMaisAesq(folha, subA->esq);
	}
}

void arvoreBi::deletaNo(int chave, no *folha)
{
    if(folha != NULL)
    {
        if(chave == folha->valor)
        {
            //Achamos o nó que queremos deletar
            //caso seja uma folha
            if(folha->esq == NULL && folha->dir == NULL)
            {
                delete folha;
            //Caso ó tenha filhos a esquerda
            }else if(folha->esq != NULL && folha->dir == NULL)
            {
                //o pai apontara para o filho esquerdo do no que sera excluido
                folha = folha->esq;
            //caso só tenha filhos a direita
            }else if(folha->esq == NULL && folha->dir != NULL)
            {
                //o pai apontara para o filho direito do no que sera removido
                folha = folha->dir;
            }else  //caso tenha filho direita e esquerda
			if(folha->esq != NULL && folha->dir != NULL)
            {
                no *aux1 = new no;
                no *aux2 = new no;
                no *aux3 = new no;
                aux1 = folha->dir;
                folha = folha->esq;
                folha->dir = insereMaisAesq(folha->dir, aux1);
            }
        }
        if(chave < folha->valor)
        {
            return deletaNo(chave, folha->esq);
        }else
        {
            return deletaNo(chave, folha->dir);
        }
    }
}

void arvoreBi::destroiArvore(){
	destroiArvore(root);
}

void arvoreBi::destroiArvore(no *folha){
	if(folha != NULL){
		destroiArvore(folha->esq);
		destroiArvore(folha->dir);
		delete folha;
	}
}

void arvoreBi::inorder_print(){
	inorder_print(root);
	cout << "\n";
}

void arvoreBi::inorder_print(no *folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		cout << folha->valor << ",";
		inorder_print(folha->dir);
	}
}

void arvoreBi::postorder_print(){
	postorder_print(root);
	cout << "\n";
}

void arvoreBi::postorder_print(no *folha){
	if(folha != NULL){
		inorder_print(folha->esq);
		inorder_print(folha->esq);
		cout << folha->valor << ",";
	}
}

void arvoreBi::preorder_print(){
	preorder_print(root);
	cout << "\n";
}

void arvoreBi::preorder_print(no *folha){
	if(folha!= NULL){
		cout << folha->valor << ",";
		inorder_print(folha->esq);
		inorder_print(folha->dir);
	}
}


int main(){


	arvoreBi *tree = new arvoreBi();

	tree->inserir(10);
	tree->inserir(6);
	tree->inserir(14);
	tree->inserir(5);
	tree->inserir(8);
	tree->inserir(11);
	tree->inserir(18);

	tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();

    tree->deletaNo(18);

    tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();

	delete tree;

}