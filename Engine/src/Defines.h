#pragma once

#ifdef ENGINE_EXPORT
  #define HAPI __declspec(dllexport)
#else
  #define HAPI __declspec(dllimport)
#endif