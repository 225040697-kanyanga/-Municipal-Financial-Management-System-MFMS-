#include "common.h"

void displayMenu(void)
{
    printf("\n==================================================\n");
    printf("       MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("==================================================\n");
    printf("  1. Employee Management\n");
    printf("  2. Budget Management\n");
    printf("  3. Supplier Management\n");
    printf("  4. Asset Management\n");
    printf("  5. Reports Menu\n");
    printf("  6. Exit\n");
    printf("==================================================\n");
}

int main(void)
{
    int choice;

    printf("\nWelcome to the Municipal Financial Management System!\n");

    /* Offer the demo data so the system can be shown quickly. */
    printf("\nLoad sample data?\n");
    printf("  1. Yes\n");
    printf("  2. No\n");
    if (getValidInt("Enter your choice (1-2): ", 1, 2) == 1) {
        loadSampleData();
    }

    do {
        displayMenu();
        choice = getValidInt("Enter your choice (1-6): ", MAIN_MENU_MIN, MAIN_MENU_MAX);

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
                printf("\nThank you for using the Municipal Financial Management System.\n");
                printf("Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a number from 1 to 6.\n");
                break;
        }

    } while (choice != MENU_EXIT);

    return 0;
}
