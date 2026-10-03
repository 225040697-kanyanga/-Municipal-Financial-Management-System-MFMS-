#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"


/* 1. Store employees in arrays */

int    empId[MAX_EMPLOYEES];
char   empName[MAX_EMPLOYEES][MAX_NAME];
char   empDept[MAX_EMPLOYEES][MAX_NAME];
char   empTitle[MAX_EMPLOYEES][MAX_NAME];
double empBasicSalary[MAX_EMPLOYEES];
double empHousing[MAX_EMPLOYEES];
double empTransport[MAX_EMPLOYEES];

int employeeCount = 0;


int getEmployeeCount(void)
{
    return employeeCount;
}


int findEmployeeById(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (empId[i] == id)
        {
            return i;
        }
    }

    return -1;
}


/* 2. Add a new employee */

void addEmployee(void)
{
    int id;

    printf("\n--- ADD EMPLOYEE ---\n");

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("The system is full. Cannot add more employees.\n");
        return;
    }

    id = getValidInt("Enter employee ID: ", 1, 999999);

    if (findEmployeeById(id) != -1)
    {
        printf("Error: Employee ID %d already exists.\n", id);
        return;
    }

    getValidString("Enter full name: ", empName[employeeCount], MAX_NAME);
    getValidString("Enter department: ", empDept[employeeCount], MAX_NAME);
    getValidString("Enter job title: ", empTitle[employeeCount], MAX_NAME);

    empBasicSalary[employeeCount] =
        getValidDouble("Enter basic salary (N$): ", 0.01, 10000000);
    empHousing[employeeCount] =
        getValidDouble("Enter housing allowance (N$): ", 0, 10000000);
    empTransport[employeeCount] =
        getValidDouble("Enter transport allowance (N$): ", 0, 10000000);

    empId[employeeCount] = id;
    employeeCount = employeeCount + 1;

    printf("Employee added successfully.\n");
}


/* 3. Display all employees */

void printTableHeading(void)
{
    printf("\n%-6s %-20s %-15s %-15s %12s %10s %10s\n",
           "ID", "Name", "Department", "Job Title",
           "Basic (N$)", "Housing", "Transport");
    printf("--------------------------------------------------"
           "------------------------------------------\n");
}


void printEmployee(int i)
{
    printf("%-6d %-20s %-15s %-15s %12.2f %10.2f %10.2f\n",
           empId[i], empName[i], empDept[i], empTitle[i],
           empBasicSalary[i], empHousing[i], empTransport[i]);
}


void displayEmployees(void)
{
    int i;

    printf("\n--- ALL EMPLOYEES ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printTableHeading();

    for (i = 0; i < employeeCount; i++)
    {
        printEmployee(i);
    }

    printf("\nTotal employees: %d\n", employeeCount);
}


/* 4. Searches for an employee (by ID or by name) */

void searchEmployee(void)
{
    int choice;
    int i;
    int found = 0;

    printf("\n--- SEARCH EMPLOYEE ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    printf("1. Search by ID\n");
    printf("2. Search by name\n");
    choice = getValidInt("Enter your choice: ", 1, 2);

    if (choice == 1)
    {
        int id = getValidInt("Enter employee ID: ", 1, 999999);
        int position = findEmployeeById(id);

        if (position == -1)
        {
            printf("Employee not found.\n");
        }
        else
        {
            printTableHeading();
            printEmployee(position);
        }
    }
    else
    {
        char searchName[MAX_NAME];

        getValidString("Enter the full name: ", searchName, MAX_NAME);

        for (i = 0; i < employeeCount; i++)
        {
            if (strcmp(empName[i], searchName) == 0)
            {
                if (found == 0)
                {
                    printTableHeading();
                }
                printEmployee(i);
                found = 1;
            }
        }

        if (found == 0)
        {
            printf("Employee not found.\n");
        }
    }
}


/* 5. Shows the employee menu */

void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Search employee\n");
        printf("4. Calculate salary\n");
        printf("5. Back to main menu\n");

        choice = getValidInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                calculateSalary();
                break;
            case 5:
                printf("Going back to the main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);
}