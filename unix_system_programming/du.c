#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

long int du(char* dirname);
long int dir_size(char * dirname);
int is_dup_inode(ino_t node);
// The main function is very simple
// if du has an argument is calls du with it
// if it doesn't it cals it on the current directory

int main(int argc, char** argv){  

    if(argc == 2)
      du(argv[1]);
    else
      du(".");
}

// This is a recursive du function that returns the blocksize in bytes
long int du(char* dirname){

    DIR* dirp;
    // open the given directory and check for errors
    if((dirp = opendir(dirname)) == NULL){ 
            perror("error opening directory");
            exit(0);
    }
    struct dirent* direntp;
    // size si what keeps track of total block size
    // it's initalize it as the size of the directory entry
    //      ( so empty directories won't show 0 size
    long int size = dir_size(dirname);
       
    // this loops over every entry in the directory
    while((direntp = readdir(dirp)) != NULL){
        //If its . or .. file skip it
        if(strcmp(direntp->d_name, ".") == 0  || strcmp(direntp->d_name, "..") == 0)
            continue;

        // Concatanate the complete path of the dir entry
        char path[1024] = "";
        strcat(path, dirname);
        strcat(path, "/");
        strcat(path, direntp->d_name);

        // Call lstat on the entry and check for errors 
        struct stat sb;
        if((lstat(path, &sb)) == -1){
            perror("error on stat()");
            printf("path: %s\n", path);
            exit(0);
        }
        
        // If it's a directory call du on it  and 
        //  add the returned size to total size
        if(S_ISDIR(sb.st_mode))
            size += du(path);
        
        // If it's not a directory and has more than one link
        // check if is a duplicate link
        else if(sb.st_nlink > 1 && (is_dup_inode(sb.st_ino)))
            continue;
        
        // If it is not a duplicate link or directory add its 
        // # of blocks * the block size to size
        else
            size += (sb.st_blocks * 512);
    }
    // After going through all entries print out its 
    // total size in KB and name
    printf("%ld\t%s\n", size/1024, dirname);
    closedir(dirp);
    return size;
}

// This function calculates the size of a directory entry
// (or any file technicaly)  and returns it
long int dir_size(char * dirname){
    struct stat sb;
    // Call lstat and check for errors
    if((lstat(dirname, &sb)) == -1){
        perror("error on stat()");
        printf("path: %s\n", dirname);
        exit(0);
    } 
    // return the blocks * 512 which is the block size
    return sb.st_blocks * 512;
}

// This function checks if a given i node has been seen before
// Technically if there are more than 1024 inodes with multiple pointers
// they will excede my array, but even in my root directory i never
// saw this happen
int is_dup_inode(ino_t node){
    // Declare a static array and static size so they percist 
    // over function calls
    static  int size = 0; 
    static ino_t node_arr[1024];
    // go through the array and if the given node is in it 
    // return true (1)
    for(int i = 0; i<size; i++){
        if( node_arr[i] == node){
            return 1;
        }
    }
    // if the give node is not found add it to the end of the array,
    // increment size
    // and return false(0)
    node_arr[size] = node;
    size++;
    return 0;
}
