#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "database.h"


int * available_appointment(int date, int month, int year ,int available_slot[] );
void display_available_appointment(int available_slot[]);
int valid_appointment(int available_app[],int selected_appointment);
User allocate_appointment_to_user(int record_pointer,char * input_date,int selected_appointment,int app_status);
void book_appointment(int record_pointer);
void manage_appointment(int record_pointer);
void create_entry(int record_pointer, char *Str);
void create_report_by_date(void);
#endif