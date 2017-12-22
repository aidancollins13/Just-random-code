#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

extern char** environ;
enum {DEFAULT, IGNORE_ENV} mode;

void print_env(char** env);
char** add_to_env(char** vars, int mode, size_t num_of_vars);
void append_to_env(char** env, char* var, int env_length);
int replace_var(char** env, char** new_env, char* var, int env_length);
void free_env(char** env);

int main(int argc, char** argv)  {

    size_t new_env_vars = 0;

    if(argc == 1) {             //If there are no arguments passed print out the environment
        print_env(environ);
        exit(0);
    }

    if(argc > 1 && argv[1][0] == '-' && argv[1][1] == 'i') mode = IGNORE_ENV;       // Set the mode to IGNORE if -i is detected
    else mode = DEFAULT;

    size_t current_arg = mode + 1;                                                  // Find the next arg to process  
                                                                                    //  if -i is detected it will make current_arg 2
    while(argv[current_arg] != NULL){                                               

        if(strstr(argv[current_arg++], "=") != NULL) new_env_vars++;                // as long as we keep finding args with an '=' in them
        else break;                                                                 //  count them, as soon as we dont stop counting

    }

    environ = add_to_env(argv + (current_arg - new_env_vars -1), mode, new_env_vars);   // this sets environ to the output of one of my functions
                                                                                        // argv + (current_arg - new_env_vars -1) gives a pointer 
                                                                                        //  to the 1st arg with an = in it
   // print_env(environ);
    execvp(argv[current_arg-1], argv + current_arg-1);                                // This is the execute call
    free_env(environ);                                                                // I then call my free function


}

void print_env(char** env){             // This loops through the give char** and prints every string until it encounters the null string
    int i = 0;
    while(env[i])
        printf("%s\n", env[i++]);
}

char** add_to_env(char** vars, int mode, size_t num_of_vars){

    int environ_length = 0;
    int new_environ_end = 0;    // This keeps track of the end of the new char** for appending
    char** new_environ;

    if(mode == IGNORE_ENV) {    // if ignore is set make a char** that is big enough to hold the vars we are given
         new_environ = (char**)malloc(sizeof(char*)*(num_of_vars));
         if(new_environ  == NULL) {
            fprintf(stderr, "Error in malloc\n");
            exit(-1);
         }
        for(int i = 0; i < num_of_vars; i++){       // for every var call my function that appends a string to a char**
             append_to_env(new_environ, vars[i],new_environ_end);
             new_environ_end++;                     // after we append increment the counter to the end of the char**
         }
}


    else{
        while(environ[environ_length])      //if ignore is not set, count the length of the current envroin
            environ_length++;


         new_environ = (char**)malloc(sizeof(char*)*(environ_length + num_of_vars )); // and char** big enough for it and all of the vars
         if(new_environ  == NULL) {
            fprintf(stderr, "Error in malloc\n");
             exit(-1);
         }
         
         memset(new_environ, '\0', sizeof(char*)*(environ_length + num_of_vars));


         for(int i = 0; i < environ_length; i++){ // now that we have a new char** fill it wiht the vars from environ
             if((new_environ[i] = (char*)malloc(sizeof(char)*(strlen(environ[i])))) == NULL) {
                 fprintf(stderr, "Error in malloc\n");
                 exit(-1);
             }
             strncpy(new_environ[i], environ[i], strlen(environ[i]));
         }

         new_environ_end = environ_length-1;    // the end of the new char** will be one less than the length of the old one

         
         for(int i = 0; i < num_of_vars; i++){      // loop through the vars
             if(replace_var(environ, new_environ, vars[i], environ_length) == -1){ // this call will return -i if it cant find the var
                                                                                   // in the existing envroin
                     append_to_env(new_environ, vars[i], new_environ_end); // if we cant find the var append it
                     new_environ_end++;                                     // and increment the end counter
             }

        }
    }
    
    
    return new_environ;
}

void append_to_env(char** env, char* var, int env_end) {         // this function appends a new char* to the given char**
    if((env[env_end] = (char*)malloc(sizeof(char)*(strlen(var)))) == NULL){  // malloc something at the end of env of the size of the var
        fprintf(stderr, "Error in malloc\n");                                   
        exit(-1);                                                              
    }
    strncpy(env[env_end], var, strlen(var));                    // copy the variable into the newly malloced space
    env[env_end+1] = NULL;
    return;
}

int replace_var(char** env, char** new_env, char* var, int env_length) {  // this looks for the given var in the old envriron 
                                                                            // and replaces it in the new one
    int equals_pos = strchr(var, '=') - var;                            // this calculates the postion of the equals sign with pointer arithmatic

    for(int i = 0; i < env_length; i++) {                               // it then loops through the envrion
        if(strncmp(env[i], var, equals_pos) == 0){                      // checking if any values match the new variables
            free(new_env[i]);
            if((new_env[i] = (char*)malloc(sizeof(char)*(strlen(var)))) == NULL){ // if it finds ones it mallocs a new block of memory there
                fprintf(stderr, "Error in malloc\n");
                exit(-1);
            }
            strncpy(new_env[i], var, strlen(var));                      // and copies in the given var
            return 0;                                                   // 0 on success
        }
    }
    return -1;                                                          // -1 on failure
}

void free_env(char** env){      // this simply loops through the given char** freeing its char*'s before freeing the char** itself
    int i = 0 ;

    while(env[i])
        free(env[i++]);
    free(env);
}
