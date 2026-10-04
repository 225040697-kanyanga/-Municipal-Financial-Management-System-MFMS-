Validation.h

#ifndef VALIDATION_H
#define VALIDATION_H

int getValidInt(const char *prompt, int min, int max);

double getValidDouble(const char *prompt, double min, double max);

void getValidString(const char *prompt, char *output, int size);

int isValidEmail(const char *email);

int isValidPhone(const char *phone);

#endif

Validation.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "validation.h"


/*
 * Reads a valid whole number within a specified range.
 *
 * Example:
 * int id = getValidInt("Enter ID: ", 1, 9999);
 */
int getValidInt(const char *prompt, int min, int max)
{
    char input[100];
    char *endPtr;
    long value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error. Please try again.\n");
            continue;
        }

        /* Remove newline */
        input[strcspn(input, "\n")] = '\0';

        /* Check for empty input */
        if (strlen(input) == 0)
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        /* Convert text to integer */
        value = strtol(input, &endPtr, 10);

        /* Allow spaces after the number */
        while (isspace((unsigned char)*endPtr))
        {
            endPtr++;
        }

        /* Make sure the entire input was a number */
        if (*endPtr != '\0')
        {
            printf("Invalid whole number. Please try again.\n");
            continue;
        }

        /* Check range */
        if (value < min || value > max)
        {
            printf("Please enter a number between %d and %d.\n",
                   min, max);
            continue;
        }

        return (int)value;
    }
}


/*
 * Reads a valid decimal number within a specified range.
 *
 * Example:
 * double salary = getValidDouble("Enter salary: ", 0.0, 1000000.0);
 */
double getValidDouble(const char *prompt, double min, double max)
{
    char input[100];
    char *endPtr;
    double value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Input error. Please try again.\n");
            continue;
        }

        /* Remove newline */
        input[strcspn(input, "\n")] = '\0';

        /* Check for empty input */
        if (strlen(input) == 0)
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        /* Convert text to decimal */
        value = strtod(input, &endPtr);

        /* Allow spaces after the number */
        while (isspace((unsigned char)*endPtr))
        {
            endPtr++;
        }

        /* Check that the whole input is a number */
        if (*endPtr != '\0')
        {
            printf("Invalid decimal number. Please try again.\n");
            continue;
        }

        /* Check range */
        if (value < min || value > max)
        {
            printf("Please enter a value between %.2f and %.2f.\n",
                   min, max);
            continue;
        }

        return value;
    }
}


/*
 * Reads text and prevents empty input.
 *
 * Example:
 * char name[100];
 * getValidString("Enter name: ", name, sizeof(name));
 */
void getValidString(const char *prompt, char *output, int size)
{
    while (1)
    {
        printf("%s", prompt);

        if (fgets(output, size, stdin) == NULL)
        {
            printf("Input error. Please try again.\n");
            continue;
        }

        /* Remove newline */
        output[strcspn(output, "\n")] = '\0';

        /* Check for empty input */
        if (strlen(output) == 0)
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        /* Check if input contains only spaces */
        int onlySpaces = 1;

        for (int i = 0; output[i] != '\0'; i++)
        {
            if (!isspace((unsigned char)output[i]))
            {
                onlySpaces = 0;
                break;
            }
        }

        if (onlySpaces)
        {
            printf("Input cannot contain only spaces.\n");
            continue;
        }

        return;
    }
}


/*
 * Checks whether an email address has a basic valid format.
 *
 * Examples:
 * john@gmail.com       -> valid
 * finance@municipality.na -> valid
 * johnexample.com     -> invalid
 * john@               -> invalid
 */
int isValidEmail(const char *email)
{
    const char *at;
    const char *dot;

    if (email == NULL)
    {
        return 0;
    }

    /* Email must have at least 5 characters */
    if (strlen(email) < 5)
    {
        return 0;
    }

    /* Email cannot contain spaces */
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (isspace((unsigned char)email[i]))
        {
            return 0;
        }
    }

    /* Find @ */
    at = strchr(email, '@');

    if (at == NULL)
    {
        return 0;
    }

    /* @ cannot be the first character */
    if (at == email)
    {
        return 0;
    }

    /* There must be only one @ */
    if (strchr(at + 1, '@') != NULL)
    {
        return 0;
    }

    /* Find dot after @ */
    dot = strchr(at + 1, '.');

    if (dot == NULL)
    {
        return 0;
    }

    /* Dot cannot immediately follow @ */
    if (dot == at + 1)
    {
        return 0;
    }

    /* Dot cannot be the final character */
    if (*(dot + 1) == '\0')
    {
        return 0;
    }

    return 1;
}


/*
 * Checks whether a phone number is valid.
 *
 * Accepted examples:
 * 0812345678
 * +264812345678
 * +264 81 234 5678
 * 081-234-5678
 */
int isValidPhone(const char *phone)
{
    int digitCount = 0;

    if (phone == NULL || strlen(phone) == 0)
    {
        return 0;
    }

    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (isdigit((unsigned char)phone[i]))
        {
            digitCount++;
        }
        else if (phone[i] == '+' && i == 0)
        {
            /* + is allowed only at the beginning */
        }
        else if (phone[i] == ' ' || phone[i] == '-')
        {
            /* Spaces and hyphens are allowed */
        }
        else
        {
            return 0;
        }
    }

    /* Phone number must contain between 7 and 15 digits */
    if (digitCount < 7 || digitCount > 15)
    {
        return 0;
    }

    return 1;
}
