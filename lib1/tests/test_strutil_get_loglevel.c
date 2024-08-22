#include "../strutil.c"

int main() {
    int iResultInfo = strncmp(get_loglevel(INFO), "INFO", strlen("INFO"));
    int iResultError = strncmp(get_loglevel(ERROR), "ERROR", strlen("ERROR"));
    if(iResultInfo != 0) {
        printf("get_loglevel(INFO) returned %s", get_loglevel(INFO));
    }
    if(iResultError != 0) {
        printf("get_loglevel(ERROR) returned %s", get_loglevel(ERROR));
    }

    if(iResultInfo == 0 && iResultError == 0)
        return 0;

    return 1;
}
