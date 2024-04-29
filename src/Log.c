#include "Log.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

LogList* NewLogList() {
        LogList *list;
        list = malloc(sizeof(LogList));
        list->first = NULL;
        list->last = NULL;

        return list;
}

void DeleteLogList(LogList* list){
        assert(list);
        Log* current = list->first;
        Log* next_log;

        while(current){
                next_log = current->next;
                DeleteMove(current);
                current = next_log;
        }
        free(list);
}

void DeleteMove(Log *log) {
        assert(log);
        free(log);
}

void UndoMove(LogList* list) {
        assert(list);

        Log *log = NULL;
        Log *prev_log = NULL;
        if(list->last) {
                log = list->last;
                prev_log = log->prev;
                DeleteMove(log);
                if(prev_log) {
                        list->last = prev_log;
                        prev_log->next = NULL;
                        }
                else{
                        list->last = NULL;
                        list->first = NULL;
                }
        }
        WriteLog(list);
}

void AddMove(LogList *list, char* move){
        assert(list);
        assert(move);
	char time_str[30];
        Log *log  = malloc(sizeof(Log));
        if(!log)
                {
                perror("Out of memory!");
                exit(10);
                }

        strncpy(log->move_entry, move, 20);
        log->move_entry[20] = '\0';

        log->log_list = list;

	time_t rawtime;
        struct tm *info;
        time(&rawtime);
        info  = localtime(&rawtime);
	strcpy(time_str, asctime(info));
	
	strcpy(log->timestamp, time_str);
        if(list->last)  {
                log->prev = list->last;
                log->next = NULL;
                list->last->next = log;
                list->last = log;
        }

        else{
                log->prev = NULL;
                log->next = NULL;
                list->first = log;
                list->last = log;
        }

        WriteLog(list);
}

void WriteLog(LogList *list){
        FILE *file = fopen("log.txt", "w");

	fprintf(file, "%s\n", "-----THE CHESSCRAFT MOVE LOG !-----");
        Log *log = list->first;

	int count = 1;
        while(log){
                fprintf(file, "%d. %s.....%s\n", count, log->move_entry, log->timestamp);
                log = log->next;
		count++;
        }
        fclose(file);
}

char* LogText(Coordinates start, Coordinates end) {
        char* log_text = NULL;
        char* start_pos = NULL;
        char*  end_pos = NULL;

        start_pos = (char*)malloc(3*sizeof(char));
        end_pos = (char*)malloc(3*sizeof(char));
        log_text = (char*)malloc(50* sizeof(char));

        sprintf(start_pos, "%c%c", 'A'+ start.column, '1' + start.row);
        sprintf(end_pos, "%c%c", 'A' + end.column, '1' + end.row);

        sprintf(log_text, "Moved from %s to %s", start_pos, end_pos);

        free(start_pos);
        free(end_pos);

        return(log_text);
}
