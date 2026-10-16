/*
   sampledata.c - loads demo data into every module so the
   system can be demonstrated quickly.
*/

#include <stdio.h>
#include "common.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void loadSampleData(void)
{
    loadSampleEmployees();
    loadSampleBudgets();
    loadSampleSuppliers();
    loadSampleAssets();

    printf("Sample data loaded (4 employees, 3 departments, 3 suppliers, 3 assets).\n");
}
