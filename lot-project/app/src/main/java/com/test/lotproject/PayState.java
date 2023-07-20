package com.test.lotproject;

public class PayState {
    private static int payment=0;
    public static int getPayment() {
        return payment;
    }
    public static void setPayment(int payment) {
        PayState.payment = payment;
    }


}
/*class PayState{
    //1、   创建一个私有的静态的自身对象的实例，类加载时就会产生
    private static final PayState instance = new PayState();

    //2、   私有化构造器，保证不能在类外部通过new构造器来构造对象
    private PayState() {
        System.out.println("-------创建了一个HungryMan对象------");
    }

    //3、   创建一个公共的静态方法，返回当前类对象实例
    public static PayState getInstance() {
        return instance;
    }
}*/

