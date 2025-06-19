#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Déclarations des fonctions de votre bibliothèque
extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);

void test_ft_strlen() {
    printf("=== Testing ft_strlen:\n");
    const char *test_str = "Hello, World!";
    printf("Len of \"%s\": %zu\n", test_str, ft_strlen(test_str));
    printf("Len of empty string: %zu\n", ft_strlen(""));
}

void test_ft_strcpy() {
    printf("\n=== Testing ft_strcpy:\n");
    char dest[50];
    const char *src = "A Lanister always pays his debts.";
    
    // Reset errno avant le test
    errno = 0;
    
    char *result = ft_strcpy(dest, src);
    if (result != NULL) {
        printf("Copied string: %s\n", result);
        printf("dest buffer: %s\n", dest);
    } else {
        printf("ft_strcpy failed with errno: %d\n", errno);
    }
    
    // Test avec un pointeur source nul
    errno = 0;
    result = ft_strcpy(dest, NULL);
    if (result == NULL) {
        printf("ft_strcpy(dest, NULL) a bien échoué avec errno: %d\n", errno);
    } else {
        printf("ft_strcpy(dest, NULL) should have failed but returned: %p\n", result);
    }
    
    // Test avec un pointeur destination nul
    errno = 0;
    result = ft_strcpy(NULL, src);
    if (result == NULL) {
        printf("ft_strcpy(NULL, src) a bien échoué avec errno: %d\n", errno);
    } else {
        printf("ft_strcpy(NULL, src) should have failed but returned: %p\n", result);
    }
}

void test_ft_strcmp() {
    printf("\n=== Testing ft_strcmp:\n");
    const char *str1 = "Arya";
    const char *str2 = "Sansa";
    const char *str3 = "Jon";
    printf("Comparison of \"%s\" and \"%s\": %d\n", str1, str2, ft_strcmp(str1, str2));
    printf("Comparison of \"%s\" and \"%s\": %d\n", str1, str3, ft_strcmp(str1, str3));
    
    // Test avec un pointeur nul
    errno = 0;
    int result = ft_strcmp(str1, NULL);
    if (result == -1) {
        printf("ft_strcmp(str, NULL) a échoué avec errno: %d\n", errno);
    }
}

void test_ft_write() {
    printf("\n=== Testing ft_write:\n");
    const char *test_str = "You know nothing, Jon Snow.\n";
    ssize_t written = ft_write(STDOUT_FILENO, test_str, ft_strlen(test_str));
    printf("ft_write returned: %zd\n", written);
    
    // Test avec un descripteur de fichier invalide
    errno = 0;
    written = ft_write(-1, test_str, ft_strlen(test_str));
    if (written == -1) {
        printf("ft_write a bien échoué avec errno: %d\n", errno);
    }
}

void test_ft_read() {
    printf("\n=== Testing ft_read:\n");
    char buffer[100];
    int fd = open("main.c", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }
    
    ssize_t bytes_read = ft_read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read != -1) {
        buffer[bytes_read] = '\0';
        printf("Read %zd bytes: %s\n", bytes_read, buffer);
    } else {
        perror("ft_read");
    }
    
    // Test avec un descripteur de fichier invalide
    errno = 0;
    bytes_read = ft_read(-1, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        printf("ft_read a bien échoué avec errno: %d\n", errno);
    }
    close(fd);
}

void test_ft_strdup() {
    printf("\n=== Testing ft_strdup:\n");
    const char *test_str = "Daenerys Targaryen, the Mother of Dragons.";
    
    errno = 0;
    char *dup_str = ft_strdup(test_str);
    if (dup_str != NULL) {
        printf("Duplicated string: %s\n", dup_str);
        free(dup_str);
    } else {
        printf("ft_strdup failed with errno: %d\n", errno);
    }
    
    // Test avec un pointeur source nul
    errno = 0;
    dup_str = ft_strdup(NULL);
    if (dup_str == NULL) {
        printf("ft_strdup a bien échoué avec errno: %d\n", errno);
    }
}

int main() {
    test_ft_strlen();
    test_ft_strcpy();
    test_ft_strcmp();
    test_ft_write();
    test_ft_read();
    test_ft_strdup();
    return 0;
}