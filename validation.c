/*


   What this file does:
     1. Reads a whole number between a minimum and a maximum
     2. Reads a decimal number between a minimum and a maximum
     3. Reads text that is not empty and fits in the array
     4. Checks if an email address is valid
     5. Checks if a phone number is valid
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validation.h"

#define LINE_SIZE 200

// Reads one line from the keyboard and removes the Enter character (returns 0 if the line was too long)
static int readLine(char *line, int size)
{
    int c;
    int tooLong = 0;

    if (fgets(line, size, stdin) == NULL)
    {
        printf("\nNo more input. Closing the program.\n");
        exit(0);
    }

    if (strchr(line, '\n') == NULL)
    {
        c = getchar();

        if (c != EOF)
        {
            tooLong = 1;

            while (c != '\n' && c != EOF)
            {
                c = getchar();
            }
        }
    }

    line[strcspn(line, "\n")] = '\0';

    if (tooLong == 1)
    {
        return 0;
    }

    return 1;
}

// 1. Reads a whole number between min and max
int getValidInt(const char *prompt, int min, int max)
{
    char line[LINE_SIZE];
    char *end;
    long number;
    int lineOk;

    while (1)
    {
        printf("%s", prompt);
        lineOk = readLine(line, LINE_SIZE);
        number = strtol(line, &end, 10);

        if (lineOk == 1 && end != line && *end == '\0' && number >= min && number <= max)
        {
            return (int)number;
        }

        printf("Invalid input. Please enter a whole number from %d to %d.\n", min, max);
    }
}

// 2. Reads a decimal number between min and max
double getValidDouble(const char *prompt, double min, double max)
{
    char line[LINE_SIZE];
    char *end;
    double number;
    int lineOk;

    while (1)
    {
        printf("%s", prompt);
        lineOk = readLine(line, LINE_SIZE);
        number = strtod(line, &end);

        if (lineOk == 1 && end != line && *end == '\0' && number >= min && number <= max)
        {
            return number;
        }

        printf("Invalid input. Please enter a number from %.2f to %.2f.\n", min, max);
    }
}

// 3. Reads text that is not empty and fits in the array (spaces are allowed)
void getValidString(const char *prompt, char *dest, int maxLen)
{
    char line[LINE_SIZE];
    int lineOk;
    int i;
    int hasText;

    while (1)
    {
        printf("%s", prompt);
        lineOk = readLine(line, LINE_SIZE);

        hasText = 0;
        for (i = 0; line[i] != '\0'; i++)
        {
            if (!isspace((unsigned char)line[i]))
            {
                hasText = 1;
            }
        }

        if (lineOk == 0 || (int)strlen(line) >= maxLen)
        {
            printf("Input is too long. Maximum is %d characters.\n", maxLen - 1);
        }
        else if (hasText == 0)
        {
            printf("Input cannot be empty.\n");
        }
        else
        {
            strcpy(dest, line);
            return;
        }
    }
}

// 4. Checks an email address (returns 1 if valid, 0 if not)
int isValidEmail(const char *email)
{
    const char *at;
    const char *dot;
    int i;

    if (strlen(email) < 5)
    {
        return 0;
    }

    for (i = 0; email[i] != '\0'; i++)
    {
        if (isspace((unsigned char)email[i]))
        {
            return 0;
        }
    }

    at = strchr(email, '@');

    if (at == NULL || at == email)
    {
        return 0;
    }

    if (strchr(at + 1, '@') != NULL)
    {
        return 0;
    }

    dot = strrchr(email, '.');

    if (dot == NULL || dot < at + 2 || dot[1] == '\0')
    {
        return 0;
    }

    return 1;
}

// 5. Checks a phone number: digits only, 7 to 15 digits, + allowed at the start (returns 1 if valid, 0 if not)
int isValidPhone(const char *phone)
{
    int i = 0;
    int digits = 0;

    if (phone[0] == '+')
    {
        i = 1;
    }

    for (; phone[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)phone[i]))
        {
            return 0;
        }
        digits = digits + 1;
    }

    if (digits < 7 || digits > 15)
    {
        return 0;
    }

    return 1;
}

// Keeps asking until the user enters a valid email
void getValidEmail(const char *prompt, char *dest, int maxLen)
{
    while (1)
    {
        getValidString(prompt, dest, maxLen);

        if (isValidEmail(dest) == 1)
        {
            return;
        }

        printf("Invalid email. Example: name@example.com\n");
    }
}

// Keeps asking until the user enters a valid phone number
void getValidPhone(const char *prompt, char *dest, int maxLen)
{
    while (1)
    {
        getValidString(prompt, dest, maxLen);

        if (isValidPhone(dest) == 1)
        {
            return;
        }

        printf("Invalid phone number. Use digits only (7 to 15 digits).\n");
    }
}