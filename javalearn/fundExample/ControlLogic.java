/**************java控制逻辑**************/
public class ControlLogic {
    public static void main(String[] args){
        ControlLogic ctl = new ControlLogic();
        ctl.enhancedFor();          //java增强型for循环, 其余逻辑同C++, break, continue, do while, while
        //ctl.branch();             //分支语句同c/c++
        ctl.switchTest();           //switch, 基本同c/c++, switch 语句中的变量类型可以是： byte、short、int 或者 char。从
                                    // Java SE7 s开始，switch 支持字符串 String 类型了，同时 case 标签必须为字符串常量或字面量.
    }
    //java5 引入了一种主要用于数组的增强型 for 循环.
    public void enhancedFor(){
        int[] numbers = {10, 20, 30, 40};
        for(int x: numbers){
            System.out.print(x);
            System.out.print(",");
        }
        System.out.println();
        String [] names ={"James", "Larry", "Tom", "Lacy"};
        for( String name : names ) {
            System.out.print( name );
            System.out.print(",");
        }
    }
    public void switchTest(){
        char grade = 'C';
        switch(grade)
        {
            case 'A' :
                System.out.println("优秀");
                break;
            case 'B' :
            case 'C' :
                System.out.println("良好");
                break;
            case 'D' :
                System.out.println("及格");
                break;
            case 'F' :
                System.out.println("你需要再努力努力");
                break;
            default :
                System.out.println("未知等级");
        }
        System.out.println("你的等级是 " + grade);
    }
}
