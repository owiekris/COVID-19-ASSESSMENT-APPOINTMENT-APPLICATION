/**
 * @file database.c
 * @author Shailesh Sankdasariya
 * @date 30 November 2021
 * @brief  This file handles all database related tasks. It handles reading, writing, and various searching operations.
 */

/* Include all Required Header Files. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* Include all dependencies Files & Folder. */
#include "..\include\task.h"
#include "..\include\appointment.h"
#include "..\include\debug.h"
#include "..\include\database.h"
#include "..\include\validation.h"
#include "..\include\user.h"

/* Global Variable declaration. */
int rec_no = 0;


/**
 * @fn int read_database(int read_rec)
 * @author Shailesh Sankdasariya
 * @brief  This function reads the database to user profile struct from initiated record number.
 * @param[in] int read_rec , starting record number for reading.
 * @return integer record number that is read successfully.
 */

int read_database(int read_rec)
{

    FILE * fp;
    char line[500];
    char file_nm[30];
    char *read_data;
    const char separator[] = ",";

    rec_no=read_rec;
    strcpy(file_nm,FILE_NAME);

    if (file_nm[0]){

        // Opening the database file in read mode
        fp = fopen(file_nm,"r");

        if ( fp == NULL )
        {
            // Checking file open or not
            printf("\n ERROR :  Database file opening Error, File Not Found Check and Try Again");
            exit(0);
        }
        else{

            // Reading Database file and extracting user information.

            while (fgets(line,500,fp)) {
                if(rec_no == 0)
                {
                    read_data = strtok(line,separator);
                    if(!(strcmp(read_data,"Sr_no"))){
                        record[rec_no].sr_no=0;
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Sr_no Read");
                        exit(0);
                    }

                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"Health_Card_No"))){
                        strcpy(record[rec_no].health_number,"health_no");
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Health_Card_No Read");
                        exit(0);
                    }

                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"First_Name"))){
                        strcpy(record[rec_no].first_name,"First_Name");
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at First_Name Read");
                        exit(0);
                    }

                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"Last_Name"))){
                        strcpy(record[rec_no].last_name,"Last_Name");
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Last_Name Read");
                        exit(0);
                    }

                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"Postal_Code"))){
                        strcpy(record[rec_no].postal_code,"P_code");
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Postal_Code Read");
                        exit(0);
                    }

                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"Email_add"))){
                        strcpy(record[rec_no].email,"Email_add");
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Email_add Read");
                        exit(0);
                    }


                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"Appointment_Date"))){
                        strcpy(record[rec_no].appointment_date,"Appnt_date");
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Appointment_Date Read");
                        exit(0);
                    }

                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"Appointment_time"))){
                        strcpy(record[rec_no].appointment_time,"Appnt_time");
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Appointment_time Read");
                        exit(0);
                    }

                    read_data = strtok(NULL,separator);
                    if(!(strcmp(read_data,"Appointment_Number"))){
                        record[rec_no].appointment_number=0;
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Appointment_Number Read");
                        exit(0);
                    }


                    read_data = strtok(NULL,"\n");
                    if(!(strcmp(read_data,"Appointment_status"))){
                        record[rec_no].appointment_status=0;
                    }
                    else{
                        printf("\nERROR :  Incorrect data format Found at Appointment_status Read");
                        exit(0);
                    }

                    rec_no++;
                }
                else
                {

                    read_data = strtok(line,separator);
                    record[rec_no].sr_no=atoi(read_data);

                    read_data = strtok(NULL,separator);
                    strcpy(record[rec_no].health_number,read_data);

                    read_data = strtok(NULL,separator);
                    strcpy(record[rec_no].first_name,read_data);

                    read_data = strtok(NULL,separator);
                    strcpy(record[rec_no].last_name,read_data);

                    read_data = strtok(NULL,separator);
                    strcpy(record[rec_no].postal_code,read_data);

                    read_data = strtok(NULL,separator);
                    strcpy(record[rec_no].email,read_data);

                    read_data = strtok(NULL,separator);
                    strcpy(record[rec_no].appointment_date,read_data);

                    read_data = strtok(NULL,separator);
                    strcpy(record[rec_no].appointment_time,read_data);

                    read_data = strtok(NULL,separator);
                    record[rec_no].appointment_number=atoi(read_data);

                    read_data = strtok(NULL,"\n");
                    record[rec_no].appointment_status=atoi(read_data);

                    if((rec_no<MAX_USER))
                    { rec_no++;}

                }
            }
        }

       // Closing the database file
        fclose(fp);
    }
    else{
        // For checking File path is defined or not
        printf("\n ERROR :  Please Enter Directory For Database File.");
        exit(0);
    }

    return rec_no;
}


/**
 * @fn int search_database(int para_no,char *str,int i_val)
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @brief  This function searches particular field from database with selected member.
 * @param[in] int para_no, inputs parameter number from profile struct field.
 * @param[in] char *str, pointer to string contains string to search.
 * @param[in] int i_val, integer value to search from database.
 * @return non zero integer record number that is searched successfully with entered searching parameter, 0 otherwise.
 */

int search_database(int para_no,char *str,int i_val)
{
    int cmp_val=1,search_rec;

    for(search_rec=1;((search_rec<MAX_USER)&&(cmp_val!=0));search_rec++)
    {

        if(para_no==1)
        {
            cmp_val=strcmp(record[search_rec].health_number,str);
        }
        else if(para_no==2)
        {
            cmp_val=strcmp(record[search_rec].first_name,str);
        }
        else if(para_no==3)
        {
            cmp_val=strcmp(record[search_rec].last_name,str);
        }
        else if(para_no==4)
        {
            cmp_val=strcmp(record[search_rec].postal_code,str);
        }
        else if(para_no==5)
        {
            cmp_val=strcmp(record[search_rec].email,str);
        }
        else if(para_no==6)
        {
            cmp_val=strcmp(record[search_rec].appointment_date,str);
        }
        else if(para_no==7)
        {
            cmp_val=strcmp(record[search_rec].appointment_time,str);
        }
        else if(para_no==8)
        {
            if(record[search_rec].appointment_number==i_val)
            {cmp_val=0; }
        }
        else if(para_no==9)
        {
            if(record[search_rec].appointment_status==i_val)
            {cmp_val=0; }
        }
    }


    if(cmp_val==0)
    {return search_rec-1;}
    else
    {return 0; }
}

/**
 * @fn int search_database_by_rec(int start_rec,int *end_rec,int para_no,char *str,int i_val)
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 * @brief  This function searches particular field from database with staring record number.
 * @param[in] int start_rec, staring record number from where to start searching.
 * @param[in] int *end_rec, pointer to integer record number where searching is done successfully.
 * @param[in] int para_no, inputs parameter number from profile struct field.
 * @param[in] char *str, pointer to string contains string to search.
 * @param[in] int i_val, integer value to search from database.
 * @return non zero integer record number that is searched successfully with entered searching parameter, 0 otherwise.
 */

int search_database_by_rec(int start_rec,int *end_rec,int para_no,char *str,int i_val)
{
    int cmp_val=1,search_rec;
    char search_date[12];

    for(search_rec=start_rec;((search_rec<MAX_USER)&&(cmp_val!=0));search_rec++)
    {  *end_rec=search_rec;

        if(para_no==1)
        {
            cmp_val=strcmp(record[search_rec].health_number,str);
        }
        else if(para_no==2)
        {
            cmp_val=strcmp(record[search_rec].first_name,str);
        }
        else if(para_no==3)
        {
            cmp_val=strcmp(record[search_rec].last_name,str);
        }
        else if(para_no==4)
        {
            cmp_val=strcmp(record[search_rec].postal_code,str);
        }
        else if(para_no==5)
        {
            cmp_val=strcmp(record[search_rec].email,str);
        }
        else if(para_no==6)
        {
            cmp_val=strcmp(record[search_rec].appointment_date,str);
        }
        else if(para_no==7)
        {
            cmp_val=strcmp(record[search_rec].appointment_time,str);
        }
        else if(para_no==8)
        {
            if(record[search_rec].appointment_number==i_val)
            {cmp_val=0; }
        }
        else if(para_no==9)
        {
            if(record[search_rec].appointment_status==i_val)
            {cmp_val=0; }
        }
    }


    if(cmp_val==0)
    {return search_rec-1;}
    else
    {return 0; }
}


/**
 * @fn User load_selected_user(int db_rec_no)
 * @author Gajan Satkunanathan
 * @brief  This function selects a user profile and assigns to a struct profile.
 * @param[in] int db_rec_no, database record number for selecting user profile.
 * @return User structure with update field according to database record number.
 */
User load_selected_user(int db_rec_no)
{
    User temp;
    temp.sr_no=record[db_rec_no].sr_no;
    strcpy(temp.health_number,record[db_rec_no].health_number);
    strcpy(temp.first_name,record[db_rec_no].first_name);
    strcpy(temp.last_name,record[db_rec_no].last_name);
    strcpy(temp.postal_code,record[db_rec_no].postal_code);
    strcpy(temp.email,record[db_rec_no].email);
    strcpy(temp.appointment_date,record[db_rec_no].appointment_date);
    strcpy(temp.appointment_time,record[db_rec_no].appointment_time);
    temp.appointment_number=record[db_rec_no].appointment_number;
    temp.appointment_status=record[db_rec_no].appointment_status;

    return temp;

}


/**
 * @fn int insert_database(User insert_new_user)
 * @author Shailesh Sankdasariya
 * @brief  This function insert a user profile to database file.
 * @param[in] User insert_new_user, user profile structure.
 * @return integer record number in which number user assigned to database.
 */
int insert_database(User insert_new_user)
{

    FILE * fp;
    char tmp_str[20];
    char file_nm[30];
    char read_data[50];
    char c;
    int wrt_sz=0,search_rec=0;

    rec_no=0;
    strcpy(file_nm,FILE_NAME);


     if (file_nm[0]) {

        // open database file with read write access
        fp = fopen(file_nm, "r+");

        if (fp == NULL)
        {
            // Checking file open or not
            printf("\n ERROR :  Database file opening Error, File Not Found Check and Try Again");
            exit(0);
        }
        else
        {
            // searching Database file and extracting user information

            for (c = fgetc(fp); c != EOF; c = fgetc(fp))
            {
                if (c == '\n') // Increment count if this character is newline
                { search_rec++;

                }
            }



            // write data to file
            //debug_print("\n %d",insert_new_user.sr_no);
            itoa(insert_new_user.sr_no,tmp_str,10);
            //debug_print("\n %s",tmp_str);
            strcpy(read_data,tmp_str);strcat(read_data,",");
            //debug_print("\n %s",read_data);
            wrt_sz=fprintf(fp, "%s", read_data);
            //debug_print("\n %s",read_data);

            strcpy(read_data,insert_new_user.health_number);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            strcpy(read_data,insert_new_user.first_name);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            strcpy(read_data,insert_new_user.last_name);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            strcpy(read_data,insert_new_user.postal_code);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            strcpy(read_data,insert_new_user.email);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            strcpy(read_data,insert_new_user.appointment_date);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            strcpy(read_data,insert_new_user.appointment_time);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            itoa(insert_new_user.appointment_number,tmp_str,10);
            strcpy(read_data,tmp_str);strcat(read_data,",");
            wrt_sz=fprintf(fp, "%s", read_data);

            itoa(insert_new_user.appointment_status,tmp_str,10);
            strcpy(read_data,tmp_str);strcat(read_data,"\n");
            wrt_sz=fprintf(fp, "%s", read_data);

            //debug_print("\n %s","data formed");

            if (wrt_sz > 0) { printf("\nINFO  : User Added To Database successfully !!!"); }
            else { printf("\nERROR :  Problem in Adding User to Database!!!"); }

        }

        // close file
        fclose(fp);
    }

    return  (insert_new_user.sr_no);
}


/**
 * @fn int modify_record(User insert_new_user,int record_number)
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 * @brief  This function modify a user profile to database file.
 * @param[in] User insert_new_user, user profile structure.
 * @param[in] int record_number, record number of user profile in database to modified.
 * @return integer record number in which record number user profile is modified in database.
 */
int modify_record(User insert_new_user,int record_number)
{

    FILE * fp;
    FILE * fp_tmp;

    char tmp_str[20];
    char file_nm[30];
    char tmp_file_nm[30];
    char read_data[150];
    char wrt_data[150];
    char c;
    int wrt_sz=0,search_rec=-1;

    rec_no=0;
    strcpy(file_nm,FILE_NAME);
    strcpy(tmp_file_nm,tmp_FILE_NAME);


    if (file_nm[0] && tmp_file_nm[0]) {

        // open database file to read
        fp = fopen(file_nm, "r");
        // open temp database file for write
        fp_tmp = fopen(tmp_file_nm, "w");

        if (fp == NULL || fp_tmp == NULL)
        {
            // Checking file open or not
            printf("\n ERROR :  Database file opening Error, File Not Found Check and Try Again");
            exit(0);
        }
        else
        {



            //debug_print("\n %d",insert_new_user.sr_no);
            itoa(insert_new_user.sr_no,tmp_str,10);
            //debug_print("\n %s",tmp_str);
            strcpy(wrt_data,tmp_str);strcat(wrt_data,",");


            strcpy(read_data,insert_new_user.health_number);strcat(read_data,",");
            strcat(wrt_data,read_data);


            strcpy(read_data,insert_new_user.first_name);strcat(read_data,",");
            strcat(wrt_data,read_data);

            strcpy(read_data,insert_new_user.last_name);strcat(read_data,",");
            strcat(wrt_data,read_data);

            strcpy(read_data,insert_new_user.postal_code);strcat(read_data,",");
            strcat(wrt_data,read_data);

            strcpy(read_data,insert_new_user.email);strcat(read_data,",");
            strcat(wrt_data,read_data);

            strcpy(read_data,insert_new_user.appointment_date);strcat(read_data,",");
            strcat(wrt_data,read_data);

            strcpy(read_data,insert_new_user.appointment_time);strcat(read_data,",");
            strcat(wrt_data,read_data);

            itoa(insert_new_user.appointment_number,tmp_str,10);
            strcpy(read_data,tmp_str);strcat(read_data,",");
            strcat(wrt_data,read_data);

            itoa(insert_new_user.appointment_status,tmp_str,10);
            strcpy(read_data,tmp_str);strcat(read_data,"\n");
            strcat(wrt_data,read_data);

            // Reading Database file and extracting user information,

            while ((fgets(read_data, 150, fp)) != NULL)
            {
                search_rec++;
                // If current line is line to replace
                if (search_rec == record_number)
                {wrt_sz=fputs(wrt_data, fp_tmp);}
                else
                    fputs(read_data, fp_tmp);

            }
              printf("\nINFO  : User Details Noted To Database successfully !!!");

        }

        // close all file
        fclose(fp);
        fclose(fp_tmp);

        //Remove old file
        remove(file_nm);
        //Renaming new file to old file name
        rename(tmp_file_nm, file_nm);
    }

    return  (search_rec);
}

