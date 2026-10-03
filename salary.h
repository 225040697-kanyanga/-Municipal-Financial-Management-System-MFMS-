#ifndef SALARY_H
#define SALARY_H

#define MAX_ITEMS 100

extern int empIds[MAX_ITEMS];
extern float empBasicSalaries[MAX_ITEMS];
extern float empAllowances[MAX_ITEMS];
extern char empNames[MAX_ITEMS][50];
extern float empDeductions[MAX_ITEMS];
extern int numEmployees;

void calculateSalary(void);
void generateReport(void);

#endif