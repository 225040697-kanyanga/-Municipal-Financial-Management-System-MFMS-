/*

   This file tells the other files which input-checking
   functions they can use.
*/

#ifndef VALIDATION_H
#define VALIDATION_H

int    getValidInt(const char *prompt, int min, int max);
double getValidDouble(const char *prompt, double min, double max);
void   getValidString(const char *prompt, char *dest, int maxLen);

int    isValidEmail(const char *email);
int    isValidPhone(const char *phone);
void   getValidEmail(const char *prompt, char *dest, int maxLen);
void   getValidPhone(const char *prompt, char *dest, int maxLen);

#endif