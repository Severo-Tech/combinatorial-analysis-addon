#define NAPI_VERSION 9

#include <stdlib.h>
#include <node_api.h>

#include "combinations.h"

// Função wrapper para combineByValue
napi_value combineByValueWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_handle_scope scope;

    status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Cannot open Handle Scope");
    }

    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    if (argc != 2) {
        napi_throw_type_error(env, NULL, "Número incorreto de argumentos");
        return NULL;
    }

    // Obtenha o array de objetos ICombinationsValue
    napi_value array = argv[0];
    uint32_t length;
    napi_get_array_length(env, array, &length);

    // Aloque memória para os objetos ICombinationsValue
    ICombinationsValue* list = malloc(length * sizeof(ICombinationsValue));
    for (uint32_t i = 0; i < length; ++i) {
        napi_value element;
        status = napi_get_element(env, array, i, &element);
        if (status != napi_ok) {
            napi_throw_error(env, NULL, "There is no element");
        }

        // Busca valor do atributo ID
        napi_value idProp;
        napi_get_element(env, element, 0, &idProp);
        napi_get_value_int64(env, idProp, &list[i].id);

        // Busca valor do atributo Value
        napi_value valueProp;
        napi_get_element(env, element, 1, &valueProp);
        napi_get_value_double(env, valueProp, &list[i].value);
    }

    // Obtenha o outro argumento (target)
    double target;
    napi_get_value_double(env, argv[1], &target);

    status = napi_close_handle_scope(env, scope);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Cannot close Handle Scope");
    }

    int combinationsCount = 0;
    Combination* combinations = combineByValue(list, length, target, &combinationsCount);

    // Libere a memória alocada dinamicamente
    free(list);

    status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Cannot open Handle Scope");
    }

    // Crie um array de objetos JS para armazenar as combinações
    napi_value resultArray;
    napi_create_array_with_length(env, combinationsCount, &resultArray);

    // Preencha o array de resultados
    for (int i = 0; i < combinationsCount; ++i) {
        napi_value combination;
        napi_create_array_with_length(env, combinations[i].size, &combination);

        // Preencha os objetos ICombinationsValue dentro da combinação
        for (int j = 0; j < combinations[i].size; ++j) {
            napi_value element;
            napi_create_array_with_length(env, 2, &element);

            napi_value* intAux;
            napi_create_int32(env, combinations[i].elements[j].id, &intAux);
            napi_set_element(env, element, 0, intAux);

            napi_value* doubleAux = NULL;
            napi_create_double(env, combinations[i].elements[j].value, &doubleAux);
            napi_set_element(env, element, 1, doubleAux);

            napi_set_element(env, combination, j, element);
        }

        // Adicione a combinação ao array de resultados
        napi_set_element(env, resultArray, i, combination);
        // Libere a memória alocada dinamicamente
        free(combinations[i].elements);
    }

    // Libere a memória alocada dinamicamente
    free(combinations);

    status = napi_close_handle_scope(env, scope);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Cannot close Handle Scope");
    }
    return resultArray;
}

// Função de inicialização do módulo
napi_value Init(napi_env env, napi_value exports) {
    napi_status status;

    // Defina a função combineByValue no objeto de exportação
    napi_value combineByValueFn;
    status = napi_create_function(env, NULL, 0, combineByValueWrapper, NULL, &combineByValueFn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Erro ao criar a função combineByValue");
        return NULL;
    }
    status = napi_set_named_property(env, exports, "combineByValue", combineByValueFn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Erro ao definir a função combineByValue no objeto de exportação");
        return NULL;
    }

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
