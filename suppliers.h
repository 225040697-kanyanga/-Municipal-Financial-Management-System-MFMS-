#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100
#define ID_LEN        16
#define NAME_LEN      50
#define EMAIL_LEN     60
#define PHONE_LEN     16
#define TOWN_LEN      30

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);
void supplierReport(void);

#endif
