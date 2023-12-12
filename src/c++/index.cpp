#include <napi.h>
#include <string>
#include <vector>
#include <iostream>

#include "combinations.h"

using namespace std;

Napi::String combineByValueWrapper(const Napi::CallbackInfo &info) {
  Napi::Array array = info[0].As<Napi::Array>();
  size_t arrayLength = array.Length();

  vector<ICombinationsValue> nativeArray;
  for (size_t i = 0; i < arrayLength; ++i) {
    Napi::Value arrayItem = array[i];
    Napi::Array element = arrayItem.As<Napi::Array>();

    cout << "primeiro: " << element[0] << "\n";

    // nativeArray.push_back({element.id, element.value});
  }


  double target = info[1].ToNumber();
  cout << "segundo: " << target << "\n";

  // Napi::Env env = info.Env();

  // vector<vector<ICombinationsValue>> result = combineByValue(info[0].ToObject(), info[1].ToNumber());

  // return Napi::Array::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "combineByValue"),
    Napi::Function::New(env, combineByValueWrapper)
  );
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
