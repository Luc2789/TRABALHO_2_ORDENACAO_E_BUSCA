#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição dos algoritmos de ordenação
void selectionSort(int arr[], int n, int *comparisons, int *swaps);
void insertionSort(int arr[], int n, int *comparisons, int *swaps);
void bubbleSort(int arr[], int n, int *comparisons, int *swaps);
void heapSort(int arr[], int n, int *comparisons, int *swaps);
void radixSort(int arr[], int n);
void quickSort(int arr[], int low, int high, int *comparisons, int *swaps);
void mergeSort(int arr[], int l, int r, int *comparisons, int *swaps);

// Funções auxiliares
void generateRandomNumbers(int arr[], int n);
void saveToFile(int arr[], int n, const char *filename);
void readFromFile(int arr[], int n, const char *filename);
int binarySearch(int arr[], int l, int r, int x, int *comparisons);
int sequentialSearch(int arr[], int n, int x, int *comparisons);
void printMenu();

int main() {
    int sizes[] = {100, 1000, 10000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int choice, n, searchValue;
    int *arr = NULL;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Gerar arquivos com números aleatórios
                for (int i = 0; i < numSizes; i++) {
                    n = sizes[i];
                    arr = (int *)malloc(n * sizeof(int));
                    generateRandomNumbers(arr, n);

                    char filename[50];
                    sprintf(filename, "random_%d.txt", n);
                    saveToFile(arr, n, filename);
                    printf("Arquivo %s gerado com sucesso!\n", filename);

                    free(arr);
                }
                break;

            case 2: // Ordenar arquivos e medir desempenho
                for (int i = 0; i < numSizes; i++) {
                    n = sizes[i];
                    arr = (int *)malloc(n * sizeof(int));

                    char filename[50];
                    sprintf(filename, "random_%d.txt", n);
                    readFromFile(arr, n, filename);

                    int comparisons, swaps;
                    clock_t start, end;
                    double cpu_time_used;

                    // Selection Sort
                    start = clock();
                    comparisons = swaps = 0;
                    selectionSort(arr, n, &comparisons, &swaps);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Selection Sort -\ntamanho: %d, \ncomparação: %d, \ntrocas: %d, \ntempo: %f s\n", n, comparisons, swaps, cpu_time_used);
                    sprintf(filename, "selection_sort_%d.txt", n);
                    saveToFile(arr, n, filename);

                    // Insertion Sort
                    readFromFile(arr, n, "random_%d.txt"); // Re-ler o arquivo original
                    start = clock();
                    comparisons = swaps = 0;
                    insertionSort(arr, n, &comparisons, &swaps);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Insertion Sort - \ntamanho: %d, \ncomparação: %d, \ntrocas: %d, \ntempo: %f s\n", n, comparisons, swaps, cpu_time_used);
                    sprintf(filename, "insertion_sort_%d.txt", n);
                    saveToFile(arr, n, filename);

                    // Bubble Sort
                    readFromFile(arr, n, "random_%d.txt");
                    start = clock();
                    comparisons = swaps = 0;
                    bubbleSort(arr, n, &comparisons, &swaps);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Bubble Sort -\ntamanho: %d, \ncomparação: %d, \ntrocas: %d, \ntempo: %f s\n", n, comparisons, swaps, cpu_time_used);
                    sprintf(filename, "bubble_sort_%d.txt", n);
                    saveToFile(arr, n, filename);

                    // Heap Sort
                    readFromFile(arr, n, "random_%d.txt");
                    start = clock();
                    comparisons = swaps = 0;
                    heapSort(arr, n, &comparisons, &swaps);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Heap Sort - \ntamanho: %d, \ncomparação: %d, \ntrocas: %d, \ntempo: %f s\n", n, comparisons, swaps, cpu_time_used);
                    sprintf(filename, "heap_sort_%d.txt", n);
                    saveToFile(arr, n, filename);

                    // Quick Sort
                    readFromFile(arr, n, "random_%d.txt");
                    start = clock();
                    comparisons = swaps = 0;
                    quickSort(arr, 0, n - 1, &comparisons, &swaps);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Quick Sort - \ntamanho: %d, \ncomparação: %d, \ntrocas: %d, \ntempo: %f s\n", n, comparisons, swaps, cpu_time_used);
                    sprintf(filename, "quick_sort_%d.txt", n);
                    saveToFile(arr, n, filename);

                    // Merge Sort
                    readFromFile(arr, n, "random_%d.txt");
                    start = clock();
                    comparisons = swaps = 0;
                    mergeSort(arr, 0, n - 1, &comparisons, &swaps);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Merge Sort - \ntamanho: %d, \ncomparação: %d, \ntrocas: %d, \ntempo: %f s\n", n, comparisons, swaps, cpu_time_used);
                    sprintf(filename, "merge_sort_%d.txt", n);
                    saveToFile(arr, n, filename);

                    // Radix Sort
                    readFromFile(arr, n, "random_%d.txt");
                    start = clock();
                    radixSort(arr, n);
                    end = clock();
                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("Radix Sort - Size: %d, Time: %f s\n", n, cpu_time_used);
                    sprintf(filename, "radix_sort_%d.txt", n);
                    saveToFile(arr, n, filename);

                    free(arr);
                }
                break;

            case 3: // Buscar valor
                printf("Digite o tamanho do arquivo (100, 1000, 10000, 100000): ");
                scanf("%d", &n);
                arr = (int *)malloc(n * sizeof(int));

                char filename[50];
                sprintf(filename, "random_%d.txt", n);
                readFromFile(arr, n, filename);

                printf("Digite o valor a ser buscado: ");
                scanf("%d", &searchValue);

                int binComparisons = 0, seqComparisons = 0;
                int binResult = binarySearch(arr, 0, n - 1, searchValue, &binComparisons);
                int seqResult = sequentialSearch(arr, n, searchValue, &seqComparisons);

                printf("Busca Binária - Valor: %d, Comparações: %d, Encontrado: %d\n", searchValue, binComparisons, binResult);
                printf("Busca Sequencial - Valor: %d, Comparações: %d, Encontrado: %d\n", searchValue, seqComparisons, seqResult);

                free(arr);
                break;

            case 0: // Sair
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}

// Implementação dos algoritmos de ordenação
void selectionSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        (*swaps)++;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            j = j - 1;
            (*swaps)++;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                (*swaps)++;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void heapify(int arr[], int n, int i, int *comparisons, int *swaps) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        (*comparisons)++;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        (*comparisons)++;
    }

    if (largest != i) {
        (*swaps)++;
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, comparisons, swaps);
    }
}

void heapSort(int arr[], int n, int *comparisons, int *swaps) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comparisons, swaps);

    for (int i = n - 1; i > 0; i--) {
        (*swaps)++;
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, comparisons, swaps);
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int partition(int arr[], int low, int high, int *comparisons, int *swaps) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            (*swaps)++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    (*swaps)++;
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int *comparisons, int *swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, swaps);
        quickSort(arr, low, pi - 1, comparisons, swaps);
        quickSort(arr, pi + 1, high, comparisons, swaps);
    }
}

void merge(int arr[], int l, int m, int r, int *comparisons, int *swaps) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r, int *comparisons, int *swaps) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparisons, swaps);
        mergeSort(arr, m + 1, r, comparisons, swaps);
        merge(arr, l, m, r, comparisons, swaps);
    }
}

// Funções auxiliares
void generateRandomNumbers(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000; // Números aleatórios entre 0 e 99999
    }
}

void saveToFile(int arr[], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

void readFromFile(int arr[], int n, const char *filename) {
    FILE *file = fopen(filename, "r");
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}

int binarySearch(int arr[], int l, int r, int x, int *comparisons) {
    while (l <= r) {
        (*comparisons)++;
        int m = l + (r - l) / 2;
        if (arr[m] == x)
            return m;
        if (arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

int sequentialSearch(int arr[], int n, int x, int *comparisons) {
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (arr[i] == x)
            return i;
    }
    return -1;
}

void printMenu() {
    printf("\n=== MENU ===\n");
    printf("1 - Gerar arquivos com números aleatórios\n");
    printf("2 - Ordenar arquivos e medir desempenho\n");
    printf("3 - Buscar valor\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}