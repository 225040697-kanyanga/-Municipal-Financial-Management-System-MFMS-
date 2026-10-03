#include <stdio.h>
#include "salary.h"
#define MAX_ITEMS 100

int empIds[MAX_ITEMS];
float empBasicSalaries[MAX_ITEMS];
float empAllowances[MAX_ITEMS];
char empNames[MAX_ITEMS][50];
float empDeductions[MAX_ITEMS];
int numEmployees = 0;


void calculateSalary();
void generateReport();

// Function to calculate salary for an employee
void calculateSalary()
{
    int searchId;
    int found = 0;
    int i;
    printf("Calculate Salary for Employee\n");
    printf("Enter Employee ID to calculate salary: ");
    scanf("%d", &searchId);

    // Search for the employee in the array
    for (i = 0; i < numEmployees; i++)
    {
        if (empIds[i] == searchId)
        {
            found = 1;
            
            //Display employee details
            printf("Employee found:\n");
            printf("Employee ID: %d\n", empIds[i]);
            printf("Basic Salary: %.2f\n", empBasicSalaries[i]);
            printf("Allowances: %.2f\n", empAllowances[i]);
            break;
        }
    }
    if (!found)
    {
        printf("Employee not found.\n");
    }

    // Calculate deductions for the employee
    printf("Enter deductions:\n");
    scanf("%f", &empDeductions[i]);

    //Calculate gross and net salary
    float grossSalary = empBasicSalaries[i] + empAllowances[i];
    float netSalary = grossSalary - empDeductions[i];
    printf("Gross Salary: %.2f\n", grossSalary);
    printf("Net Salary: %.2f\n", netSalary);

    //Display the salary slip
    printf("\nSalary Slip:\n");
    printf("Employee ID: %d\n", empIds[i]);
    printf("Basic Salary: %.2f\n", empBasicSalaries[i]);
    printf("Allowances: %.2f\n", empAllowances[i]);
    printf("Deductions: %.2f\n", empDeductions[i]);
    printf("Gross Salary: %.2f\n", grossSalary);
    printf("Net Salary: %.2f\n", netSalary);
}

    //Generate employee report 
     void generateReport()
    {
        float totalSalaries = 0.0;
        float highestSalary = 0.0;
        float lowestSalary = 0.0;
        float averageSalary = 0.0;
        printf("\nEmployee Report:\n");
        printf("EMPLOYEE REPORT\n");

    //Check if there are any employees in the system
    if (numEmployees == 0)
    {
        printf("No employees in the system.\n");
    return;
    }  

    //Use the first employee's salary as a starting point for comparison
    highestSalary = empBasicSalaries[0];
    lowestSalary = empBasicSalaries[0];

    //Go through all employees to calculate total, highest, lowest, and average salaries
    for (int i = 0; i < numEmployees; i++)
    {
        totalSalaries += empBasicSalaries[i];

        if (empBasicSalaries[i] > highestSalary)
        {
            highestSalary = empBasicSalaries[i];
        }
        if (empBasicSalaries[i] < lowestSalary)
        {
            lowestSalary = empBasicSalaries[i];
        }
    }
    averageSalary = totalSalaries / numEmployees;

    //Display the report
    printf("Total Employees: %d\n", numEmployees);
    printf("Total Salaries: %.2f\n", totalSalaries);
    printf("Highest Salary: %.2f\n", highestSalary);
    printf("Lowest Salary: %.2f\n", lowestSalary);
    printf("Average Salary: %.2f\n", averageSalary);

}