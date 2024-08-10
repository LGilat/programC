#include <stdio.h>
#define MAX 10


int main(int argc, char const *argv[])
{
    /* code */
    int matriz[MAX];
    printf("introducir los elementos de la matriz\n");
    for (int i = 0; i < MAX; i++){
        printf("matriz[%d]: ", i);
        scanf("%d", &matriz[i]);
    }

    printf("los elementos de la matriz son:\n");
    for (int i = 0; i < MAX; i++){
        printf("matriz[%d]: %d\n", i, matriz[i]);
    }

    printf("Finalizando programa\n");
    return 0;
}
