import java.lang.*;
import java.io.*;
import java.text.*;
import java.util.*;

public class AugmentedMatrix{
	public double mat[][];
	public int rows;
	public int cols;
	public int NS;
	/* Konstruktor */
	public AugmentedMatrix(int rows, int cols){
		this.mat = new double[cols][cols+1];
		this.rows = rows;
		this.cols = cols;
		this.NS = cols;
	}
	/* Selektor */
	public double Elmt(int i, int j){
		return this.mat[i][j];
	}
	public void SetElmt(int i, int j, double val){
		this.mat[i][j] = val;
	}
	/* Operasi Lain-Lain */
	public boolean IsFull0(int i){
		int j;
		for(j=0;j<this.NS;j++){
			if(!this.ElmtNear0(i,j))
				return false;
		}
		return true;
	}
	public boolean IsSolutionExist(){
		int i,j;
		for(i=0;i<this.rows;i++){
			if(this.IsFull0(i)){
				if(!this.ElmtNear0(i,this.NS))
					return false;
			}
		}
		return true;
	}
	public void SwapRow(int i, int j){
		double t;
		for(int k = 0; k <= this.cols; k++) {
			t = this.Elmt(i,k);
			this.SetElmt(i,k,this.Elmt(j,k));
			this.SetElmt(j,k,t);
		}
	}
	public void pindahkan(){
		for(int i = 0; i < this.cols; i++) {
			if (this.ElmtNear0(i,i)) {
				for(int j = i-1; j >= 0; j--) {
					if (!this.ElmtNear0(j,i)) {
						if (this.ElmtNear0(j,j))
							this.SwapRow(i,j);
					}
				}
			}
		}
	}
	public boolean IsInfinite(){
		for(int i=0;i<this.NS;i++){
			if(this.IsFull0(i))
				return true;
		}
		return false;
	}
	public boolean ElmtNear0(int i, int j){
		return Math.abs(this.Elmt(i,j))<1e-9;
	}
	public void GausJordanElimination() {
	// input: N, Augmented Matrix Aug, output: Column vector X, the answer
		int i, j, k, l;
		double t;

		for (i = 0; i < this.cols; i++) { // the forward elimination phase
			l = i;
			for (j = i + 1; j < this.cols; j++) {// which row has largest column value
				if (Math.abs(this.Elmt(j,i)) > Math.abs(this.Elmt(l,i))) {
					l = j; // remember this row l
				}
			}
			// swap this pivot row, reason: minimize floating point error
			this.SwapRow(i,l);
			
			if (this.ElmtNear0(i,i)) {
				continue;
			} else {
				for (j = i + 1; j < this.cols; j++) {// the actual forward elimination phase
					for (k = this.cols; k >= i; k--) {
						this.SetElmt(j,k,this.Elmt(j,k)-this.Elmt(i,k)*this.Elmt(j,i)/this.Elmt(i,i));
					}
				}
				t = 1/this.Elmt(i,i);
				for(j = i; j <= this.cols; j++) {
					this.SetElmt(i,j,this.Elmt(i,j)*t);
				}
			}
			this.pindahkan();	
		}	
		
		this.Sederhanakan();
	}
	public void Sederhanakan(){
		double t;
		
		for(int i = 1; i < this.cols; i++) {
			if (Math.abs(this.Elmt(i,i)) <= 1.00000001 && !this.ElmtNear0(i,i)) {
				for(int k = i-1; k >= 0; k--) {
					if (!this.ElmtNear0(k,i)) {
						t = this.Elmt(k,i);
						for(int j = i; j <= this.cols; j++) {
							this.SetElmt(k,j,this.Elmt(k,j)-(this.Elmt(i,j)*t));
						}
					}
				}
			}
		}
	}
	public void PrintMatriks(double cons, DecimalFormat presisi){
		int i,j;
		for(i=0;i<this.rows;i++){
			for(j=0;j<this.cols;j++){
				System.out.print(presisi.format(this.Elmt(i,j)/cons));
				if(j<this.cols-1)
					System.out.print("\t");
			}
			System.out.println();
		}
	}
}

public class ColumnVector{
	public double[] vec;
	public double size;
	public ColumnVector(int s){
		this.vec = new double[s];
		this.size = s;
	}
	public double Elmt(int i){
		return this.vec[i];
	}
	public void SetElmt(int i, double val){
		this.vec[i] = val;
	}
	public void GetSolution(AugmentedMatrix mat){
		int  j, k;
		double t;
		for (j = mat.NS - 1; j >= 0; j--) { // start from back
			this.SetElmt(j, mat.Elmt(j,mat.NS)); // the answer is here
		}
	}
	public void PrintVector(DecimalFormat presisi){
		int i;
		for(i=0;i<this.size;i++){
			System.out.println("var_"+(i+1)+" = "+presisi.format(this.Elmt(i)));
		}
	}
}

public class Parameter{
	public double[] cons;
	public boolean[] exist;
	public String[] pers;
	public int size;
	//Konstruktor
	public Parameter(int s){
		this.cons = new double[s];
		this.exist = new boolean[s];
		this.pers = new String[s];
		this.size = s;
	}
	public Parameter(Parameter p){
		this.cons = p.cons;
		this.size = p.size;
		this.exist = p.exist;
		this.pers = p.pers;
	}
	public void GetParameter(AugmentedMatrix mat, DecimalFormat presisi){
		int i, j;
		for(i = mat.cols-1;i>=0;i--){
			this.cons[i] = mat.Elmt(i,mat.cols);
			this.exist[i] = true;
			this.pers[i] ="";
			if(mat.IsFull0(i)){
				this.exist[i] = false;
			}
			else{
				for(j=0;j<mat.cols;j++){
					if(j!=i && !this.exist[j]&&!mat.ElmtNear0(i,j)){
						if(mat.Elmt(i,j)<0){
							this.pers[i] +=" + ";
						}
						else{
							this.pers[i] +=" - ";
						}
						this.pers[i]+=(presisi.format(Math.abs(mat.Elmt(i,j))));
						this.pers[i]+="*(t"+(j+1)+")";
					}
				}
			}
		}
	}
}

public class AlGeo{
	static DecimalFormat presisi = new DecimalFormat("#0.00000");
	static boolean printtofile = true;
	static boolean bacafile = false;
	static int NS = 0;
	
	public static Parameter ParameterSolve(AugmentedMatrix mat){
		Parameter par = new Parameter(mat.cols);
		for(int i=0;i<mat.cols;i++){
			if(!mat.IsFull0(i)){
				
			}
		}
		return par;
	}
	
	static void ReadFileNSolve(){
		/* Kamus */
		Scanner read;
		String ninfile, noutfile;
		File Infile, Outfile;
		int row, col, i, j, k;
		AugmentedMatrix mat;
		ColumnVector vec;
		Parameter par = new Parameter(0);
		PrintWriter fwrite=null;
		/* Algoritma */
		try{
			//Input nama file
			read = new Scanner(System.in);
			System.out.print("Masukkan nama file input : ");
			ninfile = read.nextLine();
			if(printtofile){
				System.out.print("Masukkan nama file output : ");
				noutfile = read.nextLine();
				fwrite = new PrintWriter(noutfile, "UTF-8");
			}
			System.out.println();
			Infile = new File(ninfile);
			Scanner readf = new Scanner(Infile);
			//Read number of matrix
			int num = readf.nextInt();
			for(i=1;i<=num;i++){
				//Read row and col
				row = readf.nextInt();
				col = readf.nextInt();
				//Assign matrix size
				if(row>col){
					mat = new AugmentedMatrix(row, row);
					for(i=0;i<row;i++){
						for(j=0;j<=col;j++){
							mat.SetElmt(i,j,read.nextDouble());
						}
					}
					for(i=row; i<col;i++){
						for(j=0;j<=col;j++){
							mat.SetElmt(i,j,0);
						}
					}
				}
				else{
					mat = new AugmentedMatrix(col, col);
					for(i=0;i<row;i++){
						for(j=0;j<=col;j++){
							mat.SetElmt(i,j,read.nextDouble());
						}
					}
					for(i=row; i<col;i++){
						for(j=0;j<=col;j++){
							mat.SetElmt(i,j,0);
						}
					}
				}
				mat.NS = col;
				//Solve it
				mat.GausJordanElimination();
				//Print to console and file
				System.out.println("Input "+i);
				if(printtofile)
					fwrite.println("Input "+i);
				if(!mat.IsSolutionExist()){
					System.out.println("No Solution Exist");
				}
				if (mat.IsInfinite()) {
					System.out.println("Infinit Solution");
					par = new Parameter(mat.NS);
					par.GetParameter(mat, presisi);
					for(j=0;j<par.size;j++){
						System.out.printf("var_%d = ", j+1);
						if(printtofile)
							fwrite.printf("var_%d = ", j+1);
						if(!par.exist[j]){
							System.out.printf("t%d", j+1);
							if(printtofile)
								fwrite.printf("t%d", j+1);
						}
						else{
							System.out.print(presisi.format(par.cons[j]));
							System.out.print(par.pers[j]);
							if(printtofile){
								fwrite.print(presisi.format(par.cons[j]));
								fwrite.print(par.pers[j]);
							}
						}
						System.out.println();
						if(printtofile)
							fwrite.println();
					}
				}
				else{
					vec = new ColumnVector(mat.NS);
					vec.GetSolution(mat);
					if(printtofile){
						fwrite.println("Solusi :");
						for(j=0;j<vec.size;j++){
							fwrite.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)));
						}
					}
					System.out.println("Solusi :");
					vec.PrintVector(presisi);
				}
				System.out.println();
				if(printtofile)
					fwrite.println();
			}
			readf.close();
			if(printtofile)
				fwrite.close();
		}
		catch(Exception e){ // if the file not exist
			e.printStackTrace();
		}
	}
	
	public static void ReadInputMatrixNSolve(){
		Scanner read = new Scanner(System.in);
		int row, col, j, i;
		System.out.print("Masukkan banyak variabel : ");
		col = read.nextInt();
		System.out.print("Masukkan banyak persamaan : ");
		row = read.nextInt();
		System.out.println("Masukkan SPL dengan format (Koef1 Koef2 .. KoefN Hasil) sebanyak persamaan yang dimasukkan");
		AugmentedMatrix mat;
		ColumnVector vec;
		Parameter par = new Parameter(col);
		if(row>col){
			mat = new AugmentedMatrix(row, row);
			for(i=0;i<row;i++){
				for(j=0;j<=col;j++){
					mat.SetElmt(i,j,read.nextDouble());
				}
			}
			for(i=row; i<col;i++){
				for(j=0;j<=col;j++){
					mat.SetElmt(i,j,0);
				}
			}
		}
		else{
			mat = new AugmentedMatrix(col, col);
			for(i=0;i<row;i++){
				for(j=0;j<=col;j++){
					mat.SetElmt(i,j,read.nextDouble());
				}
			}
			for(i=row; i<col;i++){
				for(j=0;j<=col;j++){
					mat.SetElmt(i,j,0);
				}
			}
		}
		mat.NS = col;
		//Solve
		mat.GausJordanElimination();
		mat.PrintMatriks(1,presisi);
		//Output
		try{
			String nfile;
			PrintWriter fwrite;
			fwrite = null;
			if(printtofile){
				System.out.print("Masukkan nama file output : ");
				nfile = read.nextLine();
				nfile = read.nextLine();
				fwrite = new PrintWriter(nfile, "UTF-8");
				fwrite.println("Hasil : ");
			}
			System.out.println("Hasil : ");
			if(!mat.IsSolutionExist()){
				System.out.println("No Solution Exist");
				if(printtofile)
					fwrite.println("No Solution Exist");
			}
			else if (mat.IsInfinite()) {
				System.out.println("Infinit Solution");
				par = new Parameter(mat.NS);
				par.GetParameter(mat, presisi);
				for(j=0;j<par.size;j++){
					System.out.printf("var_%d = ", j+1);
					if(printtofile)
						fwrite.printf("var_%d = ", j+1);
					if(!par.exist[j]){
						System.out.printf("t%d", j+1);
						if(printtofile)
							fwrite.printf("t%d", j+1);
					}
					else{
						System.out.print(presisi.format(par.cons[j]));
						System.out.print(par.pers[j]);
						if(printtofile){
							fwrite.print(presisi.format(par.cons[j]));
							fwrite.print(par.pers[j]);
						}
					}
					System.out.println();
					if(printtofile)
						fwrite.println();
				}
			}
			else{
				vec = new ColumnVector(mat.NS);
				vec.GetSolution(mat);
				for(j=0;j<vec.size;j++){
					System.out.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)));
					if(printtofile)
						fwrite.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)));
				}
			}
			if(printtofile)
				fwrite.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	
	static String SetPresisi(int n){
		String f = "#0.";
		while(n-->0){
			f+="0";
		}
		return f;
	}
	
	static void MatriksHilbert()
	// Untuk mengisi matriks dari persamaan Hilbert
	{
		Scanner r = new Scanner(System.in);
		String nfile ="";
		int i,j,N =0;
		double cons = 1e6;
		
		if(bacafile){
			boolean kebaca = false;
			while(!kebaca){
				try{
					System.out.print("Nama file : ");
					nfile = r.nextLine();
					File file = new File (nfile);
					r = new Scanner(file);
					N = r.nextInt();
					kebaca = true;
				}
				catch(Exception e){
					System.out.println("File \'"+nfile+"\' tidak ditemukan!");
				}
			}
		}
		else{
			r = new Scanner(System.in);
			System.out.print("Masukkan N : ");
			N = r.nextInt();
		}
		
		AugmentedMatrix mat = new AugmentedMatrix(N,N);
		ColumnVector vec = new ColumnVector(N);

		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				mat.SetElmt(i,j, cons/(j+i+1));
			}
		}
		
		for(i = 0; i < N; i++) {
			mat.SetElmt(i,N, 1);
		}
		System.out.println("Matriks Hilbert : ");
		mat.PrintMatriks(cons,presisi);
		System.out.println();
		
		//Solving
		mat.GausJordanElimination();
		vec.GetSolution(mat);
		
		//Print
		try{
			PrintWriter fwrite;
			fwrite = null;
			if(printtofile){
				System.out.print("Masukkan nama file output : ");
				nfile = r.nextLine();
				nfile = r.nextLine();
				fwrite = new PrintWriter(nfile, "UTF-8");
				fwrite.println("Hasil : ");
			}
			System.out.println("Hasil : ");
			for(j=0;j<vec.size;j++){
				System.out.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)*cons));
				if(printtofile)
					fwrite.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)*cons));
			}
			if(printtofile)
				fwrite.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	
	static void Interpolasi(){
		// Untuk mengisi matriks sesuai dengan masukan dari user
		double x, t;
		int N=1, i, j, pil;
		String nfile="";
		Scanner r = new Scanner(System.in);
		
		if(bacafile){
			boolean kebaca = false;
			while(!kebaca){
				try{
					System.out.print("Nama file : ");
					nfile = r.nextLine();
					File file = new File (nfile);
					r = new Scanner(file);
					N = r.nextInt();
					kebaca = true;
				}
				catch(Exception e){
					System.out.println("File \'"+nfile+"\' tidak ditemukan!");
				}
			}
		}
		else{
			r = new Scanner(System.in);
			System.out.print("Masukkan N : ");
			N = r.nextInt();
		}
		
		AugmentedMatrix mat = new AugmentedMatrix(N,N);
		ColumnVector vec = new ColumnVector(N);
		
		for(i = 0; i < N; i++) {
			System.out.print("Masukkan x_"+i+" : ");
			x = r.nextDouble();
			for(j = 0; j < N; j++) {
				mat.SetElmt(i,j,Math.pow(x,j));
			}
		}

		for(i = 0; i < N; i++) {
			System.out.print("Masukkan nilai dari f(x_"+i+") = ");
			mat.SetElmt(i,N,r.nextDouble());
		}
		
		//Solving
		mat.GausJordanElimination();
		vec.GetSolution(mat);
		
		//Print
		try{
			PrintWriter fwrite;
			fwrite = null;
			if(printtofile){
				System.out.print("Masukkan nama file output : ");
				nfile = r.nextLine();
				nfile = r.nextLine();
				fwrite = new PrintWriter(nfile, "UTF-8");
				fwrite.println("Hasil : ");
			}
			System.out.println("Hasil : ");
			for(j=0;j<vec.size;j++){
				System.out.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)));
				if(printtofile)
					fwrite.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)));
			}
			System.out.println("Apakah ingin menampilkan fungsi polinom(1 - Ya;2 - Tidak)?");
			System.out.print("Pilihan : ");
			pil = r.nextInt();
			if(pil==1){
				boolean first = true;
				System.out.print("F(x) = ");
				if(printtofile)
					fwrite.print("F(x) = ");
				for(j=0;j<vec.size;j++){
					if(Math.abs(vec.Elmt(j))>1e-9){
						if(!first){
							if(vec.Elmt(j)>0){
								System.out.print(" + ");
								if(printtofile)
									fwrite.print(" + ");
							}
							else{
								System.out.print(" - ");
								if(printtofile)
									fwrite.print(" - ");
							}
						}
						else{
							first = false;
							if(vec.Elmt(j)<0){
								System.out.print("-");
								if(printtofile)
									fwrite.print("-");
							}
						}
						System.out.print(presisi.format(Math.abs(vec.Elmt(j)))+"*x^"+(j));
						if(printtofile)
							fwrite.print(presisi.format(Math.abs(vec.Elmt(j)))+"*x^"+(j));
					}
				}
				System.out.println();
				if(printtofile)
					fwrite.println();
			}
			System.out.println("Apakah ingin mencoba fungsi polinom(1 - Ya;2 - Tidak)?");
			System.out.print("Pilihan : ");
			pil = r.nextInt();
			while(pil==1){
				System.out.print("Masukkan x : ");
				t = r.nextDouble();
				x=0;
				for(j=0;j<vec.size;j++){
					x += vec.Elmt(j)*Math.pow(t,j);
				}
				System.out.println("F("+t+") = "+presisi.format(x));
				System.out.println("Apakah ingin mencoba fungsi polinom(1 - Ya;2 - Tidak)?");
				System.out.print("Pilihan : ");
				pil = r.nextInt();
			}
			if(printtofile)
				fwrite.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	
	static double fx(double x){
		return 1.0/((1.0 + Math.sqrt(x) + Math.pow(x, 2)) * Math.pow(Math.E, x));
	}
	
	static void InterpolasiFungsie() {
	//Untuk mengisi matriks danri fungsi yang telah diberikan
		double a=0, b=1, x, t;
		String nfile="";
		int N=1, i, j, pil;
		Scanner r = new Scanner(System.in);

		if(bacafile){
			boolean kebaca = false;
			while(!kebaca){
				try{
					System.out.print("Nama file : ");
					nfile = r.nextLine();
					File file = new File (nfile);
					r = new Scanner(file);
					N = r.nextInt();
					a = r.nextDouble();
					b = r.nextDouble();
					kebaca = true;
				}
				catch(Exception e){
					System.out.println("File \'"+nfile+"\' tidak ditemukan!");
				}
			}
		}
		else{
			r = new Scanner(System.in);
			System.out.print("Masukkan N : ");
			N = r.nextInt();
			System.out.print("Masukkan batas bawah : ");
			a = r.nextDouble();
			System.out.print("Masukkan batas atas : ");
			b = r.nextDouble();
		}
		
		double h = (b-a)/N;
		N++;
		
		AugmentedMatrix mat = new AugmentedMatrix(N,N);
		ColumnVector vec = new ColumnVector(N);
		
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				mat.SetElmt(i,j,Math.pow(a,j));
			}
			mat.SetElmt(i,N,fx(a));
			a = a+h;
		}
		
		//Solving
		mat.GausJordanElimination();
		vec.GetSolution(mat);
		
		//Print
		try{
			PrintWriter fwrite;
			fwrite = null;
			if(printtofile){
				System.out.print("Masukkan nama file output : ");
				nfile = r.nextLine();
				nfile = r.nextLine();
				fwrite = new PrintWriter(nfile, "UTF-8");
				fwrite.println("Hasil : ");
			}
			System.out.println("Hasil : ");
			for(j=0;j<vec.size;j++){
				System.out.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)));
				if(printtofile)
					fwrite.println("var_"+(j+1)+" = "+ presisi.format(vec.Elmt(j)));
			}
			System.out.println("Apakah ingin menampilkan persamaan polinom(1 - Ya;2 - Tidak)?");
			System.out.print("Pilihan : ");
			pil = r.nextInt();
			if(pil==1){
				boolean first = true;
				System.out.print("F(x) = ");
				if(printtofile)
					fwrite.print("F(x) = ");
				for(j=0;j<vec.size;j++){
					if(Math.abs(vec.Elmt(j))>1e-9){
						if(!first){
							if(vec.Elmt(j)>0){
								System.out.print(" + ");
								if(printtofile)
									fwrite.print(" + ");
							}
							else{
								System.out.print(" - ");
								if(printtofile)
									fwrite.print(" - ");
							}
						}
						else{
							first = false;
							if(vec.Elmt(j)<0){
								System.out.print("-");
								if(printtofile)
									fwrite.print("-");
							}
						}
						System.out.print(presisi.format(Math.abs(vec.Elmt(j)))+"*x^"+(j));
						if(printtofile)
							fwrite.print(presisi.format(Math.abs(vec.Elmt(j)))+"*x^"+(j));
					}
				}
				System.out.println();
				if(printtofile)
					fwrite.println();
			}
			System.out.println("Apakah ingin mencoba fungsi polinom(1 - Ya;2 - Tidak)?");
			System.out.print("Pilihan : ");
			pil = r.nextInt();
			while(pil==1){
				System.out.print("Masukkan x : ");
				t = r.nextDouble();
				x=0;
				for(j=0;j<vec.size;j++){
					x += vec.Elmt(j)*Math.pow(t,j);
				}
				System.out.println("F("+t+") = "+presisi.format(x));
				System.out.println("Apakah ingin mencoba fungsi polinom(1 - Ya;2 - Tidak)?");
				System.out.print("Pilihan : ");
				pil = r.nextInt();
			}
			if(printtofile)
				fwrite.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	
	static void ShowMenu(){
		System.out.println("Menu - Program penyelesai SPL");
		System.out.println("0  - Info program dan credits");
		System.out.println("1  - Input SPL dari console");
		System.out.println("2  - Baca SPL dari file eksternal");
		System.out.println("3  - Input Interpolasi");
		System.out.println("4  - Baca Interpolasi dari file");
		System.out.println("5  - Input Interpolasi dengan fungsi e");
		System.out.println("6  - Baca Interpolasi dengan fungsi e dari file");
		System.out.println("7  - Input Matriks Hilbert");
		System.out.println("8  - Baca Matriks Hilbert dari file");
		System.out.println("9  - Ubah presisi (default : 5)");
		System.out.println("10 - Ubah pengaturan output ke file (set:"+(printtofile?"true":"false")+")");
		System.out.println("11 - Keluar dari program");
		System.out.print  ("Pilihan : ");
	}
	
	public static void main(String []args){
		//AugmentedMatrix matrix = ReadInputMatrix();
		Scanner r = new Scanner(System.in);
		int pil, temp;
		ShowMenu();
		pil = r.nextInt();
		while(pil!=11){
			if(pil == 0){
				System.out.println("Program penyelesai sistem persamaan linier");
				System.out.println("Dibuat oleh :");
				System.out.println("1) Tony - 13516010");
				System.out.println("2) Harry Setiawan Hamjaya - 13516079");
				System.out.println("3) Muh Habibi Haidir - 13516085");
				System.out.println("Prodi Teknik Informatika");
				System.out.println("Sekolah Teknik Elektro dan Informatika");
				System.out.println("Institut Teknologi Bandung");
			}
			else if(pil == 1){
				ReadInputMatrixNSolve();
			}
			else if(pil == 2){
				ReadFileNSolve();
			}
			else if(pil == 3){
				Interpolasi();
			}
			else if(pil == 4){
				bacafile = true;
				Interpolasi();
				bacafile = false;
			}
			else if(pil == 5){
				InterpolasiFungsie();
			}
			else if(pil == 6){
				bacafile = true;
				InterpolasiFungsie();
				bacafile = false;
			}
			else if(pil == 7){
				MatriksHilbert();
			}
			else if(pil == 8){
				bacafile = true;
				MatriksHilbert();
				bacafile = false;
			}
			else if(pil == 9){
				System.out.print("Masukkan presisi yg diinginkan (>=1) : ");
				temp = r.nextInt();
				if(temp>=1){
					presisi = new DecimalFormat(SetPresisi(temp));
					System.out.println("Presisi berhasil diubah menjadi "+temp);
				}
				else
					System.out.println("Presisi gagal diubah : Masukkan salah");
			}
			else if(pil == 10){
				System.out.println("Mau tulis output ke file eksternal ?");
				System.out.println("1 - Ya");
				System.out.println("2 - Tidak");
				System.out.print  ("Pilihan : ");
				temp = r.nextInt();
				if(temp==1){
					printtofile = true;
					System.out.println("Pengaturan berhasil diubah");
				}
				else if(temp==2){
					printtofile = false;
					System.out.println("Pengaturan berhasil diubah");
				}
				else
					System.out.println("Pengaturan gagal diubah : Masukkan salah");
			}
			else if(pil!=11){
				System.out.println("Masukkan Salah!!");
			}
			System.out.println();
			ShowMenu();
			pil = r.nextInt();
		}
		System.out.println("Sampai jumpa");
	}
};
