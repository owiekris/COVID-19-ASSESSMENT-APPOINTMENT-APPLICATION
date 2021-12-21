/**
 * @file test.c
 * @author Ritesh Panday
 * @author Shailesh Sankdasariya
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 *
 * @brief Test various functions using different conditions and output error codes
 * \mainpage This program is designed to test the various functions used in the main code to identify errors in the program and assign error codes to each error.
 * As each function is different, the test cases will vary - but each test will focus on confirming the various issues that could possible arise in the program.
 *
*/

/* Include all libraries & dependencies */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include\tvalidation.h"
#include "include\tuser.h"
#include "include\ttask.h"
#include "include\tdebug.h"
#include "include\tdatabase.h"
#include "include\tappointment.h"
#include "include\treceipt.h"

int main()
{
    int response;
    User tuser;
    char Path[50]={0};
    FILE *fp;

    strcpy(Path,"..\\tresult\\test_results.txt");

    fp= fopen(Path, "a");

    /* Check if the file can be opened */
    if(fp==NULL){
        puts("Unable to open the file");
    }
    else
    {
        /* Start the testing */

		fprintf(fp,"\n\n############################# TESTING STARTED #############################\n");
        fprintf(fp,"\n\n********************Test 1 for Identify_User Function********************\n");
        fprintf(fp,"First we will test with an invalid number (2) \n");
        fprintf(fp,"The expected output is that program will print an error message \n");

        response = identify_user(1);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else{
            fprintf(fp,"Test failed!"); /* Means the program accepted the wrong value */
        }

        fprintf(fp,"\n\n********************Test 2 for Identify_User Function********************\n");
        fprintf(fp,"Now we will test with a negative number (-5) \n");
        fprintf(fp,"The expected output is that program will print an error message \n");

        response = identify_user(2);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 3 for New_User Function********************\n");
        fprintf(fp,"We will test with an invalid length of health card # (01234567890) \n"); /* Max length should be 10, but we're trying with 11 */
        fprintf(fp,"The program should print an error message since the input is of invalid length \n");

        response = new_user(1);
        if(response==0){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 4 for New_User Function********************\n");
        fprintf(fp,"Here we will test with an invalid email address (test@gmail) \n");
        fprintf(fp,"Since the e-mail address is incorrect format, program should print an error message \n");

        response = new_user(2);
        if(response==0){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 5 for Old_User Function********************\n");
        fprintf(fp,"We will test with a new health card number (1122334455) & e-mail address (itsmemario@gmail.com) \n");
        fprintf(fp,"The program should print an error message and ask us to go to new user function \n");

        response = old_user();
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 6 for read_database Function********************\n");
        fprintf(fp,"We will test by providing no file name \n");
        fprintf(fp,"The program should print an error message \n");

        response = read_database(0,1);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 7 for read_database Function********************\n");
        fprintf(fp,"Here we will test by providing wrong file name (datacell.csv)\n");
        fprintf(fp,"The program should print an error message \n");

        response = read_database(0,2);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 8 for Insert_database Function********************\n");
        fprintf(fp,"We will test by providing no file name \n");
        fprintf(fp,"The program should print an error message \n");

        response = insert_database(tuser);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 9 for Task_Request Function********************\n");
        fprintf(fp,"We will test by providing wrong input on lower bound (0) \n");
        fprintf(fp,"The program should print an error message \n");

        response = task_request(1);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 10 for Task_Request Function********************\n");
        fprintf(fp,"We will test by providing wrong input on upper bound (10) \n");
        fprintf(fp,"The program should print an error message \n");

        response = task_request(2);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 11 for screening_task Function********************\n");
        fprintf(fp,"We will test by providing wrong lowercase input (x) \n");
        fprintf(fp,"The program should print an error message \n");

        response = screening_task(1);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 12 for screening_task Function********************\n");
        fprintf(fp,"We will test by providing wrong uppercase input (A) \n");
        fprintf(fp,"The program should print an error message \n");

        response = screening_task(2);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }


        fprintf(fp,"\n\n********************Test 13 for book_appointment Function********************\n");
        fprintf(fp,"We will test by providing wrong input on upper bound (10) \n");
        fprintf(fp,"The program should print an error message \n");

        response = book_appointment(0);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }


        fprintf(fp,"\n\n********************Test 14 for create_report_by_date Function********************\n");
        fprintf(fp,"We will test by providing wrong date which is in the past (10/10/2010) \n");
        fprintf(fp,"The program should print an error message \n");


        response = create_report_by_date();
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }

        fprintf(fp,"\n\n********************Test 15 for manage_appointment Function********************\n");
        fprintf(fp,"We will test by providing an input (10) \n");
        fprintf(fp,"The program should direct us to the main menu. \n");


        response = manage_appointment(1);
        if(response==-1){
            fprintf(fp,"Test passed!");
        }
        else {
            fprintf(fp, "Test failed!");
        }
    }
	
	fprintf(fp,"\n\n############################# TESTING ENDED #############################\n");
	
    /*Tests completed, close file*/
    fclose(fp);
    return 0;
}