#include "shell.h"
/**
 * main - central tour
 * no parameters
 * Return: 0 if SUCCESS
 */
void tokenize_command(char *command, char **tokens);
void handle_comments(char *command);
void handle_cd(char **args);
void handle_alias(char **args);
void handle_variables(char **args);
void execute_file(char *filename);


int main(int argc, char *argv[])
{
if (argc > 1)
{
execute_file(argv[1]);
return (0);
}
char buffer[BUFFER_SIZE];
char prompt[] = "$ ";
int bytes_read;
while (1)
{
printf("%s", prompt);
bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
if (bytes_read == 0)
{
printf("\n");
break;
}
if (bytes_read < 0)
{
perror("Error reading command");
continue;
}
buffer[bytes_read - 1] = '\0';
char *args[BUFFER_SIZE];
char *commands[BUFFER_SIZE];
int command_count = 0;
char *commands[BUFFER_SIZE];
tokenize_command(buffer, commands);
for (int j = 0; j < command_count; j++)
{
handle_comments(commands[j]);
handle_variables(commands[j]);
tokenize_input(buffer, args);
if (strcmp(args[0], "exit") == 0)
{
handle_exit();
break;
}
if (strcmp(args[0], "setenv") == 0)
{
handle_setenv(args);
continue;
}
if (strcmp(args[0], "unsetenv") == 0)
{
handle_unsetenv(args);
continue;
}
if (strcmp(args[0], "cd") == 0)
{
handle_cd(args);
continue;
}
if (strcmp(args[0], "alias") == 0)
{
handle_alias(args);
continue;
}
if (strcmp(args[0], "env") == 0)
{
handle_env();
continue;
}
execute_external_command(args);
}
return (0);
}

void tokenize_command(char *command, char **tokens)
{
int token_count = 0;
char *token = strtok(command, " ");
while (token != NULL && token_count < BUFFER_SIZE - 1)
{
tokens[token_count] = token;
token_count++;
token = strtok(NULL, " ");
}
tokens[token_count] = NULL;
}

void handle_alias(char **args)
{
if (args[1] == NULL)
{
char *alias = getenv("ALIAS");
if (alias != NULL)
{
char *token = strtok(alias, ",");
while (token != NULL)
{
printf("%s\n", token);
token = strtok(NULL, ",");
}
}
}
else
{
while (token != NULL)
{
printf("%s\n", token);
token = strtok(NULL, "=");
}
}
}
void handle_variables(char **args)
{
int i = 0;
while (args[i] != NULL)
{
char *variable = strchr(args[i], '$');
if (variable != NULL)
{
char *value = getenv(variable + 1);
if (value != NULL)
{
args[i] = value;
}
}
i++;
}
}

void handle_comments(char *command)
{
char *comment = strchr(command, '#');
if (comment != NULL)
{
*comment = '\0';
}
}

void execute_file(char *filename)
{
FILE *file = fopen(filename, "r");
if (file == NULL)
{
perror("Error opening file");
return;
}

char line[BUFFER_SIZE];
while (fgets(line, BUFFER_SIZE, file) != NULL)
{
line[strcspn(line, "\n")] = '\0';
char *commands[BUFFER_SIZE];
int command_count = 0;
tokenize_command(line, commands);

for (int j = 0; j < command_count; j++)
{
handle_comments(commands[j]);
handle_variables(commands[j]);


char *args[BUFFER_SIZE];
int arg_count = 0;
tokenize_command(commands[j], args);

if (strcmp(args[0], "setenv") == 0)
{
handle_setenv(args);
continue;
}

if (strcmp(args[0], "cd") == 0)
{
handle_cd(args);
continue;
}


if (strcmp(args[0], "alias") == 0)
{
handle_alias(args);
continue;
}

execute_command(args);
}
}

fclose(file);
}
