#include <stdio.h>
#include <string.h>
#include "boolean.h"
#include "stacklist.h"

#define FileTerminal "terminal.txt"
#define FileVariabel "variabel.txt"
#define FileTabel "tabel.txt"

typedef struct{
	int token;
	int line;
}Prog;

char Set[100][100], s[100];
Stack LL;
int n, line, Tsize, Vsize, Psize;
int Tab[100][100];
Prog Program[5000];

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
	for(i=0;i<Tsize;i++){
		if(strcmp(t,Set[i])==0)
			return i;
	}
	return Tsize-1;
}

int GetIdx(const char* x){
	int i;
	for(i=0;i<Vsize;i++){
		if(strcmp(Set[i], x)==0)
			return i;
	}
	return Tsize-1;
}

void HashAndCheck(){
	int p = HashStr();
	Program[Psize].token = p;
	Program[Psize].line = line;
	printf("<%d>", p);
	Psize++;
	MakeStrEmpty();
}

void ProgToken(FILE *F){
	char c;
	line =1;
	Psize=0;
	MakeStrEmpty();
	printf("%d: ", line);
	while(fscanf(F, "%c", &c) > 0){
		if(c==' '||c=='\n'||c=='\t'){
			if(n>0){
				HashAndCheck();
			}
			printf("%c", c);
			if(c=='\n'){
				line++;
				printf("%d: ", line);
			}
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
	if(n>0)
		HashAndCheck();
}

void PrintDeriv(int n){
	Stack T;
	infotype a;
	int i;
	for(i=0;i<n;i++)
		printf("%s ", Set[Program[i].token]);
	CreateEmpty(&T);
	while(!IsEmpty(LL)){
		Pop(&LL, &a);
		Push(&T, a);
		printf("%s ", Set[a]);
	}
	while(!IsEmpty(T)){
		Pop(&T, &a);
		Push(&LL, a);
	}
}

void errormsg(int i){
	if(IsEmpty(LL))
		printf("\nError : no code should be place after 'end.'");
	else
		printf("\nExpected %s", Set[InfoTop(LL)]);
	printf("\nError in token %d\n", Program[i].token);
	printf("Error in line %d\n", Program[i].line);
}

void Parse(FILE *F){
	int i;
	infotype A;
	CreateEmpty(&LL);
	Push(&LL, GetIdx("S"));
	ProgToken(F);
	puts("");
	puts("Derivation :");
	printf("S ");
	for(i=0;i<Psize&&!IsEmpty(LL);){
		// printf("%d %d %d\n", InfoTop(LL),Program[i].token, Tab[InfoTop(LL)][Program[i].token]);
		// printf("%s %s %d\n", Set[InfoTop(LL)], Set[Program[i].token], Tab[InfoTop(LL)][Program[i].token]);
		if(Program[i].token == InfoTop(LL)){
			Pop(&LL,&A);
			i++;
		}
		else{
			switch (Tab[InfoTop(LL)][Program[i].token]){
				case 1 : // S -> P Var ProgU
					Pop(&LL, &A);
					Push(&LL, GetIdx("ProgU"));
					Push(&LL, GetIdx("Var"));
					Push(&LL, GetIdx("P"));
					break;
				case 2 : // P -> program variabel ;
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("variabel"));
					Push(&LL, GetIdx("program"));
					break;
				case 3 : // Var -> var Decl
					Pop(&LL, &A);
					Push(&LL, GetIdx("Decl"));
					Push(&LL, GetIdx("var"));
					break;
				case 4 : // Decl -> e
				case 5 : // Decl -> Tvariabel : Btype
					Pop(&LL, &A);
					if(Program[i].token==GetIdx("variabel")){
						Push(&LL, GetIdx("Btype"));
						Push(&LL, GetIdx(":"));
						Push(&LL, GetIdx("Tvariabel"));
					}
					break;
				case 6 : // Btype -> Type ; Decl
					Pop(&LL, &A);
					Push(&LL, GetIdx("Decl"));
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Type"));
					break;
				case 7 : // Btype -> Tabel Type ; Decl
					Pop(&LL, &A);
					Push(&LL, GetIdx("Decl"));
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Type"));
					Push(&LL, GetIdx("Tabel"));
					break;
				case 8 : // Tabel -> Array Kray
					Pop(&LL, &A);
					Push(&LL, GetIdx("Kray"));
					Push(&LL, GetIdx("Array"));
					break;
				case 9 : // Kray -> e
				case 10 : // Kray -> Array
					Pop(&LL, &A);
					if(Program[i].token == GetIdx("array")){
						Push(&LL, GetIdx("Array"));
					}
					break;
				case 11 : // Tvariabel -> variabel
				case 12 : // Tvariabel -> variabel , Tvariabel
					Pop(&LL,&A);
					if(Program[i+1].token == GetIdx(",")){
						Push(&LL, GetIdx("Tvariabel"));
						Push(&LL, GetIdx(","));
					}
					else if(Program[i+1].token == GetIdx("[")){
						Push(&LL, GetIdx("]"));
						Push(&LL, GetIdx("variabel"));
						Push(&LL, GetIdx("["));
					}
					Push(&LL, GetIdx("variabel"));
					break;
				case 13 : // Type -> integer
					Pop(&LL, &A);
					Push(&LL, GetIdx("integer"));
					break;
				case 14 : // Type -> real
					Pop(&LL, &A);
					Push(&LL, GetIdx("real"));
					break;
				case 15 : // Type -> char
					Pop(&LL, &A);
					Push(&LL, GetIdx("char"));
					break;
				case 16 : // Array -> array [ bilangan .. bilangan ] of
					Pop(&LL, &A);
					Push(&LL, GetIdx("of"));
					Push(&LL, GetIdx("]"));
					Push(&LL, GetIdx("variabel"));
					Push(&LL, GetIdx(".."));
					Push(&LL, GetIdx("variabel"));
					Push(&LL, GetIdx("["));
					Push(&LL, GetIdx("array"));
					break;
				case 17 : // ProgU -> Isibe .
					Pop(&LL, &A);
					Push(&LL, GetIdx("."));
					Push(&LL, GetIdx("Isibe"));
					break;
				case 18 : // Isi -> Assign ; Isi
					Pop(&LL, &A);
					Push(&LL, GetIdx("Isi"));
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Assign"));
					break;
				case 19 : // Isi -> Cond Isi
					Pop(&LL, &A);
					Push(&LL, GetIdx("Isi"));
					Push(&LL, GetIdx("Cond"));
					break;
				case 20 : // Isi -> Loop Isi
					Pop(&LL, &A);
					Push(&LL, GetIdx("Isi"));
					Push(&LL, GetIdx("Loop"));
					break;
				case 21 : // Isi -> IO Isi
					Pop(&LL, &A);
					Push(&LL, GetIdx("Isi"));
					Push(&LL, GetIdx("IO"));
					break;
				case 22 : // Isi -> e
					Pop(&LL, &A);
					break;
				case 23 : // Isibe -> begin Isi end
					Pop(&LL, &A);
					Push(&LL, GetIdx("end"));
					Push(&LL, GetIdx("Isi"));
					Push(&LL, GetIdx("begin"));
					break;
				case 24 : // Cond -> if Lojik then Isibe Else
					Pop(&LL, &A);
					Push(&LL, GetIdx("Else"));
					Push(&LL, GetIdx("Isibe"));
					Push(&LL, GetIdx("then"));
					Push(&LL, GetIdx("Lojik"));
					Push(&LL, GetIdx("if"));
					break;
				case 25 : // Else -> ;
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					break;
				case 26 : // Else -> else Elseif
					Pop(&LL, &A);
					Push(&LL, GetIdx("Elseif"));
					Push(&LL, GetIdx("else"));
					break;
				case 27 : // Elseif -> Cond
					Pop(&LL, &A);
					Push(&LL, GetIdx("Cond"));
					break;
				case 28 : // Elseif -> Isibe ;
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Isibe"));
					break;
				case 29 : // Assign -> Gvariabel := Ekspresi
					Pop(&LL, &A);
					Push(&LL, GetIdx("Ekspresi"));
					Push(&LL, GetIdx(":="));
					Push(&LL, GetIdx("Gvariabel"));
					break;
				case 30 : // Loop -> for Assign For
					Pop(&LL, &A);
					Push(&LL, GetIdx("For"));
					Push(&LL, GetIdx("Assign"));
					Push(&LL, GetIdx("for"));
					break;
				case 31 : // For -> to bilangan Step
					Pop(&LL, &A);
					Push(&LL, GetIdx("Step"));
					Push(&LL, GetIdx("variabel"));
					Push(&LL, GetIdx("to"));
					break;
				case 32 : // For -> downto bilangan Step
					Pop(&LL, &A);
					Push(&LL, GetIdx("Step"));
					Push(&LL, GetIdx("variabel"));
					Push(&LL, GetIdx("downto"));
					break;
				case 33 : // Step -> do Isibe
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Isibe"));
					Push(&LL, GetIdx("do"));
					break;
				case 34 : // Step -> step bilangan do Isibe
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Isibe"));
					Push(&LL, GetIdx("do"));
					Push(&LL, GetIdx("variabel"));
					Push(&LL, GetIdx("step"));
					break;
				case 35 : // Loop -> while Lojik do Isibe
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Isibe"));
					Push(&LL, GetIdx("do"));
					Push(&LL, GetIdx("Lojik"));
					Push(&LL, GetIdx("while"));
					break;
				case 36 : // Loop -> repeat Isi until Lojik ;
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx("Lojik"));
					Push(&LL, GetIdx("until"));
					Push(&LL, GetIdx("Isi"));
					Push(&LL, GetIdx("repeat"));
					break;
				case 37 : // Lojik -> Lojikp
				case 38 : // Lojik -> Lojikl
					Pop(&LL, &A);
					if(Program[i].token == GetIdx("variabel")){
						Push(&LL, GetIdx("Lojikp"));
					}
					else{
						int j,c=1, k=0;
						for(j=i+1;j<Psize&&c>0;j++){
							if(Program[j].token == GetIdx(")"))
								c--;
							else if(Program[j].token == GetIdx("("))
								c++;
							else if(Program[j].token == GetIdx("and") || Program[j].token == GetIdx("or"))
								k=1;
						}
						if(c>0){
							errormsg(j);
							return ;
						}
						if(Program[j].token == GetIdx("and") || Program[j].token == GetIdx("or") || k){
							Push(&LL, GetIdx("Lojikl"));
						}
						else{
							Push(&LL, GetIdx("Lojikp"));
						}
					}
					break;
				case 39 : // Lojikp -> Gvariabel
				case 40 : // Lojikp -> ( Lojikp )  cobacoba
				case 41 : // Lojikp -> Ekspresi Opp Ekspresi
					Pop(&LL, &A);
					if(Program[i].token == GetIdx("variabel")){
						int j;
						for(j=i+1;j<Psize&&(Program[j].token == GetIdx("variabel") ||(Program[j].token >= GetIdx("+") && Program[j].token <= GetIdx("mod")) || Program[j].token == GetIdx("[")|| Program[j].token == GetIdx("]"));j++);
						if(Program[j].token >= GetIdx("=") && Program[j].token <= GetIdx("<=")){
							Push(&LL, GetIdx("Ekspresi"));
							Push(&LL, GetIdx("Opp"));
						}
						Push(&LL, GetIdx("Ekspresi"));
					}
					else{
						int j,c=1;
						for(j=i+1;j<Psize&&c>0;j++){
							if(Program[j].token == GetIdx(")"))
								c--;
							else if(Program[j].token == GetIdx("("))
								c++;
						}
						if(c>0){
							errormsg(i);
							return ;
						}
						if(Program[j].token >= GetIdx("=") && Program[j].token <= GetIdx("<=")){
							Push(&LL, GetIdx("Lojikp"));
							Push(&LL, GetIdx("Opp"));
							Push(&LL, GetIdx(")"));
							Push(&LL, GetIdx("Lojikp"));
							Push(&LL, GetIdx("("));
						}
						else{
							Push(&LL, GetIdx(")"));
							Push(&LL, GetIdx("Lojikp"));
							Push(&LL, GetIdx("("));
						}
					}
					break;
				case 42 : // Opp -> =
					Pop(&LL, &A);
					Push(&LL, GetIdx("="));
					break;
				case 43 : // Opp -> <>
					Pop(&LL, &A);
					Push(&LL, GetIdx("<>"));
					break;
				case 44 : // Opp -> >
					Pop(&LL, &A);
					Push(&LL, GetIdx(">"));
					break;
				case 45 : // Opp -> <
					Pop(&LL, &A);
					Push(&LL, GetIdx("<"));
					break;
				case 46 : // Opp -> >=
					Pop(&LL, &A);
					Push(&LL, GetIdx(">="));
					break;
				case 47 : // Opp -> <=
					Pop(&LL, &A);
					Push(&LL, GetIdx("<="));
					break;
				case 48 : // Lojikl -> ( Lojikl )
				case 49 : // Lojikl -> ( Lojikp )
				case 50 : // Lojikl -> Lojikl Opp Lojikl
					Pop(&LL, &A);
					int j,c=1, k=0;
					for(j=i+1;j<Psize&&c>0;j++){
						if(Program[j].token == GetIdx(")"))
							c--;
						else if(Program[j].token == GetIdx("("))
							c++;
						else if(Program[j].token == GetIdx("and")||Program[j].token == GetIdx("or"))
							k=1;
					}
					if(c==0 && (Program[j].token == GetIdx("and") || Program[j].token == GetIdx("or"))){
						Push(&LL, GetIdx("Lojikl"));
						Push(&LL, GetIdx("Opl"));
					}
					if(k){
						Push(&LL, GetIdx(")"));
						Push(&LL, GetIdx("Lojikl"));
						Push(&LL, GetIdx("("));
					}
					else{
						Push(&LL, GetIdx(")"));
						Push(&LL, GetIdx("Lojikp"));
						Push(&LL, GetIdx("("));
					}
				break;
				case 51 : // Opl -> and
					Pop(&LL, &A);
					Push(&LL, GetIdx("and"));
					break;
				case 52 : // Opl -> or
					Pop(&LL, &A);
					Push(&LL, GetIdx("or"));
					break;
				case 53 : // Ekspresi -> Gvariabel
				case 54 : // Ekspresi -> bilangan
				case 55 : // Ekspresi -> ( Ekspresi )
				case 56 : // Ekspresi -> Ekspresi Op Ekspresi
					Pop(&LL, &A);
					if(Program[i].token == GetIdx("variabel")){
						int j=i+1,c =0;
						if(Program[j].token == GetIdx("[")){
							for(c=1, j=i+2;j<Psize&&c>0;j++){
								if(Program[j].token == GetIdx("]"))
									c--;
								else if(Program[j].token == GetIdx("["))
									c++;
							}
						}
						if(c==0 && Program[j].token >= GetIdx("+") && Program[j].token <= GetIdx("mod")){
							Push(&LL, GetIdx("Ekspresi"));
							Push(&LL, GetIdx("Op"));
							Push(&LL, GetIdx("Gvariabel"));
						}
						else{
							Push(&LL, GetIdx("Gvariabel"));
						}
					}
					else{
						int j,c=1;
						for(j=i+1;j<Psize&&c>0;j++){
							if(Program[j].token == GetIdx(")"))
								c--;
							else if(Program[j].token == GetIdx("("))
								c++;
						}
						if(c==0 && Program[j].token >= GetIdx("+") && Program[j].token <= GetIdx("mod")){
							Push(&LL, GetIdx("Ekspresi"));
							Push(&LL, GetIdx("Op"));
							Push(&LL, GetIdx(")"));
							Push(&LL, GetIdx("Ekspresi"));
							Push(&LL, GetIdx("("));
						}
						else{
							Push(&LL, GetIdx(")"));
							Push(&LL, GetIdx("Ekspresi"));
							Push(&LL, GetIdx("("));
						}
					}
					break;
				case 57 : // Op -> +
					Pop(&LL, &A);
					Push(&LL, GetIdx("+"));
					break;
				case 58 : // Op -> -
					Pop(&LL, &A);
					Push(&LL, GetIdx("-"));
					break;
				case 59 : // Op -> *
					Pop(&LL, &A);
					Push(&LL, GetIdx("*"));
					break;
				case 60 : // Op -> div
					Pop(&LL, &A);
					Push(&LL, GetIdx("div"));
					break;
				case 61 : // Op -> mod
					Pop(&LL, &A);
					Push(&LL, GetIdx("mod"));
					break;
				case 62 : // IO -> input ( Gvariabel ) ;
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx(")"));
					Push(&LL, GetIdx("Gvariabel"));
					Push(&LL, GetIdx("("));
					Push(&LL, GetIdx("input"));
					break;
				case 63 : // IO -> output ( Gvariabel ) ;
					Pop(&LL, &A);
					Push(&LL, GetIdx(";"));
					Push(&LL, GetIdx(")"));
					Push(&LL, GetIdx("Gvariabel"));
					Push(&LL, GetIdx("("));
					Push(&LL, GetIdx("output"));
					break;
				case 64 : // Gvariabel -> variabel
				case 65 : // Gvariabel -> variabel [ Ekspresi ]
					Pop(&LL, &A);
					if(Program[i+1].token == GetIdx("[")){
						Push(&LL, GetIdx("]"));
						Push(&LL, GetIdx("Ekspresi"));
						Push(&LL, GetIdx("["));
					}
					Push(&LL, GetIdx("variabel"));
				break;
				default : 
					errormsg(i);
					return ;
			}
			if(!IsEmpty(LL)){
				printf("-> ");
				PrintDeriv(i);
				puts("");
			}
		}
	}
	puts("");
	if(IsEmpty(LL)&&i==Psize){
		printf("%d total of token(s)\n", Psize);
		printf("Parsing %d line(s) of code finished successfully\n", line);
	}
	else{
		errormsg(i-1);
	}
}

void BacaTerminal(){
	FILE *F = fopen(FileTerminal, "r");
	Tsize = 0;
	while(fscanf(F, "%s", s)>0){
		strcpy(Set[Tsize], s);
		Tsize++;
	}
	fclose(F);
}

void BacaVariabel(){
	FILE *F = fopen(FileVariabel, "r");
	Vsize = Tsize;
	while(fscanf(F, "%s", s)>0){
		strcpy(Set[Vsize], s);
		Vsize++;
	}
	fclose(F);
}

void BacaTabel(){
	char a[100], b[100];
	int c;
	FILE *F = fopen(FileTabel, "r");
	memset(Tab, 0, sizeof Tab);
	while(fscanf(F, "%s %s %d", a, b, &c)>2){
		Tab[GetIdx(a)][GetIdx(b)] = c;
	}
	fclose(F);
}

int main(int argc, char *argv[]){
	int i;
	BacaTerminal();
	BacaVariabel();
	BacaTabel();
	// for(i=0;i<Vsize;i++){
		// printf("%d - %s\n", i, Set[i]);
	// }
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
