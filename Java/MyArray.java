import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * @author Ray
 * @since 2016-05-02
 * Useful functions about Java array.
 *
 */

public class MyArray {

    private int[] remove_duplicate(int[] nums){
        Set<Integer> unique = new HashSet<>();
        int[] white_list = new int[nums.length];
        int i=0;

        for(int item : nums)
        {
            if(unique.add(item)){
                white_list[i++] = item;
            }
        }
        return Arrays.copyOf(white_list, i);
    }

    public static void main(String[] argv){
        MyArray myArray = new MyArray();
        int[] test = {53,2,1,1,2,3,4,1,4,3};
        int[] res = myArray.remove_duplicate(test);
        for(int r : res)
            System.out.print(r + " ");
    }
}
