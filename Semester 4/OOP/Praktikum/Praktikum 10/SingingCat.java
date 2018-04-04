public class SingingCat extends SingingAnimal{
	private String breed;
	public SingingCat(String name, String voice){
		super(4, name, voice);
		this.breed = "normal";
	}
	public SingingCat(String name, String voice, String breed){
		super(4, name, voice);
		this.breed = breed;
	}
	public void introduce(){
		System.out.println("My name is "+super.getName());
		System.out.println("My breed is "+breed);
	}
	public void dance() {
        super.dance();
        System.out.println("I am also flying");
    }
    public void sing() {
        System.out.println("Meow");
        super.sing();
    }
}
