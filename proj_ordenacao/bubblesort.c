#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void trocar(int *a, int *b){ /*funcao responsavel pela troca de posicao de dois numeros no array*/
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n){ /*ordena o array usando bubble sort, recebendo o array (arr) e o tamanho desse array (n)*/
    int i, j;
    bool troca; /*essa variavel booleana eh usada para verificar se houve ou nao trocas na iteracao interna do array*/
    for (i = 0; i < n - 1; i++) {  /*esse laco vai servir para controlar as passagens do algoritmo*/
        troca = false; /*se nao tiver havido troca, o algoritmo eh interrompido para nao ser usado desnecessariamente*/
        for (j = 0; j < n - i - 1; j++) { /*ja esse segudo vai comparar cada elemento com o seu proximo, caso o anterior seja maior que o proximo, eh feita a troca de posicao*/
            if (arr[j] > arr[j + 1]) { 
                trocar(&arr[j], &arr[j + 1]); 
                troca = true;
            }
        }
        if (troca == false) /*essa verificacao serve para interromper a execucao do algoritmo caso o array ja esteja ordenado*/ 
            break;
    }
}
int *lerArrayDoArquivo(const char *filename, int *n){ /*essa funcao sera responsavel por ler os números do arquivo e retornar o array e seu tamanho*/
    FILE *arquivo = fopen(filename, "r"); /*esse f na frente do open eh tipo f de file, pra dizer que vai abrir o arquivo*/
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    int contador = 0; /*esse contador vai ser usado para verificar quantos números existem no arquivo*/
    int numero;
    while (fscanf(arquivo, "%d", &numero) != EOF) { /*por issso tambem tem o f aqui, na frente do scanf, que eh pra dizer que ta lendo o dado do arquivo. esse laco que vai percorrer o arquivo, lendo os nuemeros um por um para poder adicionar aos contador*/
        contador++;
    }
    rewind(arquivo); /*apos contar os numeros a funcao rewind faz o ponteiro de leitura voltar ao inicio do arquivo*/

    int* arr = (int*)malloc(contador *sizeof(int)); /*aqui eh onde sera alocada a memoria, em um array, com tamanho necessario para armazenar os numeros*/
    if (arr == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    int i = 0;
    while (fscanf(arquivo, "%d", &arr[i]) != EOF) {  /*aqui os numeros do arquivo serao lidos novamente e armazenados no array criado na funcao acima dessa*/
        i++;
    }
  fclose(arquivo); /*para fechar o arquivo pos leitura*/

    /*Retorna o array e o tamanho*/ 
    *n = contador;
    return arr;
}

int main(){
    int n;
    int *arr = lerArrayDoArquivo("100Numeros.txt", &n); /*leitura dos numeros do arquivo txt*/

    clock_t inicio = clock(); /*funcao para medir o tempo de execucao*/

    bubbleSort(arr, n); /*ordena o array usando bubble sort*/

    clock_t fim = clock();

    /*calculo e impressao do tempo de execução*/ 
    double tempoGasto = (double)(fim - inicio) *1000 / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.2f milissegundos\n", tempoGasto);

    // Libera a memória alocada para o array
    free(arr);

    return 0;
}

/*Referência: https://www.geeksforgeeks.org/bubble-sort-algorithm/*/