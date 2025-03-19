#define OK 0
#define NULL_ERROR 1;
#define REALOC_FAILED 2
#define OVERFLOW 3
#define UNDERFLOW 4
#define FILE_ERROR 5
#define NOT_FOUND 6


typedef struct {
    float startTime;
    float endTime;
    int room;
}Meeting;

typedef struct {
    Meeting** AD;
    int dArraySize;
    int dArrayBlockSize;
    int NumOfMeetings;
} DiaryManagement;

/*
description: Create Diary
input: size and block size
Output: pointer to Diary
Error: NULL error*/
DiaryManagement* DiaryManagementCreate(signed int size, int blockSize);

/*
description: Create meeting
input: start time, end time, room number
Output: pointer to meeting
Error: NULL error, OVERLAP*/
Meeting* CreateMeeting(float startTime, float endTime, int room);

/*
description: inserts meeting to diary array.
input: pointer to Diary, pointer to Meeting.
Output: status.
Error: NULL error*/
int InsertMeetingToAD(DiaryManagement* dptr, Meeting* meeting);
/*
description: Removes a meeting from Diary array
input: pointer to diary, start time of the meeting you want to delete
Output: status
Error: NULL error*/
int RemoveMeeting(DiaryManagement *dptr, float data);

/*
description: Find meeting in diary array
input: pointer to diary, start time of the meeting you want to find
Output: status
Error: NULL error, meeting not found*/
int FindAppointment(DiaryManagement* dptr, float data);

/*
description: Destroy Diary array and all meetings.
input: pointer to diary
Output: status
Error: NULL error*/
int DestroyAD(DiaryManagement* dptr);

/*
description: save all appointments to file
input: pointer to diary array, file name
Output: status
Error: NULL error*/
int SaveToFile(DiaryManagement* dptr, char* name);

/*
description: Loads all appointments from file to diary array
input: diary pointer, file name
Output: pointer to Diary
Error: NULL error*/
DiaryManagement* LoadfromFile(DiaryManagement* dptr, char* fileName);

/*
description: Prints all meetings in Diary
input: diary pointer
Output: status
Error: NULL error*/
int PrintAD(DiaryManagement* dptr);

/*
description: print one meeting.
input: meeting pointer
Output: none
Error: NULL error*/
void PrintMeeting(Meeting* mptr);
