// ListMapEntry.java

public class ListMapEntry extends MapEntry {
    private ListMapEntry next;
    public ListMapEntry(String key, String value) {
		super(key, value);
		next = null;
	} // next = null
    
    public ListMapEntry(String key, String value, ListMapEntry next) {
		super(key, value);
		this.next = next;
	}

    public ListMapEntry getNext() {
		return next;
	}
    public void setNext(ListMapEntry next) {
		this.next = next;
	}
}
