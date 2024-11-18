#pragma once

#ifdef _WIN32
  #ifdef ENGINE_EXPORT
    #define HAPI __declspec(dllexport)
  #else
    #define HAPI __declspec(dllimport)
  #endif
#else
  #ifdef ENGINE_EXPORT
    #define HAPI __attribute__((visibility("default")))
  #else
    #define HAPI
  #endif
#endif
