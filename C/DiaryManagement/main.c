#include <stdio.h>
#include "appointment.h"

int main() {

    int action = -1;

    int size = 10, blocksize = 4;
    DiaryManagement* dptr;
    Meeting* meeting1;

    float startTime, endTime;
    int roomNumber;
    char fileName[20];

    dptr = DiaryManagementCreate(size, blocksize);

    while(action != 9) {
    
    printf("Please choose one of the following options:\n");
    printf("1. Create Meeting\n");
    printf("2. Remove meeting\n");
    printf("3. Find Meeting\n");
    printf("4. Delete Meeting\n");
    printf("5. Save all meetings to file\n");
    printf("6. Load meeting from file to Diary array\n");
    printf("7. Print all appointments\n");
    printf("9. exit\n");

        scanf("%d", &action);

        switch(action) {

        case 1:
            printf("Create meeting:\nplease choose start time: ");
            scanf("%f", &startTime);
            printf("End Time: ");
            scanf("%f", &endTime);
            printf("Room number: ");
            scanf("%d", &roomNumber);
            meeting1 = CreateMeeting(startTime, endTime, roomNumber);
            InsertMeetingToAD(dptr,meeting1);

            if(meeting1 == NULL) {
                printf("meeting was failed to be created\nplease try again :(");
                break;
            } else {
                printf("Meeting was created successfully.\n");
                break;
                }
        case 2:
            printf("Remove Meeting:\nplease enter the start time of the meeting: ");
            scanf("%f", &startTime);
            if(!RemoveMeeting(dptr, startTime)) {
                printf("Meeting was deleted successfully.\n");
            } else {
                printf("meeting was not found.\n");
            }
            break;
        case 3:
            printf("Find meeting by start time, please insert: ");
            scanf("%f", &startTime);
            if(FindAppointment(dptr, startTime) == NOT_FOUND) {
                printf("Appointment doesn't exist\n");
            } else {
                printf("Appointment exist");
            }
            break;
        case 4: 
            printf("deleting Diary..\n");
            if(DestroyAD(dptr) == OK) {
                printf("AD deleted successfully.\n");
            } else {
                printf("Deletion failed..\n");
            }
            break;
        case 5:
            printf("insert the file name you want to save to: ");
            scanf("%s", &fileName);
            if(SaveToFile(dptr, fileName) == OK) {
                printf("File saved successfully\n");
            } else {
                printf("FAILED TO SAVE FILE\n");
            }
            break;
        case 6:
            printf("insert the file name you want to load: ");
            scanf("%s", &fileName);
            printf("Loading File..");
            dptr = LoadfromFile(dptr, fileName);

            if(dptr != NULL) {
                printf("file was loaded successfully.\n");
            } else {
                printf("FAILED TO LOAD FILE");
            }
            break;
        case 7:
            printf("Printing all appoointments:\n");
            if(PrintAD(dptr) == OK) {
                break;
            } else {
                printf("no meetings found\n");
            }
            break;
        case 9:
            printf("Bye.. :P\n");
            action = 9;    
        }
            
    }

    return 0;
}