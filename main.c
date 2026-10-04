#include "common.h"
#include <stdlib.h>
#include <string.h>

/* Read an integer safely without leaving invalid characters in stdin. */
static int readMenuChoice(void)
{
    char input[100];
    char *end;
    long value;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    value = strtol(input, &end, 10);

    /* Reject blank input, non-numeric input and extra characters. */
    if (end == input) {
        return -1;
    }

    while (*end == ' ' || *end == '\\t' || *end == '\\n' || *end == '\\r') {
        end++;
    }

    if (*end != '\\0') {
        return -1;
    }

    if (value < MAIN_MENU_MIN || value > MAIN_MENU_MAX) {
        return -1;
    }

    return (int)value;
}

void displayMenu(void)
{
    printf("\\n==================================================\\n");
    printf("       MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\\n");
    printf("                    VAN HOODBO\\n");
    printf("==================================================\\n");
    printf("  1. Employee Management\\n");
    printf("  2. Budget Management\\n");
    printf("  3. Supplier Management\\n");
    printf("  4. Asset Management\\n");
    printf("  5. Reports Menu\\n");
    printf("  6. Exit\\n");
    printf("==================================================\\n");
    printf("Enter your choice (1-6): ");
}

int main(void)
{
    int choice;

    printf("\\nWelcome to the Municipal Financial Management System!\\n");

    /* Load sample data here if the group's sample-data module is ready. */
    /* loadSampleData(); */

    do {
        displayMenu();
        choice = readMenuChoice();

        switch (choice) {
            case MENU_EMPLOYEES:
                employeeMenu();
                break;

            case MENU_BUDGETS:
                budgetMenu();
                break;

            case MENU_SUPPLIERS:
                supplierMenu();
                break;

            case MENU_ASSETS:
                assetMenu();
                break;

            case MENU_REPORTS:
                displayReports();
                break;

            case MENU_EXIT:
                printf("\\nThank you for using the Municipal Financial Management System.\\n");
                printf("Goodbye!\\n");
                break;

            default:
                printf("\\nInvalid choice. Please enter a number from 1 to 6.\\n");
                break;
        }

    } while (choice != MENU_EXIT);

    return 0;
}
