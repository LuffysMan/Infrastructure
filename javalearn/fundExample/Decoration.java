import javax.swing.*;

/*****************java修饰符*******************/
public class Decoration {
    /*******访问控制修饰符*******/
    //default
    String version = "1.8.0";       //默认访问权限default, 不适用任何修饰符, 包内可见
    boolean processor(){
        return  true;
    }
    //private
    private String format;
    public void setFormat(String format){       //私有变量通过public方法访问
        this.format = format;
    }
    public String getFormat(){
        return this.format;
    }
    //protected, 在子类中重写, 子类可重新修饰为public或protected
    protected void getMoney(){
        //pass
    }
    //public, 可以被子类继承, 子类重写必须为public
    public void objectRefer(){                  //对象赋值, 不生成拷贝, 相当于引用
        Decoration dt1 = new Decoration();
        Decoration dt2;
        dt2 = dt1;
        System.out.println(dt2.getFormat());
        dt1.setFormat("Time new roman");
        System.out.println(dt2.getFormat());
    }
    /*******非访问控制修饰符*********/
    //final修饰符
        //final变量, 变量一旦赋值后，不能被重新赋值, 且final变量必须初始化. final 修饰符通常和 static 修饰符一起使用来创建类常量.
        public static final int Box_Width = 6;
        public void changeValue(){
            //Box_Width = 12; //将输出一个错误
        }
        //final方法, 类中的 final 方法可以被子类继承，但是不能被子类修改.
        public final void changename(){
            //pass
        }
    //synchronized 修饰符, 关键字声明的方法同一时间只能被一个线程访问, 比C++方便多了呀
        public synchronized void changename(String name){
            //pass
        }
    //transient修饰符, 序列化的对象包含被 transient 修饰的实例变量时，java 虚拟机(JVM)跳过该特定的变量.
        public transient int trLimit;   //不会被持久化
        public int limit;   //会被持久化
    //volatile 修饰符, volatile 修饰的成员变量在每次被线程访问时，都强制从共享内存中重新读取该成员变量的值.
        public volatile boolean active;
        public void run(){
            active = true;
            //如果不用volatile, 分别在两个线程中调用run和stop ,run不会停止
            while (active){
                //pass}
            }
        }
        public void stop(){
            active = false;
        }

}

class ChildDecration extends Decoration{
    @Override
    public void getMoney() {
        super.getMoney();           //super相当于一个父类对象
    }
    //@Override
    //public void changename(){}     //error: overridden method is final
}

//final类, final 类不能被继承，没有类能够继承 final 类的任何特性.
final class finalClass{
    //pass
}

// class childFinalClass extends finalClass{ }      //error: cannot inherit from final finalClass

//abstract关键字, 抽象类和抽象方法
abstract class superClass{
    abstract void makeMoney();
}

//子类要不也声明为abstract, 要不必须实现父类的方法
class subClass extends superClass{
    @Override
    void makeMoney(){
        //pass
    }
}