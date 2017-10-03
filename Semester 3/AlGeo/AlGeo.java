import java.lang.*;
import java.io.*;
import java.util.*;

class AugmentedMatrix{
	public double mat[][];
	public int row;
	public int col;
	public AugmentedMatrix(int rows, int cols){
		this.mat = new double[rows][cols+1];
		this.row = rows;
		this.col = cols;
	}
	public double Elmt(int i, int j){
		return this.mat[i][j];
	}
	public void SetElmt(int i, int j, double val){
		this.mat[i][j] = val;
	}
}

class ColumnVector{
	public double[] vec;
	public double size;
	public ColumnVector(){
		this.vec = new double[0];
		this.size = 0;
	}
	public ColumnVector(int s){
		this.vec = new double[s];
		this.size = s;
	}
	public ColumnVector(ColumnVector v){
		this.vec = v.vec;
		this.size = v.size;
	}
	public double Elmt(int i){
		return this.vec[i];
	}
	public void SetElmt(int i, double val){
		this.vec[i] = val;
	}
}

public class AlGeo{
	public static boolean Infinit;
	
	public static AugmentedMatrix ReadInputMatrix(){
		Scanner read = new Scanner(System.in);
		int row, col;
		System.out.print("Masukkan banyak persamaan : ");
		row = read.nextInt();
		System.out.print("Masukkan banyak variabel : ");
		col = read.nextInt();
		AugmentedMatrix mat = new AugmentedMatrix(row, col);
		for(int i=0;i<row;i++){
			for(int j=0;j<=col;j++){
				mat.SetElmt(i,j,read.nextDouble());
			}
		}
		for(int i=row; i<col;i++){
			for(int j=0;j<=col;j++){
				mat.SetElmt(i,j,0);
			}
		}
		return mat;
	}
	
	public static ColumnVector GaussianElimination(AugmentedMatrix mat){
		int i, j, k, l;
		double t;
		ColumnVector Ans = new ColumnVector(mat.col);
		
		for (i = 0; i < mat.row-1; i++) { // the forward elimination phase
			l = i;
			for (j = i + 1; j < mat.col; j++) {// which row has largest column value
				if (Math.abs(mat.Elmt(j,i)) > Math.abs(mat.Elmt(l,i))) {
					l = j; // remember this row l
				}
			}
			// swap this pivot row, reason: minimize floating point error
			for (k = i; k <= mat.col; k++) {// t is a temporary double variable
				t = mat.Elmt(i,k);
				mat.SetElmt(i,k,mat.Elmt(l,k));
				mat.SetElmt(l,k,t);
			}
			for (j = i + 1; j < mat.row; j++) {// the actual forward elimination phase
				for (k = mat.col; k >= i; k--) {
					mat.SetElmt(j, k, mat.Elmt(j,k)-(mat.Elmt(i,k)*mat.Elmt(j,i)/mat.Elmt(i,i)));
				}
			}
		}
		
		for(i = 0; i < mat.row; i++) {
			Infinit = true;
			for(j = 0; j < mat.col; j++) {
				if (Math.abs(mat.Elmt(i,j)) > 0.0000000001) {					
					Infinit = false;
					break;
				}
			}
			if (Infinit) {
				break;
			} 
		}
		
		for (j = mat.row - 1; j >= 0; j--) { // start from back
			for (t = 0.0, k = j + 1; k < mat.col; k++) {
				t += mat.Elmt(j,k) * Ans.Elmt(k);
			}
			Ans.SetElmt(j,(mat.Elmt(j,mat.col)-t)/mat.Elmt(j,j)); // the answer is here
		}

		return Ans;	
	}
	
	static void ReadFileNSolve(){
		/* Kamus */
		Scanner read;
		String ninfile, noutfile;
		File Infile, Outfile;
		int row, col, i, j, k;
		AugmentedMatrix mat;
		ColumnVector vec;
		PrintWriter fwrite;
		/* Algoritma */
		try{
			//Input nama file
			read = new Scanner(System.in);
			System.out.print("Masukkan nama file input : ");
			ninfile = read.nextLine();
			System.out.print("Masukkan nama file output : ");
			noutfile = read.nextLine();
			Infile = new File(ninfile);
			Scanner readf = new Scanner(Infile);
			fwrite = new PrintWriter(noutfile, "UTF-8");
			//Read number of matrix
			int num = readf.nextInt();
			for(i=1;i<=num;i++){
				//Read row and col
				row = readf.nextInt();
				col = readf.nextInt();
				//Assign matrix size
				mat = new AugmentedMatrix(row, col);
				//Read matrix element
				for(j=0;j<row;j++){
					for(k=0;k<=col;k++){
						mat.SetElmt(j,k,readf.nextDouble());
					}
				}
				for(j=row;j<col;j++){
					for(k=0;k<=col;k++){
						mat.SetElmt(j,k,0);
					}
				}
				//Solve it
				vec = new ColumnVector(GaussianElimination(mat));
				//Print to console and file
				System.out.println("Input "+i);
				fwrite.println("Input "+i);
				if (Infinit) {
					System.out.println("Infinit Solution");
				}
				for(j=0;j<vec.size;j++){
					System.out.printf("var_%d = %.2f\n", j+1, vec.Elmt(j));
					fwrite.printf("var_%d = %.2f\n", j+1, vec.Elmt(j));
				}
				System.out.println();
				fwrite.println();
			}
			readf.close();
			fwrite.close();
			read.close();
		}
		catch(Exception e){ // if the file not exist
			e.printStackTrace();
		}
	}
	
	static void ShowMenu(){
		System.out.println("Opsi pilihan");
		System.out.println("0 - Info program dan credits");
		System.out.println("1 - Input SPL dari console");
		System.out.println("2 - Baca SPL dari file eksternal");
		System.out.println("3 - ");
		System.out.println("4 - Keluar dari program");
		System.out.print  ("Pilihan : ");
	}
	
	public static void main(String []args){
		//AugmentedMatrix matrix = ReadInputMatrix();
		Scanner read = new Scanner(System.in);
		String pil;
		ShowMenu();
		pil = read.nextLine();
		while(pil!="4"){
			if(pil == "0"){
				
			}
			else if(pil == "1"){
				
			}
			else if(pil == "2"){
				
			}
			else if(pil == "3"){
				
			}
			else if(pil == "4"){
				
			}
			else{
				System.out.println("Masukkan Salah!!");
			}
			PrintMenu();
			pil = read.nextLine();
		}
		ReadFileNSolve();
	}
};
