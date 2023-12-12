typedef struct {
    int id;
    double value;
} ICombinationsValue;

typedef struct {
    ICombinationsValue* elements;
    int size;
} Combination;

Combination* combineByValue(ICombinationsValue* list, int listSize, double target, int* combinationsCount);
