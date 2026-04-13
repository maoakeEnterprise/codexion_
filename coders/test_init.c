#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

// Prototypes
long ft_atol(const char *nptr);
t_dongle *init_dongle(int id);
t_coder *init_coder(t_data *data, t_dongle *left, t_dongle *right);
t_data *init_data(char **argv);
int is_edf(char *str); // Assuming it's defined somewhere

// Test ft_atol
void test_ft_atol() {
    printf("Testing ft_atol:\n");

    // Normal positive
    assert(ft_atol("123") == 123);
    printf("  '123' -> %ld\n", ft_atol("123"));

    // Negative
    assert(ft_atol("-456") == -456);
    printf("  '-456' -> %ld\n", ft_atol("-456"));

    // Zero
    assert(ft_atol("0") == 0);
    printf("  '0' -> %ld\n", ft_atol("0"));

    // With spaces
    assert(ft_atol("  789  ") == 789);
    printf("  '  789  ' -> %ld\n", ft_atol("  789  "));

    // Leading zeros
    assert(ft_atol("00123") == 123);
    printf("  '00123' -> %ld\n", ft_atol("00123"));

    // Large number
    assert(ft_atol("9223372036854775807") == LONG_MAX);
    printf("  '9223372036854775807' -> %ld\n", ft_atol("9223372036854775807"));

    // Negative large
    assert(ft_atol("-9223372036854775808") == LONG_MIN);
    printf("  '-9223372036854775808' -> %ld\n", ft_atol("-9223372036854775808"));

    // Empty string
    assert(ft_atol("") == 0);
    printf("  '' -> %ld\n", ft_atol(""));

    // Non-digit
    assert(ft_atol("abc") == 0);
    printf("  'abc' -> %ld\n", ft_atol("abc"));

    // Mixed
    assert(ft_atol("123abc") == 123);
    printf("  '123abc' -> %ld\n", ft_atol("123abc"));

    // NULL (should crash or handle)
    // assert(ft_atol(NULL) == 0); // Uncomment if handled

    printf("ft_atol tests passed.\n\n");
}

// Test init_dongle
void test_init_dongle() {
    printf("Testing init_dongle:\n");

    t_dongle *d = init_dongle(5);
    assert(d != NULL);
    assert(d->id == 5);
    assert(d->available_at == 0);
    printf("  Created dongle with id %d\n", d->id);

    // Free
    pthread_mutex_destroy(&d->mutex);
    free(d);
    printf("  Freed dongle\n");

    printf("init_dongle tests passed.\n\n");
}

// Test init_data
void test_init_data() {
    printf("Testing init_data:\n");

    char *argv[] = {"program", "4", "1000", "2000", "3000", "4000", "5", "6000", "fifo"};
    t_data *data = init_data(argv);
    assert(data != NULL);
    assert(data->nb_coders == 4);
    assert(data->time_burnout == 1000);
    assert(data->time_compile == 2000);
    assert(data->time_debug == 3000);
    assert(data->time_refactor == 4000);
    assert(data->nb_compile_required == 5);
    assert(data->dongle_cooldown == 6000);
    assert(data->is_edf == 0); // Assuming fifo -> 0
    assert(data->simul_end == 0);
    printf("  Created data with nb_coders %d\n", data->nb_coders);

    // Free
    pthread_mutex_destroy(&data->write_mutex);
    pthread_mutex_destroy(&data->data_mutex);
    free(data);
    printf("  Freed data\n");

    printf("init_data tests passed.\n\n");
}

// Test init_coder
void test_init_coder() {
    printf("Testing init_coder:\n");

    // First create data and dongles
    char *argv[] = {"program", "4", "1000", "2000", "3000", "4000", "5", "6000", "fifo"};
    t_data *data = init_data(argv);
    t_dongle *left = init_dongle(1);
    t_dongle *right = init_dongle(2);

    t_coder *coder = init_coder(data, left, right);
    assert(coder != NULL);
    assert(coder->compile_count == 0);
    assert(coder->data == data);
    assert(coder->left_dongle == left);
    assert(coder->right_dongle == right);
    printf("  Created coder with compile_count %d\n", coder->compile_count);

    // Free
    free(coder);
    printf("  Freed coder\n");

    // Free data and dongles
    pthread_mutex_destroy(&data->write_mutex);
    pthread_mutex_destroy(&data->data_mutex);
    free(data);
    pthread_mutex_destroy(&left->mutex);
    free(left);
    pthread_mutex_destroy(&right->mutex);
    free(right);
    printf("  Freed all\n");

    printf("init_coder tests passed.\n\n");
}

int main() {
    test_ft_atol();
    test_init_dongle();
    test_init_data();
    test_init_coder();

    printf("All unit tests passed!\n");
    return 0;
}