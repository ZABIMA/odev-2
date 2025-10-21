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
    if (s >= 3.0) return "Mükemmel (>= 3.0)";
    if (s >= 2.0) return "Çok iyi (>= 2.0)";
    if (s >= 1.0) return "İyi (>= 1.0)";
    if (s > 0.0)  return "Pozitif ama zayıf (< 1.0)";
    if (s == 0.0) return "Sıfır (getiri riskle eşleşiyor)";
    return "Negatif (risk başına getiri eksi)";
}

int main(void) {
    double ret_pct = 0.0; // yatırım getirisi (yüzde)
    double rf_pct = 0.0;  // risksiz faiz oranı (yüzde)
    double sd_pct = 0.0;  // standart sapma / risk (yüzde)
    int ok;

    printf("Sharpe Oranı Hesaplayıcı - C Programı\n");
    printf("(Girdi yüzde cinsinden olabilir, örn: 15 veya 15%% )\n\n");

    while (1) {
        printf("Yeni hesaplama için lütfen değerleri girin (iptal için sadece ENTER basın):\n");
        ok = read_double_percent("Yatırım getiri oranı (%%): ", &ret_pct);
        if (!ok) break;
        ok = read_double_percent("Risksiz faiz oranı (%%): ", &rf_pct);
        if (!ok) break;
        ok = read_double_percent("Portföy standart sapması / risk (%%): ", &sd_pct);
        if (!ok) break;

        if (sd_pct == 0.0) {
            printf("Hata: Standart sapma (risk) sıfır olamaz. Bölme hatası olur.\n\n");
            continue;
        }

        double sharpe = (ret_pct - rf_pct) / sd_pct;

        printf("\n--- Sonuç ---\n");
        printf("Yatırım getirisi: %.4f%%\n", ret_pct);
        printf("Risksiz faiz oranı: %.4f%%\n", rf_pct);
        printf("Portföy standart sapması: %.4f%%\n", sd_pct);
        printf("Hesaplanan Sharpe oranı: %.4f\n", sharpe);
        printf("Sınıflandırma: %s\n", classify_sharpe(sharpe));
        printf("(Not: Formül Sharpe = (Rp - Rf) / sigma_p)\n\n");

        printf("Başka bir hesaplama yapmak ister misiniz? (E/H): ");
        char ans[8];
        if (!fgets(ans, sizeof(ans), stdin)) break;
        if (ans[0] == 'E' || ans[0] == 'e' || ans[0] == 'Y' || ans[0] == 'y') {
            // devam (Y = Evet in Turkish? Y used for English yes; keep E/e or Y/y)
            printf("\n");
            continue;
        } else {
            break;
        }
    }

    printf("Program sonlandırılıyor. Teşekkürler.\n");
    return 0;
}