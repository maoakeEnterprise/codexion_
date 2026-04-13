#include "codexion.h"

// Test function
void test_parsing(int test_num, int argc, char **argv) {
    printf("Test %d: ", test_num);
    fflush(stdout);
    int result = parsing(argc, argv);
    printf("Result: %d\n", result);
}

int main() {
    // Test 1: Normal case with valid args (positives, should fail because text_is_digit returns 0 for >0)
    char *argv1[] = {"program", "1", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(1, 9, argv1);

    // Test 2: Valid with negatives/zeros (should pass)
    char *argv2[] = {"program", "0", "-1", "-2", "-3", "-4", "-5", "-6", "edf"};
    test_parsing(2, 9, argv2);

    // Test 3: argc < 9
    test_parsing(3, 8, argv1);

    // Test 4: argc > 9
    char *argv4[] = {"program", "1", "2", "3", "4", "5", "6", "7", "fifo", "extra"};
    test_parsing(4, 10, argv4);

    // Test 5: argv[1] NULL (crash expected)
    char *argv5[] = {"program", NULL, "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(5, 9, argv5);

    // Test 6: argv[8] NULL (crash expected)
    char *argv6[] = {"program", "1", "2", "3", "4", "5", "6", "7", NULL};
    test_parsing(6, 9, argv6);

    // Test 7: Empty string
    char *argv7[] = {"program", "", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(7, 9, argv7);

    // Test 8: Non-digit
    char *argv8[] = {"program", "abc", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(8, 9, argv8);

    // Test 9: String with spaces
    char *argv9[] = {"program", " 123 ", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(9, 9, argv9);

    // Test 10: Large number
    char *argv10[] = {"program", "999999999999999999999", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(10, 9, argv10);

    // Test 11: INT_MAX + 1
    char *argv11[] = {"program", "2147483648", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(11, 9, argv11);

    // Test 12: INT_MIN - 1
    char *argv12[] = {"program", "-2147483649", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(12, 9, argv12);

    // Test 13: argv[8] invalid
    char *argv13[] = {"program", "1", "2", "3", "4", "5", "6", "7", "invalid"};
    test_parsing(13, 9, argv13);

    // Test 14: argv[8] empty
    char *argv14[] = {"program", "1", "2", "3", "4", "5", "6", "7", ""};
    test_parsing(14, 9, argv14);

    // Test 15: argv[8] with special chars
    char *argv15[] = {"program", "1", "2", "3", "4", "5", "6", "7", "fifo!"};
    test_parsing(15, 9, argv15);

    // Test 16: Very long string (may cause issues)
    char long_str[10000] = "1";
    memset(long_str + 1, '0', 9997);
    long_str[9998] = '\0';
    char *argv16[] = {"program", long_str, "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(16, 9, argv16);

    // Test 19: Mixed NULLs
    char *argv19[] = {"program", "1", NULL, "3", "4", "5", "6", "7", "fifo"};
    test_parsing(19, 9, argv19);

    // Test 20: argv[8] = "EDF" (case sensitive)
    char *argv20[] = {"program", "1", "2", "3", "4", "5", "6", "7", "EDF"};
    test_parsing(20, 9, argv20);

    // Test 21: All args NULL except program
    char *argv21[] = {"program", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    test_parsing(21, 9, argv21);

    // Test 22: argc = 1
    test_parsing(22, 1, argv1);

    // Test 23: Non-ASCII in argv[8]
    char *argv23[] = {"program", "1", "2", "3", "4", "5", "6", "7", "fïfo"};
    test_parsing(23, 9, argv23);

    // Test 24: argv[1] with leading zeros
    char *argv24[] = {"program", "00123", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(24, 9, argv24);

    // Test 25: argv[1] = "-0"
    char *argv25[] = {"program", "-0", "2", "3", "4", "5", "6", "7", "fifo"};
    test_parsing(25, 9, argv25);

    printf("All tests completed.\n");
    return 0;
}