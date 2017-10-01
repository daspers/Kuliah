#include <cmath>

#include <cstdio>

using namespace std;

#define MAX_N 10 // adjust this value as needed

struct AugmentedMatrix { 
	double mat[MAX_N][MAX_N + 1];
};

struct ColumnVector { 
	double vec[MAX_N]; 
};

	bool Infinit;


ColumnVector GaussianElimination(int N, AugmentedMatrix Aug) {
// input: N, Augmented Matrix Aug, output: Column vector X, the answer
 	int i, j, k, l; double t;

 	for (i = 0; i < N - 1; i++) { // the forward elimination phase
 		l = i;
		for (j = i + 1; j < N; j++) {// which row has largest column value
			if (Math.abs(Aug.mat[j][i]) > fabs(Aug.mat[l][i])) {
				l = j; // remember this row l
			}
		}
		// swap this pivot row, reason: minimize floating point error
		for (k = i; k <= N; k++) {// t is a temporary double variable
			t = Aug.mat[i][k], Aug.mat[i][k] = Aug.mat[l][k], Aug.mat[l][k] = t;
		}
		for (j = i + 1; j < N; j++) {// the actual forward elimination phase
			for (k = N; k >= i; k--) {
				Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];
			}
		}
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%.2f ", Aug.mat[i][j]);
		}
		printf("\n");
	}

	for(i = 0; i < N; i++) {
		Infinit = true;
		for(j = 0; j < N; j++) {
			printf("%f\n", floor(ceil(fabs(Aug.mat[i][j]))));
			if (floor(ceil(fabs(Aug.mat[i][j]))) != 0) {
				printf("HAI\n");
				Infinit = false;
				break;
			}
		}
		if (Infinit) {
			break;
		} 
	}
	
	ColumnVector Ans; // the back substitution phase
		
	for (j = N - 1; j >= 0; j--) { // start from back
		for (t = 0.0, k = j + 1; k < N; k++) {
			t += Aug.mat[j][k] * Ans.vec[k];
		}
		Ans.vec[j] = (Aug.mat[j][N] - t) / Aug.mat[j][j]; // the answer is here
	}

	return Ans;		

	


}

int main() {

 	AugmentedMatrix Aug;

 	Aug.mat[0][0] = 1; Aug.mat[0][1] = 1; Aug.mat[0][2] = 1; Aug.mat[0][3] = 1; Aug.mat[0][4] = 6;

 	Aug.mat[1][0] = 1; Aug.mat[1][1] = 3; Aug.mat[1][2] = 5; Aug.mat[1][3] = 7; Aug.mat[1][4] = 28;
 	
	Aug.mat[2][0] = 2; Aug.mat[2][1] = 3; Aug.mat[2][2] = 6; Aug.mat[2][3] = 8; Aug.mat[2][4] = 33;
	
 	Aug.mat[3][0] = 1; Aug.mat[3][1] = 2; Aug.mat[3][2] = 3; Aug.mat[3][3] = 4; Aug.mat[3][4] = 17;

 	ColumnVector X = GaussianElimination(4, Aug);

	if (Infinit) {
		printf("Infinit Solution\n");
	}
 	printf("W = %.2f, X = %.2f, Y = %.2f, Z = %.2f\n", X.vec[0], X.vec[1], X.vec[2], X.vec[3]);

 	return 0;
}
