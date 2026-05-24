//Name:Salih Okumuş

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Registration{
    int regid;
    char name[81];
    char surname[81];
    char status[81];
    int year;
    char macaddress[81];
}typedef registration;
registration *Load_registrationData( char *,int);
void Display_RegistrationData(registration*,int);
registration *Add_registration(registration* ,int,char *);
void Sort_data(registration*,int);
void data_statistics(registration*,int);
void menu();
int main(int argc, char **argv) {
    char ch;
    int line_count=0;
    char filename[50];
    int selected_num=0;
    strcpy(filename,argv[1]);
    FILE *data_file;
    data_file= fopen(filename,"r");
    while(data_file==NULL){
        printf("Could not open the file");
        printf("\nEnter file name:");
        scanf("%s",filename);
        data_file= fopen(filename,"r");
    }
    while ((ch = fgetc(data_file)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }
    registration *data=Load_registrationData(filename,line_count);
    printf("The following records have been loaded:\n");
    Display_RegistrationData(data,line_count);
    while (selected_num!=4){
        menu();
        printf("Enter your choice:");
        scanf("%d",&selected_num);

        if(selected_num==1){
            data=Add_registration(data,line_count,filename);
            line_count++;
            Display_RegistrationData(data,line_count);
        }
        else if(selected_num==2){
            Sort_data(data,line_count);
        }
        else if(selected_num==3){
            data_statistics(data,line_count);
        }
        else if(selected_num==4) {
            printf("\nBye!");
        }
        else printf("Wrong input!\n");

    }

    fclose(data_file);
    free(data);
    return 0;
}

void menu(void){
    printf("What would you like to do?\n"
           "1-add\n"
           "2-sort\n"
           "3-statistics\n"
           "4-exit\n");
}
registration *Load_registrationData( char *file,int record_size){
    FILE *data_file= fopen(file,"r");

    if(data_file==NULL){
        printf("Could not open the file");
        exit(1);
    }
    registration *data= (registration*)malloc((record_size)*sizeof(registration));
    if(data==NULL){
        printf("Failed to allocate memory");
        exit(1);
    }
    char line[256];
    fgets(line, sizeof(line), data_file);

    for (int i = 0; i < record_size; i++) {
        fscanf(data_file,"%d %s %s %s %d %s",&data[i].regid,data[i].name,data[i].surname,data[i].status,&data[i].year,data[i].macaddress);
    }
    fclose(data_file);
    return data;
}

void Display_RegistrationData(registration* registration_data,int record_size){
    printf("REGID\tNAME\tSURNAME\tSTATUS\t\tYEAR\tDEVICEMACADDRESS\n");
    for (int i = 0; i < record_size; i++) {
        printf("%d\t%s\t%s\t%s\t%d\t%s\n",
               registration_data[i].regid, registration_data[i].name, registration_data[i].surname,
               registration_data[i].status, registration_data[i].year, registration_data[i].macaddress);
    }
}

registration* Add_registration(registration *registration_data, int record_size,char *filename) {
    int i = record_size;
    FILE *data_file= fopen(filename,"a");
    if(data_file==NULL){
        printf("Could not open the file");
        exit(1);
    }
    registration* temp = realloc(registration_data, (record_size + 1) * sizeof(registration));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        free(registration_data);
        exit(1);
    }
    registration_data = temp;

    printf("\nPlease enter the name: ");
    scanf("%s", registration_data[i].name);

    printf("Please enter the surname: ");
    scanf("%s", registration_data[i].surname);

    printf("Please enter the status: ");
    scanf("%s", registration_data[i].status);
    while (strcmp(registration_data[i].status, "Approved") != 0 &&
           strcmp(registration_data[i].status, "Blocked") != 0 &&
           strcmp(registration_data[i].status, "Declined") != 0) {
        printf("This is not valid\n");
        printf("Please enter the status: ");
        scanf("%s", registration_data[i].status);
    }

    printf("Please enter the year: ");
    scanf("%d", &registration_data[i].year);


    printf("Please enter the mac address: ");
    scanf("%s", registration_data[i].macaddress);
    while (strlen(registration_data[i].macaddress) != 17 ||
           registration_data[i].macaddress[2] != ':' ||
           registration_data[i].macaddress[5] != ':' ||
           registration_data[i].macaddress[8] != ':' ||
           registration_data[i].macaddress[11] != ':' ||
           registration_data[i].macaddress[14] != ':') {
        printf("This is not valid\n");
        printf("Please enter the mac address: ");
        scanf("%s", registration_data[i].macaddress);
    }

    registration_data[i].regid = i + 1;
    fprintf(data_file,"\n%d %s %s %s  %d %s",
            registration_data[i].regid,registration_data[i].name,registration_data[i].surname,
            registration_data[i].status,registration_data[i].year,registration_data[i].macaddress);

    printf("\nIt is recorded successfully!\n");
    fclose(data_file);
    return registration_data;
}


void Sort_data(registration* data,int record_size){
    int swapped,swapped2,column_num;
    printf("\nWhich column (1: year, 2: surname)?");
    scanf("%d",&column_num);
    while (column_num!=1&&column_num!=2){
        printf("this is not valid\n");
        printf("Which column (1: year, 2: surname)?");
        scanf("%d",&column_num);
    }
    if(column_num==1){
    do {
        swapped = 0;
        for (int i = 1; i < record_size; i++) {
            if (data[i-1].year > data[i].year) {
                registration temp = data[i];
                data[i] = data[i - 1];
                data[i - 1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);}
    else{
        do {
            swapped2 = 0;
            for (int i = 1; i < record_size; i++) {
                if (strcmp(data[i - 1].surname, data[i].surname) > 0) {

                    registration temp = data[i];
                    data[i] = data[i - 1];
                    data[i - 1] = temp;
                    swapped2 = 1;
                }
            }
        } while (swapped2);
    }
    Display_RegistrationData(data,record_size);
}

void data_statistics(registration* reg_data,int record_size){
    int blocked_num=0,approved_num=0,declined_num=0;
    for (int i = 0; i < record_size; ++i) {
        if(strcmp(reg_data[i].status,"Approved")==0)approved_num++;
        else if(strcmp(reg_data[i].status,"Declined")==0)declined_num++;
        else if(strcmp(reg_data[i].status,"Blocked")==0)blocked_num++;
    }
    printf("summary\n"
           "%d Blocked\n"
           "%d Approved\n"
           "%d Declined\n",blocked_num,approved_num,declined_num);
}