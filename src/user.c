/**
 * @file user.c
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 * @date 30 November 2021
 * @brief handles all user related functions, manage different program flow from old and new users
 */

/* Include all Required Header Files. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Include all dependencies Files & Folder. */
#include "..\include\task.h"
#include "..\include\appointment.h"
#include "..\include\debug.h"
#include "..\include\database.h"
#include "..\include\validation.h"
#include "..\include\user.h"

/**
 * @fn int identify_user(void)
 * @author Christopher Owoicho
 * @brief  This function identifies if new or old user or admin.
 * @param[in] void , no parameter needed to specify.
 * @return integer number 1 if new, 0 if old and predefined REPORT_CODE on matching input number
 */

int identify_user(void)
{
    int number;

    printf("\nWelcome, are you a new user? \nIf yes Enter 1,If Existing User then enter 0\n");
    delay_ms(DISPLAY_DELAY);
    printf("\nINFO  : Waiting For User Input:");
    scanf("%d", &number);
    fflush(stdin);

    if((number>=0 && number<=1) || (number == REPORT_CODE))
    {
        return number;
    }
    else
    {
        printf("\nERROR : Invalid Input Value Entered\nTry Again !!!");//user input not recognized, end program
        return -1;
    }
}


/**
 * @fn int new_user(void)
 * @author Christopher Owoicho
 * @brief  This function validate user is new based on entered details.
 * @param[in] void , no parameter needed to specify.
 * @return integer number 1 if new, 0 if not new
 */
int new_user(void)
{


    char User_ip;
    int validation_check=0,em_validation=0;
    int health_rec=0,email_rec=0,found_rec=0,last_rec=0;

    printf("\nWelcome, Please Enter Following Details Prior to proceed further");
    delay_ms(DISPLAY_DELAY);
    printf("\nEnter your 10 digit health card number:");
    delay_ms(DISPLAY_DELAY);
    scanf("%s",Ins_user.health_number);

    //Validate health number & request for re-entry if invalid
    validation_check=validate_input(Ins_user.health_number,ALPHA_NUM_str,MAX_HL_NO-1,MAX_HL_NO-1);
    while(!(validation_check==1))
    {  delay_ms(DISPLAY_DELAY);
        printf("\nRetry with Inputting Correct Number.");
        printf("\nEnter your 10 digit health card number again:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",Ins_user.health_number);
        fflush(stdin);
        validation_check=validate_input(Ins_user.health_number,ALPHA_NUM_str,MAX_HL_NO-1,MAX_HL_NO-1);
    }

    printf("\nEnter Your Registered Email Address:");
    delay_ms(DISPLAY_DELAY);
    scanf("%s",Ins_user.email);
    validation_check=validate_input(Ins_user.email,ALPHA_NUM_SYM_str,MAX_EMAIL-1,5);
    em_validation= validate_email(Ins_user.email);

    //Validate email & request for re-entry if invalid
    while((validation_check != 1)|| (em_validation !=1))
    {   delay_ms(DISPLAY_DELAY);
        printf("\nRetry with Inputting Correct Email Address.");
        printf("\nEnter Your Registered Email Address again:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",Ins_user.email);
        fflush(stdin);
        validation_check=validate_input(Ins_user.email,ALPHA_NUM_SYM_str,MAX_EMAIL-1,5);
        em_validation= validate_email(Ins_user.email);
    }

    read_database(0);
    health_rec=search_database(1,Ins_user.health_number,0);
    email_rec=search_database(5,Ins_user.email,0);

    //check user exist with entered health card and email details
    if((health_rec!=0)&&(email_rec!=0)&&(health_rec==email_rec))
    {
        delay_ms(DISPLAY_DELAY);
        found_rec=health_rec;
        printf("\nINFO  : Existing user found with entered Email Address & Health Card Number at record no %d",found_rec);
        print_user_information(found_rec);
        delay_ms(DISPLAY_DELAY);
        printf("\nWould you like to continue with this Health Card number ?");
        printf("\nEnter Y For yes and Enter N for No:");
        delay_ms(DISPLAY_DELAY);
        scanf("%c",&User_ip);
        fflush(stdin);
        delay_ms(DISPLAY_DELAY);
        while((User_ip!='Y')&&(User_ip!='y')&&(User_ip!='N')&&(User_ip!='n'))
        {
            delay_ms(DISPLAY_DELAY);
            printf("\nERROR : Invalid Input Entered");
            printf("\nINFO  : Retry by Entering Y For yes and Entering N for No:");
            delay_ms(DISPLAY_DELAY);
            scanf("%c",&User_ip);
            fflush(stdin);
        }
        if((User_ip=='Y')||(User_ip=='y'))
        {
            return found_rec;

        }
        else
        {
            delay_ms(DISPLAY_DELAY);
            printf("\n\nINFO  : Please Enter Your Details Again.\n");
            delay_ms(DISPLAY_DELAY);
            return 0;
        }

    }
    //check user is new , by verifying existence with entered health card and email details in database
    else if((health_rec==0)&&(email_rec==0))
    {
        printf("\nEnter Your First Name:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",Ins_user.first_name);
        fflush(stdin);
        validation_check=validate_input(Ins_user.first_name,ALPHA_str,MAX_FRS_NM-1,1);
        while(!(validation_check==1))
        { delay_ms(DISPLAY_DELAY);
            printf("\nRetry with Inputting Correct Number.");
            printf("\nEnter Your First Name again:");
            delay_ms(DISPLAY_DELAY);
            scanf("%s",Ins_user.first_name);
            fflush(stdin);
            validation_check=validate_input(Ins_user.first_name,ALPHA_str,MAX_FRS_NM-1,1);

        }

        printf("\nEnter Your Last Name:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",Ins_user.last_name);
        fflush(stdin);
        validation_check=validate_input(Ins_user.last_name,ALPHA_str,MAX_LST_NM-1,1);
        while(!(validation_check==1))
        {  delay_ms(DISPLAY_DELAY);
            printf("\nRetry with Inputting Correct Number.");
            printf("\nEnter Your Last Name again:");
            delay_ms(DISPLAY_DELAY);
            scanf("%s",Ins_user.last_name);
            fflush(stdin);
            validation_check=validate_input(Ins_user.last_name,ALPHA_str,MAX_LST_NM-1,1);

        }

        printf("\nEnter Your Postal Code with out any space:");
        delay_ms(DISPLAY_DELAY);
        gets(Ins_user.postal_code);
        fflush(stdin);
        validation_check=validate_input(Ins_user.postal_code,ALPHA_NUM_str,MAX_PST_CD-1,3);
        while(!(validation_check==1))
        {  delay_ms(DISPLAY_DELAY);
            printf("\nRetry with Inputting Correct Number.");
            printf("\nEnter Your Postal Code with out any space again:");
            delay_ms(DISPLAY_DELAY);
            gets(Ins_user.postal_code);
            fflush(stdin);
            validation_check=validate_input(Ins_user.postal_code,ALPHA_NUM_str,MAX_PST_CD-1,3);

        }

        last_rec=read_database(0);

        if(last_rec!=0)
        {
            Ins_user.sr_no=last_rec;
            strcpy(Ins_user.appointment_date,"0");strcpy(Ins_user.appointment_time,"0");
            Ins_user.appointment_number=0;Ins_user.appointment_status=0;
            last_rec=insert_database(Ins_user);
            return last_rec;
        }

        return 1;

    }
    // User existed in database with entered Email address.
    else if((health_rec==0)&&(email_rec!=0)&&(health_rec!=email_rec))
    {
        delay_ms(DISPLAY_DELAY);
        printf("\nERROR : No Existing user found with entered Health Card Number");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nINFO  : User Found with Entered Email address");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nPlease Try again By entering Different Email Address with Entered Health Card No");
        delay_ms(DISPLAY_DELAY);
        return 0;
    }
    // User existed in database with entered Health Card Number.
    else if((health_rec!=0)&&(email_rec==0)&&(health_rec!=email_rec))
    {
        delay_ms(DISPLAY_DELAY);
        printf("\nERROR : No Existing user found with entered Email Address");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nINFO  : User Found with Entered Health Card Number");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nPlease Try again By entering Different Health Card Number with Entered Email Address");
        delay_ms(DISPLAY_DELAY);
        return 0;
    }
}


/**
 * @fn int old_user(void)
 * @author Shailesh Sankdasariya
 * @author Gajan Satkunanathan
 * @brief  This function validate user is old or existing based on entered details.
 * @param[in] void , no parameter needed to specify.
 * @return integer number 1 if old, -1 if no record of both email and health card number and 0 if any other error
 */

int old_user(void)
{
    char health_card[MAX_HL_NO];
    char email_address[MAX_EMAIL];
    char User_ip;
    int validation_check=0;
    int health_rec=0,email_rec=0,found_rec=0;

    printf("\nWelcome, Please Enter Following Details Prior to proceed further");
    delay_ms(DISPLAY_DELAY);
    printf("\nEnter your 10 digit health card number:");
    delay_ms(DISPLAY_DELAY);
    scanf("%s",health_card);
    fflush(stdin);

    //Validate health number & request for re-entry if invalid
    validation_check=validate_input(health_card,ALPHA_NUM_str,MAX_HL_NO-1,MAX_HL_NO-1);
    while(!(validation_check==1))
    {  delay_ms(DISPLAY_DELAY);
        printf("\nRetry with Inputting Correct Number.");
        printf("\nEnter your 10 digit health card number again:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",health_card);
        fflush(stdin);
        validation_check=validate_input(health_card,ALPHA_NUM_str,MAX_HL_NO-1,MAX_HL_NO-1);
    }

    printf("\nEnter Your Registered Email Address:");
    scanf("%s",email_address);

    //Validate email & request for re-entry if invalid
    validation_check=validate_input(email_address,ALPHA_NUM_SYM_str,MAX_EMAIL-1,5);
    while(!(validation_check==1))
    {   delay_ms(DISPLAY_DELAY);
        printf("\nRetry with Inputting Correct Number.");
        printf("\nEnter Your Registered Email Address again:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",email_address);
        fflush(stdin);
        validation_check=validate_input(email_address,ALPHA_NUM_SYM_str,MAX_EMAIL-1,5);

    }

    read_database(0);
    health_rec=search_database(1,health_card,0);
    email_rec=search_database(5,email_address,0);

    //if User with existed in database with entered Email and Health Card no
    if((health_rec!=0)&&(email_rec!=0)&&(health_rec==email_rec))
    {
        found_rec=health_rec;
        printf("\nINFO  : Existing user found with entered Email Address & Health Card Number at record no %d",found_rec);
        print_user_information(found_rec);
        delay_ms(DISPLAY_DELAY);
        printf("\nWould you like to continue with this Health Card number ?");
        printf("\nEnter Y For yes and Enter N for No:");
        fflush(stdin);
        delay_ms(DISPLAY_DELAY);
        scanf("%c",&User_ip);
        fflush(stdin);
        delay_ms(DISPLAY_DELAY);

        while((User_ip!='Y')&&(User_ip!='y')&&(User_ip!='N')&&(User_ip!='n'))
        {
            delay_ms(DISPLAY_DELAY);
            printf("\nERROR : Invalid Input Entered");
            delay_ms(DISPLAY_DELAY);
            printf("\nINFO  : Retry by Entering Y For yes and Entering N for No:");
            scanf("%c",&User_ip);
            fflush(stdin);
        }
        if((User_ip=='Y')||(User_ip=='y'))
        {
            return found_rec;

        }
        else
        {
            delay_ms(DISPLAY_DELAY);
            printf("\n\nINFO  : Please Enter Your Details Again.\n");
            delay_ms(DISPLAY_DELAY);
            return 0;
        }

    }
    //No User with existed in database with entered Email and Health Card no.So, It must be new User.
    else if((health_rec==0)&&(email_rec==0))
    {
        printf("\nERROR : No Existing user found with entered Email Address and Health Card Number ");
        printf("\n--------------------------------------------------------");
        printf("\nINFO  : Navigating As New User");

        return -1;

    }
    // User existed in database with entered Email address.
    else if((health_rec==0)&&(email_rec!=0)&&(health_rec!=email_rec))
    {
        delay_ms(DISPLAY_DELAY);
        printf("\nERROR : No Existing user found with entered Health Card Number");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nINFO  : User Exist with Entered Email address");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nHINT  : Please Try again By entering Different Email Address with Entered Health Card No");
        delay_ms(DISPLAY_DELAY);
        return 0;

    }
    // User existed in database with entered Health Card Number.
    else if((health_rec!=0)&&(email_rec==0)&&(health_rec!=email_rec))
    {
        delay_ms(DISPLAY_DELAY);
        printf("\nERROR : No Existing user found with entered Email Address");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nINFO  : User Exist with  Entered Health Card Number");
        printf("\n--------------------------------------------------------");
        delay_ms(DISPLAY_DELAY);
        printf("\nHINT  : Please Try again By entering Different Health Card Number with Entered Email Address");
        delay_ms(DISPLAY_DELAY);
        return 0;
    }
}


/**
* @fn void print_user_information(int user_no)
* @author Shailesh Sankdasariya
* @brief  This function print details of user field based on record number.
* @param[in] int user_no , record no for displaying user information.
* @return void , no parameter needed to specify.
*/
void print_user_information(int user_no)
{
    printf("\n############################################################################");
    printf("\nSr No              :%d",record[user_no].sr_no);
    printf("\nHealth Card No     :%s",record[user_no].health_number);
    printf("\nFirst Name         :%s",record[user_no].first_name);
    printf("\nLast Name          :%s",record[user_no].last_name);
   // printf("\nPostal Code        :%s",record[user_no].postal_code);
    printf("\nEmail              :%s",record[user_no].email);
    // printf("\nAppointment Date   :%s",record[user_no].appointment_date);
    //  printf("\nAppointment Time   :%s",record[user_no].appointment_time);
    //  printf("\nAppointment No     :%d",record[user_no].appointment_number);
    //  printf("\nAppointment Status :%d",record[user_no].appointment_status);
    printf("\n############################################################################");
}


/**
* @fn print_active_user_information (void)
* @author Shailesh Sankdasariya
* @brief  This function print details of current user.
* @param[in] void , no parameter needed to specify.
* @return void , no parameter needed to specify.
*/

void print_active_user_information (void)
{
    printf("\n############################################################################");
    printf("\nDetails For Current Selected User");
    printf("\nSr No              :%d", Fetch_user.sr_no);
    printf("\nHealth Card No     :%s", Fetch_user.health_number);
    printf("\nFirst Name         :%s", Fetch_user.first_name);
    printf("\nLast Name          :%s", Fetch_user.last_name);
    printf("\nPostal Code        :%s", Fetch_user.postal_code);
    printf("\nEmail              :%s", Fetch_user.email);
    printf("\nAppointment Date   :%s", Fetch_user.appointment_date);
    printf("\nAppointment Time   :%s", Fetch_user.appointment_time);
    printf("\nAppointment No     :%d", Fetch_user.appointment_number);
    printf("\nAppointment Status :%d", Fetch_user.appointment_status);
    printf("\n############################################################################");
}

