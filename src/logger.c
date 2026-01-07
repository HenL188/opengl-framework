#include "logger.h"

#ifdef RELEASE_MODE
FILE *log_file = nullptr;

void init_logger() {
    log_file = fopen("game.log", "w");
}
void shutdown_logger() {
    fclose(log_file);
    log_file = nullptr;
}
#endif

void log_message(char *message, char *message_formated, MessageType type) {
    switch(type) {
        case ERROR:
#ifdef DEBUG_MODE
            if (message_formated != nullptr) {
                printf("%s %s/n", message, message_formated);
            }
            else {
                puts(message);
            }
#endif
#ifdef RELEASE_MODE
            if (message_formated != nullptr) {
                fprintf(log_file,"%s %s/n", message, message_formated);
                exit(EXIT_FAILURE);
            }
            fputs(message, log_file);
            exit(EXIT_FAILURE);
#endif
            break;
        case CRITICAL:
#ifdef DEBUG_MODE
            if (message_formated != nullptr) {
                printf("%s %s/n", message, message_formated);
                exit(EXIT_FAILURE);
            }
            else {
                puts(message);
                exit(EXIT_FAILURE);
            }
#endif
#ifdef RELEASE_MODE
            if (message_formated != nullptr) {
                fprintf(log_file, "%s %s/n", message, message_formated);
                exit(EXIT_FAILURE);
            }
            fputs(message, log_file);
            exit(EXIT_FAILURE);
#endif
            break;
        default:
            break;
    }
}
