#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "combinations.h"

const double FLOAT_ACCEPTABLE_DIFF = 0.001;
int MAX_ALLOWED_COMBINATIONS = -1;

int getMaxAllowedCombinations() {
    if (MAX_ALLOWED_COMBINATIONS == -1) {
        char *maxAllowedCombinations = getenv("MAX_ALLOWED_COMBINATIONS");

        if (maxAllowedCombinations != NULL) {
            MAX_ALLOWED_COMBINATIONS = atoi(maxAllowedCombinations);
        } else {
            MAX_ALLOWED_COMBINATIONS = 10000;
        }
    }
    return MAX_ALLOWED_COMBINATIONS;
}

int compareByValue(const void *a, const void *b) {
    double aValue = ((ICombinationsValue *)a)->value;
    double bValue = ((ICombinationsValue *)b)->value;

    return bValue - aValue;
}

Combination addElementToCombination(Combination* current, ICombinationsValue* element) {
    Combination newCombination;
    newCombination.size = current->size + 1;
    newCombination.elements = malloc(newCombination.size * sizeof(ICombinationsValue));

    for (int i = 0; i < current->size; ++i) {
        newCombination.elements[i] = current->elements[i];
    }

    newCombination.elements[current->size] = *element;

    return newCombination;
}

int validateRemainingList(ICombinationsValue* remaining, int remainingSize, double remainingValue) {
    // Filtrar elementos que cabem na soma
    int innerRemainingSize = 0;
    for (int i = 0; i < remainingSize; ++i) {
        if (remaining[i].value <= remainingValue) {
            innerRemainingSize++;
        }
    }
    if (innerRemainingSize == 0) {
        return 0;
    }

    // Verificar se a soma dos restantes pode combinar com o target
    double sumOfRemaining = 0;
    for (int i = 0; i < remainingSize; ++i) {
        sumOfRemaining += remaining[i].value;
    }
    if (sumOfRemaining < remainingValue) {
        return 0;
    }

    return 1;
}

void findCombination(Combination* current, ICombinationsValue* remaining, int remainingSize, double remainingValue, Combination** combinations, int* combinationsCount) {
    if (*combinationsCount >= getMaxAllowedCombinations()) {
        return;
    }

    if (fabs(remainingValue - 0.00) < FLOAT_ACCEPTABLE_DIFF) {
        *combinations = realloc(*combinations, (*combinationsCount + 1) * sizeof(Combination));
        (*combinations)[*combinationsCount] = *current;
        *combinationsCount += 1;
        return;
    }

    if (remainingValue < 0 || remainingSize == 0) {
        return;
    }

    if (validateRemainingList(remaining, remainingSize, remainingValue) != 1) {
        return;
    }

    ICombinationsValue invoice = remaining[0];
    double invoiceValue = invoice.value;

    Combination newCurrent = addElementToCombination(current, &invoice);
    ICombinationsValue* newRemaining = remaining + 1;

    findCombination(
        &newCurrent,
        newRemaining,
        remainingSize - 1,
        remainingValue - invoiceValue,
        combinations,
        combinationsCount
    );

    findCombination(
        current,
        newRemaining,
        remainingSize - 1,
        remainingValue,
        combinations,
        combinationsCount
    );
}

Combination* combineByValue(ICombinationsValue* list, int listSize, double target, int* combinationsCount) {
    Combination* combinations = NULL;
    *combinationsCount = 0;

    Combination current;
    current.size = 0;

    qsort(list, listSize, sizeof(ICombinationsValue), compareByValue);

    clock_t start = clock();
    findCombination(&current, list, listSize, target, &combinations, combinationsCount);
    printf("Tempo de execução: %f segundos\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);

    return combinations;
}
