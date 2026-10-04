/*

   What this file does:
     1. Stores department budgets and expenditure in arrays
     2. Adds a department budget
     3. Adds expenditure to a department
     4. Calculates the remaining budget
     5. Displays all budgets
     6. Prints the budget report
     7. Shows the budget menu
*/

#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "validation.h"

#define MAX_DEPARTMENTS 20
#define DEPT_NAME 50

// 1. Stores department budgets and expenditure in arrays
char departments[MAX_DEPARTMENTS][DEPT_NAME];
double budgets[MAX_DEPARTMENTS];
double expenditures[MAX_DEPARTMENTS];
int departmentCount = 0;

// 2. Adds a department budget
void addBudget(void)
{
    int i;

    printf("\n--- ADD BUDGET ---\n");

    if (departmentCount >= MAX_DEPARTMENTS)
    {
        printf("Maximum number of departments reached.\n");
        return;
    }

    getValidString("Enter department name: ", departments[departmentCount], DEPT_NAME);

    for (i = 0; i < departmentCount; i++)
    {
        if (strcmp(departments[i], departments[departmentCount]) == 0)
        {
            printf("Error: this department already has a budget.\n");
            return;
        }
    }

    budgets[departmentCount] = getValidDouble("Enter budget: N$", 0, 1000000000);
    expenditures[departmentCount] = 0;

    departmentCount++;

    printf("Budget added successfully.\n");
}

// 3. Adds expenditure to a department
void addExpenditure(void)
{
    char name[DEPT_NAME];
    int found = -1;
    int i;

    printf("\n--- ADD EXPENDITURE ---\n");

    if (departmentCount == 0)
    {
        printf("No departments have been added yet.\n");
        return;
    }

    getValidString("Enter department name: ", name, DEPT_NAME);

    for (i = 0; i < departmentCount; i++)
    {
        if (strcmp(departments[i], name) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Department not found.\n");
        return;
    }

    expenditures[found] = getValidDouble("Enter expenditure: N$", 0, 1000000000);

    printf("Expenditure added successfully.\n");
}

// 4. Calculates the remaining budget of department i
double calculateBudget(int i)
{
    return budgets[i] - expenditures[i];
}

// 5. Displays all budgets
void displayBudgets(void)
{
    int i;
    double remaining;

    printf("\n--- BUDGETS ---\n");

    if (departmentCount == 0)
    {
        printf("No budgets available.\n");
        return;
    }

    for (i = 0; i < departmentCount; i++)
    {
        remaining = calculateBudget(i);

        printf("\nDepartment: %s\n", departments[i]);
        printf("Allocated Budget: N$%.2f\n", budgets[i]);
        printf("Expenditure: N$%.2f\n", expenditures[i]);
        printf("Remaining Budget: N$%.2f\n", remaining);

        if (remaining >= 0)
        {
            printf("Status: WITHIN BUDGET\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
        }
    }
}

// 6. Prints the budget report
void budgetReport(void)
{
    double totalBudget = 0;
    double totalExpenditure = 0;
    double totalRemaining = 0;
    int overBudget = 0;
    int i;

    printf("\n========================================\n");
    printf("              BUDGET REPORT\n");
    printf("========================================\n");

    if (departmentCount == 0)
    {
        printf("No budget data available.\n");
        return;
    }

    for (i = 0; i < departmentCount; i++)
    {
        totalBudget = totalBudget + budgets[i];
        totalExpenditure = totalExpenditure + expenditures[i];
        totalRemaining = totalRemaining + calculateBudget(i);
    }

    printf("Total Allocated Budget: N$%.2f\n", totalBudget);
    printf("Total Expenditure: N$%.2f\n", totalExpenditure);
    printf("Total Remaining: N$%.2f\n", totalRemaining);

    printf("\nDepartments Over Budget:\n");

    for (i = 0; i < departmentCount; i++)
    {
        if (calculateBudget(i) < 0)
        {
            printf("- %s\n", departments[i]);
            overBudget = overBudget + 1;
        }
    }

    if (overBudget == 0)
    {
        printf("None\n");
    }
}

// 7. Shows the budget menu
void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("            BUDGET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add budget\n");
        printf("2. Add expenditure\n");
        printf("3. Display budgets\n");
        printf("4. Budget report\n");
        printf("5. Back to main menu\n");

        choice = getValidInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
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
                printf("Going back to the main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);
}
