#ifndef COMMON_H
#define COMMON_H

/* MFMS - Municipal Financial Management System
   Shared constants and function prototypes. */

#include <stdio.h>
#include "validation.h"

#define MAIN_MENU_MIN 1
#define MAIN_MENU_MAX 6

#define REPORT_MENU_MIN 1
#define REPORT_MENU_MAX 5

/* Main menu options */
#define MENU_EMPLOYEES 1
#define MENU_BUDGETS   2
#define MENU_SUPPLIERS 3
#define MENU_ASSETS    4
#define MENU_REPORTS   5
#define MENU_EXIT      6

/* Reports menu options */
#define REPORT_EMPLOYEES 1
#define REPORT_BUDGETS   2
#define REPORT_SUPPLIERS 3
#define REPORT_ASSETS    4
#define REPORT_BACK      5

/* Menus implemented by Libebe */
void displayMenu(void);
void displayReports(void);

/* Employee module - kanyanga and shiviro */
void employeeMenu(void);
void employeeReport(void);

/* Budget module - Edwina */
void budgetMenu(void);
void budgetReport(void);

/* Supplier module - Ndapewa */
void supplierMenu(void);
void supplierReport(void);

/* Asset module - Nghinamito */
void assetMenu(void);
void assetReport(void);

/* Functions implemented by the validation member, if used */
void loadSampleData(void);

#endif
