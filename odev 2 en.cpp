#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_double_percent(const char *prompt, double *out) {
    char line[200];
    char *p;
    double val;

    printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) return 0;
    line[strcspn(line, "\n")] = '\0';
    p = line;
    while (isspace((unsigned char)*p)) p++;
    if (*p == '\0') return 0;

    char *pct = strchr(p, '%');
    if (pct) *pct = '\0';

    char *endptr;
    val = strtod(p, &endptr);
    if (endptr == p) return 0;

    *out = val;
    return 1;
}

const char* classify_sharpe(double s) {
    if (s >= 3.0) return "Excellent (>= 3.0)";
    if (s >= 2.0) return "Very good (>= 2.0)";
    if (s >= 1.0) return "Good (>= 1.0)";
    if (s > 0.0)  return "Positive but weak (< 1.0)";
    if (s == 0.0) return "Zero (return matches risk)";
    return "Negative (return per unit risk is negative)";
}

int main(void) {
    double ret_pct = 0.0;
    double rf_pct = 0.0;  
    double sd_pct = 0.0; 
    int ok;

    printf("Sharpe Ratio Calculator - C Program\n");
    printf("(Inputs can be given in percent, e.g., 15 or 15%%)\n\n");

    while (1) {
        printf("Enter new values (press ENTER to quit):\n");
        ok = read_double_percent("Investment return (%): ", &ret_pct);
        if (!ok) break;
        ok = read_double_percent("Risk-free rate (%): ", &rf_pct);
        if (!ok) break;
        ok = read_double_percent("Portfolio standard deviation / risk (%): ", &sd_pct);
        if (!ok) break;

        if (sd_pct == 0.0) {
            printf("Error: Standard deviation (risk) cannot be zero. Division by zero.\n\n");
            continue;
        }

        double sharpe = (ret_pct - rf_pct) / sd_pct;

        printf("\n--- Result ---\n");
        printf("Investment return: %.4f%%\n", ret_pct);
        printf("Risk-free rate: %.4f%%\n", rf_pct);
        printf("Portfolio standard deviation: %.4f%%\n", sd_pct);
        printf("Calculated Sharpe Ratio: %.4f\n", sharpe);
        printf("Classification: %s\n", classify_sharpe(sharpe));
        printf("(Formula: Sharpe = (Rp - Rf) / sigma_p)\n\n");

        printf("Would you like to perform another calculation? (Y/N): ");
        char ans[8];
        if (!fgets(ans, sizeof(ans), stdin)) break;
        if (ans[0] == 'Y' || ans[0] == 'y') {
            printf("\n");
            continue;
        } else {
            break;
        }
    }

    printf("Program terminated. Thank you.\n");
    return 0;
}
