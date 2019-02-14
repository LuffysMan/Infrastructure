/***************java变量类型*************************/
public class Variable {
    static int objCount;       //类变量, 所有实例化的对象共用
    int nLocal;                 //实例变量, 数值型变量默认值是0，布尔型默认值是false，引用类型默认值是null。
    public Variable(){
        objCount += 1;
    }
    public void method(){
        int a = 0;      //局部变量, 必须初始化
        System.out.println("局部变量: "+ a);
    }
    public static void main(String[] args){
        Variable var = new Variable();
        Variable var1 = new Variable();
        System.out.println("静态变量: " + Variable.objCount);     //使用完全限定名访问类静态变量
        System.out.println("实例变量: " + var.nLocal);             //实例变量必须先实例化对象再访问
        var.method();

    }
}
