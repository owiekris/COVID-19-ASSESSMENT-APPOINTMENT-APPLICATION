/**
 * @file appointment.c
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @date 9 December 2021
 * @brief  This file handles all appointment related tasks. It checks and returns available time slots to users.
 * It displays the available slots that can select based on entered date by user.
 * It ensures selected appointment date is not already picked by another user.
 * It creates a report showing selected date appointments and prints to a file.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "..\include\appointment.h"
#include "..\include\debug.h"
#include "..\include\database.h"
#include "..\include\validation.h"
#include "..\include\user.h"
#include "..\include\receipt.h"

/**
 * @fn int * available_appointment(int date, int month, int year ,   int available_slot[] )
 * @author Shailesh Sankdasariya
 * @brief This function returns integer pointer to an array, array consist of an available slot number based on selected date.
 * @param[in] int date , integer value of date
 * @param[in] int month, integer value of month
 * @param[in] int year , integer value of year
 * @param[in] int pointer to available_slot[], array for getting list of element of available appointment number in sorted form.
 *
 * @return pointer to integer array consist of element having available appointment slot
 */
int * available_appointment(int date, int month, int year ,  int available_slot[] )
{
    int used_slot[28]={0};
    int max_app_slot=28;
    char search_date[12],slot_used=0;
    int start_rec_no=0,end_rec_no=0,find_rec_no=0;
    int slot_no=0,search_slot_no=1,av_slot_no=0,i=0;

    //Creating date in dd/mm/yyyy format
    sprintf(search_date,"%02d/%02d/%04d",date,month,year);


    //Searching all the record
    while(end_rec_no<MAX_USER-1)
    {
        //Finding record number of user, having the same appointment date & search date
        find_rec_no=search_database_by_rec(start_rec_no,&end_rec_no,6,search_date,0);

        //Extracting the status of appointment,0=not allotted; 1=booked ; 2=cancelled
       if(record[find_rec_no].appointment_status==1)
       {used_slot[slot_no]=record[find_rec_no].appointment_number;
           slot_no++;
       }
        start_rec_no=find_rec_no+1;
    }

    // Creating sorted available appointment array by deducting used appointment
    for(search_slot_no=1;search_slot_no<max_app_slot;search_slot_no++)
    {
        for(i=0;((i<max_app_slot)&&(used_slot[i] != '\0'));i++)
        {
            if(search_slot_no == used_slot[i])
            { slot_used=1;}
        }

        if(slot_used==1)
        {
            slot_used=0;
        }else
        {
            available_slot[av_slot_no]=search_slot_no;
             av_slot_no++;
        }
    }
    available_slot[av_slot_no]='\0';

 return available_slot;

}

/**
 * @fn void display_available_appointment(int available_slot[])
 * @author Shailesh Sankdasariya
 * @brief This function displays a list of available appointment along with slot number and time.
 * @param[in] int pointer to available_slot[], array holding elements of available appointment number in sorted form.
 * @return no return value
 */
void display_available_appointment(int available_slot[])
{
    int pos=0,j=0;
    printf("\n##################################################################################");
    printf("\nSlot No.       Time ");  printf("          ");  printf("Slot No.       Time "); printf("          ");  printf("Slot No.       Time ");

    while(((available_slot[j])!='\0')&&(j<28))
    {
        if ((available_slot[j] >= 1) && (available_slot[j] < 10) && (pos==0))
        {printf("\n %d.   =======> %s", available_slot[j],appnt_slot[ available_slot[j]]); printf("          "); }
        else if ((available_slot[j] >= 1) && (available_slot[j] < 10) && (pos == 1))
        {printf(" %d.   =======> %s", available_slot[j],appnt_slot[ available_slot[j]]); printf("          "); }
        else if ((available_slot[j] >= 1) && (available_slot[j] < 10) && (pos == 2))
        {printf(" %d.   =======> %s", available_slot[j],appnt_slot[ available_slot[j]]); printf("          "); }



        if ((available_slot[j] >= 10) && (available_slot[j] < 28) && (pos==0))
        {printf("\n %d.  =======> %s", available_slot[j],appnt_slot[ available_slot[j]]); printf("          "); }
        else if ((available_slot[j] >= 10) && (available_slot[j] < 28) && (pos == 1))
        {printf(" %d.  =======> %s", available_slot[j],appnt_slot[ available_slot[j]]); printf("          "); }
        else if ((available_slot[j] >= 10) && (available_slot[j] < 28) && (pos == 2))
        {printf(" %d.  =======> %s", available_slot[j],appnt_slot[ available_slot[j]]); printf("          "); }

        pos++;j++;
        if(pos>2)
        {pos=0;}

    }

    printf("\n##################################################################################");
}


/**
 * @fn int valid_appointment(int available_app[],int selected_appointment)
 * @author Shailesh Sankdasariya
 * @brief This function returns an integer to validate that the selected appointment number is not valid or note according to available slot array.
 * @param[in] int pointer to available_slot[], array holding elements of available appointment number in sorted form.
 * @param[in] int selected_appointment, appointment number selected by user.
 * @return integer 0 if not valid and 1 if valid.
 */

int valid_appointment(int available_app[],int selected_appointment)
{
    int j=0,Is_valid=0;

    while(((available_app[j])!='\0')&&(j<28))
    {
        if(available_app[j] == selected_appointment)
        {Is_valid=1;break;}
      j++;
    }

    return Is_valid;
}

/**
 * @fn User allocate_appointment_to_user(int db_rec_no,char * input_date,int selected_appointment,int app_status)
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @brief This function allocates the booked appointment date,appointment number and appointment status to the struct profile of the user.
 * @param[in] int db_rec_no, record number of user.
 * @param[in] char * input_date, pointer to date string for appointment date.
 * @param[in] int selected_appointment, appointment number selected by user.
 * @param[in] int app_status, appointment status selected by user/function call.
 * @return User structure with all updated field.
 */

User allocate_appointment_to_user(int db_rec_no,char * input_date,int selected_appointment,int app_status)
{
    User temp;
    temp.sr_no=record[db_rec_no].sr_no;
    strcpy(temp.health_number,record[db_rec_no].health_number);
    strcpy(temp.first_name,record[db_rec_no].first_name);
    strcpy(temp.last_name,record[db_rec_no].last_name);
    strcpy(temp.postal_code,record[db_rec_no].postal_code);
    strcpy(temp.email,record[db_rec_no].email);
    strcpy(temp.appointment_date,input_date);
    temp.appointment_number=selected_appointment;
    strcpy(temp.appointment_time,appnt_slot[selected_appointment]);
    temp.appointment_status=app_status;

    return temp;

}


/**
 * @fn void book_appointment(int record_pointer)
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 * @brief This function initiate the booking appointment task to selected user.
 * @param[in] int record_pointer, record number of user.
 * @return no return value
 */

void book_appointment(int record_pointer)
{
    int valid_date;
    int en_date,en_month,en_year;
    int selected_appointment,validate_appointment;
    int available_app[28]={0};
    int *avai_appoint;
    char input_date[12];

    // Requesting date input for booking appointment
    printf("\nPlease Enter your date in DD/MM/YYYY format:");
    scanf("%s",input_date);
    fflush(stdin);

    // Validate input date, whether entered date is correct or not
    valid_date=extract_value(input_date,&en_date,&en_month,&en_year, 0);

    // requesting further till user enter valid appointment date
    while(!(valid_date==1))
    {  delay_ms(DISPLAY_DELAY);
        printf("\nERROR : Retry with Inputting Correct Date Format.");
        printf("\nINFO  : Enter Valid Appointment Date in DD/MM/YYYY format Again:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",input_date);
        delay_ms(DISPLAY_DELAY);
        fflush(stdin);
        valid_date=extract_value(input_date,&en_date,&en_month,&en_year, 0);
    }

    // getting available appointment numbers based on entered date
    avai_appoint=available_appointment(en_date, en_month, en_year,available_app);

    // Displaying available appointment numbers based on entered date
    display_available_appointment(avai_appoint);

    // Requesting Slot Number for appointment booking to user
    printf("\nPlease Enter Slot No only from above displayed Slot Numbers:");
    scanf("%d",&selected_appointment);
    delay_ms(DISPLAY_DELAY);
    fflush(stdin);
    printf("\nAppointment No = %d and Time slot= %s is selected",selected_appointment,appnt_slot[selected_appointment]);

    // Validating selected appointment
    validate_appointment=valid_appointment(avai_appoint,selected_appointment);

    // requesting further till user enter valid appointment number
    while(!(validate_appointment==1))
    {  delay_ms(DISPLAY_DELAY);
        printf("\nERROR : Retry with Inputting Correct Slot Number.");
        printf("\nINFO  : Enter Valid Slot No from above displayed slot:");
        delay_ms(DISPLAY_DELAY);
        scanf("%d",&selected_appointment);
        delay_ms(DISPLAY_DELAY);
        fflush(stdin);
        printf("\nAppointment No = %d  and Time slot= %s is selected",selected_appointment,appnt_slot[selected_appointment]);
        validate_appointment=valid_appointment(available_app,selected_appointment);
    }

    // allocated appointment to user
    Fetch_user=allocate_appointment_to_user(record_pointer,input_date,selected_appointment,1);

    // Modifying database based on appointment
    modify_record(Fetch_user,record_pointer);

    //Create Receipt File for Appointment
    print_receipt(Fetch_user);

    // reading database
    read_database(0);
}

/**
 * This function manages the booked appointment for the user by either canceling and booking a new one or return to main function.
 * @param record_pointer inputs an integer input to signify decision from user
 */

/**
 * @fn void manage_appointment(int record_pointer)
 * @author Shailesh Sankdasariya
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 * @brief This function manages the booked appointment for the user by either canceling and booking a new one or return to main function.
 * @param[in] int record_pointer, record number of current user.
 * @return no return value
 */
void manage_appointment(int record_pointer)
{

    int input;

    printf("\nINFO  : User Has Booked Appointment with Following Details.");
    delay_ms(DISPLAY_DELAY);

    //Displaying current details of user along with appointment & taking user input for appointment related task.
    print_active_user_information();
    delay_ms(DISPLAY_DELAY);
    printf("\nINFO  : To Cancel This Appointment Enter 1.");
    printf("\nINFO  : To Return to main menu Enter any keys except 1");
    delay_ms(DISPLAY_DELAY);
    printf("\nINFO  : Waiting For User Response:");
    scanf("%d",&input);
    delay_ms(DISPLAY_DELAY);
    fflush(stdin);

    //On cancellation input of appointment
    if(input==1)
    {
        printf("\nINFO  : Your Appointment is cancelled, You can book new appointment from main menu.");
        Fetch_user.appointment_status=2;
        modify_record(Fetch_user,record_pointer);
        read_database(0);
    }
    else
    {
        delay_ms(DISPLAY_DELAY);
        printf("\nINFO  : Returning To Main Menu.");
    }
}

/**
 * @fn void create_entry(int record_pointer, char *Str)
 * @author Ritesh Panday
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 * @brief This function creates a string ready for entry in the database file.
 * @param[in] int record_pointer, record number of current user.
 * @param[in,out] char *Str, pointer to formatted string which ready to entered in database.
 * @return no return value
 */

void create_entry(int record_pointer, char *Str)
{
    char wrt_data[150]={0};
    char read_data[40]={0};
    char tmp_str[8]={0};

    itoa(record[record_pointer].sr_no,tmp_str,10);
    strcpy(wrt_data,tmp_str);strcat(wrt_data,",");

    strcpy(read_data,record[record_pointer].health_number);strcat(read_data,",");
    strcat(wrt_data,read_data);


    strcpy(read_data,record[record_pointer].first_name);strcat(read_data,",");
    strcat(wrt_data,read_data);

    strcpy(read_data,record[record_pointer].last_name);strcat(read_data,",");
    strcat(wrt_data,read_data);

    strcpy(read_data,record[record_pointer].postal_code);strcat(read_data,",");
    strcat(wrt_data,read_data);

    strcpy(read_data,record[record_pointer].email);strcat(read_data,",");
    strcat(wrt_data,read_data);

    strcpy(read_data,record[record_pointer].appointment_date);strcat(read_data,",");
    strcat(wrt_data,read_data);

    strcpy(read_data,record[record_pointer].appointment_time);strcat(read_data,",");
    strcat(wrt_data,read_data);

    itoa(record[record_pointer].appointment_number,tmp_str,10);
    strcpy(read_data,tmp_str);strcat(read_data,",");
    strcat(wrt_data,read_data);

    itoa(record[record_pointer].appointment_status,tmp_str,10);
    strcpy(read_data,tmp_str);strcat(read_data,"\n");
    strcat(wrt_data,read_data);

    strcpy(Str,wrt_data);
}


/**
 * @fn void create_report_by_date(void)
 * @author Shailesh Sankdasariya
 * @author Christopher Owoicho
 * @author Gajan Satkunanathan
 * @brief This function creates report as a file for allocated appointment for appointments having inputted date .
 * @param[in] void , no input parameter need to specify.
 * @return no return value
 */

void create_report_by_date(void)
{
    FILE * fp;

    char tmp_str[30]={0};
    char file_nm[30]={0};
    char wrt_data[150]={0};
    char read_data[150]={0};


    int max_app_slot=28;
    char search_date[12];
    int start_rec_no=1,end_rec_no=0,find_rec_no=0;
    int slot_no=0,total_appoint=0;

    int valid_date;
    int date,month,year;
    char input_date[12];


    // Requesting date for creating report
    printf("\nPlease Enter Report date in DD/MM/YYYY format:");
    scanf("%s",input_date);
    fflush(stdin);

    // validating date input entered by user
    valid_date=extract_value(input_date,&date,&month,&year, 1);

    // requesting further till user enter valid date
    while(valid_date != 1)
    {  delay_ms(DISPLAY_DELAY);
        printf("\nERROR : Retry with Inputting Correct Date Format.");
        printf("\nINFO  : Enter Valid Appointment Date in DD/MM/YYYY format Again:");
        delay_ms(DISPLAY_DELAY);
        scanf("%s",input_date);
        delay_ms(DISPLAY_DELAY);
        fflush(stdin);
        valid_date=extract_value(input_date,&date,&month,&year, 1);
    }

    // creating string for report file name

    sprintf(tmp_str,"report_%02d_%02d_%04d",date,month,year);
    strcpy(file_nm,report_path);
    strcat(file_nm,tmp_str);
    strcat(file_nm,".csv");

    // reading database
    read_database(0);

    if (file_nm[0])
    {
        // Opening file with write mode
        fp = fopen(file_nm, "w");

        if (fp == NULL)
        {
            // checking file is opened or not
            printf("\n ERROR :  Problem with Creating Report File, Please Try Later.");
            exit(0);
        } else
        {

            strcpy(wrt_data,"Sr_no,Health_Card_No,First_Name,Last_Name,Postal_Code,Email_add,Appointment_Date,Appointment_time,Appointment_Number,Appointment_status\n");
            fputs(wrt_data, fp);

            sprintf(search_date,"%02d/%02d/%04d",date,month,year);

            // Searching and printing appointment from database to file
            for(slot_no=1;slot_no<max_app_slot;slot_no++)
            {
                while (end_rec_no < MAX_USER - 1)
                {
                    find_rec_no = search_database_by_rec(start_rec_no, &end_rec_no, 6, search_date, 0);
                     if (((record[find_rec_no].appointment_status == 1) ||(record[find_rec_no].appointment_status == 2))&&(record[find_rec_no].appointment_number==slot_no))
                    {
                        create_entry(find_rec_no,read_data);
                        strcpy(wrt_data,read_data);
                        fputs(wrt_data, fp);
                        total_appoint++;

                    }
                    start_rec_no = find_rec_no + 1;
                }
                start_rec_no=1;end_rec_no=0;
            }

        }
        // close file
        fclose(fp);
    }
    //Printing acknowledgement
    printf("\n INFO :  Report Created Successfully, Total %d appointment Exist on Date %s.",total_appoint,input_date);

}