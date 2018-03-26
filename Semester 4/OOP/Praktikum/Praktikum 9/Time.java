import java.*;

public class Time {
    private int hour;
    private int minute;
    private int second;

    public Time() {
        // Set seluruh atribut dengan nilai 0
        hour = minute = second = 0;
    }

    public Time(int hour, int minute, int second) {
		this.hour = hour;
		this.minute = minute;
		this.second = second;
    }

    public Time(Time t) {
        // Set atribut dengan atribut milik t
        hour = t.hour;
        minute = t.minute;
        second = t.second;
    }

    public int getHour() {
		return hour;
    }

    public void setHour(int hour) {
		this.hour = hour;
    }

    public int getMinute() {
		return minute;
    }

    public void setMinute(int minute) {
		this.minute = minute;
    }

    public int getSecond() {
		return second;
    }

    public void setSecond(int second) {
		this.second = second;
    }

    public int convertToSecond() {
		return 3600*hour+60*minute+second;
    }

    public Time add(Time t) {
        // Return penjumlahan dua objek jam, yaitu *this* dan t.
        // Apabila hasil penjumlahan melebihi 23:59:59, maka Anda harus mengonversinya seperti tampilan jam digital asli.
        // Contoh : 24:00:00 dituliskan 00:00:00, 25:00:00 dituliskan 01:00:00, dst.
        Time ans = new Time(hour, minute, second);
        ans.second += t.second;
        if(ans.second>59){
			ans.second%=60;
			ans.minute ++;
		}
		ans.minute += t.minute;
		if(ans.minute>59){
			ans.minute%=60;
			ans.hour++;
		}
		ans.hour += t.hour;
		ans.hour%=24;
		return ans;
    }

    public Time minus(Time t) {
        // Return selisih antara dua objek jam, yaitu *this* dan t.
        // Perhitungan selisih hanya dapat dilakukan jika objek ruas kiri lebih akhir dari atau sama dengan objek ruas kanan.
        // Jika objek ruas kiri lebih awal, maka kembalikan nilai objek ruas kiri.
        // Contoh: 00:00:01 - 00:00:02 = 00:00:01
        if(lessThan(t)){
			return new Time(this);
		}
        Time ans = new Time(hour-t.hour, minute-t.minute, second-t.second);
        if(ans.second<0){
			ans.minute--;
			ans.second+=60; 
		}
		if(ans.minute<0){
			ans.hour--;
			ans.minute+=60; 
		}
		if(ans.hour<0){
			ans.hour+=24; 
		}
		return ans;
    }

    public boolean lessThan(Time t) {
        // Returns true jika *this* < t menurut definisi waktu
        return this.convertToSecond() < t.convertToSecond();
    }

    public boolean greaterThan(Time t) {
        // Returns true jika *this* > t menurut definisi waktu
        return this.convertToSecond() > t.convertToSecond();
    }

    public void printTime() {
        // Menuliskan jam dalam format hh:mm:ss diakhiri dengan newline. Perhatikan bahwa setiap parameter harus dituliskan 2 digit.
        if(hour<10)
			System.out.print("0");
		System.out.print(hour+":");
		if(minute<10)
			System.out.print("0");
		System.out.print(minute+":");
		if(second<10)
			System.out.print("0");
		System.out.print(second+"\n");
    }
}
