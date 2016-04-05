import java.util.Comparator;

/**
 * Created by ray on 4/4/16.
 * MyComparator  包括三个成员变量. 实现对[a,b,c] 的排序和比较判断
 * 注意： 在equals函数中做类型强制转换的时候，要确保转弯安全，做一些if判断。
 */
public class MyComparator implements Comparator<MyComparator>{
    private int a;
    private int b;
    private int c;

    MyComparator(int p1, int p2, int p3){
        a = p1;
        b = p2;
        c = p3;
    }

    public int getC() {
        return c;
    }

    public int getB() {
        return b;
    }

    public int getA() {
        return a;
    }

    @Override
    public int compare(MyComparator o1, MyComparator o2) {
        if(o1.getA()!=o2.getA()){
            return o1.getA() > o2.getA()? 1 : -1;
        }else if(o1.getB()!=o2.getB()){
            return o1.getB() > o2.getB()? 1 : -1;
        }else{
            return o1.getC() > o2.getC()? 1 : -1;
        }
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj){
            return true;
        }
        if(null == obj){
            return false;
        }
        if(getClass() != obj.getClass()){
            return false;
        }
        MyComparator myComparator = (MyComparator)obj;
        return (this.a==myComparator.getA() && this.b==myComparator.getB() && this.c==myComparator.getC());
    }
}
