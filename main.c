#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

// Déclarations des fonctions de votre bibliothèque
extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

int test_count = 0;
int test_passed = 0;

void print_test_result(const char *test_name, int passed) {
    test_count++;
    if (passed) {
        test_passed++;
        printf(GREEN "✓ PASS" RESET " %s\n", test_name);
    } else {
        printf(RED "✗ FAIL" RESET " %s\n", test_name);
    }
}

void test_ft_strlen() {
    printf(BLUE "\n=== Testing ft_strlen ===\n" RESET);
    
    // Test chaîne normale
    const char *test1 = "Hello, World!";
    size_t result1 = ft_strlen(test1);
    size_t expected1 = strlen(test1);
    printf("Test: \"%s\" -> ft: %zu, std: %zu\n", test1, result1, expected1);
    print_test_result("strlen normal string", result1 == expected1);
    
    // Test chaîne vide
    const char *test2 = "";
    size_t result2 = ft_strlen(test2);
    size_t expected2 = strlen(test2);
    printf("Test: empty string -> ft: %zu, std: %zu\n", result2, expected2);
    print_test_result("strlen empty string", result2 == expected2);
    
    // Test chaîne avec un seul caractère
    const char *test3 = "A";
    size_t result3 = ft_strlen(test3);
    size_t expected3 = strlen(test3);
    printf("Test: \"%s\" -> ft: %zu, std: %zu\n", test3, result3, expected3);
    print_test_result("strlen single char", result3 == expected3);
    
    // Test chaîne très longue
    char long_str[1000];
    memset(long_str, 'X', 999);
    long_str[999] = '\0';
    size_t result4 = ft_strlen(long_str);
    size_t expected4 = strlen(long_str);
    printf("Test: long string (999 chars) -> ft: %zu, std: %zu\n", result4, expected4);
    print_test_result("strlen long string", result4 == expected4);
    
    // Test avec caractères spéciaux
    const char *test5 = "Hello\nWorld\t!";
    size_t result5 = ft_strlen(test5);
    size_t expected5 = strlen(test5);
    printf("Test: special chars -> ft: %zu, std: %zu\n", result5, expected5);
    print_test_result("strlen special chars", result5 == expected5);
}

void test_ft_strcpy() {
    printf(BLUE "\n=== Testing ft_strcpy ===\n" RESET);
    
    // Test copie normale
    char dest1[100], dest1_std[100];
    const char *src1 = "A Lannister always pays his debts.";
    char *result1 = ft_strcpy(dest1, src1);
    char *expected1 = strcpy(dest1_std, src1);
    printf("Test: normal copy\n");
    printf("  ft_strcpy: \"%s\" (returned: %p)\n", dest1, (void*)result1);
    printf("  strcpy:    \"%s\" (returned: %p)\n", dest1_std, (void*)expected1);
    print_test_result("strcpy normal", strcmp(dest1, dest1_std) == 0 && result1 == dest1);
    
    // Test chaîne vide
    char dest2[10], dest2_std[10];
    const char *src2 = "";
    char *result2 = ft_strcpy(dest2, src2);
    char *expected2 = strcpy(dest2_std, src2);
    printf("Test: empty string -> ft: \"%s\", std: \"%s\"\n", dest2, dest2_std);
    print_test_result("strcpy empty string", strcmp(dest2, dest2_std) == 0 && result2 == dest2);
    
    // Test un seul caractère
    char dest3[10], dest3_std[10];
    const char *src3 = "X";
    char *result3 = ft_strcpy(dest3, src3);
    char *expected3 = strcpy(dest3_std, src3);
    printf("Test: single char -> ft: \"%s\", std: \"%s\"\n", dest3, dest3_std);
    print_test_result("strcpy single char", strcmp(dest3, dest3_std) == 0 && result3 == dest3);
    
    // Test avec pointeur source NULL
    char dest4[10];
    errno = 0;
    char *result4 = ft_strcpy(dest4, NULL);
    int errno4 = errno;
    printf("Test: NULL source -> result: %p, errno: %d\n", (void*)result4, errno4);
    print_test_result("strcpy NULL source", result4 == NULL && errno4 == 14);
    
    // Test avec pointeur destination NULL
    errno = 0;
    char *result5 = ft_strcpy(NULL, src1);
    int errno5 = errno;
    printf("Test: NULL dest -> result: %p, errno: %d\n", (void*)result5, errno5);
    print_test_result("strcpy NULL dest", result5 == NULL && errno5 == 14);
    
    // Test avec les deux pointeurs NULL
    errno = 0;
    char *result6 = ft_strcpy(NULL, NULL);
    int errno6 = errno;
    printf("Test: both NULL -> result: %p, errno: %d\n", (void*)result6, errno6);
    print_test_result("strcpy both NULL", result6 == NULL && errno6 == 14);
}

void test_ft_strcmp() {
    printf(BLUE "\n=== Testing ft_strcmp ===\n" RESET);
    
    // Test chaînes identiques
    const char *s1 = "Lady Arryn of the Vale";
    const char *s2 = "Lady Arryn of the Vale";
    int result1 = ft_strcmp(s1, s2);
    int expected1 = strcmp(s1, s2);
    printf("Test: identical -> ft: %d, std: %d\n", result1, expected1);
    print_test_result("strcmp identical", (result1 == 0) == (expected1 == 0));
    
    // Test première < deuxième
    const char *s3 = "Arya";
    const char *s4 = "Sansa";
    int result2 = ft_strcmp(s3, s4);
    int expected2 = strcmp(s3, s4);
    printf("Test: \"%s\" vs \"%s\" -> ft: %d, std: %d\n", s3, s4, result2, expected2);
    print_test_result("strcmp s1 < s2", (result2 < 0) == (expected2 < 0));
    
    // Test première > deuxième
    const char *s5 = "Tyrion";
    const char *s6 = "Jon";
    int result3 = ft_strcmp(s5, s6);
    int expected3 = strcmp(s5, s6);
    printf("Test: \"%s\" vs \"%s\" -> ft: %d, std: %d\n", s5, s6, result3, expected3);
    print_test_result("strcmp s1 > s2", (result3 > 0) == (expected3 > 0));
    
    // Test chaînes vides
    const char *s7 = "";
    const char *s8 = "";
    int result4 = ft_strcmp(s7, s8);
    int expected4 = strcmp(s7, s8);
    printf("Test: empty strings -> ft: %d, std: %d\n", result4, expected4);
    print_test_result("strcmp empty strings", result4 == expected4);
    
    // Test une chaîne vide vs non-vide
    const char *s9 = "";
    const char *s10 = "Jorah Mormont";
    int result5 = ft_strcmp(s9, s10);
    int expected5 = strcmp(s9, s10);
    printf("Test: empty vs non-empty -> ft: %d, std: %d\n", result5, expected5);
    print_test_result("strcmp empty vs non-empty", (result5 < 0) == (expected5 < 0));
    
    // Test préfixe
    const char *s11 = "Not";
    const char *s12 = "Not Today";
    int result6 = ft_strcmp(s11, s12);
    int expected6 = strcmp(s11, s12);
    printf("Test: prefix -> ft: %d, std: %d\n", result6, expected6);
    print_test_result("strcmp prefix", (result6 < 0) == (expected6 < 0));
    
    // Test avec NULL (votre implémentation custom)
    errno = 0;
    int result7 = ft_strcmp(s1, NULL);
    int errno7 = errno;
    printf("Test: NULL second -> result: %d, errno: %d\n", result7, errno7);
    print_test_result("strcmp NULL second", result7 == -1 && errno7 == 14);
    
    errno = 0;
    int result8 = ft_strcmp(NULL, s1);
    int errno8 = errno;
    printf("Test: NULL first -> result: %d, errno: %d\n", result8, errno8);
    print_test_result("strcmp NULL first", result8 == -1 && errno8 == 14);
}

void test_ft_write() {
    printf(BLUE "\n=== Testing ft_write ===\n" RESET);
    
    // Test écriture normale sur stdout
    const char *msg1 = "Any man who must say \"I am the King\" is no true King.\n";
    printf("Expected output: %s", msg1);
    printf("Actual output:   ");
    ssize_t result1 = ft_write(STDOUT_FILENO, msg1, strlen(msg1));
    printf("ft_write returned: %zd (expected: %zu)\n", result1, strlen(msg1));
    print_test_result("write to stdout", result1 == (ssize_t)strlen(msg1));
    
    // Test écriture de 0 octets
    ssize_t result2 = ft_write(STDOUT_FILENO, msg1, 0);
    printf("Write 0 bytes -> ft: %zd (expected: 0)\n", result2);
    print_test_result("write 0 bytes", result2 == 0);
    
    // Test avec descripteur invalide
    errno = 0;
    ssize_t result3 = ft_write(-1, msg1, strlen(msg1));
    int errno3 = errno;
    printf("Invalid fd -> ft: %zd, errno: %d\n", result3, errno3);
    print_test_result("write invalid fd", result3 == -1 && errno3 > 0);
    
    // Test avec buffer NULL et taille > 0
    errno = 0;
    ssize_t result4 = ft_write(STDOUT_FILENO, NULL, 10);
    int errno4 = errno;
    printf("NULL buffer -> ft: %zd, errno: %d\n", result4, errno4);
    print_test_result("write NULL buffer", result4 == -1 && errno4 > 0);
    
    // Test écriture vers un fichier
    int fd = open("test_write.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd != -1) {
        const char *file_msg = "Drakarys\n";
        ssize_t result5 = ft_write(fd, file_msg, strlen(file_msg));
        close(fd);
        printf("Write to file -> ft: %zd (expected: %zu)\n", result5, strlen(file_msg));
        print_test_result("write to file", result5 == (ssize_t)strlen(file_msg));
        unlink("test_write.txt"); // nettoyer
    }
}

void test_ft_read() {
    printf(BLUE "\n=== Testing ft_read ===\n" RESET);
    
    // Créer un fichier de test
    const char *test_content = "I did not do it, but I wish that I had.\nWatching your vicious bastard die gave me more relief than a thousand whores.\n";
    int write_fd = open("test_read.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (write_fd == -1) {
        printf("Cannot create test file\n");
        return;
    }
    write(write_fd, test_content, strlen(test_content));
    close(write_fd);
    
    // Test lecture normale
    int fd = open("test_read.txt", O_RDONLY);
    if (fd != -1) {
        char buffer[150];
        ssize_t result1 = ft_read(fd, buffer, sizeof(buffer) - 1);
        if (result1 > 0) {
            buffer[result1] = '\0';
            printf("Read from file: \"%s\" (%zd bytes)\n", buffer, result1);
            print_test_result("read from file", result1 == (ssize_t)strlen(test_content) && 
                            strcmp(buffer, test_content) == 0);
        } else {
            printf("Read failed: %zd\n", result1);
            print_test_result("read from file", 0);
        }
        close(fd);
    }
    
    // Test lecture de 0 octets
    fd = open("test_read.txt", O_RDONLY);
    if (fd != -1) {
        char buffer[10];
        ssize_t result2 = ft_read(fd, buffer, 0);
        printf("Read 0 bytes -> ft: %zd\n", result2);
        print_test_result("read 0 bytes", result2 == 0);
        close(fd);
    }
    
    // Test avec descripteur invalide
    errno = 0;
    char buffer[10];
    ssize_t result3 = ft_read(-1, buffer, sizeof(buffer));
    int errno3 = errno;
    printf("Invalid fd -> ft: %zd, errno: %d\n", result3, errno3);
    print_test_result("read invalid fd", result3 == -1 && errno3 > 0);
    
    // Test avec buffer NULL
    fd = open("test_read.txt", O_RDONLY);
    if (fd != -1) {
        errno = 0;
        ssize_t result4 = ft_read(fd, NULL, 10);
        int errno4 = errno;
        printf("NULL buffer -> ft: %zd, errno: %d\n", result4, errno4);
        print_test_result("read NULL buffer", result4 == -1 && errno4 > 0);
        close(fd);
    }
    
    unlink("test_read.txt"); // nettoyer
}

void test_ft_strdup() {
    printf(BLUE "\n=== Testing ft_strdup ===\n" RESET);
    
    // Test duplication normale
    const char *src1 = "Daenerys Targaryen, Mother of Dragons";
    char *result1 = ft_strdup(src1);
    char *expected1 = strdup(src1);
    
    if (result1 && expected1) {
        printf("Original: \"%s\"\n", src1);
        printf("ft_strdup: \"%s\"\n", result1);
        printf("strdup:    \"%s\"\n", expected1);
        printf("Addresses: ft=%p, std=%p, src=%p\n", (void*)result1, (void*)expected1, (void*)src1);
        
        int strings_equal = strcmp(result1, expected1) == 0;
        int different_addresses = (result1 != src1) && (expected1 != src1);
        
        print_test_result("strdup normal", strings_equal && different_addresses);
        
        free(result1);
        free(expected1);
    } else {
        printf("Allocation failed: ft=%p, std=%p\n", (void*)result1, (void*)expected1);
        print_test_result("strdup normal", 0);
        if (result1) free(result1);
        if (expected1) free(expected1);
    }
    
    // Test chaîne vide
    const char *src2 = "";
    char *result2 = ft_strdup(src2);
    char *expected2 = strdup(src2);
    
    if (result2 && expected2) {
        printf("Empty string: ft=\"%s\", std=\"%s\"\n", result2, expected2);
        print_test_result("strdup empty", strcmp(result2, expected2) == 0);
        free(result2);
        free(expected2);
    } else {
        print_test_result("strdup empty", 0);
        if (result2) free(result2);
        if (expected2) free(expected2);
    }
    
    // Test un seul caractère
    const char *src3 = "X";
    char *result3 = ft_strdup(src3);
    char *expected3 = strdup(src3);
    
    if (result3 && expected3) {
        printf("Single char: ft=\"%s\", std=\"%s\"\n", result3, expected3);
        print_test_result("strdup single char", strcmp(result3, expected3) == 0);
        free(result3);
        free(expected3);
    } else {
        print_test_result("strdup single char", 0);
        if (result3) free(result3);
        if (expected3) free(expected3);
    }
    
    // Test chaîne très longue
    char long_str[2000];
    memset(long_str, 'A', 1999);
    long_str[1999] = '\0';
    
    char *result4 = ft_strdup(long_str);
    char *expected4 = strdup(long_str);
    
    if (result4 && expected4) {
        int same_length = strlen(result4) == strlen(expected4);
        int content_match = strcmp(result4, expected4) == 0;
        printf("Long string (%zu chars): lengths match=%d, content match=%d\n", 
               strlen(long_str), same_length, content_match);
        print_test_result("strdup long string", same_length && content_match);
        free(result4);
        free(expected4);
    } else {
        print_test_result("strdup long string", 0);
        if (result4) free(result4);
        if (expected4) free(expected4);
    }
    
    // Test avec pointeur NULL
    errno = 0;
    char *result5 = ft_strdup(NULL);
    int errno5 = errno;
    printf("NULL source -> result: %p, errno: %d\n", (void*)result5, errno5);
    print_test_result("strdup NULL", result5 == NULL && errno5 == 22);
    
}

void print_summary() {
    printf(BLUE "\n=== SUMMARY ===\n" RESET);
    printf("Tests passed: %s%d/%d%s\n", 
           (test_passed == test_count) ? GREEN : RED,
           test_passed, test_count, RESET);
    
    if (test_passed == test_count) {
        printf(GREEN "🎉 All tests passed!\n" RESET);
    } else {
        printf(RED "❌ Some tests failed. Check implementation.\n" RESET);
    }
    
    double percentage = (double)test_passed / test_count * 100.0;
    printf("Success rate: %.1f%%\n", percentage);
}

int main() {
    printf(YELLOW "🧪 Advanced libasm tester\n" RESET);
    printf("Testing custom assembly functions against standard library...\n");
    
    test_ft_strlen();
    test_ft_strcpy();
    test_ft_strcmp();
    test_ft_write();
    test_ft_read();
    test_ft_strdup();
    
    print_summary();
    
    return (test_passed == test_count) ? 0 : 1;
}