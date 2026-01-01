/*
 * string_exercises.c — Day 4 String Exercises
 * Hunter Protocol: Season 1
 *
 * Rules:
 *   - No [] operator in exercises 1, 2, 3
 *   - Use const where not modifying
 *   - Compile: gcc -Wall -Wextra -std=c17 -o strings string_exercises.c
 */

#include <stdio.h>
#include <stddef.h>

/* Exercise 1 */
size_t my_strlen(const char *s)
{
    size_t counter = 0; 
    while(*s != '\0'){
	s++; 
	counter++; 
    } 
    return counter; 
}

/* Exercise 2 */
char *my_strcpy(char *dest, const char *src)
{
    char *original = dest; 
    while(*src != '\0'){
         *dest = *src; 
	 dest++; 
	 src++; 
    }
    *dest = '\0';
    return original; 
}

/* Exercise 3 */
int my_strcmp(const char *s1, const char *s2)
{
    while(*s1 && *s1 == *s2){
        s1++;
	s2++; 
    }
    return *s1 - *s2;
}

/* Exercise 4 */
void my_strrev(char *s)
{
    size_t len = my_strlen(s); 
    char *left = s; 
    char *right = s + len - 1;

    while(left < right){
	char temp = *left; 
	*left = *right; 
        *right = temp;
	
	left++; 
	right--;	
    } 
}

/* Test Harness */
int main(void)
{
    printf("=== Exercise 1: my_strlen ===\n");
    printf("strlen(\"Afsan\") = %zu\n", my_strlen("Afsan"));
    printf("strlen(\"\") = %zu\n", my_strlen(""));
    printf("strlen(\"GPU\") = %zu\n\n", my_strlen("GPU"));

    printf("=== Exercise 2: my_strcpy ===\n");
    char buffer[32];
    my_strcpy(buffer, "Shadow Monarch");
    printf("Copied: \"%s\"\n\n", buffer);

    printf("=== Exercise 3: my_strcmp ===\n");
    printf("strcmp(\"apple\", \"apple\") = %d\n", my_strcmp("apple", "apple"));
    printf("strcmp(\"apple\", \"banana\") = %d\n", my_strcmp("apple", "banana"));
    printf("strcmp(\"banana\", \"apple\") = %d\n\n", my_strcmp("banana", "apple"));

    printf("=== Exercise 4: my_strrev ===\n");
    char word[] = "Hunter";
    printf("Before: \"%s\"\n", word);
    my_strrev(word);
    printf("After:  \"%s\"\n", word);

    return 0;
}
