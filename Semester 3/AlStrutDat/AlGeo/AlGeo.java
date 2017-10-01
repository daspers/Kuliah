import java.lang.*;

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
		this.vec = new double[];
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
	public boolean Infinit;
	static AugmentedMatrix ReadMatrix(){
		int row=0, col=0;
		AugmentedMatrix mat;
		//read row and col
		
		//Assign matrix size
		mat = new AugmentedMatrix(row, col);
		//Read matrix num
		
		return mat;
	}
	
	public ColumnVector GaussianElimination(AugmentedMatrix mat){
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
			for(j = 0; j < mat.col; j++) {
				System.out.print(mat.Elmt(i,j)+" ");
			}
			System.out.println();
		}
		
		for(i = 0; i < mat.row; i++) {
			Infinit = true;
			for(j = 0; j < mat.col; j++) {
				System.out.println(Math.floor(Math.ceil(Math.abs(mat.Elmt(i,j)))));
				if (Math.floor(Math.ceil(Math.abs(mat.Elmt(i,j)))) != 0) {
					System.out.println("HAI");
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
	
	public static void main(String []args){
		AugmentedMatrix matrix = ReadMatrix();
		
		ColumnVector X = new ColumnVector();
		x = GaussianElimination(matrix);

		if (Infinit) {
			System.out.println("Infinit Solution");
		}
		System.out.printf("W = %.2f, X = %.2f, Y = %.2f, Z = %.2f\n", X.vec[0], X.vec[1], X.vec[2], X.vec[3]);
			
		}
};
