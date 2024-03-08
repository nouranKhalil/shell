#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <sys/wait.h>

#define MAX_LIMIT 100

char *var[MAX_LIMIT];
char *values[MAX_LIMIT];
int len = 0;
int size;

char *read_input()
{
    char *str = (char *)malloc(MAX_LIMIT * sizeof(char));
    printf("%s:", getcwd(str, MAX_LIMIT));
    fgets(str, MAX_LIMIT, stdin);
    // Remove trailing newline character
    str[strcspn(str, "\n")] = 0;
    return str;
}

void parse_input(char **input, char *str)
{

    const char delimiter[] = " =";
    char *token = strtok(str, delimiter);
    size = 0;

    while (token != NULL && size < MAX_LIMIT - 1)
    { // Avoid overflow
        input[size++] = token;
        token = strtok(NULL, delimiter);
    }
    input[size] = NULL; // NULL terminate the argument list
}

void setup_environment()
{
    chdir("/home/nouran");
}

void execute_command(char **input)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(input[0], input);
        perror("execvp");
        exit(0);
    }
    else if (pid > 0)
    {
        wait(&pid);
    }
}

void execute_shell_bultin(char **input)
{
    if (strcmp(input[0], "cd") == 0)
    {
        chdir(input[1]);
    }
    else if (strcmp(input[0], "echo") == 0)
    {
        printf("%s\n", input[1]);
    }
    else if (strcmp(input[0], "export") == 0)
    {
        if (len == 0)
        {
        update:
            var[len] = input[1];
            values[len] = input[2];
            len++;
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                if (strcmp(var[i], input[1]) == 0)
                {
                    values[i] = input[2];
                    break;
                }
                else if (i == len - 1) goto update;
            }
        }
    }
}

void evaluate_expression(char **input)
{
    if (size != 1 && input[1][0] == '&')
    {
        for (int i = 0; i < len; i++)
        {
            char tmp[MAX_LIMIT] = "&";
            if (strcmp(strcat(tmp, var[i]), input[1]) == 0)
            {
                input[1] = values[i];
                break;
            }
        }
    }
}

void shell()
{
    char *input[MAX_LIMIT];
    do
    {
        parse_input(input, read_input());
        evaluate_expression(input);
        if (strcmp(input[0], "cd") == 0 || strcmp(input[0], "echo") == 0 || strcmp(input[0], "export") == 0)
        {
            execute_shell_bultin(input);
        }
        else if (strcmp(input[0], "exit"))
        {
            execute_command(input);
        }
    } while (strcmp(input[0], "exit"));
}

// function on_child_exit()
//     reap_child_zombie()
//     write_to_log_file("Child terminated")

int main()
{
    // register_child_signal(on_child_exit())
    setup_environment();
    shell();
    return 0;
}
