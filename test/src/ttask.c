/**
 * @file task.c
 * @author Shailesh Sankdasariya
 * @author Gajan Satkunanathan
 * @date 30 November 2021
 * @brief  Contain functions that Executes a Task Requested By User.
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


/**
 * @fn char task_request(void)
 * @author Shailesh Sankdasariya
 * @brief  This function print details of task and request input from user for specific valid task.
 * @param[in] void , no parameter needed to specify.
 * @return valid Value of Task Number that is selected by user.
 */

char task_request(int d)
{
    int user_input;

    //Printing task details
    printf("\n\nPlease Enter Sr No Only associated with task you want to do.");
    printf("\nSr No.        Description Of Task");
    printf("\n  1.          To Book a vaccination appointment.");
    printf("\n  2.          For COVID-19 Self-screening assessment.");
    printf("\n  3.          To Manage your appointment.");
    printf("\n  4.          To Exit from Current User Session.");
    printf("\n  5.          To Exit from Application.");
    delay_ms(DISPLAY_DELAY);

    //Provide test input
    switch(d){
        case 1: user_input=0; break;
        case 2: user_input=10; break;
        default: break;
    };
    fflush(stdin);

    //validating & re-requesting user input
   while((user_input != 1 )&&(user_input != 2)&&(user_input != 3) && (user_input != 4 )&& (user_input != 5 ))
    {   delay_ms(DISPLAY_DELAY);
        printf("\nERROR : Invalid Input Entered");
        return -1;
        fflush(stdin);

    }

    //Displaying confirmation
    switch (user_input)
    {
        case 1:
                printf("\nThank You For Choosing Booking option for a vaccination appointment.");
                printf("\nPlease wait while we are searching empty slot for you.");
                break;
        case 2:
                printf("\nThank You For Choosing option for COVID-19 Self-screening assessment.");
                break;
        case 3:
                printf("\nThank You For Choosing Managing option for a vaccination appointment.");
                break;
        case 4:
                printf("\nThank you for using application \nYour User Session will terminate shortly.");
                break;
        case 5:
            printf("\nThank you for using application \nProgram will terminate shortly.");
            break;
        default:
                printf("\nERROR : Invalid User Entry.");
                break;
    }

    if( user_input >= 1 && user_input<= 5)
    {return (char)user_input;}
    else
    {return 0;}
}


/**
 *
 * @fn int screening_task(void)
 * @author Gajan Satkunanathan
 * @brief  This function takes user response to screening questions
 * @param[in] void , no parameter needed to specify.
 * @return integer number 1 if appointment to see doctor is required, 2 if user got a green mark and 3 if user asymptomatic.
 */

int screening_task(int e)
{
    char answer;
    //Provide test input
    switch(e){
        case 1: answer='x'; break;
        case 2: answer='A'; break;
        default: break;
    };

    while((answer!='Y')&&(answer!='y')&&(answer!='N')&&(answer!='n'))
    {
        delay_ms(DISPLAY_DELAY);
        printf("\nERROR : Invalid Input Entered");
        return -1;
        fflush(stdin);
    }

    if ((answer == 'Y') || (answer == 'y'))
    {
        printf("\nContact either your health care provider or Telehealth Ontario (1-866-797-0000) to get advice or assessment,\nincluding if you need a COVID-19 test.\n");
        return 1;

    }else if ((answer == 'N') || (answer == 'n'))
    {
        printf("\nHas a doctor, health care provider, or public health unit told you that you should be currently isolating\n(staying at home)?");
        delay_ms(DISPLAY_DELAY);
        printf("\nPlease Enter your Response by entering Y for Yes, N for No :");
        scanf("%c", &answer);
        fflush(stdin);

        while((answer!='Y')&&(answer!='y')&&(answer!='N')&&(answer!='n'))
        {
            delay_ms(DISPLAY_DELAY);
            printf("\nERROR : Invalid Input Entered");
            delay_ms(DISPLAY_DELAY);
            printf("\nPlease Enter your Response by entering Y for Yes, N for No :");
            scanf("%c", &answer);
            fflush(stdin);
        }

        if ((answer == 'Y') || (answer == 'y'))
        {
            printf("\nContact either your health care provider or Telehealth Ontario (1-866-797-0000) to get advice or assessment,\nincluding if you need a COVID-19 test.\n");
            return 1;
        }else if ((answer == 'N') || (answer == 'n'))
        {
            printf("\nDo you like with someone who has been told by a doctor, health care provider,\nor public health unit that they should currently be in isolation?");
            delay_ms(DISPLAY_DELAY);
            printf("\nPlease Enter your Response by entering Y for Yes, N for No :");
            scanf("%c", &answer);
            fflush(stdin);

            while((answer!='Y')&&(answer!='y')&&(answer!='N')&&(answer!='n'))
            {
                delay_ms(DISPLAY_DELAY);
                printf("\nERROR : Invalid Input Entered");
                delay_ms(DISPLAY_DELAY);
                printf("\nPlease Enter your Response by entering Y for Yes, N for No :");
                scanf("%c", &answer);
                fflush(stdin);
            }

            if ((answer == 'Y') || (answer == 'y'))
            {
                printf("\nContact either your health care provider or Telehealth Ontario (1-866-797-0000) to get advice or assessment,\nincluding if you need a COVID-19 test.\n");
                return 1;
            }else if ((answer == 'N') || (answer == 'n'))
            {
                printf("\nAre you vaccinated with both doses of vaccine approved by Government of Canada ?");
                delay_ms(DISPLAY_DELAY);
                printf("\nPlease Enter your Response by entering Y for Yes, N for No :");
                scanf("%c", &answer);
                fflush(stdin);

                while((answer!='Y')&&(answer!='y')&&(answer!='N')&&(answer!='n'))
                {
                    delay_ms(DISPLAY_DELAY);
                    printf("\nERROR : Invalid Input Entered");
                    delay_ms(DISPLAY_DELAY);
                    printf("\nPlease Enter your Response by entering Y for Yes, N for No :");
                    scanf("%c", &answer);
                    fflush(stdin);
                }
                if ((answer == 'Y') || (answer == 'y'))
                {
                    printf("\nYou Got a Green Mark !!!\nYou are Good to Go.\nThank You For Using Our Assessment Application.");
                    return 2;
                }else if ((answer == 'N') || (answer == 'n'))
                {
                   printf("\nUser is asymptomatic,We recommended you to take both doses of vaccine.\nyou can proceed with the Vaccination Appointment Booking in Main menu.");
                    return 3;
                }
            }
        }
    }
}