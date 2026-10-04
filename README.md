# Municipal Financial Management System (MFMS)

**Course:** PAP521S – Programming in Practice
**Project:** Project A – Foundation System
**Language:** ANSI C (C99)
**Due date:** 04 October 2026

## Group members and responsibilities

| Member | Responsibility | Files |
|---|---|---|
| kanyanga 225040697 | Employees: add, display, search | employees.c, employees.h |
| shiviro 225106507  | Employees: salary calculation and employee report | employees.c, employees.h (or salary.c, salary.h) |
| Edwina 225040255 | Budget management and budget report | budget.c, budget.h |
| Ndapewa 220060975| Supplier management and supplier report | suppliers.c, suppliers.h Asset management and asset report assets.c, assets.h |
| Van Hoodbo | Main menu, reports menu, joining the modules together | main.c, reports.c, reports.h |
| Big Time Dario | Input validation, sample data, testing, README and report | validation.c, validation.h, sampledata.c, sampledata.h, README.md |

## Project description

The MFMS is a menu-driven program written in C for a municipality. It stores employees, department budgets, suppliers and municipal assets, and it can search the records, do calculations and print reports. This is the foundation version. It will be extended in Project B.

## System features

- **Main menu** with clear navigation and handling of invalid choices
- **Employee management:** add, display and search employees, and calculate salary information
- **Budget management:** enter department budgets and expenditure, calculate the remaining budget, show whether a department is within budget, and list departments that exceeded their budget
- **Supplier management:** add, display and search suppliers (ID, name, email, telephone, town)
- **Asset management:** add, display and search assets, and calculate the total asset value
- **Reports:** employee, budget, supplier and asset reports
- **Input validation:** no negative salaries or budgets, no empty names, numbers must be within range, email and phone number checks
- **Sample data** that can be loaded to start the demo quickly

## Project structure

```
MFMS/
├── main.c
├── employees.c
├── employees.h
├── budget.c
├── budget.h
├── suppliers.c
├── suppliers.h
├── assets.c
├── assets.h
├── reports.c
├── reports.h
├── validation.c
├── validation.h
├── sampledata.c
├── sampledata.h
└── README.md
```

## How to compile

You need the GCC compiler. Open a terminal in the project folder and run:

```
gcc -std=c99 -Wall -Wextra -pedantic main.c employees.c budget.c suppliers.c assets.c reports.c validation.c sampledata.c -o mfms
```

If Owen uses a separate `salary.c` file, add it to the command.

## How to run

Windows:

```
.\mfms.exe
```

Linux / macOS:

```
./mfms
```

Choose an option from the main menu by typing its number and pressing Enter.

## Testing

Test cases and results are recorded in `TEST_LOG.md`.
