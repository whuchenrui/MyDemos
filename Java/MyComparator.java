import java.util.Arrays;
import java.util.Comparator;

/**********************************
 * Project:  untitled
 * Author:   Ray Chen
 * Email:    raychen0411@gmail.com
 * Time:     09-29-2016
 * All rights reserved!
 * 
 * 本例子中包含了自定义equals方法，comparator比较器。
 * (1)在equals函数中做类型强制转换的时候，要确保转换安全，判断object是否合法
 * (2)对comparator的定义中，需要确认好 == 的情况怎么处理，这个例子中，obj1 == obj2 被视为 obj1 < obj2来处理.
 * (3)与instance无关的函数，应该使用static
 * (4)关于comparator, comparable的比较，参考笔记
 ***********************************/

public class MyComparator {
    private int a;
    private int b;
    private int c;

    MyComparator(){ a = 0; b = 0; c = 0; }

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
    public boolean equals(Object obj) {
        if(this == obj){
            return true;
        }
        if(null == obj){                   // check null
            return false;
        }
        if(getClass() != obj.getClass()){  // check the same class
            return false;
        }
        MyComparator myComparator = (MyComparator)obj;
        return (this.a==myComparator.getA() && this.b==myComparator.getB() && this.c==myComparator.getC());
    }

    public void output(MyComparator[] myComparator){
        for(MyComparator m : myComparator)
            System.out.println(m.getA() + ", " + m.getB() + ", " + m.getC());
    }

    public static class ComparatorExample implements Comparator<MyComparator>{
        @Override
        public int compare(MyComparator o1, MyComparator o2) {
            if(o1.getA() != o2.getA())
                return o1.getA() > o2.getA() ? 1 : -1;

            else if(o1.getB() != o2.getB())
                return o1.getB() > o2.getB() ? 1 : -1;

            else
                return o1.getC() > o2.getC() ? 1 : -1;
        }
    }

    public static void main(String[] args) {

        MyComparator[] a = new MyComparator[4];
        a[0] = new MyComparator(1, 2, 3);
        a[1] = new MyComparator(4, 5, 6);
        a[2] = new MyComparator(3, 5, 6);
        a[3] = new MyComparator(3, 5, 6);

        MyComparator myComparator = new MyComparator();
        myComparator.output(a);
        Arrays.sort(a, new ComparatorExample());
        myComparator.output(a);
    }
}

