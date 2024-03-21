#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

void mostrarMenu();
int vetorVazio(int *ponteiro);

void popularVetor(int *vetor, int tamanho),
encontrarMaior(int *vetor, int tamanho),
encontrarPares(int *vetor, int tamanho),
somatoria(int *vetor, int tamanho),
inverterOrdem(int *vetor, int tamanho),
ordenar(int *vetor, int tamanho);

void quicksort(int *vetor, int i_esq, int i_dir),
trocar (int *vetor, int indice_a, int indice_b);

int main()
{
    setlocale(LC_ALL, "");

    srand(time(NULL));

    int tamanho_vetor = 10;
    int vetor[tamanho_vetor];
    *vetor = NULL; // Ponteiro para o valor no primeiro índice declarado como NULL para análises futuras, checando se o vetor já foi ou não preenchido antes de executar determinadas operações.

    int qnt_opc = 7;
    int func[] = {popularVetor, encontrarMaior, encontrarPares, somatoria, inverterOrdem, ordenar};
    
    int (*f)(int *, int) = NULL; // Ponteiro para uma função que receberá: 1. um ponteiro para inteiro (o vetor de valores, no caso), 2. um inteiro (correspondente ao tamanho do vetor).

    int escolha = 0;
    while(1)
    {
        mostrarMenu();
        scanf("%d", &escolha);

        if(escolha > 0 && escolha <= qnt_opc) f = func[escolha-1];
        else
        {
            escolha = 0;
            
        }

        if(escolha) // Caso haja uma escolha válida
        {
            if(escolha == qnt_opc) break;
            else (*f)(vetor, tamanho_vetor);
        }
    }

    printf("\n\nEncerrando o programa.\n\n");
}


void popularVetor(int *vetor, int tamanho)
{
    int min = 0, max = min;
    
    printf("\n< Defina o mínimo valor possível a ser inserido: ");
    scanf("%d", &min);
    
    while(1)
    {
        printf("\n< Defina o máximo valor possível a ser inserido: ");
        scanf("%d", &max);
        
        if(max > min) break;
        else {printf("<# O valor máximo não pode ser menor ou igual ao valor mínimo!\n"); continue;}
    }
    
    for(int i = 0; i < tamanho; i++) vetor[i] = (rand() % (max - min)) + min;
    

    printf("\n< Os valores do vetor são:\n< ");
    for(int i = 0; i < tamanho; i++) printf("%d%c ", vetor[i], i+1 < tamanho ? ',' : '.');
    printf("\n\n\n");
}

void encontrarMaior(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;
    int maior = vetor[0];
    for(int i = 0; i < tamanho; i++) if(vetor[i]>maior) maior = vetor[i];
    
    printf("\n< O maior valor encontrado é: %d.\n\n\n", maior);
}

void encontrarPares(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;
    
    int pares[tamanho], n_pares = 0;
    for(int i = 0; i < tamanho; i++) if(vetor[i] % 2 == 0){pares[n_pares++] = vetor[i];}

    printf("\n< Há um total de %d número(s) par(es):\n< ", n_pares);
    for(int i = 0; i < n_pares; i++) printf("%d%c ", pares[i], i < n_pares-1 ? ',' : '.');
    printf("\n\n\n");   
}

void somatoria(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;

    int soma = 0;
    for(int i = 0; i < tamanho; i++) soma += vetor[i];
    printf("\n< A somatória de todos os elementos é igual a %d.\n\n\n", soma);
}

void inverterOrdem(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;

    int vetor_original[tamanho];
    for(int i = 0; i < tamanho; i++) vetor_original[i] = vetor[i];
    for(int i = 0; i < tamanho; i++) vetor[i] = vetor_original[tamanho-(i+1)];

    printf("\n< Ordem original: "); for(int i = 0; i < tamanho; i++) printf("%d%c ", vetor_original[i], i+1 < tamanho ? ',' : '.');
    printf("\n< Nova ordem: "); for(int i = 0; i < tamanho; i++) printf("%d%c ", vetor[i], i+1 < tamanho ? ',' : '.');
    printf("\n\n\n");
}

void ordenar(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;

    quicksort(vetor, 0, tamanho-1);

    printf("\n< Os itens do vetor foram ordenados em ordem crescente.");
    printf("\n< A nova ordem é a seguinte: ");
    for(int i = 0; i < tamanho; i++) printf("%d%c ", vetor[i], i+1 < tamanho ? ',' : '.');
    printf("\n\n\n");
}

void quicksort(int *vetor, int i_esq, int i_dir)
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

void trocar(int *vetor, int indice_a, int indice_b)
{
    int aux = vetor[indice_a];
    vetor[indice_a] = vetor[indice_b];
    vetor[indice_b] = aux;
}

void mostrarMenu()
{
    printf
    (
    "-------------------------------------------------------------------\n"
    "------------------------------ MENU -------------------------------\n\n"
    "1. Popular um vetor com 10 números aleatórios\n"
    "2. Encontrar e exibir o maior elemento do vetor\n"
    "3. Calcular e exibir quantos elementos são pares no vetor\n"
    "4. Calcular e exibir o valor da somatória dos elementos do vetor\n"
    "5. Inverter a ordem dos elementos do vetor\n"
    "6. Ordenar e exibir os elementos do vetor na ordem crescente\n"
    "7. Sair\n"
    "\n< Digite o número do item:"
    "\n> "
    );
}

int vetorVazio(int *ponteiro) // Checa se o vetor apontado está vazio com base no ponteiro para o primeiro elemento.
{
    if(ponteiro == NULL){ printf("\n<# Não há valores a serem analisados no vetor.\n\n"); return 1; }
    else return 0;
}