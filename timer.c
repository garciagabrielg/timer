#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

time_t current_time;
struct tm *current_time_info = NULL;
time_t target_time;
struct tm *target_time_info = NULL;
bool succes = false;

void initalize_current_time ()
{
    time(&current_time);
    current_time_info = localtime(&current_time);
}

void initalize_target_time()
{
    target_time_info = (struct tm *)malloc(sizeof(struct tm));
    if (target_time_info == NULL){
        fprintf(stderr, "Memory allocation error\n");
        return;
    }
    *target_time_info = *current_time_info;
    succes = true;
}

void free_memory()
{
    free(target_time_info);
}

time_t set_timer(int * input)
{
    int increment;
    switch (*input)
    {
        case 1:
            printf("How many hours to add?: ");
            scanf("%d", &increment);
            target_time_info->tm_hour += increment;
            break;
        case 2:
            printf("How many minutes to add?: ");
            scanf("%d", &increment);
            target_time_info->tm_min += increment;
            break;
        case 3:
            printf("How many seconds to add?: ");
            scanf("%d", &increment);
            target_time_info->tm_sec += increment;
            break;
        default:
            printf("Invalid input \n");
            return EXIT_FAILURE;
    }
    target_time = mktime(target_time_info);
    return 0;
}

int main()
{
    int user_input;
    initalize_current_time();
    initalize_target_time();
    if (!succes)
    {
        free_memory();
        return EXIT_FAILURE;
    }
    printf("Current time: %02d:%02d\n", current_time_info->tm_hour,current_time_info->tm_min);
    printf("Choose 1 for hours, 2 for minutes, or 3 for seconds: ");
    scanf("%d", &user_input);
    set_timer(&user_input);
    while (current_time < target_time)
    {
        initalize_current_time();
        int remaining_secs = (int)difftime(target_time, current_time);
        int remaining_hours = remaining_secs / 3600;
        int remaining_minutes = (remaining_secs % 3600) / 60;
        remaining_secs %= 60;
        printf("Remaining time: %02d:%02d:%02d\n", 
        remaining_hours, remaining_minutes, remaining_secs);
        sleep(1);
    };
    MessageBox(NULL, "You have reached your time goal!", "Timer Notification", MB_OK | MB_ICONINFORMATION);
    free_memory();
    return EXIT_SUCCESS;
}