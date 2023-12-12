#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "combinations.h"

int compareByValue(const void *a, const void *b) {
    double aValue = ((ICombinationsValue *)a)->value;
    double bValue = ((ICombinationsValue *)b)->value;

    return bValue - aValue;
}

int isDoubleEquals(double a, double b) {
    double epsilon = 0.001;
    return fabs(a - b) < epsilon;
}

Combination addElementToCombination(const Combination* current, const ICombinationsValue* element) {
    Combination newCombination;
    newCombination.size = current->size + 1;
    newCombination.elements = malloc(newCombination.size * sizeof(ICombinationsValue));

    for (int i = 0; i < current->size; ++i) {
        newCombination.elements[i] = current->elements[i];
    }

    newCombination.elements[current->size] = *element;

    return newCombination;
}

double getListSum(const ICombinationsValue* list, int listSize) {
    double sum = 0;
    for (int i = 0; i < listSize; ++i) {
        sum += list[i].value;
    }
    return sum;
}

void findCombination(const Combination* current, const ICombinationsValue* remaining, int remainingSize, double remainingValue, Combination** combinations, int* combinationsCount) {
    if (isDoubleEquals(remainingValue, 0.00)) {
        *combinations = realloc(*combinations, (*combinationsCount + 1) * sizeof(Combination));
        (*combinations)[*combinationsCount] = *current;
        ++(*combinationsCount);
        return;
    }

    if (remainingValue < 0 || remainingSize == 0) {
        return;
    }

    // Filtrar elementos que cabem na soma
    ICombinationsValue* innerRemaining = malloc(remainingSize * sizeof(ICombinationsValue));
    int innerRemainingSize = 0;
    for (int i = 0; i < remainingSize; ++i) {
        if (remaining[i].value <= remainingValue) {
            innerRemaining[innerRemainingSize++] = remaining[i];
        }
    }

    if (innerRemainingSize == 0) {
        free(innerRemaining);
        return;
    }

    double sumOfRemaining = getListSum(innerRemaining, innerRemainingSize);
    if (sumOfRemaining < remainingValue) {
        free(innerRemaining);
        return;
    }

    ICombinationsValue invoice = innerRemaining[0];
    double invoiceValue = invoice.value;

    Combination newCurrent = addElementToCombination(current, &invoice);
    findCombination(
        &newCurrent,
        innerRemaining + 1,
        innerRemainingSize - 1,
        remainingValue - invoiceValue,
        combinations,
        combinationsCount
    );

    findCombination(
        current,
        innerRemaining + 1,
        innerRemainingSize - 1,
        remainingValue,
        combinations,
        combinationsCount
    );

    // Liberar a memória alocada dinamicamente
    free(innerRemaining);
}

Combination* combineByValue(ICombinationsValue* list, int listSize, double target, int* combinationsCount) {
    Combination* combinations = NULL;
    *combinationsCount = 0;

    Combination current;
    current.size = 0;

    qsort(list, listSize, sizeof(ICombinationsValue), compareByValue);

    clock_t start;

    start = clock();
    findCombination(&current, list, listSize, target, &combinations, combinationsCount);

    // for (int i = 0; i < *combinationsCount; ++i) {
    //     printCombination(&combinations[i]);
    // }

    printf("Tempo de execução: %f segundos\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);
    // printf("combinações: %d\n", *combinationsCount);

    return combinations;
}
