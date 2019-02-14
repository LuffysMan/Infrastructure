import org.omg.CORBA.PUBLIC_MEMBER;

/************java运算符**************/
public class Operator {
    public static void main(String[] args) {
        Operator opt = new Operator();
        opt.algebraOperator();      //算术运算符
        opt.relationOperator();
        opt.bitOperator();
        opt.logicOperator();        //逻辑运算符, 短路逻辑运算符
        opt.assignmentOperator();   //赋值运算符, 同C++
        opt.questionmarkExpression();   //问号表达式
        opt.instanceOperator();     //instanceof
        //运算优先级, 请看菜鸟教程
    }
    //算术运算符
    public void algebraOperator(){
        int a = 10;
        int b = 20;
        int c = 25;
        int d = 25;
        System.out.println("a + b = " + (a + b) );
        System.out.println("a - b = " + (a - b) );
        System.out.println("a * b = " + (a * b) );
        System.out.println("b / a = " + (b / a) );
        System.out.println("b % a = " + (b % a) );
        System.out.println("c % a = " + (c % a) );
        System.out.println("a++   = " +  (a++) );
        System.out.println("a--   = " +  (a--) );
        // c++ 与 ++d的区别
        System.out.println("2 * c++: " + 2 * c++);
        System.out.println("2 * ++d: " + 2 * ++d);
    }
    //关系运算符
    public void relationOperator(){
        int a = 10;
        int b = 20;
        System.out.println("a == b = " + (a == b) );
        System.out.println("a != b = " + (a != b) );
        System.out.println("a > b = " + (a > b) );
        System.out.println("a < b = " + (a < b) );
        System.out.println("b >= a = " + (b >= a) );
        System.out.println("b <= a = " + (b <= a) );
    }
    //位运算符, 重点是 >> 和>>>的区别, >>是带符号右移(-2>>1得-1), >>>是无符号右移, 高位统统补零(-1>>>1得Integer.MAX_VALUE)
    public void bitOperator(){
        int a = 60; /* 60 = 0011 1100 */
        int b = 13; /* 13 = 0000 1101 */
        int c = 0;
        c = a & b;       /* 12 = 0000 1100 */
        System.out.println("a & b = " + c );

        c = a | b;       /* 61 = 0011 1101 */
        System.out.println("a | b = " + c );

        c = a ^ b;       /* 49 = 0011 0001 */
        System.out.println("a ^ b = " + c );

        c = ~a;          /*-61 = 1100 0011 */
        System.out.println("~a = " + c );

        c = a << 2;     /* 240 = 1111 0000 */
        System.out.println("a << 2 = " + c );

        c = a >> 2;     /* 15 = 1111 */
        System.out.println("a >> 2  = " + c );

        c = a >>> 2;     /* 15 = 0000 1111 */
        System.out.println("a >>> 2 = " + c );
    }
    public void logicOperator(){
        boolean a = true;
        boolean b = false;
        System.out.println("a && b = " + (a&&b));
        System.out.println("a || b = " + (a||b) );
        System.out.println("!(a && b) = " + !(a && b));
        //短路逻辑运算符
        int c = 5;//定义一个变量；
        boolean d = (c<4)&&(c++<10);    //当得到第一个操作为false时，其结果就必定是false，这时候就不会再判断第二个操作了
    }
    public void assignmentOperator(){
        /*
        =
        +=
        -=
        ...
        >>=
        <<=
        ...
        ^=
        |=
         */
    }
    public void questionmarkExpression(){
        int a , b;
        a = 10;
        // 如果 a 等于 1 成立，则设置 b 为 20，否则为 30
        b = (a == 1) ? 20 : 30;
        System.out.println( "Value of b is : " +  b );

        // 如果 a 等于 10 成立，则设置 b 为 20，否则为 30
        b = (a == 10) ? 20 : 30;
        System.out.println( "Value of b is : " + b );
    }
    public void instanceOperator(){
        Vehile car = new Car();
        boolean bIsCar = car instanceof Car;
        System.out.println("Is a car?: " + bIsCar);
    }
}

class Vehile{}
class Car extends Vehile{}