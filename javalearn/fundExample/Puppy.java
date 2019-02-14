public class Puppy {
    int puppyAge;
    public void setPuppyAge(int age){
        puppyAge = age;
    }
    public int getPuppyAge(){
        return puppyAge;
    }
    public Puppy(){
        puppyAge = 1;
    }

    public Puppy(String name) {
        puppyAge = 1;
        System.out.println("小狗的名字是: " + name);
    }
}
