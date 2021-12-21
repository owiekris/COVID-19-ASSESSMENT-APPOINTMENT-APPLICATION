/**
 * @file receipt.c
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @date 12 December 2021
 * @brief  This file handles task to creating receipt files.
 */

/* Include the required default libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Include all dependencies Files & Folders */
#include "..\include\task.h"
#include "..\include\appointment.h"
#include "..\include\debug.h"
#include "..\include\database.h"
#include "..\include\validation.h"
#include "..\include\user.h"
#include "..\include\receipt.h"

/**
 * @fn void print_receipt(User Fetch_user)
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @brief  This function create a receipt file for booked appointment and show in notepad application.
 * @param[in] User Fetch_user, user profile structure.
 * @return void, no parameter need to specify.
 */
void print_receipt(User cur_user)
{
    FILE* receipt;
    char filename[80] ={0};
    char tmp_str[20]={0};
    char message[200] = {0};
    char cmd[80]={0};

    //Print a confirmation message for the user on-screen
    printf("\n\nHello %s %s, \n\n", cur_user.first_name, cur_user.last_name);
    printf("Success! Your appointment has been booked for Date:%s Time:%s \nYour appointment number is: %d", Fetch_user.appointment_date,
           cur_user.appointment_time, cur_user.appointment_number);
    puts("\n\nThank you for using the COVID-19 appointment booking system!");

    //Create a receipt file using Health Card #
    strcpy(filename,receipt_path);
    strcat(filename,"Rc_");
    strcat(filename,cur_user.health_number);
    strcat(filename, ".txt");

    //To test whether the filename is correct
    //debug_print("File =%s",filename);

    //Write the appointment confirmation message to the receipt file

    strcpy(message, "Hello ");
    strcat(message, cur_user.first_name);
    strcat(message, " ");
    strcat(message, cur_user.last_name);
    strcat(message, ",\n\n");



    strcat(message,"Your appointment has been booked for the date of ");
    strcat(message, cur_user.appointment_date);
    strcat(message," at ");
    strcat(message, cur_user.appointment_time);
    strcat(message,".");
    strcat(message,"\nYour appointment number is ");
    sprintf(tmp_str,"%d",cur_user.appointment_number);
    strcat(message, tmp_str);
    strcat(message,".\n\nThank you for using the COVID-19 appointment booking system!");

    //debug_print("\nMsg =%s",message);

    receipt = fopen(filename,"w"); //Open the receipt file
   // debug_print("\n%s","file opened");
    if (receipt == NULL)
    {
        // Checking file open or not
        printf("\n ERROR :  Receipt file creation Error, File Not created, Check and Try Again");
        exit(0);
    }
    else
    {
       // debug_print("\nMsg=%s",message);
        fprintf(receipt, "%s", message); //Write the message to the receipt file

       // debug_print("\n%s","writing done");
        fclose(receipt); //Close the receipt file

        /*Send command to the compiler to open the receipt file and show it to user*/
        sprintf(cmd, "notepad.exe %s", filename);

        //To test whether the filename is correct
       // debug_print("\nCmd =%s",cmd);
        system(cmd);
    }
}

