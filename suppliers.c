#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"
#include "validation.h"

#define INPUT_BUF 256

static char supplierId[MAX_SUPPLIERS][ID_LEN];
static char supplierName[MAX_SUPPLIERS][NAME_LEN];
static char supplierEmail[MAX_SUPPLIERS][EMAIL_LEN];
static char supplierPhone[MAX_SUPPLIERS][PHONE_LEN];
static char supplierTown[MAX_SUPPLIERS][TOWN_LEN];
static int  supplierCount = 0;

static void trim(char *s);
static void toLowerCopy(char *dest, const char *src, int size);
static int  equalsIgnoreCase(const char *a, const char *b);
static int  containsIgnoreCase(const char *text, const char *key);
static int  askText(const char *prompt, const char *label, char *out, int size);
static int  readChoice(const char *prompt);
static int  findSupplierIndex(const char *id);
static void printTableHeader(void);
static void printSupplierRow(int i);
static void buildLabel(int i, char *out);
static int  searchBy(int mode, const char *key);

static void trim(char *s)
{
    int start = 0;
    int end = (int)strlen(s) - 1;
    int i, j = 0;

    while (s[start] != '\0' && isspace((unsigned char)s[start]))
        start++;
    while (end >= start && isspace((unsigned char)s[end]))
        end--;

    for (i = start; i <= end; i++)
        s[j++] = s[i];
    s[j] = '\0';
}

static void toLowerCopy(char *dest, const char *src, int size)
{
    int i;
    for (i = 0; i < size - 1 && src[i] != '\0'; i++)
        dest[i] = (char)tolower((unsigned char)src[i]);
    dest[i] = '\0';
}

static int equalsIgnoreCase(const char *a, const char *b)
{
    char la[INPUT_BUF], lb[INPUT_BUF];
    toLowerCopy(la, a, INPUT_BUF);
    toLowerCopy(lb, b, INPUT_BUF);
    return strcmp(la, lb) == 0;
}

static int containsIgnoreCase(const char *text, const char *key)
{
    char lt[INPUT_BUF], lk[INPUT_BUF];
    toLowerCopy(lt, text, INPUT_BUF);
    toLowerCopy(lk, key, INPUT_BUF);
    return strstr(lt, lk) != NULL;
}

static int askText(const char *prompt, const char *label, char *out, int size)
{
    char temp[INPUT_BUF];
    size_t len;
    int c;

    while (1) {
        printf("%s", prompt);
        if (fgets(temp, sizeof(temp), stdin) == NULL)
            return 0;

        len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') {
            temp[len - 1] = '\0';
        } else {
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

        trim(temp);

        if (strlen(temp) == 0) {
            printf("  Error: %s cannot be empty.\n", label);
            continue;
        }
        if ((int)strlen(temp) >= size) {
            printf("  Error: %s is too long (maximum %d characters).\n",
                   label, size - 1);
            continue;
        }

        strcpy(out, temp);
        return 1;
    }
}

static int readChoice(const char *prompt)
{
    char line[INPUT_BUF];
    int value;
    char extra;

    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL)
        return -2;

    if (sscanf(line, "%d %c", &value, &extra) != 1)
        return -1;

    return value;
}

static int findSupplierIndex(const char *id)
{
    int i;
    for (i = 0; i < supplierCount; i++) {
        if (equalsIgnoreCase(supplierId[i], id))
            return i;
    }
    return -1;
}

static void printTableHeader(void)
{
    printf("\n%-8s %-24s %-28s %-15s %-15s\n",
           "ID", "NAME", "EMAIL", "TELEPHONE", "TOWN");
    printf("------------------------------------------------------------"
           "--------------------------\n");
}

static void printSupplierRow(int i)
{
    printf("%-8s %-24s %-28s %-15s %-15s\n",
           supplierId[i], supplierName[i], supplierEmail[i],
           supplierPhone[i], supplierTown[i]);
}

static void buildLabel(int i, char *out)
{
    strcpy(out, supplierId[i]);
    strcat(out, " - ");
    strcat(out, supplierName[i]);
}

/* mode: 1 = ID, 2 = name, 3 = town */
static int searchBy(int mode, const char *key)
{
    int i, found = 0;

    for (i = 0; i < supplierCount; i++) {
        int match = 0;

        if (mode == 1)
            match = equalsIgnoreCase(supplierId[i], key);
        else if (mode == 2)
            match = containsIgnoreCase(supplierName[i], key);
        else if (mode == 3)
            match = containsIgnoreCase(supplierTown[i], key);

        if (match) {
            if (found == 0)
                printTableHeader();
            printSupplierRow(i);
            found++;
        }
    }
    return found;
}

void addSupplier(void)
{
    char id[ID_LEN], name[NAME_LEN], email[EMAIL_LEN];
    char phone[PHONE_LEN], town[TOWN_LEN];

    printf("\n--- ADD SUPPLIER ---\n");

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

    while (1) {
        if (!askText("Supplier ID: ", "Supplier ID", id, ID_LEN))
            return;
        if (findSupplierIndex(id) != -1)
            printf("  Error: a supplier with ID '%s' already exists.\n", id);
        else
            break;
    }

    if (!askText("Supplier name: ", "Supplier name", name, NAME_LEN))
        return;

    while (1) {
        if (!askText("Email: ", "Email", email, EMAIL_LEN))
            return;
        if (isValidEmail(email))
            break;
        printf("  Error: invalid email (it must contain '@', e.g. name@example.com).\n");
    }

    while (1) {
        if (!askText("Telephone (digits only): ", "Telephone", phone, PHONE_LEN))
            return;
        if (isValidPhone(phone))
            break;
        printf("  Error: telephone must contain digits only (7 to 15 digits).\n");
    }

    if (!askText("Town: ", "Town", town, TOWN_LEN))
        return;

    strcpy(supplierId[supplierCount], id);
    strcpy(supplierName[supplierCount], name);
    strcpy(supplierEmail[supplierCount], email);
    strcpy(supplierPhone[supplierCount], phone);
    strcpy(supplierTown[supplierCount], town);
    supplierCount++;

    printf("\nSupplier '%s' added successfully.\n", name);
}

void displaySuppliers(void)
{
    int i;

    printf("\n--- ALL SUPPLIERS ---\n");

    if (supplierCount == 0) {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printTableHeader();
    for (i = 0; i < supplierCount; i++)
        printSupplierRow(i);
}

void searchSupplier(void)
{
    char key[INPUT_BUF];
    int choice, found;

    printf("\n--- SEARCH SUPPLIER ---\n");

    if (supplierCount == 0) {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("1. Search by ID\n");
    printf("2. Search by name\n");
    printf("3. Search by town\n");
    printf("0. Cancel\n");

    choice = readChoice("Enter your choice: ");

    switch (choice) {
    case 1:
        if (!askText("Enter supplier ID: ", "Supplier ID", key, ID_LEN))
            return;
        found = searchBy(1, key);
        break;
    case 2:
        if (!askText("Enter supplier name (or part of it): ", "Name", key, NAME_LEN))
            return;
        found = searchBy(2, key);
        break;
    case 3:
        if (!askText("Enter town: ", "Town", key, TOWN_LEN))
            return;
        found = searchBy(3, key);
        break;
    case 0:
    case -2:
        return;
    default:
        printf("Invalid choice. Please enter 0, 1, 2 or 3.\n");
        return;
    }

    if (found == 0)
        printf("No supplier found matching '%s'.\n", key);
    else
        printf("\n%d supplier(s) found.\n", found);
}

void compareSuppliers(void)
{
    char id1[ID_LEN], id2[ID_LEN];
    char label1[ID_LEN + NAME_LEN + 4], label2[ID_LEN + NAME_LEN + 4];
    int a, b;

    printf("\n--- COMPARE SUPPLIERS ---\n");

    if (supplierCount < 2) {
        printf("You need at least 2 registered suppliers to compare.\n");
        return;
    }

    if (!askText("Enter first supplier ID: ", "Supplier ID", id1, ID_LEN))
        return;
    a = findSupplierIndex(id1);
    if (a == -1) {
        printf("Supplier '%s' was not found.\n", id1);
        return;
    }

    if (!askText("Enter second supplier ID: ", "Supplier ID", id2, ID_LEN))
        return;
    b = findSupplierIndex(id2);
    if (b == -1) {
        printf("Supplier '%s' was not found.\n", id2);
        return;
    }

    if (a == b) {
        printf("You entered the same supplier twice. Choose two different suppliers.\n");
        return;
    }

    buildLabel(a, label1);
    buildLabel(b, label2);

    printf("\nComparing  %s  and  %s\n", label1, label2);
    printTableHeader();
    printSupplierRow(a);
    printSupplierRow(b);

    if (equalsIgnoreCase(supplierTown[a], supplierTown[b]))
        printf("\nResult: both suppliers are in the SAME town (%s).\n",
               supplierTown[a]);
    else
        printf("\nResult: the suppliers are in DIFFERENT towns (%s and %s).\n",
               supplierTown[a], supplierTown[b]);
}

void supplierReport(void)
{
    int i;

    printf("\n========================================\n");
    printf("            SUPPLIER REPORT\n");
    printf("========================================\n");

    if (supplierCount == 0) {
        printf("No suppliers have been registered yet.\n");
        printf("Total Suppliers: 0\n");
        return;
    }

    printf("Total Suppliers: %d\n", supplierCount);
    printTableHeader();
    for (i = 0; i < supplierCount; i++)
        printSupplierRow(i);
    printf("\n--- End of supplier report ---\n");
}

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("          SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add supplier\n");
        printf("2. Display suppliers\n");
        printf("3. Search supplier\n");
        printf("4. Compare suppliers\n");
        printf("5. Supplier report\n");
        printf("6. Back to main menu\n");

        choice = readChoice("Enter your choice: ");

        switch (choice) {
        case 1: addSupplier();       break;
        case 2: displaySuppliers();  break;
        case 3: searchSupplier();    break;
        case 4: compareSuppliers();  break;
        case 5: supplierReport();    break;
        case 6:                      break;
        case -2: choice = 6;         break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 6.\n");
        }
    } while (choice != 6);
}
