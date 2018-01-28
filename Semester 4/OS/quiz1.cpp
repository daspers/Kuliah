#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char* argv[]){
	char *data, *begin, *end, finput[300], foutput[300];
	ssize_t readb, writeb;
	const size_t maxread = 262144;
	if(argc == 1){
		fgets(finput, 300, stdin);
		fgets(foutput, 300, stdin);
		finput[strlen(finput)-1] = '\0';
		foutput[strlen(foutput)-1] = '\0';
	}
	else if(argc == 3){
		strcpy(finput, argv[1]);
		strcpy(foutput, argv[2]);
	}
	else if(argc != 3){
		puts("Error, wrong format!");
		puts("Should be \"program <sorce file name and/or directory> <file destination name and/or directory>\""); 
		exit(0);
	}
	int sc = open(finput, O_RDONLY);
	if(sc==-1){
		puts("Error in opening file!");
		printf("%s\n", strerror(errno));
		exit(0);
	}
	int des = open(foutput, O_WRONLY | O_EXCL | O_CREAT, S_IRWXU);
	if(des==-1){
		puts("Error in creating file!");
		printf("%s\n", strerror(errno));
		close(sc);
		exit(0);
	}
	/*
	temp = (char*) malloc(strlen(argv[2])+6);
	strcpy(temp, argv[2]);
	if(des==-1){
		temp = (char*) malloc(strlen(argv[2])+6);
		tnum = (char*) malloc(5);
		int coun = 0;
		do{
			coun++;
			sprintf(tnum, "%d", coun);
			strcpy(temp, argv[2]);
			strcat(temp, "(");
			strcat(temp, tnum);
			strcat(temp, ")");
		}while(access(temp, F_OK)!=-1);
		puts("There exist file with same name");
		printf("You wish to continue with this file name \'%s\' ?(y/n)\n", temp);
		fgets(in, 2, stdin);
		free(tnum);
		if(strcmp(in, "y")&&strcmp(in, "Y")){
			free(temp);
			close(sc);
			close(des);
			exit(0);
		}
		des = open(temp, O_WRONLY | O_EXCL | O_CREAT, S_IRWXU);
	}
	*/
	data = (char *) malloc(maxread+1);
	while(1){
		readb = read(sc, data, maxread);
		if(readb<0){
			puts("Error when reading file!");
			printf("%s\n", strerror(errno));
			close(sc);
			close(des);
			free(data);
			//free(temp);
			exit(0);
		}
		if(readb==0)
			break;
		begin = data;
		end = data + readb;
		while(begin<end){
			writeb = write(des, data, end - begin);
			if(writeb<0){
				puts("Error when writing to file!");
				printf("%s\n", strerror(errno));
				close(sc);
				close(des);
				free(data);
				//free(temp);
				exit(0);
			}
			begin += writeb;
		}
	}
	puts("Copying data finished successfully");
	close(sc);
	close(des);
	//free(temp);
	free(data);
	return 0;
}
