{
  "targets": [
    {
      "target_name": "combinations-addon",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/c/combinations.c",
        "./src/c/index.c"
      ],
      "include_dirs": [
        "./node_modules/node-addon-api"
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
    }
  ]
}