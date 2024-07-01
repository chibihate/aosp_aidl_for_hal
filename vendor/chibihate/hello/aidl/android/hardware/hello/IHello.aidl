package android.hardware.hello;

@VintfStability
interface IHello {
    String getChars();
    void putChars(in String msg);
}
