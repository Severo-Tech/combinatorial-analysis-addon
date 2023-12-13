/*
  Comando para executar esse arquivo:
  # gcc -o ./src/c/combinations ./src/c/test.c && ./src/c/combinations
*/

#include <stdio.h>
#include <stdlib.h>

#include "combinations.c"

void printCombination(const Combination* combination) {
    printf("Combinação: %d\n", combination->size);
    for (int i = 0; i < combination->size; ++i) {
        printf("    [%d, %.2f]\n", combination->elements[i].id, combination->elements[i].value);
    }
    printf("---------\n");
}

int main() {
    ICombinationsValue list[] = {
      {0, 8.04},
      {0, 58.72},
      {0, 3.54},
      {0, 46.56},
      {0, 42.56},
      {0, 15.84},
      {0, 4.46},
      {0, 3.23},
      {0, 12.56},
      {0, 357.25},
      {0, 15.19},
      {0, 326.57},
      {0, 196.37},
      {0, 11.47},
      {0, 270.96},
      {0, 450.62},
      {0, 17.91},
      {0, 162.98},
      {0, 214.80},
      {0, 129.21},
      {0, 118.11},
      {0, 9.89},
      {0, 24.71},
      {0, 19.59},
      {0, 8.66},
      {0, 316.49},
      {0, 7.91},
      {0, 10.92},
      {0, 10.82},
      {0, 13.65},
      {0, 19.17},
      {0, 13.88},
      {0, 2116.48 },
      {0, 164.61 },
      {0, 436.70 },
      {0, 180.07 },
      {0, 2920.35 },
      {0, 346.21 },
      {0, 2315.22 },
      {0, 227.1 }
    };

    int listSize = sizeof(list) / sizeof(ICombinationsValue);

    double target = 2120.58;

    int combinationsCount;
    Combination* combinations = combineByValue(list, listSize, target, &combinationsCount);

    // Imprimir as combinações encontradas
    for (int i = 0; i < combinationsCount; ++i) {
        printCombination(&combinations[i]);
    }

    printf("Tamanho lista para comparação: %d\n", listSize);
    printf("Total de Combinações: %d\n", combinationsCount);

    // Liberar a memória alocada dinamicamente
    for (int i = 0; i < combinationsCount; ++i) {
        free(combinations[i].elements);
    }
    free(combinations);

    return 0;
}
