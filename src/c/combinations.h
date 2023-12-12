typedef struct {
    int64_t id;
    double value;
} ICombinationsValue;

typedef struct {
    ICombinationsValue* elements;
    int size;
} Combination;

Combination* combineByValue(ICombinationsValue* list, int listSize, double target, int* combinationsCount);
