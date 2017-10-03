import java.lang.*;
import java.io.*;
import java.util.*;

class AugmentedMatrix{
	public double mat[][];
	public int rows;
	public int cols;
	public boolean Infinit;
	public AugmentedMatrix(int rows, int cols){
		this.mat = new double[cols][cols+1];
		this.rows = rows;
		this.cols = cols;
		this.Infinit = false;
	}
	public AugmentedMatrix(AugmentedMatrix t){
		this.mat = t.mat;
		this.rows = t.rows;
		this.cols = t.cols;
		this.Infinit = t.Infinit;
	}
	public double Elmt(int i, int j){
		return this.mat[i][j];
	}
	public void SetElmt(int i, int j, double val){
		this.mat[i][j] = val;
	}
	public boolean IsFull0(int i){
		int j;
		for(j=0;j<this.cols;j++){
			if(Math.abs(this.Elmt(i,j)) > 0.0000000001)
				return false;
		}
		return true;
	}
	public boolean IsSolutionExist(){
		int i,j;
		for(i=0;i<this.cols;i++){
			if(this.IsFull0(i)){
				if(Math.abs(this.Elmt(i,cols)) > 0.0000000001)
					return false;
			}
		}
		return true;
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

class Parameter{
	public int[] var;
	public double[] koef;
	public double[] cons;
	public int size;
	//Konstruktor
	public Parameter(int s){
		this.var = new int[s];
		this.koef = new double[s];
		this.cons = new double[s];
		this.size = s;
	}
	public int GetVar(int i){
		return this.var[i];
	}
	public double GetKoef(int i){
		return this.koef[i];
	}
	public double GetConst(int i){
		return this.cons[i];
	}
	//Setter
	public void SetVar(int i, int val){
		this.var[i] = val;
	}
	public void SetKoef(int i, double val){
		this.koef[i] = val;
	}
	public void SetConst(int i, double val){
		this.cons[i] = val;
	}
}

public class AlGeo{
	public static Parameter ParameterSolve(AugmentedMatrix mat){
		Parameter par = new Parameter(mat.cols);
		
		return par;
	}
	
	public static AugmentedMatrix GaussianElimination(AugmentedMatrix mat){
		int i, j, k, l;
		double t;
		
		for (i = 0; i < mat.rows-1; i++) { // the forward elimination phase
			l = i;
			for (j = i + 1; j < mat.cols; j++) {// which row has largest column value
				if (Math.abs(mat.Elmt(j,i)) > Math.abs(mat.Elmt(l,i))) {
					l = j; // remember this row l
				}
			}
			// swap this pivot row, reason: minimize floating point error
			for (k = i; k <= mat.cols; k++) {// t is a temporary double variable
				t = mat.Elmt(i,k);
				mat.SetElmt(i,k,mat.Elmt(l,k));
				mat.SetElmt(l,k,t);
			}
			for (j = i + 1; j < mat.rows; j++) {// the actual forward elimination phase
				for (k = mat.cols; k >= i; k--) {
					mat.SetElmt(j, k, mat.Elmt(j,k)-(mat.Elmt(i,k)*mat.Elmt(j,i)/mat.Elmt(i,i)));
				}
			}
		}
		
		for(i = 0; i < mat.rows; i++) {
			mat.Infinit = true;
			for(j = 0; j < mat.cols; j++) {
				if (Math.abs(mat.Elmt(i,j)) > 0.0000000001) {					
					mat.Infinit = false;
					break;
				}
			}
			if (mat.Infinit) {
				break;
			} 
		}
		
		return mat;	
	}
	
	static ColumnVector GetSolution(AugmentedMatrix mat){
		ColumnVector Ans = new ColumnVector(mat.cols);
		int  j, k;
		double t;
		
		for (j = mat.rows - 1; j >= 0; j--) { // start from back
			for (t = 0.0, k = j + 1; k < mat.cols; k++) {
				t += mat.Elmt(j,k) * Ans.Elmt(k);
			}
			Ans.SetElmt(j,(mat.Elmt(j,mat.cols)-t)/mat.Elmt(j,j)); // the answer is here
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
				mat = new AugmentedMatrix(GaussianElimination(mat));
				//Print to console and file
				System.out.println("Input "+i);
				fwrite.println("Input "+i);
				if(!mat.IsSolutionExist()){
					System.out.println("No Solution Exist");
				}
				if (mat.Infinit) {
					System.out.println("Infinit Solution");
				}
				else{
					vec = new ColumnVector(GetSolution(mat));
					for(j=0;j<vec.size;j++){
						System.out.printf("var_%d = %.2f\n", j+1, vec.Elmt(j));
						fwrite.printf("var_%d = %.2f\n", j+1, vec.Elmt(j));
					}
				}
				System.out.println();
				fwrite.println();
			}
			readf.close();
			fwrite.close();
		}
		catch(Exception e){ // if the file not exist
			e.printStackTrace();
		}
	}
	
	public static void ReadInputMatrixNSolve(){
		Scanner read = new Scanner(System.in);
		int row, col, j, i;
		System.out.print("Masukkan banyak persamaan : ");
		row = read.nextInt();
		System.out.print("Masukkan banyak variabel : ");
		col = read.nextInt();
		AugmentedMatrix mat = new AugmentedMatrix(row, col);
		ColumnVector vec = new ColumnVector(row);
		Parameter par = new Parameter(col);
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
		//Solve
		mat = new AugmentedMatrix(GaussianElimination(mat));
		if(!mat.IsSolutionExist()){
			System.out.println("No Solution Exist");
		}
		if (mat.Infinit) {
			System.out.println("Infinit Solution");
			
		}
		else{
			vec = new ColumnVector(GetSolution(mat));
			for(j=0;j<vec.size;j++){
				System.out.printf("var_%d = %.2f\n", j+1, vec.Elmt(j));
			}
		}
	}
	
	static void ShowMenu(){
		System.out.println("Menu - Program penyelesai SPL");
		System.out.println("0 - Info program dan credits");
		System.out.println("1 - Input SPL dari console");
		System.out.println("2 - Baca SPL dari file eksternal");
		System.out.println("3 - ");
		System.out.println("4 - Keluar dari program");
		System.out.print  ("Pilihan : ");
	}
	
	public static void main(String []args){
		//AugmentedMatrix matrix = ReadInputMatrix();
		Scanner r = new Scanner(System.in);
		int pil;
		ShowMenu();
		pil = r.nextInt();
		while(pil!=4){
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
				
			}
			else{
				System.out.println("Masukkan Salah!!");
			}
			System.out.println();
			ShowMenu();
			pil = r.nextInt();
		}
		System.out.println("Sampai jumpa");
	}
};
