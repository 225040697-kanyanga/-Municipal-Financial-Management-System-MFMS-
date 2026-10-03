#include <stdio.h>
#include <string.h>
#define MAX_DEPARTMENTS 20

char departments[MAX_DEPARTMENTS][50];
double budgets[MAX_DEPARTMENTS];
double expenditures[MAX_DEPARTMENTS];
int count = 0;

void addBudget() {
    if (count >= MAX_DEPARTMENTS) {
        printf("Maximum number of departments reached.\n");
        return;
    }

    printf("\nEnter department name: ");
    scanf(" %49[^\n]", departments[count]);

    printf("Enter budget: N$");
    scanf("%lf", &budgets[count]);

    while (budgets[count] < 0) {
        printf("Budget cannot be negative. Enter again: N$");
        scanf("%lf", &budgets[count]);
    }

    expenditures[count] = 0;

    count++;

    printf("Budget added successfully.\n");
}

void addExpenditure() {
    char name[50];
    int found = -1;

    if (count == 0) {
        printf("\nNo departments have been added yet.\n");
        return;
    }

    printf("\nEnter department name: ");
    scanf(" %49[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(departments[i], name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Department not found.\n");
        return;
    }

    printf("Enter expenditure: N$");
    scanf("%lf", &expenditures[found]);

    while (expenditures[found] < 0) {
        printf("Expenditure cannot be negative. Enter again: N$");
        scanf("%lf", &expenditures[found]);
    }

    printf("Expenditure added successfully.\n");
}

double calculateBudget(int i) {
    return budgets[i] - expenditures[i];
}


void displayBudgets() {
    if (count == 0) {
        printf("\nNo budgets available.\n");
        return;
    }

    printf("\nBUDGETS\n");

    for (int i = 0; i < count; i++) {
        double remaining = calculateBudget(i);

        printf("\nDepartment: %s\n", departments[i]);
        printf("Budget: N$%.2f\n", budgets[i]);
        printf("Expenditure: N$%.2f\n", expenditures[i]);
        printf("Remaining: N$%.2f\n", remaining);

        if (remaining >= 0)
            printf("Status: WITHIN BUDGET\n");
        else
            printf("Status: OVER BUDGET\n");
    }
}

void budgetReport() {
    double totalBudget = 0;
    double totalExpenditure = 0;
    double totalRemaining = 0;
    int overBudget = 0;

    if (count == 0) {
        printf("\nNo budget data available.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        totalBudget += budgets[i];
        totalExpenditure += expenditures[i];
        totalRemaining += calculateBudget(i);
    }

    printf("\nBUDGET REPORT\n");
    printf("Total Budget: N$%.2f\n", totalBudget);
    printf("Total Expenditure: N$%.2f\n", totalExpenditure);
    printf("Total Remaining: N$%.2f\n", totalRemaining);

    printf("\nDepartments Over Budget:\n");

    for (int i = 0; i < count; i++) {
        if (calculateBudget(i) < 0) {
            printf("- %s\n", departments[i]);
            overBudget++;
        }
    }

    if (overBudget == 0)
        printf("None\n");
}

void budgetMenu() {
    int choice;

    do {
        printf("\nBUDGET MENU\n");
        printf("1. Add Budget\n");
        printf("2. Add Expenditure\n");
        printf("3. Display Budgets\n");
        printf("4. Budget Report\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBudget();
                break;

            case 2:
                addExpenditure();
                break;

            case 3:
                displayBudgets();
                break;

            case 4:
                budgetReport();
                break;

            case 5:
                printf("Exiting budget menu...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);
}

int main() {
    budgetMenu();

    return 0;
}