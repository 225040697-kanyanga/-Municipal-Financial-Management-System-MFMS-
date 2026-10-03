#ifndef EMPLOYEES_H
#define EMPLOYEES_H

/* Constants */
#define MAX_EMPLOYEES 100
#define MAX_NAME 50

/* Employee arrays */
extern int    empId[MAX_EMPLOYEES];
extern char   empName[MAX_EMPLOYEES][MAX_NAME];
extern char   empDept[MAX_EMPLOYEES][MAX_NAME];
extern char   empTitle[MAX_EMPLOYEES][MAX_NAME];
extern double empBasicSalary[MAX_EMPLOYEES];
extern double empHousing[MAX_EMPLOYEES];
extern double empTransport[MAX_EMPLOYEES];

extern int employeeCount;

/* Functions */
int  getEmployeeCount(void);
int  findEmployeeById(int id);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void employeeMenu(void);

void calculateSalary(void);

#endif