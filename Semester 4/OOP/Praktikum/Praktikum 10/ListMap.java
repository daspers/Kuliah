public class ListMap implements Map {
	ListMapEntry first;
	ListMap(){
		first = null;
	}
    /**
     * Menambahkan (key, value) ke dalam map
     * Melakukan overwrite jika sudah terdapat elemen dengan key yang sama.
     */
    public void set(String key, String value){
		if(first == null){
			first = new ListMapEntry(key, value);
		}
		ListMapEntry temp = first;
		ListMapEntry prev = null;
		while(temp!=null && !temp.getKey().equals(key)){
			prev = temp;
			temp = temp.getNext();
		}
		if(temp==null){
			prev.setNext(new ListMapEntry(key, value));
		}
		else{
			temp.setValue(value);
		}
	}
    /**
     * Mengembalikan value yang tersimpan untuk key tertentu pada map
     * Mengembalikan NULL apabila map tidak mengandung key masukan.
     */
    public String get(String key){
		ListMapEntry temp = first;
		while(temp!=null && !temp.getKey().equals(key)){
			temp = temp.getNext();
		}
		if(temp==null){
			return null;
		}
		else{
			return temp.getValue();
		}
	}
	
	public void print(){
		ListMapEntry temp = first;
		while(temp!=null){
			System.out.println(temp.getKey()+ " "+temp.getValue());
			temp = temp.getNext();
		}
	}
	
    /**
     * Menghitung jumlah elemen yang ada pada map
     */
    public int size(){
		ListMapEntry temp = first;
		int c=0;
		while(temp!=null){
			c++;
			temp = temp.getNext();
		}
		return c;
	}
}
