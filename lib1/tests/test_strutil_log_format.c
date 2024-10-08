#include <regex.h>
#include <stdio.h>
#include "../strutil.h"

int main() {
    char szDst1[128];
    char szDst2[128];
    char szDst3[25];
    char sz1[] = "\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\|INFO\\|Tester\\|Additional xyz 154 3\\.14";
    char sz2[] = "\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\|INFO\\|Additional xyz 154 3\\.14";
    char sz3[] = "\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}\\|INF";
    regex_t r1, r2, r3;

    // all information present
    if( regcomp(&r1, sz1, 0) || regcomp(&r2, sz2, 0) || regcomp(&r3, sz3, 0)) {
        printf("regex failed");
    }
    log_format(
        szDst1, sizeof(szDst1) - 1, INFO, "Tester", "Additional %s %d %.2f", "xyz", 154, 3.14
        );
    const int i1 = regexec(&r1, szDst1, 0, NULL, 0);

    // missing module
    log_format(
        szDst2, sizeof(szDst2) - 1, INFO, NULL, "Additional %s %d %.2f", "xyz", 154, 3.14
        );

    const int i2 = regexec(&r2, szDst2, 0, NULL, 0);

    // destination smaller than requested
    log_format(
        szDst3, sizeof(szDst3) - 1, INFO, NULL, "Additional %s %d %.2f", "xyz", 154, 3.14
        );

    const int i3 = regexec(&r3, szDst3, 0, NULL, 0);

    if (i1 != 0) {
        printf("Full - Expected: '%s', got: '%s'", sz1, szDst1);
    }
    if (i2 != 0) {
        printf("No module - Expected: '%s', got: '%s'", sz2, szDst2);
    }
    if (i3 != 0) {
        printf("Desttination size - Expected: '%s', got: '%s'", sz3, szDst3);
    }
    if (i1 == 0 && i2 == 0 && i3 == 0) {
        return 0;
    }
    return 1;
}
