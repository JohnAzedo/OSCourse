#include <iostream>
#include <ctime>
#include <unistd.h>
#include <wait.h>

void process_error(){
    fprintf(stdout, "Process error");
    exit(-1);
}

void print_time(std::string person){
    char *buffer [10];
    time_t now;
    time(&now);
    tm *now_tm = localtime(&now);
    strftime(*buffer, 10, "%M:%S", now_tm);
    fprintf(stdout, "%s, %s\n", person.c_str(), *buffer);
}


int main() {
    // Father
    print_time("BORN -> Father");
    pid_t pid[5] = {-1, -1, -1, -1, -1};

    sleep(14);

    // Creating first child
    print_time("BORN -> First child");
    pid[0] = fork();

    if (pid[0] < 0){ // Error
        process_error();
    }

    if(pid[0] > 0){ // Father as first child father
        sleep(2);
        // Creating second child
        print_time("BORN -> Second child");
        pid[1] = fork();

        if(pid[1] < 0 ){
            process_error();
        }
        wait(nullptr);
    }

    if(pid[1] > 0){ // Father as second child father
        wait(nullptr);
        sleep(12);
        print_time("DEATH -> Father: Lived 60");

    }

    if(pid[0] == 0){ // First child
        // Creating first grandchild
        sleep(12);
        print_time("BORN -> First grandchild");
        pid[2] = fork();

        if (pid[2] < 0){
            process_error();
        }
    }

    if(pid[1] == 0){ // Second child
        // Creating second grandchild
        sleep(14);
        print_time("BORN -> Second grandchild");
        pid[3] = fork();

        if (pid[3] < 0){
            process_error();
        }
    }

    if(pid[2] == 0){ // First grandchild
        sleep(12);
        print_time("DEATH -> First grandchild: Lived 12");
    }

    if(pid[3] == 0){ // Second grandchild
        sleep(18);
        print_time("DEATH -> Second grandchild: Lived 18");

    }

    if (pid[2] > 0){ // First child as first grandchild father
        sleep(18);
        print_time("DEATH -> First child: Lived 30");
    }

    if(pid[3] > 0){ // Second child as second grandchild father
        sleep(16);
        print_time("DEATH -> Second child: Lived 30");
        wait(nullptr);
    }
    return 0;
}