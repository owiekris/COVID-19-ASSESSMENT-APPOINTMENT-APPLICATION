/**
 * @file main.c
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 *
 * @brief By Processing input given by user, calling different functions from other files to perform the various
 * tasks related COVID-19 self screening,booking and managing appointment, and create date-wise report for allotted appointments
 * and store all user data in database file.
 * \mainpage This program is designed to fetch user data from excel that is in csv format - comma seperated and based on the data retrieved from the file which will be further seperated and stored in
 * array of structure and this data will be used to implement further functionalities in the application, i.e., identify user, create a new user, retrieve data from a existing/old user, requesting task for user,
 * creating and managing appointment and generating report and receipt for allotted appointment, etc and at the end of each notable operation user details are saved in database.
 * Database file is a .csv containing multiple Users data records. Database File contains the information about Unique Health Card Number, First name, last name, postal code, email, appointment date & time,
 * appointment number and status.
 *
*/


/* Include all Required Header Files. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Include all dependencies Files & Folder. */
#include "include\validation.h"
#include "include\user.h"
#include "include\task.h"
#include "include\debug.h"
#include "include\database.h"
#include "include\appointment.h"
#include "include\receipt.h"


/* Global Variable declaration. */

/**
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 *
 * @brief The main function which distributes various tasks by validating function call, based on input given by user,
 * also keep track of position pointer for user interface.
 *
*/
int main()
{

    char task_req=0;
    int inp_type,record_pointer;
    int Navigation_Cntrl;

    printf("\n\n");
    printf("******************* WELCOME TO COVID-19 SELF SCREENING & APPOINTMENT MANAGEMENT  SYSTEM    *******************");
    printf("\n\n");


    // Identify User based on input entered by user.
    User_Selection:
    inp_type=identify_user();

    while (inp_type == -1)
    {inp_type=identify_user();
    }

    delay_ms(DISPLAY_DELAY);

    if(inp_type==0)
    {record_pointer=old_user();
       if(record_pointer==0)
       {goto User_Selection;}

    }

    if((record_pointer==-1)||(inp_type==1))
    {record_pointer=new_user();
        if(record_pointer==0)
         { goto User_Selection;}

    }

    // Read the database file to refresh the user structure.
    read_database(0);

    if( inp_type != REPORT_CODE) {
        // Load User details based on record number.
        Fetch_user = load_selected_user(record_pointer);

        // Print details of current active user.
        print_active_user_information();

        // Taking User input for requesting task that user want to do .
        Main_menu:
        task_req = task_request();

        // If User Requested Task for booking an appointment.
        if (task_req == 1)
        {
            // Checking that user has already booked appointment.
            if (Fetch_user.appointment_status != 1)
            {
                // Booking an appointment.
                book_appointment(record_pointer);
            }
            else
            {
                printf("\nERROR : User Has already Booked Appointment with Following Details");
                delay_ms(DISPLAY_DELAY);
                printf("\n=============================================================================");
                printf("\nDate:%s Time:%s Appointment Number:%d", Fetch_user.appointment_date,
                       Fetch_user.appointment_time, Fetch_user.appointment_number);
                printf("\n=============================================================================");
                delay_ms(DISPLAY_DELAY);
                printf("\nINFO  : You Can book One Appointment Only.");
                printf("\nINFO  : For Other Option Related To appointment, Choose Manage Appointment Option From Main Menu.");
                delay_ms(DISPLAY_DELAY);

            }
            // To transfer control to main menu
            goto Main_menu;
        }
        // If User Requested Task for Self-screening.
        else if (task_req == 2)
        {
            // Conducting COVID-19 Self-screening assessment and processing the result.
            Navigation_Cntrl = screening_task();
            if ((Navigation_Cntrl == 1) || (Navigation_Cntrl == 2))
            {
                //transfer control to another user selection.
                printf("\nINFO  : Your User session will terminated shortly.");
                printf("\nINFO  : You Can Proceed Further.");
                printf("\nThank You For Using COVID-19 Self-screening Application.\n\n");
                delay_ms(DISPLAY_DELAY);
                goto User_Selection;
            }
            else if (Navigation_Cntrl == 3) { goto Main_menu; }
        }
        // If User Requested Task for Managing already booked appointment.
        else if (task_req == 3)
        {
            // Checking that user has active booked appointment.
            if (Fetch_user.appointment_status == 1)
            {
                manage_appointment(record_pointer);
            } else
            {
                printf("\nERROR : User Has Not Booked any Appointment.");
                delay_ms(DISPLAY_DELAY);
                printf("\nINFO  : You Can Use This Menu after Booking Appointment.");
                printf("\nINFO  : For Option Related To Booking appointment, Choose Book Appointment Option From Main Menu.");
                delay_ms(DISPLAY_DELAY);
            }
            goto Main_menu;
        }
        // If Users Requested Task for Exit their session.
        else if (task_req == 4)
        {
            //transfer control to another user selection.
            goto User_Selection;
        }
        // If Users Requested Task for Exit the application.
        else if (task_req == 5)
        {
            //Exit the application with exit code 1.
            exit(1);

        }
        // On Unwanted exemption generated by system exit application.
        else if (task_req == 0)
        {
            printf("\nERROR :  Unexpected Output Returned Program Will Terminate.");
            exit(0);

        }
    }
    else
    {
        //To create date wise report file for allotted appointment slot.
        create_report_by_date();
        goto User_Selection;
    }


    return 0;

}