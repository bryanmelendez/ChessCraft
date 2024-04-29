#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>
#include "Piece.h"

typedef struct Log Log;
typedef struct LogList LogList;

struct LogList
{
        Log *first;
        Log *last;
};

struct Log
{
        LogList* log_list;
        char move_entry[20];
	char timestamp[30];
        Log *next;
        Log *prev;
};

LogList* NewLogList(void);

void DeleteLogList(LogList* list);

void DeleteMove(Log* log);

void UndoMove(LogList* list);

void AddMove(LogList *list, char* move);

void WriteLog(LogList* list);

char* LogText(Coordinates start, Coordinates end);
 
#endif
