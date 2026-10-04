/*
   salary.c
   Salary module - written by Owen

   What this file does:
     1. Calculates the salary of an employee (gross and net)
     2. Prints the employee report (total, highest, lowest, average)

   It uses the employee arrays from employees.c, so it sees the
   employees that were added in the employee menu.
*/

#include <stdio.h>
#include "salary.h"
#include "employees.h"
#include "validation.h"

// 1. Calculates the salary of an employee
void calculateSalary(void)
{
    int id;
    int position;
    double allowances;
    double grossSalary;
    double deductions;
    double netSalary;

    printf("\n--- CALCULATE SALARY ---\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    id = getValidInt("Enter employee ID to calculate salary: ", 1, 999999);
    position = findEmployeeById(id);

    if (position == -1)
    {
        printf("Employee not found.\n");
        return;
    }

    allowances = empHousing[position] + empTransport[position];
    grossSalary = empBasicSalary[position] + allowances;

    printf("\nEmployee found: %s (%s)\n", empName[position], empDept[position]);
    printf("Basic Salary : N$%.2f\n", empBasicSalary[position]);
    printf("Allowances   : N$%.2f\n", allowances);
    printf("Gross Salary : N$%.2f\n", grossSalary);

    deductions = getValidDouble("Enter deductions (N$): ", 0, grossSalary);
    netSalary = grossSalary - deductions;

    printf("\n--- SALARY SLIP ---\n");
    printf("Employee ID  : %d\n", empId[position]);
    printf("Name         : %s\n", empName[position]);
    printf("Basic Salary : N$%.2f\n", empBasicSalary[position]);
    printf("Allowances   : N$%.2f\n", allowances);
    printf("Deductions   : N$%.2f\n", deductions);
    printf("Gross Salary : N$%.2f\n", grossSalary);
    printf("Net Salary   : N$%.2f\n", netSalary);
}

// 2. Prints the employee report
void generateReport(void)
{
    double totalSalaries = 0;
    double highestSalary;
    double lowestSalary;
    double averageSalary;
    int i;

    printf("\n========================================\n");
    printf("            EMPLOYEE REPORT\n");
    printf("========================================\n");

    if (employeeCount == 0)
    {
        printf("No employees in the system.\n");
        return;
    }

    highestSalary = empBasicSalary[0];
    lowestSalary = empBasicSalary[0];

    for (i = 0; i < employeeCount; i++)
    {
        totalSalaries = totalSalaries + empBasicSalary[i];

        if (empBasicSalary[i] > highestSalary)
        {
            highestSalary = empBasicSalary[i];
        }
        if (empBasicSalary[i] < lowestSalary)
        {
            lowestSalary = empBasicSalary[i];
        }
    }

    averageSalary = totalSalaries / employeeCount;

    printf("Total Employees: %d\n", employeeCount);
    printf("Total Salaries : N$%.2f\n", totalSalaries);
    printf("Average Salary : N$%.2f\n", averageSalary);
    printf("Highest Salary : N$%.2f\n", highestSalary);
    printf("Lowest Salary  : N$%.2f\n", lowestSalary);
}
