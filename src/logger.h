#pragma once
#include "stdio.h"
#include "stdlib.h"

typedef enum MessageType {
    ERROR,
    CRITICAL,
} MessageType;

#ifdef RELEASE_MODE
void init_logger();
void shutdown_logger();
#else
// In Debug(or any other) mode, these become "no-ops"
// The compiler sees init_logger() and replaces it with nothing
#define init_logger() ((void)0)
#define shutdown_logger() ((void)0)
#endif

void log_message(char *message, char *message_formated, MessageType type);

