#include "common.h"
#include <stdlib.h>

/* Read and validate a reports-menu choice. */
static int readReportChoice(void)
{
    char input[100];
    char *end;
    long value;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    value = strtol(input, &end, 10);

    if (end == input) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
        end++;
    }

    if (*end != '\0' || value < REPORT_MENU_MIN || value > REPORT_MENU_MAX) {
        return -1;
    }

    return (int)value;
}

void displayReports(void)
{
    int choice;

    do {
        printf("\n==============================================\n");
        printf("                 REPORTS MENU\n");
        printf("==============================================\n");
        printf("  1. Employee Report\n");
        printf("  2. Budget Report\n");
        printf("  3. Supplier Report\n");
        printf("  4. Asset Report\n");
        printf("  5. Back to Main Menu\n");
        printf("==============================================\n");
        printf("Enter your choice (1-5): ");

        choice = readReportChoice();

        switch (choice) {
            case REPORT_EMPLOYEES:
                employeeReport();
                break;

            case REPORT_BUDGETS:
                budgetReport();
                break;

            case REPORT_SUPPLIERS:
                supplierReport();
                break;

            case REPORT_ASSETS:
                assetReport();
                break;

            case REPORT_BACK:
                printf("\nReturning to the main menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a number from 1 to 5.\n");
                break;
        }

    } while (choice != REPORT_BACK);
}
