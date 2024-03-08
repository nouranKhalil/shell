#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <sys/wait.h>

#define MAX_LIMIT 100

int main() { 
    char *input[MAX_LIMIT];
    do{
        char str[MAX_LIMIT];
        printf("Enter command with full path: ");
        fgets(str, MAX_LIMIT, stdin);

        // Remove trailing newline character
        str[strcspn(str, "\n")] = 0;

        const char delimiter[] = " ";
        char *token = strtok(str, delimiter);
        int size = 0;

        while (token != NULL && size < MAX_LIMIT - 1) { // Avoid overflow
            input[size++] = token;
            token = strtok(NULL, delimiter); 
        } 
        input[size] = NULL; // NULL terminate the argument list


        pid_t pid = fork();
        if(pid == 0){
            execvp(input[0], input);
            if(strcmp(input[0], "exit")){
                perror("execvp");
                return -1;
            }
        }
        else if (pid > 0){
            wait(&pid);
        }
    }while (strcmp(input[0], "exit"));
    return 0;
}


// function parent_main()
//     register_child_signal(on_child_exit())
//     setup_environment()
//     shell()


// function on_child_exit()
//     reap_child_zombie()
//     write_to_log_file("Child terminated")


// function setup_environment()
//     cd(Current_Working_Directory)


// function shell()
//     do
//         parse_input(read_input())
//         evaluate_expression():
//         switch(input_type):
//             case shell_builtin:
//                 execute_shell_bultin();
//             case executable_or_error:
//                 execute_command():

//     while command_is_not_exit


// function execute_shell_bultin()
//     swirch(command_type):
//         case cd:
//         case echo:
//         case export:


// function execute_command()
//     child_id = fork()
//     if child:
//         execvp(command parsed)
//         print("Error")
//         exit()
//     else if parent and foreground:
//         waitpid(child)