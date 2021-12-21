/**
* @file validation.c
* @author Shailesh Sankdasariya
* @author Ritesh Panday
* @author Christopher Owoicho
* @author Gajan Satkunanathan
* @date 30 November 2021
* @brief handles validation of all inputted data by user
*/

/* Include all Required Header Files. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Include all dependencies Files & Folder. */
#include "..\include\ttask.h"
#include "..\include\tappointment.h"
#include "..\include\tdebug.h"
#include "..\include\tdatabase.h"
#include "..\include\tvalidation.h"
#include "..\include\tuser.h"

/* Global Variable declaration. */
char *FILE_NAME="..\\data\\database\\db.csv";
char *tmp_FILE_NAME="..\\data\\database\\tmp_db.csv";
char *report_path="..\\data\\report\\";
char *receipt_path="..\\data\\receipt\\";
char *NUM_str="0123456789";
char *ALPHA_str="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *ALPHA_NUM_str="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *ALPHA_NUM_SYM_str="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&'*+-/=?^_`{|}~.@";
char *DATE_TIME_str="0123456789/:";

int days_in_month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

const char appnt_slot[28][6]={"00:00",
                              "08:00","08:20","08:40",
                              "09:00","09:20","09:40",
                              "10:00","10:20","10:40",
                              "11:00","11:20","11:40",
                              "12:00","12:20","12:40",
                              "13:00","13:20","13:40",
                              "14:00","14:20","14:40",
                              "15:00","15:20","15:40",
                              "16:00","16:20","16:40"};


/**
* @fn void delay_ms(int ms_second)
* @author Shailesh Sankdasariya
* @brief  This function create delay to halt further operation.
* @param[in] int ms_second , integer value of the delay in milli seconds
* @return void , no parameter needed to specify.
*/
void delay_ms(int ms_second)
{
    // Storing start time of system on funciton invocation
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + ms_second)
        ;
}


/**
* @fn int validate_input(char *str,char *cmp_str,int max_length,int min_length)
* @author Shailesh Sankdasariya
* @author Ritesh Panday
* @author Christopher Owoicho
* @author Gajan Satkunanathan
* @brief  This function validate input string's character set by another character set in string and based on string length provide validation.
 * @param[in] char * str, pointer to string entered by user
 * @param[in] char * cmp_str, pointer to string compared with user's entered string
 * @param[in] max_length maximum string length limit
 * @param[in] min_length minimum string length limit
 * @return returns 0 on failure and 1 on success
*/
int validate_input(char *str,char *cmp_str,int max_length,int min_length)
{
    int char_length;

    char_length= strlen(str);
    if(char_length<min_length)
    {
        printf("\nERROR : Character length lesser than min limit");
        printf("\nINFO  : Minimum character length is %d and you type %d character",min_length,char_length);
        return 0;
    }
    if(char_length>max_length)
    {
        printf("\nERROR : Character length exceed beyond maximum limit");
        printf("\nINFO  : Maximum character length is %d and you type %d character",max_length,char_length);
        return 0;
    }

    if(strspn(str, cmp_str) == strlen(str))
    { return 1;

    }
    else
    {
        printf("\nERROR : Invalid character typed ");
        printf("\nINFO  : Valid character set for this input is:\n%s ",cmp_str);
        return 0;
    }
}

/**
* @fn int validate_email(char *str)
* @author Shailesh Sankdasariya
* @brief  This function validate for entered email address string length.
* @param[in] char * str, pointer to string entered by user
* @return  returns 0 on failure and 1 on success
*/

int validate_email(char *str)
{
 char email[20];
 int at_found=0,dot_found=0,at_pos=0,dot_pos=0,last_ch,i;
 int em_valid=0;

 strcpy(email,str);

 for(i=0;((i<20 )&& (email[i] !='\0'));i++)
 {
     if(email[i]=='@')
     {at_found=1;at_pos=i;}

     if(email[i]=='.')
     {dot_found=1;dot_pos=i;}

 }
    last_ch=i;

 if((at_found==1)&&(dot_found==1))
 {
     if(at_pos>1)
     {
         if((dot_pos > at_pos + 1)&&(last_ch!=dot_pos))
         { em_valid = 1; }
     }
 }
return em_valid;

}


/**
* @fn int leap_year(int year)
* @author Gajan Satkunanathan
* @brief  This function gives information about entered year is leap or not.
* @param[in] int year , integer value of the year
* @return  returns 0 if not leap  and 1 if leap
*/

int leap_year(int year)
{
    if((year% 400 == 0) || (year% 4 == 0 && year% 4 != 0))
    {return 1;}
    else
    {return 0;}
}

/**
* @fn long number_of_days(int date, int month, int year)
* @author Christopher Owoicho
* @author Gajan Satkunanathan
* @brief  This function gives information about number of day from entered date details.
* @param[in] int date , integer value of the date
* @param[in] int month , integer value of the month
* @param[in] int year , integer value of the year
* @return  returns long integer number of day
*/
long number_of_days(int date, int month, int year)
{
    long result = 0;
    int i;

    for(i=1; i < year; i++)
    {
        if(leap_year(i))
            result += 366;
        else
            result += 365;
    }

    for(i=1; i < month; i++)
    {
        result += days_in_month[i];

        if(leap_year(year) && i == 2)
            result++;
    }

    result += date;
    return result;
}

/**
* @fn int day_for_date(int date, int month, int year)
* @author Shailesh Sankdasariya
* @author Ritesh Panday
* @brief  This function gives information about day number from entered date details.
* @param[in] int date , integer value of the date
* @param[in] int month , integer value of the month
* @param[in] int year , integer value of the year
* @return  returns int numbers i.e. 0="Monday"; 1= "Tuesday"; 2= "Wednesday"; 3="Thursday"; 4="Friday";5= "Saturday";6="Sunday"
*/

int day_for_date(int date, int month, int year)
{
    int day_no = 0;

    day_no = (date + ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5)
              + (365 * (year + 4800 - ((14 - month) / 12)))
              + ((year + 4800 - ((14 - month) / 12)) / 4)
              - ((year + 4800 - ((14 - month) / 12)) / 100)
              + ((year + 4800 - ((14 - month) / 12)) / 400)
              - 32045)
             % 7;

    return day_no;

    // 0="Monday"; 1= "Tuesday"; 2= "Wednesday"; 3="Thursday"; 4="Friday";5= "Saturday";6="Sunday"
}

/**
* @fn int day_validation(int day_no)
* @author Gajan Satkunanathan
* @brief  This function Validates day to check for weekend.
* @param[in] int day_no , integer value of the day number
* @return  1 if a valid day and 0 if not
*/

int day_validation(int day_no)
{

    if ((day_no>=0)&&(day_no<=4))
    {return 1;}
    else if(day_no==5)
    { if(SATURDAY_ENABLE==1)
        {return 1;}
        else
        {return 0;}
    }
    else if(day_no==6)
    {if(SUNDAY_ENABLE==1)
        {return 1;}
        else
        {return 0;}
    }
    else
    {return 0;}
}


/**
* @fn int date_validation(int date, int month, int year, int mode)
* @author Shailesh Sankdasariya
* @author Ritesh Panday
* @author Christopher Owoicho
* @author Gajan Satkunanathan
* @brief  This function Validates date based on input data entered by user.
* @param[in] int date , integer value of the date
* @param[in] int month , integer value of the month
* @param[in] int year , integer value of the year
* @param[in] int mode , to pass validation check type
* @return  1 if a valid day and 0 if not
*/

int date_validation(int date, int month, int year, int mode)
{
    int Cur_date,Cur_month,Cur_year;
    int Is_date_valid=0,Is_day_valid=0;
    int No_of_day_crntdate,No_of_day_entdate;


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //Extract Current System time
    Cur_year=tm.tm_year + 1900;
    Cur_month=tm.tm_mon + 1;
    Cur_date =tm.tm_mday;

    //printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    //check year validity
    if (year >= MIN_YEAR && year <= MAX_YEAR)
    {
        //check month validity
        if (month>= 1 && month<= 12) {
            //check day validity
            if (date>= 1 && date<= 31)
            {
                if ((date>= 1 && date<= 30) && (month== 4 || month== 6 || month== 9 || month== 11))
                    Is_date_valid=1; //valid date
                else if ((date>= 1 && date<= 31) && (month== 1 || month== 3 || month== 5 || month== 7 || month== 8 || month== 10 || month== 12))
                    Is_date_valid=1;  //valid date
                else if ((date>= 1 && date<= 28) && (month== 2))
                    Is_date_valid=1;  //valid date
                else if (date== 29 && month== 2 && ((year% 400 == 0) || ((year% 4 == 0) && (year% 100 != 0))))
                    Is_date_valid=1;  //valid date
                else
                    Is_date_valid=0;  //invalid day
            }
            else {
                Is_date_valid=0;  //day is invalid
            }
        }
        else {
            Is_date_valid=0;  //month is invalid
        }
    }
    else {
        Is_date_valid=0; //month is invalid
    }

    if(Is_date_valid==0)
    {
        printf("\nERROR : Invalid Date Entered");
        delay_ms(DISPLAY_DELAY);
        printf("\nINFO  : Please Try Again By Entering valid date");
        delay_ms(DISPLAY_DELAY);
        return 0;
    }
    if(Is_date_valid ==1 )
    {
        if(mode == 0)
        {
            No_of_day_crntdate = number_of_days(Cur_date, Cur_month, Cur_year);
            No_of_day_entdate = number_of_days(date, month, year);

            if ((No_of_day_entdate - No_of_day_crntdate) == 0) {
                printf("\nERROR : Invalid Date Entered, You Cannot book appointment for current date");
                delay_ms(DISPLAY_DELAY);
                printf("\nINFO  : Nearest Possible Date for valid Appointment starting from Tomorrow");
                delay_ms(DISPLAY_DELAY);
                return 0;
            } else if ((No_of_day_entdate - No_of_day_crntdate) < 0) {
                printf("\nERROR : Invalid Date Entered, You Cannot book appointment for previous date");
                delay_ms(DISPLAY_DELAY);
                printf("\nINFO  : Nearest Possible Date for valid Appointment starting from Tomorrow");
                delay_ms(DISPLAY_DELAY);
                return 0;
            } else if ((No_of_day_entdate - No_of_day_crntdate) > MAX_DAYS_FOR_BOOK) {
                printf("\nERROR : Invalid Date Entered, You Cannot book appointment beyond %d day", MAX_DAYS_FOR_BOOK);
                delay_ms(DISPLAY_DELAY);
                printf("\nINFO  : Possible valid Appointment starting from Tomorrow till %d days", MAX_DAYS_FOR_BOOK);
                delay_ms(DISPLAY_DELAY);
                return 0;
            } else if (((No_of_day_entdate - No_of_day_crntdate) > 0) &&
                       ((No_of_day_entdate - No_of_day_crntdate) <= MAX_DAYS_FOR_BOOK)) {
                Is_day_valid = day_validation(day_for_date(date, month, year));

                if (Is_day_valid == 0)
                {
                    if ((SATURDAY_ENABLE != 1) && (SUNDAY_ENABLE != 1)) {
                        printf("\nERROR : Invalid Date Entered, You Cannot book appointment on Saturday and Sunday");
                    }
                    else if ((SATURDAY_ENABLE == 1) && (SUNDAY_ENABLE != 1)) {
                        printf("\nERROR : Invalid Date Entered, You Cannot book appointment on Sunday");
                    }
                    else if ((SATURDAY_ENABLE != 1) && (SUNDAY_ENABLE == 1)) {
                        printf("\nERROR : Invalid Date Entered, You Cannot book appointment on Saturday");
                    }

                    delay_ms(DISPLAY_DELAY);
                    printf("\nINFO  : Please Try Again By Entering valid date");
                    delay_ms(DISPLAY_DELAY);
                    return 0;
                }
                if(Is_day_valid==1)
                {

                    return 1;
                }
            }
        }
        else
        {
            return Is_date_valid;
        }
    }
}

/**
* @fn int extract_value(char *tmp_str,int *dd,int *mm,int *yyyy, int mode)
* @author Shailesh Sankdasariya
* @author Christopher Owoicho
* @brief  This function extract date value in date,month and year in integer form from entered string.
* @param[in] int *dd , integer value of the date
* @param[in] int month , integer value of the month
* @param[in] int year , integer value of the year
* @param[in] int mode , to pass validation check type
* @return  1 if a valid date and 0 if not
*/

int extract_value(char *tmp_str,int *dd,int *mm,int *yyyy, int mode)
{
    char tmp_date[5]={0},tmp_month[5]={0},tmp_year[5]={0};
    char tmp_input_date[12]={0};
    int val,i=0,j=0,validation_check;
    int Is_date_valid;
    int date, month, year;

    strcpy(tmp_input_date,tmp_str);

    // Validating input
    validation_check=validate_input(tmp_input_date,DATE_TIME_str,MAX_AP_DT-1,8);
    while(!(validation_check==1))
    {  delay_ms(DISPLAY_DELAY);
        printf("\nERROR : Retry with Inputting Correct character set in Date Format.");
        printf("\nINFO  : Enter Appointment Date Again:");
        delay_ms(DISPLAY_DELAY);
        fflush(stdin);
        return 0;

    }
    delay_ms(DISPLAY_DELAY);

    while((tmp_input_date[j]!= '/')&&(i<5))
    {
        tmp_date[i]= tmp_input_date[j];
        j++;i++;
    }
    i++;tmp_date[i]='\0';
    *dd=atoi(tmp_date);

    j++;i=0;
    while((tmp_input_date[j]!= '/')&&(i<5))
    {
        tmp_month[i]= tmp_input_date[j];
        j++;i++;
    }
    i++;tmp_month[i]='\0';
    *mm=atoi(tmp_month);

    j++;i=0;
    while((tmp_input_date[i]!= '\0')&&(i<5))
    {
        tmp_year[i]=tmp_input_date[j];
        j++;i++;
    }
    *yyyy=atoi(tmp_year);

    date=*dd; month=*mm;year=*yyyy;

    Is_date_valid=date_validation(date, month, year, mode);
    return Is_date_valid;

}