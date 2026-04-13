#include "codexion.h"

// Test function
void test_parsing(int test_num, int argc, char **argv) {
    printf("Test %d: ", test_num);
    fflush(stdout);
    int result = parsing(argc, argv);
    printf("Result: %d\n", result);
}

int main() {
    // Test 1: Normal case with valid args
    char *argv1[] = {"program", "1", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(1, 9, argv1);

    // Test 4: argv[1] NULL
    char *argv4[] = {"program", NULL, "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(4, 9, argv4);

    // Test 5: argv[8] NULL
    char *argv5[] = {"program", "1", "2", "3", "4", "5", "6", "7", NULL};
    test_parsing(5, 9, argv5);

    printf("All tests completed.\n");
    return 0;
}