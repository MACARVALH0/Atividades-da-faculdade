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
    *vetor = NULL; // Ponteiro para o valor no primeiro �ndice declarado como NULL para an�lises futuras, checando se o vetor j� foi ou n�o preenchido antes de executar determinadas opera��es.

    int qnt_opc = 7;
    int func[] = {popularVetor, encontrarMaior, encontrarPares, somatoria, inverterOrdem, ordenar};
    
    int (*f)(int *, int) = NULL; // Ponteiro para uma fun��o que receber�: 1. um ponteiro para inteiro (o vetor de valores, no caso), 2. um inteiro (correspondente ao tamanho do vetor).

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

        if(escolha) // Caso haja uma escolha v�lida
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
    
    printf("\n< Defina o m�nimo valor poss�vel a ser inserido: ");
    scanf("%d", &min);
    
    while(1)
    {
        printf("\n< Defina o m�ximo valor poss�vel a ser inserido: ");
        scanf("%d", &max);
        
        if(max > min) break;
        else {printf("<# O valor m�ximo n�o pode ser menor ou igual ao valor m�nimo!\n"); continue;}
    }
    
    for(int i = 0; i < tamanho; i++) vetor[i] = (rand() % (max - min)) + min;
    

    printf("\n< Os valores do vetor s�o:\n< ");
    for(int i = 0; i < tamanho; i++) printf("%d%c ", vetor[i], i+1 < tamanho ? ',' : '.');
    printf("\n\n\n");
}

void encontrarMaior(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;
    int maior = vetor[0];
    for(int i = 0; i < tamanho; i++) if(vetor[i]>maior) maior = vetor[i];
    
    printf("\n< O maior valor encontrado �: %d.\n\n\n", maior);
}

void encontrarPares(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;
    
    int pares[tamanho], n_pares = 0;
    for(int i = 0; i < tamanho; i++) if(vetor[i] % 2 == 0){pares[n_pares++] = vetor[i];}

    printf("\n< H� um total de %d n�mero(s) par(es):\n< ", n_pares);
    for(int i = 0; i < n_pares; i++) printf("%d%c ", pares[i], i < n_pares-1 ? ',' : '.');
    printf("\n\n\n");   
}

void somatoria(int *vetor, int tamanho)
{
    if(vetorVazio(*vetor)) return;

    int soma = 0;
    for(int i = 0; i < tamanho; i++) soma += vetor[i];
    printf("\n< A somat�ria de todos os elementos � igual a %d.\n\n\n", soma);
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
    printf("\n< A nova ordem � a seguinte: ");
    for(int i = 0; i < tamanho; i++) printf("%d%c ", vetor[i], i+1 < tamanho ? ',' : '.');
    printf("\n\n\n");
}

void quicksort(int *vetor, int i_esq, int i_dir)
{
    if(i_esq < i_dir)
    {
        int pivot = vetor[i_esq];
        int i = i_esq; // i = �ndice do pr�ximo piv� na recurs�o

        for(int j = i_esq+1; j <= i_dir; j++)
        {
            if(vetor[j] <= pivot)
            {i++; trocar(vetor, i, j);}
        }

        trocar(vetor, i_esq, i);
        
        // Recurs�o
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
    "1. Popular um vetor com 10 n�meros aleat�rios\n"
    "2. Encontrar e exibir o maior elemento do vetor\n"
    "3. Calcular e exibir quantos elementos s�o pares no vetor\n"
    "4. Calcular e exibir o valor da somat�ria dos elementos do vetor\n"
    "5. Inverter a ordem dos elementos do vetor\n"
    "6. Ordenar e exibir os elementos do vetor na ordem crescente\n"
    "7. Sair\n"
    "\n< Digite o n�mero do item:"
    "\n> "
    );
}

int vetorVazio(int *ponteiro) // Checa se o vetor apontado est� vazio com base no ponteiro para o primeiro elemento.
{
    if(ponteiro == NULL){ printf("\n<# N�o h� valores a serem analisados no vetor.\n\n"); return 1; }
    else return 0;
}