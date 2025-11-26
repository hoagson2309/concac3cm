#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

bool parse_person(const char *line, person_t *person)
{
    if(!line || !person) return false;

    char name [100];
    int counted_chars;

    if(sscanf(line, "%99[^,],%n", name, &counted_chars) != 1) return false;
    
    char *new_ptr = (char *) malloc (strlen(name) + 1);
    if(!new_ptr) return false;
    strcpy(new_ptr, name);
    person->name = new_ptr;

    line+= counted_chars;

    int day = 0;
    int month = 0;
    int year = -1;
    if(sscanf("%d-%d-%d", &day, &month, &year) != 3) return false;

    if(day<1 || day>31) return false;
    person->birthdate.day = day;
    if(month<1 || month>12) return false;
    person->birthdate.month = month;
    person->birthdate.year = year;
    return true;
}

calendar_t read_calendar (FILE *file)
{
    calendar_t logbook = {NULL, 0, 0};
    if (!file) return logbook;

    char line[1000];
    while(fgets(line, sizeof(line), file))
    {
        if(logbook.size == logbook.capacity){
            if(!set_capacity(logbook, logbook.capacity + 10)) return logbook;
        }
        if(!parse_person(line, logbook.person[logbook.size])) return logbook;
            logbook.count++;
        
    }
    return logbook;
}


int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(stderr, "argument is missing");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file){
        fprintf(stderr, "cannot open file");
        return 1;
    }
    int month = argv[2];
    calendar_t calendar = __read_calendar(file);
    fclose(file);

    qsort(calendar.person, calendar.size, sizeof(person_t), compare);

    int birthmonth_info[calendar.size];
    int count_people = 0;

    for(size_t i = 0; i < calendar.size; i++){
        if(month == calendar.person->birthdate.month){
            birthmonth_info[count_people] = i;
            count_people++;   
        }
    }

    printf("Found %d people w this month.\n", count_people);

    for(size_t i = 0; i < count_people; i++){
        printf("%s.\n", person_to_string(calendar.people[birthmonth_info[i]]));
    }
    free(calendar.people->name);
    free(calendar.people);
}

int compare(const void *a, const void *b){
    const person_t* p1 = (const person_t *) a;
    const person_t* p2 = (const person_t *) b;

    p1->birthdate.date > 
}




