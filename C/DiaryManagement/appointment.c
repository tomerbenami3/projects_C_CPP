#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "appointment.h"

DiaryManagement* DiaryManagementCreate(signed int size, int blockSize) {

        if(size == 0 && blockSize == 0) {
        return NULL;
    }

    DiaryManagement* dptr;
    dptr = (DiaryManagement*)malloc(sizeof(DiaryManagement));

    if(dptr == NULL) {
    return NULL;
    }

    dptr->AD = (Meeting**)malloc(size*sizeof(Meeting));

    if(dptr->AD == NULL) {
        free(dptr);
        return NULL;
    }

    dptr->dArrayBlockSize = blockSize;
    dptr->dArraySize = size;
    dptr->NumOfMeetings = 0;

    return dptr;

}

Meeting* CreateMeeting(float startTime, float endTime, int room) {

    if(endTime < startTime) {
        return NULL;
    }

    Meeting* mptr;
    mptr = (Meeting*)malloc(sizeof(Meeting));

    if(mptr == NULL) {
        return mptr;
    }

    mptr->startTime = startTime;
    mptr->endTime = endTime;
    mptr->room = room;

    return mptr;
}

int OverlapCheck(DiaryManagement* dptr, Meeting* meeting) {

    for(int i = 0; i < dptr->NumOfMeetings; ++i) {
        if(meeting->startTime > dptr->AD[i]->startTime && meeting->startTime < dptr->AD[i]->endTime) {
            return 1;
        }
        if (meeting->endTime > dptr->AD[i]->startTime && meeting->endTime < dptr->AD[i]->endTime) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void InsertToAD(DiaryManagement* dptr, Meeting* meeting) {

    int i;

    if(dptr == NULL || meeting == NULL) {
        return;
    }

    // if(OverlapCheck(dptr,meeting)) {
    //     printf("OVERLAP\n");
    //     // return;
    // }

    dptr->AD[dptr->NumOfMeetings] = meeting;
    ++(dptr->NumOfMeetings);

    for(i = 0; i < dptr->NumOfMeetings - 1; i++) {

        if(meeting->startTime < dptr->AD[i]->startTime) {
            for(int j = i + 1; j < dptr->NumOfMeetings; ++j) {
                dptr->AD[j] = dptr->AD[j-1];
            }
            dptr->AD[i] = meeting;
            return;
        }
    }
}

int InsertMeetingToAD(DiaryManagement* dptr, Meeting* meeting) {

    Meeting* temp;

    if(dptr == NULL || meeting == NULL) {
        return NULL_ERROR;
    }

    if(dptr->dArrayBlockSize == 0) {
        return OVERFLOW;
    }

    if(dptr->NumOfMeetings == dptr->dArraySize) {
        temp = realloc(dptr->AD, (dptr->dArraySize + dptr->dArrayBlockSize)*sizeof(int));

        if (temp != NULL) {
        dptr->AD[dptr->NumOfMeetings] = temp;
        } else if (temp == NULL) {
            return REALOC_FAILED;
        }

        dptr->dArraySize += dptr->dArrayBlockSize;
    }

    InsertToAD(dptr, meeting);

    return OK;
}

int RemoveMeeting(DiaryManagement *dptr, float data) {

    if(dptr == NULL) {
        return NULL_ERROR;
    }

    for(int i = 0; i < dptr->NumOfMeetings - 1; ++i) {
        if(dptr->AD[i]->startTime == data) {
            for(int j = i; j < dptr->NumOfMeetings - 1; ++j) {
                dptr->AD[j] = dptr->AD[j+1];
            }
            dptr->NumOfMeetings -= 1;
            return OK;
        }
    }
    return OK;
}

int FindAppointment(DiaryManagement* dptr, float data) {

    if(dptr == NULL) {
        return NULL_ERROR;
    }

    for(int i = 0; i < dptr->NumOfMeetings; ++i) {
        if(dptr->AD[i]->startTime == data) {
            PrintMeeting(dptr->AD[i]);
            return OK;
        }
    }
    return NOT_FOUND;
}

int DestroyAD(DiaryManagement* dptr) {

    if(dptr == NULL) {
        return NULL_ERROR;
    }

    for(int i = 0; i < dptr->NumOfMeetings - 1; ++i) {
        free(dptr->AD[i]);
    }

    free(dptr);

    return OK;
}

int SaveToFile(DiaryManagement* dptr, char* name) {

    FILE* fp;

    fp = fopen(name, "w");

    if(fp == NULL) {
        return NULL_ERROR;
    }

    fprintf(fp,"%d\t%d\t%d\n",dptr->dArraySize,dptr->dArrayBlockSize,dptr->NumOfMeetings);

    for(int i = 0; i < dptr->NumOfMeetings - 1; ++i) {
        fprintf(fp, "%.2f\t%.2f\t%d\n", dptr->AD[i]->startTime, dptr->AD[i]->endTime, dptr->AD[i]->room);
    }

    fclose(fp);

    return OK;
}

DiaryManagement* LoadfromFile(DiaryManagement* dptr, char* fileName) {

    FILE* fp;
    Meeting* tempMeeting;
    DiaryManagement* tempDiary;

    int i, dArraysize, dArrayBlockSize, NumOfMeetings, room;
    float startTime, endTime;

    fp = fopen(fileName, "r");

    if(fp == NULL) {
        return NULL;
    }

    fscanf(fp, "%d\t%d\t%d", &dArraysize, &dArrayBlockSize, &NumOfMeetings);

    tempDiary = DiaryManagementCreate(dArraysize, dArrayBlockSize);
    tempDiary->NumOfMeetings = 0;

    if(tempDiary == NULL) {
        return NULL;
    }

    for(i = 0; i < NumOfMeetings - 1; ++i) {
        fscanf(fp, "%f\t%f\t%d\n", &startTime, &endTime, &room);
        tempMeeting = CreateMeeting(startTime, endTime, room);

        if(tempMeeting == NULL) {
            return NULL;
        }

        InsertMeetingToAD(tempDiary,tempMeeting);
    }
    fclose(fp);

    return tempDiary;
}

void PrintMeeting(Meeting* mptr) {

    if(mptr == NULL) {
        return;
    }
    printf("%f\t%f\t%d\n", mptr->startTime, mptr->endTime, mptr->room);
}

int PrintAD(DiaryManagement* dptr) {

    if(dptr == NULL) {
        return NULL_ERROR;
    }

    for(int i = 0; i < dptr->NumOfMeetings; ++i) {
        PrintMeeting(dptr->AD[i]);
    }
    printf("\n");
    return OK;
}

// if(dptr->NumOfMeetings) {
//         DestroyAD(dptr);
//     }