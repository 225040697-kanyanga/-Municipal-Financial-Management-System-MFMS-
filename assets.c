#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "assets.h"

#define INPUT_BUF   256
#define TYPE_COUNT  5
#define COND_COUNT  3

static const char *assetTypes[TYPE_COUNT] = {
    "Vehicle", "Computer", "Building", "Equipment", "Office Furniture"
};
static const char *assetConditions[COND_COUNT] = {
    "Good", "Fair", "Poor"
};

static char   assetId[MAX_ASSETS][ASSET_ID_LEN];
static char   assetName[MAX_ASSETS][ASSET_NAME_LEN];
static char   assetType[MAX_ASSETS][ASSET_TYPE_LEN];
static double assetValue[MAX_ASSETS];
static char   assetDept[MAX_ASSETS][ASSET_DEPT_LEN];
static char   assetCondition[MAX_ASSETS][ASSET_COND_LEN];
static int    assetCount = 0;

static void trim(char *s);
static void toLowerCopy(char *dest, const char *src, int size);
static int  equalsIgnoreCase(const char *a, const char *b);
static int  containsIgnoreCase(const char *text, const char *key);
static int  askText(const char *prompt, const char *label, char *out, int size);
static int  askValue(const char *prompt, double *out);
static int  readChoice(const char *prompt);
static int  chooseFromList(const char *title, const char *options[], int count, char *out);
static int  findAssetIndex(const char *id);
static void printTableHeader(void);
static void printAssetRow(int i);
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

static int askValue(const char *prompt, double *out)
{
    char line[INPUT_BUF];
    double value;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
            return 0;

        if (sscanf(line, "%lf %c", &value, &extra) != 1) {
            printf("  Error: please enter a valid number.\n");
            continue;
        }
        if (value <= 0) {
            printf("  Error: the value must be greater than zero.\n");
            continue;
        }

        *out = value;
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

static int chooseFromList(const char *title, const char *options[], int count, char *out)
{
    int i, choice;

    while (1) {
        printf("%s\n", title);
        for (i = 0; i < count; i++)
            printf("  %d. %s\n", i + 1, options[i]);

        choice = readChoice("Enter your choice: ");
        if (choice == -2)
            return 0;
        if (choice >= 1 && choice <= count) {
            strcpy(out, options[choice - 1]);
            return 1;
        }
        printf("  Error: please enter a number from 1 to %d.\n", count);
    }
}

static int findAssetIndex(const char *id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (equalsIgnoreCase(assetId[i], id))
            return i;
    }
    return -1;
}

static void printTableHeader(void)
{
    printf("\n%-8s %-22s %-17s %14s %-18s %-10s\n",
           "ID", "NAME", "TYPE", "VALUE (N$)", "DEPARTMENT", "CONDITION");
    printf("------------------------------------------------------------"
           "------------------------------\n");
}

static void printAssetRow(int i)
{
    printf("%-8s %-22s %-17s %14.2f %-18s %-10s\n",
           assetId[i], assetName[i], assetType[i], assetValue[i],
           assetDept[i], assetCondition[i]);
}

/* mode: 1 = ID, 2 = name, 3 = type, 4 = department */
static int searchBy(int mode, const char *key)
{
    int i, found = 0;

    for (i = 0; i < assetCount; i++) {
        int match = 0;

        if (mode == 1)
            match = equalsIgnoreCase(assetId[i], key);
        else if (mode == 2)
            match = containsIgnoreCase(assetName[i], key);
        else if (mode == 3)
            match = containsIgnoreCase(assetType[i], key);
        else if (mode == 4)
            match = containsIgnoreCase(assetDept[i], key);

        if (match) {
            if (found == 0)
                printTableHeader();
            printAssetRow(i);
            found++;
        }
    }
    return found;
}

void addAsset(void)
{
    char id[ASSET_ID_LEN], name[ASSET_NAME_LEN], type[ASSET_TYPE_LEN];
    char dept[ASSET_DEPT_LEN], condition[ASSET_COND_LEN];
    double value;

    printf("\n--- ADD ASSET ---\n");

    if (assetCount >= MAX_ASSETS) {
        printf("Asset register is full (%d assets).\n", MAX_ASSETS);
        return;
    }

    while (1) {
        if (!askText("Asset ID: ", "Asset ID", id, ASSET_ID_LEN))
            return;
        if (findAssetIndex(id) != -1)
            printf("  Error: an asset with ID '%s' already exists.\n", id);
        else
            break;
    }

    if (!askText("Asset name: ", "Asset name", name, ASSET_NAME_LEN))
        return;
    if (!chooseFromList("Asset type:", assetTypes, TYPE_COUNT, type))
        return;
    if (!askValue("Purchase value (N$): ", &value))
        return;
    if (!askText("Department: ", "Department", dept, ASSET_DEPT_LEN))
        return;
    if (!chooseFromList("Condition:", assetConditions, COND_COUNT, condition))
        return;

    strcpy(assetId[assetCount], id);
    strcpy(assetName[assetCount], name);
    strcpy(assetType[assetCount], type);
    assetValue[assetCount] = value;
    strcpy(assetDept[assetCount], dept);
    strcpy(assetCondition[assetCount], condition);
    assetCount++;

    printf("\nAsset '%s' added successfully.\n", name);
}

void displayAssets(void)
{
    int i;

    printf("\n--- ALL ASSETS ---\n");

    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }

    printTableHeader();
    for (i = 0; i < assetCount; i++)
        printAssetRow(i);
}

void searchAsset(void)
{
    char key[INPUT_BUF];
    int choice, found;

    printf("\n--- SEARCH ASSET ---\n");

    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }

    printf("1. Search by ID\n");
    printf("2. Search by name\n");
    printf("3. Search by type\n");
    printf("4. Search by department\n");
    printf("0. Cancel\n");

    choice = readChoice("Enter your choice: ");

    switch (choice) {
    case 1:
        if (!askText("Enter asset ID: ", "Asset ID", key, ASSET_ID_LEN))
            return;
        found = searchBy(1, key);
        break;
    case 2:
        if (!askText("Enter asset name (or part of it): ", "Name", key, ASSET_NAME_LEN))
            return;
        found = searchBy(2, key);
        break;
    case 3:
        if (!askText("Enter asset type: ", "Type", key, ASSET_TYPE_LEN))
            return;
        found = searchBy(3, key);
        break;
    case 4:
        if (!askText("Enter department: ", "Department", key, ASSET_DEPT_LEN))
            return;
        found = searchBy(4, key);
        break;
    case 0:
    case -2:
        return;
    default:
        printf("Invalid choice. Please enter 0, 1, 2, 3 or 4.\n");
        return;
    }

    if (found == 0)
        printf("No asset found matching '%s'.\n", key);
    else
        printf("\n%d asset(s) found.\n", found);
}

void assetReport(void)
{
    int i, c, count;
    double total = 0;

    printf("\n========================================\n");
    printf("              ASSET REPORT\n");
    printf("========================================\n");

    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        printf("Total Assets: 0\n");
        return;
    }

    for (i = 0; i < assetCount; i++)
        total += assetValue[i];

    printf("Total Assets: %d\n", assetCount);
    printf("Total Purchase Value: N$%.2f\n", total);

    for (c = 0; c < COND_COUNT; c++) {
        count = 0;
        for (i = 0; i < assetCount; i++) {
            if (strcmp(assetCondition[i], assetConditions[c]) == 0)
                count++;
        }
        printf("Assets in %s condition: %d\n", assetConditions[c], count);
    }

    printTableHeader();
    for (i = 0; i < assetCount; i++)
        printAssetRow(i);
    printf("\n--- End of asset report ---\n");
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("            ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add asset\n");
        printf("2. Display assets\n");
        printf("3. Search asset\n");
        printf("4. Asset report\n");
        printf("5. Back to main menu\n");

        choice = readChoice("Enter your choice: ");

        switch (choice) {
        case 1: addAsset();       break;
        case 2: displayAssets();  break;
        case 3: searchAsset();    break;
        case 4: assetReport();    break;
        case 5:                   break;
        case -2: choice = 5;      break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 5.\n");
        }
    } while (choice != 5);
}
