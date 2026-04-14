#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

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
    free_dongle(d);
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
    free_data(data);
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
    free_dongle(left);
    free_dongle(right);
    free_data(data);
    printf("  Freed all\n");

    printf("init_coder tests passed.\n\n");
}

// Test init_dongles
void test_init_dongles() {
    printf("Testing init_dongles:\n");

    // Test 1: Create with 0 dongles
    printf("  Test 1: Creating with 0 dongles\n");
    t_dongle **dongles_0 = init_dongles(0);
    assert(dongles_0 != NULL);
    assert(dongles_0[0] == NULL);
    printf("    ✓ Array created correctly with null terminator\n");
    free_dongles(dongles_0);

    // Test 2: Create with 1 dongle
    printf("  Test 2: Creating with 1 dongle\n");
    t_dongle **dongles_1 = init_dongles(1);
    assert(dongles_1 != NULL);
    assert(dongles_1[0] != NULL);
    assert(dongles_1[0]->id == 0);
    assert(dongles_1[0]->available_at == 0);
    assert(dongles_1[1] == NULL);
    printf("    ✓ Single dongle created with correct id and null terminator\n");
    free_dongles(dongles_1);

    // Test 3: Create with 5 dongles
    printf("  Test 3: Creating with 5 dongles\n");
    t_dongle **dongles_5 = init_dongles(5);
    assert(dongles_5 != NULL);
    for (int i = 0; i < 5; i++) {
        assert(dongles_5[i] != NULL);
        assert(dongles_5[i]->id == i);
        assert(dongles_5[i]->available_at == 0);
    }
    assert(dongles_5[5] == NULL);
    printf("    ✓ 5 dongles created with correct ids and null terminator\n");
    free_dongles(dongles_5);

    // Test 4: Create with 100 dongles
    printf("  Test 4: Creating with 100 dongles\n");
    t_dongle **dongles_100 = init_dongles(100);
    assert(dongles_100 != NULL);
    for (int i = 0; i < 100; i++) {
        assert(dongles_100[i] != NULL);
        assert(dongles_100[i]->id == i);
    }
    assert(dongles_100[100] == NULL);
    printf("    ✓ 100 dongles created correctly\n");
    free_dongles(dongles_100);

    // Test 5: Verify mutex is initialized for each dongle
    printf("  Test 5: Verifying mutex initialization\n");
    t_dongle **dongles_test = init_dongles(3);
    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&dongles_test[i]->mutex);
        pthread_mutex_unlock(&dongles_test[i]->mutex);
    }
    printf("    ✓ All mutexes are properly initialized\n");
    free_dongles(dongles_test);

    printf("init_dongles tests passed.\n\n");
}

// Test init_coders
void test_init_coders() {
    printf("Testing init_coders:\n");

    // Create test data and dongles
    char *argv[] = {"program", "4", "1000", "2000", "3000", "4000", "5", "6000", "fifo"};
    t_data *data = init_data(argv);
    assert(data != NULL);

    // Test 1: Create with 0 coders
    printf("  Test 1: Creating with 0 coders\n");
    t_dongle **dongles_0 = init_dongles(0);
    t_coder **coders_0 = init_coders(data, dongles_0, 0);
    assert(coders_0 != NULL);
    assert(coders_0[0] == NULL);
    printf("    ✓ Array created correctly with null terminator\n");
    free_coders(coders_0);
    free_dongles(dongles_0);

    // Test 2: Create with 1 coder and 1 dongle
    printf("  Test 2: Creating with 1 coder and 1 dongle\n");
    t_dongle **dongles_1 = init_dongles(1);
    t_coder **coders_1 = init_coders(data, dongles_1, 1);
    assert(coders_1 != NULL);
    assert(coders_1[0] != NULL);
    assert(coders_1[0]->data == data);
    assert(coders_1[0]->left_dongle == dongles_1[0]);  // Circular: left of 0 is 0
    assert(coders_1[0]->right_dongle == dongles_1[0]); // Circular: right of 0 is 0
    assert(coders_1[0]->compile_count == 0);
    assert(coders_1[0]->last_compile_start == 0);
    assert(coders_1[1] == NULL);
    printf("    ✓ Single coder created with correct dongle assignments\n");
    free_coders(coders_1);
    free_dongles(dongles_1);

    // Test 3: Create with 2 coders and 2 dongles
    printf("  Test 3: Creating with 2 coders and 2 dongles\n");
    t_dongle **dongles_2 = init_dongles(2);
    t_coder **coders_2 = init_coders(data, dongles_2, 2);
    assert(coders_2 != NULL);
    // Coder 0: left = dongle[1], right = dongle[1]
    assert(coders_2[0]->left_dongle == dongles_2[1]);
    assert(coders_2[0]->right_dongle == dongles_2[1]);
    // Coder 1: left = dongle[0], right = dongle[0]
    assert(coders_2[1]->left_dongle == dongles_2[0]);
    assert(coders_2[1]->right_dongle == dongles_2[0]);
    assert(coders_2[2] == NULL);
    printf("    ✓ 2 coders created with correct circular dongle assignments\n");
    free_coders(coders_2);
    free_dongles(dongles_2);

    // Test 4: Create with 3 coders and 3 dongles
    printf("  Test 4: Creating with 3 coders and 3 dongles\n");
    t_dongle **dongles_3 = init_dongles(3);
    t_coder **coders_3 = init_coders(data, dongles_3, 3);
    assert(coders_3 != NULL);
    // Coder 0: left = dongle[2], right = dongle[1]
    assert(coders_3[0]->left_dongle == dongles_3[2]);
    assert(coders_3[0]->right_dongle == dongles_3[1]);
    // Coder 1: left = dongle[0], right = dongle[2]
    assert(coders_3[1]->left_dongle == dongles_3[0]);
    assert(coders_3[1]->right_dongle == dongles_3[2]);
    // Coder 2: left = dongle[1], right = dongle[0]
    assert(coders_3[2]->left_dongle == dongles_3[1]);
    assert(coders_3[2]->right_dongle == dongles_3[0]);
    assert(coders_3[3] == NULL);
    printf("    ✓ 3 coders created with correct circular dongle assignments\n");
    free_coders(coders_3);
    free_dongles(dongles_3);

    // Test 5: Create with 4 coders and 4 dongles (matching data->nb_coders)
    printf("  Test 5: Creating with 4 coders and 4 dongles\n");
    t_dongle **dongles_4 = init_dongles(4);
    t_coder **coders_4 = init_coders(data, dongles_4, 4);
    assert(coders_4 != NULL);
    for (int i = 0; i < 4; i++) {
        assert(coders_4[i] != NULL);
        assert(coders_4[i]->data == data);
        assert(coders_4[i]->compile_count == 0);
        assert(coders_4[i]->last_compile_start == 0);
        // Verify circular assignment
        int left_idx = (i == 0) ? 3 : i - 1;
        int right_idx = (i == 3) ? 0 : i + 1;
        assert(coders_4[i]->left_dongle == dongles_4[left_idx]);
        assert(coders_4[i]->right_dongle == dongles_4[right_idx]);
    }
    assert(coders_4[4] == NULL);
    printf("    ✓ 4 coders created with correct circular dongle assignments\n");
    free_coders(coders_4);
    free_dongles(dongles_4);

    // Free test data
    free_data(data);

    printf("init_coders tests passed.\n\n");
}

int main() {
    test_ft_atol();
    test_init_dongle();
    test_init_data();
    test_init_coder();
    test_init_dongles();
    test_init_coders();

    printf("All unit tests passed!\n");
    return 0;
}