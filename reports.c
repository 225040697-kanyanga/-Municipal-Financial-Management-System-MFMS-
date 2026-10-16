#include "common.h"
#include "reports.h"

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

        choice = getValidInt("Enter your choice (1-5): ", REPORT_MENU_MIN, REPORT_MENU_MAX);

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
