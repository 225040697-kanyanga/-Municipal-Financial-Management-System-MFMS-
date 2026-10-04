#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS     100
#define ASSET_ID_LEN   16
#define ASSET_NAME_LEN 50
#define ASSET_TYPE_LEN 20
#define ASSET_DEPT_LEN 30
#define ASSET_COND_LEN 12

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
void assetReport(void);

#endif
