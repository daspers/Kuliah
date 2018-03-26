class Complex{
	private int real;
	private int imaginer;
	
	public Complex(){
		real = imaginer = 0;
	}
	public Complex(int a, int b){
		real = a;
		imaginer = b;
	}
	public int getReal(){
		return real;
	}
	public int getImaginer(){
		return imaginer;
	}
	public void setReal(int a){
		real = a;
	}
	public void setImaginer(int b){
		imaginer = b;
	}
	
	// Mengembalikan objek Complex dengan nilai ini ditambah b
	public Complex plus(Complex b){
		Complex ans = new Complex(real + b.real, imaginer+b.imaginer);
		return ans;
	}

	// Mengembalikan objek Complex dengan nilai ini dikurangi b
	public Complex minus(Complex b){
		Complex ans = new Complex(real - b.real, imaginer - b.imaginer);
		return ans;
	}

	// Mengembalikan objek Complex dengan nilai ini dikali b
	public Complex multiply(Complex b){
		Complex ans = new Complex(real*b.real - imaginer*b.imaginer, imaginer*b.real + real*b.imaginer);
		return ans;
	}
}
