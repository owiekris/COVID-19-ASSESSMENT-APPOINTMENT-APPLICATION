#ifndef DATABASE_H
#define DATABASE_H

#define MAX_USER 500

#define MAX_HL_NO       11
#define MAX_FRS_NM      11
#define MAX_LST_NM      11
#define MAX_PST_CD      10
#define MAX_EMAIL       20
#define MAX_AP_DT       12
#define MAX_AP_TM       10


typedef struct {
    int sr_no;
    char health_number[MAX_HL_NO];
    char first_name[MAX_FRS_NM];
    char last_name[MAX_LST_NM];
    char postal_code[MAX_PST_CD];
    char email[MAX_EMAIL];
    char appointment_date[MAX_AP_DT];
    char appointment_time[MAX_AP_TM];
    int appointment_number;
    int appointment_status;
    char Line_Feed;
} User;

User record[MAX_USER],Ins_user,Fetch_user;

extern int rec_no;

int read_database(int read_rec);
int search_database(int para_no,char *str,int i_val);
int search_database_by_rec(int start_rec,int *end_rec,int para_no,char *str,int i_val);
User load_selected_user(int db_rec_no);
int insert_database(User);
int modify_record(User,int);



#endif
