#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

#include "opthelpers.h"


#ifdef __GNUC__
#define DECL_FORMAT(x, y, z) __attribute__((format(x, (y), (z))))
#else
#define DECL_FORMAT(x, y, z)
#endif


extern FILE *gLogFile;

#if !defined(_WIN32)
#define AL_PRINT(T, ...) fprintf(gLogFile, "AL lib: " T " " __VA_ARGS__)
#else
void al_print(const char *type, const char *fmt, ...) DECL_FORMAT(printf, 2,3);
#define AL_PRINT(T, ...) al_print((T), __VA_ARGS__)
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define LOG_ANDROID(T, ...) __android_log_print(T, "openal", "AL lib: " __VA_ARGS__)
#else
#define LOG_ANDROID(T, ...) ((void)0)
#endif

enum LogLevel {
    NoLog,
    LogError,
    LogWarning,
    LogTrace,
    LogRef
};
extern LogLevel gLogLevel;

#define TRACEREF(...) do {                                                    \
    if(UNLIKELY(gLogLevel >= LogRef))                                         \
        AL_PRINT("(--)", __VA_ARGS__);                                        \
} while(0)

#define TRACE(...) do {                                                       \
    if(UNLIKELY(gLogLevel >= LogTrace))                                       \
        AL_PRINT("(II)", __VA_ARGS__);                                        \
    LOG_ANDROID(ANDROID_LOG_DEBUG, __VA_ARGS__);                              \
} while(0)

#define WARN(...) do {                                                        \
    if(UNLIKELY(gLogLevel >= LogWarning))                                     \
        AL_PRINT("(WW)", __VA_ARGS__);                                        \
    LOG_ANDROID(ANDROID_LOG_WARN, __VA_ARGS__);                               \
} while(0)

#define ERR(...) do {                                                         \
    if(UNLIKELY(gLogLevel >= LogError))                                       \
        AL_PRINT("(EE)", __VA_ARGS__);                                        \
    LOG_ANDROID(ANDROID_LOG_ERROR, __VA_ARGS__);                              \
} while(0)

#endif /* LOGGING_H */
