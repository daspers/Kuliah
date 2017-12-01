#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "phases.h"

FILE *infile;

int main(int argc, char *argv[])
{
    char *input;

    /* Saat dijalankan tanpa argumen, program akan membaca dari standar input */
    if (argc == 1) {  
	infile = stdin;
    } 

    /* Saat dijalankan dengan argumen berupa file, program akan membaca file sampai
    	EOF, kemudian akan membaca dari standar input. Jadi, setiap sudah berhasil menyelesaikan
    	satu level, password untuk memecahkan level tersebut dapat ditaruh ke dalam suatu file 
    	dan dapat menghindari untuk mengetik ulang */
    else if (argc == 2) {
	if (!(infile = fopen(argv[1], "r"))) {
	    printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
	    exit(8);
	}
    }

   	/* Tidak dapat memanggil program dengan lebih dari satu baris command */
    else {
	printf("Usage: %s [<input_file>]\n", argv[0]);
	exit(8);
    }

    /* Melakukan semua bagian rahasia yang membuat program lebih susah untuk dijinakkan */
    initialize_bomb();

    printf("Welcome to the wizarding world. You have 6 horcruxes to destroy.\n");
    printf("Careful not to get yourself killed. Have fun!\n");

    /* Terdiri dari 6 level */
    input = read_line();             /* Membaca input                   */
    phase_1(input);                  /* Menjalankan level               */
    phase_defused();                 /* Sial mereka berhasil menyelesaikannya
				      * Biarkan aku tahu bagaimana cara mereka menyelsaikannya */
    printf("Whoa, you destroyed Tom Riddle's diary with that Basilisk fang. How about the next one?\n");

    /* Level 2 akan lebih susah. Tidak ada seorang pun yang bisa mengetahui cara menyelasaikan level ini */
    input = read_line();
    phase_2(input);
    phase_defused();
    printf("Marvolo Gaunt's Ring has been destroyed. Keep going!\n");

    /* Saya kira semua ini sangat gampang. Mari tambahkan beberapa kekompleksan dalam kode untuk membuat orang bingung */
    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Another horcrux down, Salazar Slytherin's locket this time!\n");

    /* Benarkah? Seberapa pintar anda dalam matematika silahkan kerjakan soal aneh ini */
    input = read_line();
    phase_4(input);
    phase_defused();
    printf("Helga Hufflepuff's Cup? What a waste. Keep up the good work!\n");
    
    /* Lari lari kesana kemari, kemanapun kita pergi, akan terkena jebakan */
    input = read_line();
    phase_5(input);
    phase_defused();
    printf("That was Rowena Ravenclaw's Diadem, on to the next one.\n");

    /* Level ini tidak akan pernah terpakai, karena tidak ada seorang pun yang dapat melewati level sebelumnya. Mari kita lambah level kepedasan soal */
    input = read_line();
    phase_6(input);
    phase_defused();
    printf("Well well well. Congrats Mr. Longbottom you just killed Nagini the Snake.\n");

    /* Wow, mereka berhasil melewatinya! tetapi apakah kamu lupa ada sesuatu yang kurang? Ayo cari tahu */
    
    return 0;
}

/***************************************************************************
 * LICENSE:
 *
 * Dr. Evil Incorporated (the PERPETRATOR)
***************************************************************************/
