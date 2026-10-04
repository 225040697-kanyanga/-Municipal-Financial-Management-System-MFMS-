# MFMS Test Log

Project A – Municipal Financial Management System (PAP521S)
Tested with: `gcc -std=c99 -Wall -Wextra -pedantic` (GCC)

Each member fills in the **Tester** column for the tests they ran themselves.
Rows marked "Not tested yet" must be run once `main.c` and `reports.c` are added.

## 1. Input validation (validation.c)

| No. | Test | Input | Expected result | Actual result | Pass / Fail | Tester |
|---|---|---|---|---|---|---|
| 1 | Menu choice: letters | abc | Error message, asks again | Error message, asks again | Pass | |
| 2 | Menu choice: above range (1 to 5) | 9 | Error message, asks again | Error message, asks again | Pass | |
| 3 | Menu choice: zero | 0 | Error message, asks again | Error message, asks again | Pass | |
| 4 | Menu choice: valid | 3 | Accepted | Accepted | Pass | |
| 5 | Number: negative | -5 | Error message, asks again | Error message, asks again | Pass | |
| 6 | Number: letters | xyz | Error message, asks again | Error message, asks again | Pass | |
| 7 | Number: valid decimal | 12.50 | Accepted | Accepted | Pass | |
| 8 | Text: empty | (just Enter) | "Input cannot be empty" | "Input cannot be empty" | Pass | |
| 9 | Text: only spaces | (spaces) | "Input cannot be empty" | "Input cannot be empty" | Pass | |
| 10 | Text: too long for the array | 40 characters in a 20 character field | "Input is too long" | "Input is too long" | Pass | |
| 11 | Text with a space | Maria Shikongo | Accepted | Accepted | Pass | |
| 12 | Email: no @ | bad | Not valid | Not valid | Pass | |
| 13 | Email: no dot after @ | a@b | Not valid | Not valid | Pass | |
| 14 | Email: valid | name@mail.com | Accepted | Accepted | Pass | |
| 15 | Phone: letters mixed in | 12ab | Not valid | Not valid | Pass | |
| 16 | Phone: too short | 12345 | Not valid | Not valid | Pass | |
| 17 | Phone: valid | +264811234567 | Accepted | Accepted | Pass | |

## 2. Employee management (employees.c)

| No. | Test | Input | Expected result | Actual result | Pass / Fail | Tester |
|---|---|---|---|---|---|---|
| 18 | Add a valid employee | ID 101, John Smith, Finance, Accountant, 15000, 3000, 1500 | "Employee added successfully" | "Employee added successfully" | Pass | |
| 19 | Add an employee with an existing ID | 101 | "Employee ID 101 already exists" | "Employee ID 101 already exists" | Pass | |
| 20 | Negative basic salary | -5 | Error message, asks again | Error message, asks again | Pass | |
| 21 | Empty employee name | (just Enter) | "Input cannot be empty" | "Input cannot be empty" | Pass | |
| 22 | Search by ID that does not exist | 999 | "Employee not found" | "Employee not found" | Pass | |
| 23 | Search by name | John Smith | Shows John Smith's row | Shows John Smith's row | Pass | |
| 24 | Display all employees | menu option 2 | Table with all employees and the total | Table with all employees and the total | Pass | |

## 3. Salary and employee report (salary.c)

| No. | Test | Input | Expected result | Actual result | Pass / Fail | Tester |
|---|---|---|---|---|---|---|
| 25 | Salary for an employee that does not exist | 999 | "Employee not found", stops | "Employee not found", stops | Pass | |
| 26 | Salary calculation (checked by hand: 15000 + 3000 + 1500 = 19500, minus 2000 = 17500) | ID 101, deductions 2000 | Gross 19500.00, net 17500.00 | Gross 19500.00, net 17500.00 | Pass | |
| 27 | Deductions greater than the gross salary | 30000 | Error message, asks again | Error message (0.00 to 19500.00), asks again | Pass | |
| 28 | Employee report with one employee (15000) | report | Total 1, average, highest and lowest all 15000.00 | Total 1, average, highest and lowest all 15000.00 | Pass | |

## 4. Budget management (budget.c)

| No. | Test | Input | Expected result | Actual result | Pass / Fail | Tester |
|---|---|---|---|---|---|---|
| 29 | Add a department budget | Finance, 500000 | "Budget added successfully" | "Budget added successfully" | Pass | |
| 30 | Add the same department again | Finance | "this department already has a budget" | "this department already has a budget" | Pass | |
| 31 | Negative budget | -100 | Error message, asks again | Error message, asks again | Pass | |
| 32 | Expenditure within budget | Finance, 420000 | Remaining 80000.00, WITHIN BUDGET | Remaining 80000.00, WITHIN BUDGET | Pass | |
| 33 | Expenditure over budget | Health (budget 100000), 150000 | Remaining -50000.00, OVER BUDGET | Remaining -50000.00, OVER BUDGET | Pass | |
| 34 | Expenditure for an unknown department | Unknown | "Department not found" | "Department not found" | Pass | |
| 35 | Letters in the budget menu | abc | Error message, asks again | Error message, asks again | Pass | |
| 36 | Budget report totals | Finance and Health above | Allocated 600000.00, expenditure 570000.00, remaining 30000.00 | Allocated 600000.00, expenditure 570000.00, remaining 30000.00 | Pass | |

## 5. Supplier management (suppliers.c)

| No. | Test | Input | Expected result | Actual result | Pass / Fail | Tester |
|---|---|---|---|---|---|---|
| 37 | Invalid email | abc | Error, asks again | Error, asks again | Pass | |
| 38 | Invalid phone number | 123 | Error, asks again | Error, asks again | Pass | |
| 39 | Add a valid supplier | S1, Acme Ltd, acme@mail.com, 0811234567, Windhoek | "added successfully" | "Supplier 'Acme Ltd' added successfully" | Pass | |
| 40 | Duplicate supplier ID | S1 | "a supplier with ID 'S1' already exists" | "a supplier with ID 'S1' already exists" | Pass | |
| 41 | Search by town | windhoek | Both suppliers in Windhoek found | 2 suppliers found | Pass | |
| 42 | Search for an ID that does not exist | S9 | "No supplier found" | "No supplier found matching 'S9'" | Pass | |
| 43 | Compare two suppliers in the same town | S1 and S2 | "SAME town" | "both suppliers are in the SAME town (Windhoek)" | Pass | |
| 44 | Compare with fewer than 2 suppliers | one supplier registered | "You need at least 2 registered suppliers" | "You need at least 2 registered suppliers to compare" | Pass | |
| 45 | Supplier report | menu option 5 | Total and the list of suppliers | Total Suppliers: 2 and the list | Pass | |

## 6. Asset management (assets.c)

| No. | Test | Input | Expected result | Actual result | Pass / Fail | Tester |
|---|---|---|---|---|---|---|
| 46 | Add a valid asset | ID 1, Toyota Hilux, Vehicle, 350000, Transport, Good | "Asset added successfully" | "Asset added successfully" | Pass | |
| 47 | Duplicate asset ID | 1 | "Asset ID 1 already exists" | "Asset ID 1 already exists" | Pass | |
| 48 | Purchase value of zero | 0 | Error message, asks again | Error message (0.01 to 1000000000.00), asks again | Pass | |
| 49 | Search by type | Computer | Shows Dell Laptop only | Shows Dell Laptop only | Pass | |
| 50 | Search by name | Toyota Hilux | Shows the Toyota row | Shows the Toyota row | Pass | |
| 51 | Total asset value (350000 + 18000) | menu option 4 | N$368000.00 | N$368000.00 | Pass | |

## 7. Main menu and reports (main.c, reports.c) – Not tested yet

| No. | Test | Input | Expected result | Actual result | Pass / Fail | Tester |
|---|---|---|---|---|---|---|
| 52 | Invalid main menu option | 9 | Error message, menu shows again | Not tested yet | | |
| 53 | Letters in the main menu | abc | Error message, asks again | Not tested yet | | |
| 54 | Open each submenu from the main menu | 1, 2, 3, 4 | Each submenu opens | Not tested yet | | |
| 55 | Reports menu shows all four reports | 5 | Employee, budget, supplier and asset reports | Not tested yet | | |
| 56 | Exit | 6 | Program closes | Not tested yet | | |