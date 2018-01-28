#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define se second
#define fi first

using namespace std;

typedef struct{
	bool hor;
	int i;
	int j;
	int len;
} slot;

vector<string> jawabantts;
vector<string> tts; // tts nya
int panjang;
//map<int, vector<string>> kata; //pengelompokkan kata terhadap panjang
vector<string> kata[100];
//map<string, int> cekkata; // cek jika kata masih bisa dipake >0
bool cekkata[100][200];
vector<slot> pengisi;
// cek horizontal dan vertical -> pengisi.hor
// panjang pengisi.len
// index (i,j) -> i = pengisi.i, j = pengisi.j
bool SudahSelesai = false;

void tubespayah(int idx){
	if(SudahSelesai)
		return;
	if(idx == pengisi.size()){
		SudahSelesai = true;
		return;
	}
	int panjang = pengisi[idx].len;
	for(int i = 0;i<kata[panjang].size();i++){
		if(!cekkata[panjang][i]) //kata telah digunakan :(
			continue;
		//cek jika bisa diisi di tts
		bool bisa = true;
		if(pengisi[idx].hor){ //jika horizontal
			for(int j=0;j<panjang;j++){
				if(tts[pengisi[idx].i][j+pengisi[idx].j]!='-'&&tts[pengisi[idx].i][j+pengisi[idx].j]!=kata[panjang][i][j])
					bisa = false;
			}
		}
		else{	//vertikal
			for(int j=0;j<panjang;j++){
				if(tts[j+pengisi[idx].i][pengisi[idx].j]!='-'&&tts[j+pengisi[idx].i][pengisi[idx].j]!=kata[panjang][i][j])
					bisa = false;
			}
		}
		if(bisa){ // kalo bisa, ya diisi lah
			string temp="";	//temporary untuk kembali ke wujud asal
			if(pengisi[idx].hor){ //jika horizontal
				for(int j=0;j<panjang;j++){
					temp +=tts[pengisi[idx].i][j+pengisi[idx].j];
					tts[pengisi[idx].i][j+pengisi[idx].j] = kata[panjang][i][j];
				}
			}
			else{	//vertikal
				for(int j=0;j<panjang;j++){
					temp +=tts[j+pengisi[idx].i][pengisi[idx].j];
					tts[j+pengisi[idx].i][pengisi[idx].j] = kata[panjang][i][j];
				}
			}
			cekkata[panjang][i] = false; //kurangi satu, karna kepake
			tubespayah(idx+1);
			if(SudahSelesai) // kalo udah ketemu jawaban jgn lanjut iterasi ntar tambah lama
				return;
			//kembalikkan ke asal untuk iterasi selanjutnya
			cekkata[panjang][i] = true; //tambahkan satu, karna ga jadi pake
			if(pengisi[idx].hor){ //jika horizontal
				for(int j=0;j<panjang;j++)
					tts[pengisi[idx].i][j+pengisi[idx].j] = temp[j];
			}
			else{	//vertikal
				for(int j=0;j<panjang;j++)
					tts[j+pengisi[idx].i][pengisi[idx].j] = temp[j];
			}
		}
	}
}

int main(){
	//input s :/
	string s,tem;
	cin>>s;
	fstream F;
	F.open(s, fstream::in);
	F >> panjang;
	for(int i=0;i<panjang;i++){
		F>>tem;
		tts.push_back(tem);
	}
	F>>tem;
	//input kata dan isi cekkata dan kata
	string kat="";
	for(auto x : tem){
		if(x==';'){
			// if(cekkata.count(kat))
				// cekkata[kat]++;
			// else
				// cekkata[kat]=1;
			kata[kat.size()].push_back(kat);
			kat="";
		}
		else
			kat+=x;
	}
	//isi pengisi
	for(int i=0;i<panjang;i++){
		for(int j=0;j<panjang;j++){
			if(tts[i][j]=='-'){
				int k, len;
				slot tempe;
				tempe.i= i;
				tempe.j= j;
				if (j>0 && j+1<panjang){
					if(tts[i][j-1]=='#' && tts[i][j+1]=='-'){
						for(k=j+1, len=1;k<panjang && tts[i][k]=='-';k++)
							len++;
						tempe.hor = true;
						tempe.len = len;
						if(len>1)
							pengisi.push_back(tempe);
					}
				}
				else if (j+1<panjang){
					if(tts[i][j+1]=='-'){
						for(k=j+1, len=1;k<panjang && tts[i][k]=='-';k++)
							len++;
						tempe.hor = true;
						tempe.len = len;
						if(len>1)
							pengisi.push_back(tempe);
					}
				}
				if (i>0 and i+1<panjang){
					if(tts[i-1][j]=='#' and tts[i+1][j]=='-') {
						for(k=i+1, len=1;k<panjang && tts[k][j]=='-';k++)
							len++;
						tempe.hor = false;
						tempe.len = len;
						if(len>1)
							pengisi.push_back(tempe);
					}
				}
				else if (i+1<panjang) {
					if(tts[i+1][j]=='-'){
						for(k=i+1, len=1;k<panjang && tts[k][j]=='-';k++)
							len++;
						tempe.hor = false;
						tempe.len = len;
						if(len>1)
							pengisi.push_back(tempe);
					}
				}
			}
		}
	}
	for(int i=0;i<100;i++)
		for(int j=0;j<200;j++)
			cekkata[i][j] = true;
	srand(unsigned(time(0)));
	for(int i =2;i<100;i++){
		if(kata[i].size())
			random_shuffle(kata[i].begin(), kata[i].end());
	}
	//start time counter
	time_t begin = clock();
	tubespayah(0); //dari elemen pertama pengisian
	time_t end = clock();
	//end time counter
	//output jawaban :(
	for(auto z:tts)
		cout<<z<<endl;
	cout<<1000.0*double(end-begin)/(CLOCKS_PER_SEC)<<endl;
	return 0;
}
