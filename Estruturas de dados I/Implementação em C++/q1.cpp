#include <iostream>
#include <locale.h>
#include <time.h>
#include <cstdlib>
#include <vector>
using namespace std;

void mostrarMenu();
int vetorVazio(vector<int> vetor);

void popularVetor(vector<int> &vetor),
encontrarMaior(vector<int> &vetor),
encontrarPares(vector<int> &vetor),
somatoria(vector<int> &vetor),
inverterOrdem(vector<int> &vetor),
ordenar(vector<int> &vetor);

void quicksort(vector<int> &vetor, int i_esq, int i_dir),
trocar (vector<int> &vetor, int indice_a, int indice_b);


int main()
{
	setlocale(LC_ALL, "");

	vector<int> vetor(10);

	void (*vetor_f[])(vector<int>&) = {popularVetor, encontrarMaior, encontrarPares, somatoria, inverterOrdem, ordenar, 0};
	void (*f)(vector<int>&) = nullptr;

	size_t qnt_opc = sizeof(vetor_f) / sizeof(vetor_f[0]);
	cout << qnt_opc << " itens no vetor de funções.\n\n";

	srand(time(NULL));

	int escolha = 0;
	while(1)
	{
		mostrarMenu();
		cin >> escolha;

		if(escolha > 0 && escolha <= qnt_opc)
		{
			f = vetor_f[(escolha-1)];

			if(escolha == qnt_opc) break;
			else f(vetor);
		}

		else printf("\n<# Houve um problema na seleção dos itens. Insira um número de índice válido.\n\n");
	}

	cout << "\n< Encerrando o programa.\n\n";
}


void popularVetor(vector<int> &vetor)
{
	int tamanho = vetor.size();
	int min, max;

	cout << "\n< Insira o valor mínimo: ";
	cin >> min;

	while(1)
	{
		cout << "\n< Insira o valor máximo: ";
		cin >> max;

		if(max > min) break;
		cout << "<# O valor máximo não pode ser menor ou igual ao valor mínimo!\n";
	}

	for(int i = 0; i < tamanho; i++) vetor[i] = (rand()%(max - min)) + min;

	cout << "\n< Os valores do vetor são:\n< ";
	for(int i = 0; i < tamanho; i++) cout << vetor[i] << ((i+1 < tamanho) ? ", " : ".\n");
	cout << "\n\n";
}


void encontrarMaior(vector<int> &vetor)
{
	if(vetorVazio(vetor)) return;

	int maior = vetor[0];
	int tamanho = vetor.size();
    for(int i = 0; i < tamanho; i++) if(vetor[i]>maior) maior = vetor[i];
    
    cout << "\n< O maior valor encontrado é: " << maior << ".\n\n\n";
}


void encontrarPares(vector<int> &vetor)
{
	if(vetorVazio(vetor)) return;

	int tamanho = vetor.size();
    vector<int> pares(tamanho);
	int n_pares = 0;
    for(int i = 0; i < tamanho; i++) if(vetor[i] % 2 == 0){pares[n_pares++] = vetor[i];}

	// Retorna todos os números pares, inclusive repetidos.
    cout << "\n< Há um total de " << n_pares << " número(s) par(es):\n< ";
    for(int i = 0; i < n_pares; i++) cout << pares[i] << ((i+1 < n_pares) ? ", " : ".\n");
    cout << "\n\n";   
}


void somatoria(vector<int> &vetor)
{
	if(vetorVazio(vetor)) return;

	int tamanho = vetor.size();
	int soma = 0;
    for(int i = 0; i < tamanho; i++) soma += vetor[i];
	cout << "\n< A somatória de todos os elementos é igual a " << soma << ".\n\n\n";
}


void inverterOrdem(vector<int> &vetor)
{
	if(vetorVazio(vetor)) return;

	int tamanho = vetor.size();
	vector<int> vetor_original(tamanho);

    for(int i = 0; i < tamanho; i++) vetor_original[i] = vetor[i];
    for(int i = 0; i < tamanho; i++) vetor[i] = vetor_original[tamanho-(i+1)];

	cout << "Ordem original: "; for(int i = 0; i < tamanho; i++) cout << vetor_original[i] << ((i+1 < tamanho) ? ", " : ".\n");
	cout << "Nova ordem: "; for(int i = 0; i < tamanho; i++) cout << vetor[i] << ((i+1 < tamanho) ? ", " : ".");
	cout << "\n\n\n";
}


void ordenar(vector<int> &vetor)
{
	if(vetorVazio(vetor)) return;

	int tamanho = vetor.size();
    quicksort(vetor, 0, tamanho-1);

    cout << "\n< Os itens do vetor foram organizados em ordem crescente.\n";
    cout << "< A nova ordem é a seguinte: ";
    for(int i = 0; i < tamanho; i++) cout << vetor[i] << ((i+1 < tamanho) ? ", " : ".");
    cout << "\n\n\n";
}


void quicksort(vector<int> &vetor, int i_esq, int i_dir)
{
    if(i_esq < i_dir)
    {
        int pivot = vetor[i_esq];
        int i = i_esq; // i = índice do próximo pivô na recursão

        for(int j = i_esq+1; j <= i_dir; j++)
        {
            if(vetor[j] <= pivot)
            {i++; trocar(vetor, i, j);}
        }

        trocar(vetor, i_esq, i);
        
        // Recursão
        quicksort(vetor, i_esq, i-1);
        quicksort(vetor, i+1, i_dir);
    }
}


void trocar(vector<int> &vetor, int indice_a, int indice_b)
{
    int aux = vetor[indice_a];
    vetor[indice_a] = vetor[indice_b];
    vetor[indice_b] = aux;
}


void mostrarMenu()
{
	cout << "-------------------------------------------------------------------\n"
	<< "------------------------------ MENU -------------------------------\n\n"
	<< "1. Popular um vetor com 10 números aleatórios\n"
	<< "2. Encontrar e exibir o maior elemento do vetor\n"
	<< "3. Calcular e exibir quantos elementos são pares no vetor\n"
	<< "4. Calcular e exibir o valor da somatória dos elementos do vetor\n"
	<< "5. Inverter a ordem dos elementos do vetor\n"
	<< "6. Ordenar e exibir os elementos do vetor na ordem crescente\n"
	<< "7. Sair\n"
	<< "\n< Digite o número do item:"
	<< "\n> ";
}


int vetorVazio(vector<int> vetor)
{
	// for(int i = 0; i < vetor.size(); i++) cout << "\nvetor[" << i << "] : " << vetor[i];
	int tamanho = vetor.size();
	int valor_inicial = vetor[0];
	for (int i = 1; i < tamanho; i++) if(vetor[i] != valor_inicial) return 0;
	cout << "\n<# Não há valores a serem analisados no vetor.\n\n";
	return 1;
}