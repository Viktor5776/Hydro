#pragma once
// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#define HPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define HPLATFORM_LINUX 1
#if defined(__ANDROID__)
#define HPLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define HPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define HPLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define HPLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define HPLATFORM_IOS 1
#define HPLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define HPLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef HEXPORT
// Exports
#ifdef _MSC_VER
#define HAPI __declspec(dllexport)
#else
#define HAPI __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define HAPI __declspec(dllimport)
#else
#define HAPI
#endif
#endif
