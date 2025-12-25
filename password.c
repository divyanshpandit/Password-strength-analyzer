#include <math.h>
#include <string.h>
#include <emscripten/emscripten.h>

// Estimate character set size ;)
int charset_size(const char *password) {
    int has_lower = 0, has_upper = 0, has_digit = 0, has_symbol = 0;

    for (int i = 0; password[i]; i++) {
        if (password[i] >= 'a' && password[i] <= 'z') has_lower = 1;
        else if (password[i] >= 'A' && password[i] <= 'Z') has_upper = 1;
        else if (password[i] >= '0' && password[i] <= '9') has_digit = 1;
        else has_symbol = 1;
    }

    int size = 0;
    if (has_lower) size += 26;
    if (has_upper) size += 26;
    if (has_digit) size += 10;
    if (has_symbol) size += 32;

    return size;
}

// Shannon-style entropy ;3
EMSCRIPTEN_KEEPALIVE
double password_entropy(const char *password) {
    int len = strlen(password);
    int charset = charset_size(password);

    if (len == 0 || charset == 0) return 0.0;

    return len * log2((double)charset);
}

// Brute-force time estimate
EMSCRIPTEN_KEEPALIVE
double brute_force_time(double entropy) {
    // Assume 10^9 guesses/sec (GPU attacker) ;)
    double guesses_per_sec = 1e9;
    return pow(2, entropy) / guesses_per_sec;
}
