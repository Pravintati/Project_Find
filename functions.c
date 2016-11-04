/*************************************************************************
*   <find_command>
*   Copyright (C) 2017  Pravin Narayan Tati tatipn16.it@coep.ac.in
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>
**************************************************************************/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

/* List directory structure from the name of directory */
void files(char *name)
{
    DIR *dir;
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("./project : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }
 	printf("%s\n",name);
    if(name[strlen(name)-1] == '/'){
    	name[strlen(name)-1] = '\0';
    	}
    if(strcmp(name,"./") == 0)	
	strcpy((char *)name,".");
	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
            files(path);
        }
        else
            printf("%s/%s\n",name, filename->d_name);
    } while ((filename = readdir(dir)));
    closedir(dir);
}

void optional(char *name, char *file)
{
    DIR *dir;
    int r = 0;
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("./project : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }
 	printf("%s\n",name);
    if(name[strlen(name)-1] == '/'){
    	name[strlen(name)-1] = '\0';
    	} 	
    if(strcmp(name,"./") == 0)	
	strcpy((char *)name,".");
	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
            optional(path, file);
        }
	else if(strcmp(filename->d_name, file) == 0){
            printf("%s/%s\n",name, filename->d_name);
		r = 1;
        }
        else 
        printf("%s/%s\n",name, filename->d_name);
	
    } while ((filename = readdir(dir)));
	if(r == 1)
	  printf("%s\n", file);
    closedir(dir);
}

/* List all files which matches the name specified from the directory */
void namefile(char *name, char *fname, char *cname)
{
    DIR *dir;
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("./project : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if(name[strlen(name)-1] == '/'){
    	name[strlen(name)-1] = '\0';
    	}        
    if(strcmp(name,"./") == 0)	
	strcpy((char *)name,".");
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }
	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
            namefile(path, fname, cname);
        }
        else if((strcmp(filename->d_name, fname)) == 0 && strcmp(cname, "-name") == 0)
            printf("%s/%s\n",name, filename->d_name);
        else if((strcasecmp(filename->d_name, fname)) == 0 && strcmp(cname, "-iname") == 0)
        	printf("%s/%s\n",name, filename->d_name);
    } while ((filename = readdir(dir)));
    closedir(dir);
}

/* List directorys whose name matches with the specified name from the directory */
void nameFolder(char *name, char *fname, char *cname)
{
    DIR *dir;
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("./project : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }
    if(name[strlen(name)-1] == '/'){
    	name[strlen(name)-1] = '\0';
    	}        
    if(strcmp(name,"./") == 0)	
	strcpy((char *)name,".");
	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
	    if(strcmp(cname,"-name") == 0 && strcmp(filename->d_name, fname) == 0)
	    printf("%s\n",path);
	    else if(strcmp(cname,"-iname") == 0 && strcasecmp(filename->d_name, fname) == 0)
	    printf("%s\n",path);
            nameFolder(path, fname, cname);
        }
    } while ((filename = readdir(dir)));
    closedir(dir);
}

/* List files of size matches with value in k(kilobytes) from the direcotry */
void sizekfile(char *name, long size1)
{
    DIR *dir;
    int fd, a;
    struct stat st; 
    double s;
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("./project : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }        
    if(name[strlen(name)-1] == '/'){
    	name[strlen(name)-1] = '\0';
    	}        
    if(strcmp(name,"./") == 0)	
	strcpy((char *)name,".");
	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
            sizekfile(path, size1);
        }
        else {
		if((fd = open(filename->d_name, O_RDONLY)) != -1){
		fstat(fd,&st);
		s=(double)st.st_size/1024;
		a=ceil(s);
		if(a == size1)
		printf("%s/%s\n",name, filename->d_name);
	    }
	}
	
    } while ((filename = readdir(dir)));
    closedir(dir);
}

/* List empty files from the specified directory */
void emptyfile(char *name)
{
    DIR *dir;
    int fd;
    struct stat st; 
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("./project : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }
    if(name[strlen(name)-1] == '/'){
    	name[strlen(name)-1] = '\0';
    	}        
    if(strcmp(name,"./") == 0)	
	strcpy((char *)name,".");
	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
            emptyfile(path);
        }
        else {
		if((fd = open(filename->d_name, O_RDONLY)) != -1){
		fstat(fd,&st);
		if(st.st_size == 0)
		printf("%s/%s\n",name, filename->d_name);
		}
	}
	
    } while ((filename = readdir(dir)));
    closedir(dir);
}

/* List files of size matches with value in M(Megabyte) from the direcotry */
void sizeMfile(char *name, long size1)
{
    DIR *dir;
    int fd, a;
    struct stat st; 
    double s;
    struct dirent *filename;
   
    if (!(dir = opendir(name))){
    	printf("./project : '%s' : %s\n", name,strerror(errno));
        return;
        }
    if (!(filename = readdir(dir))){
    	printf("%s\n", strerror(errno));
        return;
        }        
    if(name[strlen(name)-1] == '/'){
    	name[strlen(name)-1] = '\0';
    	}        
    if(strcmp(name,"./") == 0)	
	strcpy((char *)name,".");
	do {
        if (filename->d_type == DT_DIR) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, filename->d_name);
            if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
                continue;
            sizeMfile(path, size1);
        }
        else {
		if((fd = open(filename->d_name, O_RDONLY)) != -1){
		fstat(fd,&st);
		s=(double)st.st_size/(1024*1024);
		a=ceil(s);
		if(a == size1)
		printf("%s/%s\n",name, filename->d_name);
		}
	}
	
    } while ((filename = readdir(dir)));
    closedir(dir);
}

/* Display the help file for the command */
void printhelp(void)
{
	FILE *fp;
	char c, *s="help.txt";
	fp = fopen(s,"r");
	if(fp == NULL){
		printf("cann't open file");
		exit(0);
	}
	c=fgetc(fp);
	while(c != EOF){
		printf("%c",c);
		c=fgetc(fp);
	}
	fclose(fp);
}
