#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100

typedef struct {
    char title[MAX_LEN];
    char size[MAX_LEN];
    float price;
    int year;
    char author[MAX_LEN];
} Painting;
void enterPaintings(Painting* arr, int count) {
    for (int i = 0; i < count; i++) {
        printf("\n--- Введення даних для картини %d ---\n", i + 1);

        printf("Назва (англійською мовою): ");
        while (getchar() != '\n'); 
        fgets(arr[i].title, MAX_LEN, stdin);
        arr[i].title[strcspn(arr[i].title, "\n")] = '\0';

        printf("Розмір: ");
        fgets(arr[i].size, MAX_LEN, stdin);
        arr[i].size[strcspn(arr[i].size, "\n")] = '\0';

        printf("Ціна: ");
        scanf("%f", &arr[i].price);

        printf("Рік написання: ");
        scanf("%d", &arr[i].year);

        printf("Автор (англійською мовою): ");
        while (getchar() != '\n'); 
        fgets(arr[i].author, MAX_LEN, stdin);
        arr[i].author[strcspn(arr[i].author, "\n")] = '\0';
    }
}

void writeToFile(const char* filename, Painting* arr, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Не вдалося відкрити файл");
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%s;%.2f;%d;%s\n",
                arr[i].title, arr[i].size, arr[i].price, arr[i].year, arr[i].author);
    }
    fclose(file);
}

void updatePrices(Painting* arr, int count) {
    for (int i = 0; i < count; i++) {
        printf("\nНова ціна для картини \"%s\": ", arr[i].title);
        scanf("%f", &arr[i].price);
    }
}

int main() {
    system("chcp 65001");
    int n;
    printf("Введіть кількість картин: ");
    scanf("%d", &n);

    Painting* paintings = (Painting*)malloc(n * sizeof(Painting));
    if (!paintings) {
        printf("Помилка виділення пам'яті!\n");
        return 1;
    }

    enterPaintings(paintings, n);
    writeToFile("paintings.txt", paintings, n);
    printf("\nДані збережено у файл paintings.txt.\n");
    printf("\n--- Оновлення цін ---\n");
    updatePrices(paintings, n);
    writeToFile("paintings.txt", paintings, n);
    printf("\nОновлені дані збережено у файл paintings.txt.\n");
    free(paintings);
    return 0;
}