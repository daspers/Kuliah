#include <stdio.h>
#include <string.h>
#include "boolean.h"

char Terminal[][100] = {"program",";","var","begin","end",".","..","array","of","integer","real","char",",",":=","=","<>",">","<",">=","<=",
						"and","or","(",")","[","]",":","if","then","else","for","to","downto","step","do","while","repeat","until","input",
						"output","+","-","*","div","mod"}; //size 45
char s[100];
int n, line, Psize;

void MakeStrEmpty(){
	s[0]= '\0';
	n = 0;
}

void StrAppend(char c){
	s[n] = c;
	n++;
	s[n] = '\0';
}

void LowerCase(char* t){
	int i=0;
	while(s[i]!='\0'){
		if(s[i]>='A' && s[i]<='Z')
			t[i] = s[i] - 'A' + 'a';
		else
			t[i] = s[i];
		i++;
	}
	t[i] = '\0';
}

boolean IsNumberChar(char c){
	return c>='0'&& c<='9';
}

boolean IsStrNumber(){
	int i;
	for(i=0;i<n;i++){
		if(!IsNumberChar(s[i]))
			return false;
	}
	return true;
}

boolean IsValidVar(){
	return !(s[0]>='0' && s[0]<='9');
}

boolean IsVarChar(char c){
	return c=='_'||(c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z');
}

boolean IsVariable(){
	int i=0;
	while(s[i]!='\0'){
		if(!IsVarChar(s[i]))
			return false;
		i++;
	}
	return true;
}

int HashStr(){
	int i;
	char t[100];
	LowerCase(t);
	for(i=0;i<45;i++){
		if(strcmp(t,Terminal[i])==0)
			return i;
	}
	return 47;
}

void HashAndCheck(){
	int p = HashStr();
	printf("<%d>", p);
	MakeStrEmpty();
}

void Parse(FILE *F){
	char c;
	line =1;
	Psize = 0;
	MakeStrEmpty();
	while(fscanf(F, "%c", &c) > 0){
		if(c==' '||c=='\n'||c=='\t'){
			if(n>0){
				HashAndCheck();
			}
			if(c=='\n')
				line++;
			printf("%c", c);
		}
		else if(IsVarChar(c)){
			if(n>0)
				if(!IsVarChar(s[n-1])){
					HashAndCheck();
				}
			StrAppend(c);
		}
		else{
			if(n>0){
				if(c=='.'&&s[n-1]=='.'&&n==1);
				else if(c=='='&&(s[n-1]=='<'||s[n-1]=='>'||s[n-1]==':'));
				else if(c=='>'&&s[n-1]=='<');
				else
					HashAndCheck();
			}
			StrAppend(c);
		}
	}
	puts("Parsing finished successfully");
}

int main(int argc, char *argv[]){
	int i;
	for(i=0;i<45;i++){
		printf("%d - %s\n", i, Terminal[i]);
	}
	FILE *F = NULL;
	char namafile[101];
	if(argc>1)
		strncpy(namafile, argv[1], 101);
	else
		scanf("%s", namafile);
	F = fopen(namafile, "r");
	if(F == NULL)
		printf("File %s not exist\n", namafile);
	else
		Parse(F);
	return 0;
}
