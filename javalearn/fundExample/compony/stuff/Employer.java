package compony.stuff;
public class Employer {
    public static void main(String[] args) {
        Employee empOne = new Employee("Red");
        Employee empTwo = new Employee("BLue");
        empOne.empAge(22);
        empOne.empDesignation("初级开发工程师");
        empOne.empSalary(7777);
        empTwo.empAge(33);
        empTwo.empDesignation("资深架构师");
        empTwo.empSalary(33333);
        empOne.printEmployee();
        empTwo.printEmployee();
    }

}
