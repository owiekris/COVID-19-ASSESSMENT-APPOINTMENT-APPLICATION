#ifndef VALIDATION_H
#define VALIDATION_H

#define DISPLAY_DELAY 500

#define MAX_DAYS_FOR_BOOK 10

#define SATURDAY_ENABLE 1
#define SUNDAY_ENABLE 1

#define MIN_YEAR 2021
#define MAX_YEAR 2022

#define REPORT_CODE 25

extern char *FILE_NAME,*tmp_FILE_NAME,*report_path,*receipt_path,*NUM_str,*ALPHA_str,*ALPHA_NUM_str,*ALPHA_NUM_SYM_str,*DATE_TIME_str;
extern int days_in_month[13];
extern const char appnt_slot[28][6];

void delay_ms(int ms_second);
int validate_input(char *str,char *cmp_str,int max_length,int min_length);
int validate_email(char *str);
int leap_year(int year);
long number_of_days(int date, int month, int year);
int day_for_date(int date, int month, int year);

int day_validation(int day_no);
int date_validation(int date, int month, int year, int mode);
int extract_value(char *tmp_str,int *dd,int *mm,int *yyyy, int mode);

#endif
