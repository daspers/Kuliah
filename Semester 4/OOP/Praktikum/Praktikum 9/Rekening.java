public class Rekening {
    // Daftar transaksi yang telah dilakukan pada rekening ini
    private Transaksi[] daftarTransaksi;
    // Jumlah transaksi yang telah dilakukan pada rekening ini
    private int jumlahTransaksi;
    // Jumlah transaksi maksimum yang dapat disimpan
    private int maxTransaksi;

    // Konstruktor, dengan nilai maxTransaksi awal
    public Rekening(int maxTrans) {
		daftarTransaksi = new Transaksi[maxTrans];
		jumlahTransaksi = 0;
		maxTransaksi = maxTrans;
    }

    // Getter
    public int getJumlahTransaksi() {
		return jumlahTransaksi;
    }
    public int getMaxTransaksi() {
		return maxTransaksi;
    }

    // Mengembalikan array baru yang berisi `count` transaksi terakhir yang dilakukan
    public Transaksi[] getLastTransaksi(int count) {
		if(count > jumlahTransaksi)
			count = jumlahTransaksi;
		Transaksi[] ans = new Transaksi[count];
		for(int i=0;i<count;i++){
			int j = jumlahTransaksi-count+i;
			ans[i] = new Transaksi(daftarTransaksi[j].getRekening(), daftarTransaksi[j].getPerubahan());
		}
		return ans;
    }

    // Mengembalikan saldo pada rekening, yaitu hasil penjumlahan perubahan semua transaksi yang telah dilakukan
    public double getSaldo() {
		double ans =0 ;
		for(int i=0;i<jumlahTransaksi;i++){
			ans += daftarTransaksi[i].getPerubahan();
		}
		return ans;
    }

    // Membuat transaksi baru yang menambahkan `amount` uang pada rekening.
    // `amount` harus positif dan harus ada sisa tempat di rekening.
    // Mengembalikan status berhasil/gagal penyimpanan uang. (Jika berhasil, mengembalikan true)
    public boolean simpanUang(double amount) {
		if(jumlahTransaksi<maxTransaksi&&amount>0){
			daftarTransaksi[jumlahTransaksi] = new Transaksi(this, amount);
			jumlahTransaksi++;
			return true;
		}
		return false;
    }

    // Membuat transaksi baru yang mengurangi `amount` uang pada rekening.
    // `amount` harus positif dan lebih kecil dari saldo, dan harus ada sisa tempat di rekening.
    // Harus ada sisa tempat di rekening.
    // Mengembalikan status berhasil/gagal penarikan uang. (Jika berhasil, mengembalikan true)
    public boolean tarikUang(double amount) {
		if(jumlahTransaksi<maxTransaksi&&amount>0&&amount<getSaldo()){
			daftarTransaksi[jumlahTransaksi] = new Transaksi(this, -amount);
			jumlahTransaksi++;
			return true;
		}
		return false;
    }
}
