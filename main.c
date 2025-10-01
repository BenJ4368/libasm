#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
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
    // Test chaîne normale
    const char *test1 = "Hello, World!";
    print_test_result("ft_strlen normal string", ft_strlen(test1) == strlen(test1));

    // Test chaîne vide
    const char *test2 = "";
    print_test_result("ft_strlen empty string", ft_strlen(test2) == strlen(test2));

    // Test chaîne avec un seul caractère
    const char *test3 = "A";
    print_test_result("ft_strlen single char", ft_strlen(test3) == strlen(test3));

    // Test chaîne très longue
    char long_str[1000];
    memset(long_str, 'X', 999);
    long_str[999] = '\0';
    print_test_result("ft_strlen long string", ft_strlen(long_str) == strlen(long_str));

    // Test avec caractères spéciaux
    const char *test5 = "Hello\nWorld\t!";
    print_test_result("ft_strlen special chars", ft_strlen(test5) == strlen(test5));
}

void test_ft_strcpy() {
    // Test copie normale
    char dest1[100], dest1_std[100];
    const char *src1 = "A Lannister always pays his debts.";
    print_test_result("ft_strcpy normal", strcmp(ft_strcpy(dest1, src1), strcpy(dest1_std, src1)) == 0);

    // Test chaîne vide
    char dest2[10], dest2_std[10];
    const char *src2 = "";
    print_test_result("ft_strcpy empty string", strcmp(ft_strcpy(dest2, src2), strcpy(dest2_std, src2)) == 0);

    // Test un seul caractère
    char dest3[10], dest3_std[10];
    const char *src3 = "X";
    print_test_result("ft_strcpy single char", strcmp(ft_strcpy(dest3, src3), strcpy(dest3_std, src3)) == 0);
}

void test_ft_strcmp() {
    // Test chaînes identiques
    const char *s1 = "Lady Arryn of the Vale";
    const char *s2 = "Lady Arryn of the Vale";
    print_test_result("ft_strcmp identical", (ft_strcmp(s1, s2) == 0) == (strcmp(s1, s2) == 0));

    // Test première < deuxième
    const char *s3 = "Arya";
    const char *s4 = "Sansa";
    print_test_result("ft_strcmp s1 < s2", (ft_strcmp(s3, s4) < 0) == (strcmp(s3, s4) < 0));

    // Test première > deuxième
    const char *s5 = "Tyrion";
    const char *s6 = "Jon";
    print_test_result("ft_strcmp s1 > s2", (ft_strcmp(s5, s6) > 0) == (strcmp(s5, s6) > 0));

    // Test chaînes vides
    const char *s7 = "";
    const char *s8 = "";
    print_test_result("ft_strcmp empty strings", ft_strcmp(s7, s8) == strcmp(s7, s8));

    // Test une chaîne vide vs non-vide
    const char *s9 = "";
    const char *s10 = "Jorah Mormont";
    print_test_result("ft_strcmp empty vs non-empty", (ft_strcmp(s9, s10) < 0) == (strcmp(s9, s10) < 0));

    // Test préfixe
    const char *s11 = "Not";
    const char *s12 = "Not Today";
    print_test_result("ft_strcmp prefix", (ft_strcmp(s11, s12) < 0) == (strcmp(s11, s12) < 0));
}

void test_ft_write() {
    // Test écriture normale sur stdout
    const char *msg1 = "Any man who must say \"I am the King\" is no true King.\n";
    print_test_result("ft_write to stdout", ft_write(STDOUT_FILENO, msg1, strlen(msg1)) == (ssize_t)strlen(msg1));

    // Test écriture de 0 octets
    print_test_result("ft_write 0 bytes", ft_write(STDOUT_FILENO, msg1, 0) == 0);

    // Test avec descripteur invalide
    errno = 0;
    ssize_t result3 = ft_write(-1, msg1, strlen(msg1));
    print_test_result("ft_write invalid fd", result3 == -1 && errno > 0);

    // Test écriture vers un fichier
    int fd = open("test_write.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd != -1) {
        const char *file_msg = "Drakarys\n";
        ssize_t result5 = ft_write(fd, file_msg, strlen(file_msg));
        close(fd);
        print_test_result("ft_write to file", result5 == (ssize_t)strlen(file_msg));
        unlink("test_write.txt");
    }
}

void test_ft_read() {
    // Créer un fichier de test
    const char *test_content = "I did not do it, but I wish that I had.\nWatching your vicious bastard die gave me more relief than a thousand lying whores.\n";
    int write_fd = open("test_read.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (write_fd == -1) return;
    write(write_fd, test_content, strlen(test_content));
    close(write_fd);

    // Test lecture normale
    int fd = open("test_read.txt", O_RDONLY);
    if (fd != -1) {
        char buffer[150];
        ssize_t result1 = ft_read(fd, buffer, sizeof(buffer) - 1);
        if (result1 > 0) {
            buffer[result1] = '\0';
            print_test_result("ft_read from file", result1 == (ssize_t)strlen(test_content) && strcmp(buffer, test_content) == 0);
        }
        close(fd);
    }

    // Test lecture de 0 octets
    fd = open("test_read.txt", O_RDONLY);
    if (fd != -1) {
        char buffer[10];
        print_test_result("ft_read 0 bytes", ft_read(fd, buffer, 0) == 0);
        close(fd);
    }

    // Test avec descripteur invalide
    errno = 0;
    char buffer[10];
    print_test_result("ft_read invalid fd", ft_read(-1, buffer, sizeof(buffer)) == -1 && errno > 0);

    unlink("test_read.txt");
}

void test_ft_strdup() {
    // Test duplication normale
    const char *src1 = "Daenerys Targaryen, Mother of Dragons";
    char *result1 = ft_strdup(src1);
    char *expected1 = strdup(src1);
    int ok = result1 && expected1 && strcmp(result1, expected1) == 0 && result1 != src1;
    print_test_result("ft_strdup normal", ok);
    if (result1) free(result1);
    if (expected1) free(expected1);

    // Test chaîne vide
    const char *src2 = "";
    char *result2 = ft_strdup(src2);
    char *expected2 = strdup(src2);
    ok = result2 && expected2 && strcmp(result2, expected2) == 0;
    print_test_result("ft_strdup empty", ok);
    if (result2) free(result2);
    if (expected2) free(expected2);

    // Test chaîne très longue
    char long_str[2000];
    memset(long_str, 'A', 1999);
    long_str[1999] = '\0';
    char *result4 = ft_strdup(long_str);
    char *expected4 = strdup(long_str);
    ok = result4 && expected4 && strcmp(result4, expected4) == 0;
    print_test_result("ft_strdup long string", ok);
    if (result4) free(result4);
    if (expected4) free(expected4);
}

void print_summary() {
    printf("\n=== SUMMARY ===\n");
    printf("Tests passed: %s%d/%d%s\n", (test_passed == test_count) ? GREEN : RED, test_passed, test_count, RESET);
    if (test_passed == test_count) {
        printf(GREEN "🎉 All tests passed!\n" RESET);
    } else {
        printf(RED "❌ Some tests failed.\n" RESET);
    }
}

int main() {
    test_ft_strlen();
    test_ft_strcpy();
    test_ft_strcmp();
    test_ft_write();
    test_ft_read();
    test_ft_strdup();
    print_summary();
    return (test_passed == test_count) ? 0 : 1;
}
