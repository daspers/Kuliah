/* abstract class A {
    A() {
        System.out.println("Constructor A");
    }

    abstract void cetak();

}

 class B extends A {
    B() {
        System.out.println("Constructor B");
    }

    @Override void cetak() {
        System.out.println("Cetak B");
    }


}

 class C extends B {
    C() {
        System.out.println("Constructor C");
    }

    @Override
    void cetak() {
        System.out.println("Cetak C");
    }

}

 class D extends B {
    D() {
        System.out.println("Constructor D");
    }
}
*/
public class Main {
    public static void main(String[] args) {
		A a = new B();
		A b = new C();
		A c = new D();
		A d = new B();
		A e = new C();
		A f = new D();
		A g = new C();
		A h = new D();
		a.cetak();
		b.cetak();
		a.cetak();
		a.cetak();
		b.cetak();
		a.cetak();
		b.cetak();
		a.cetak();
    }
}
