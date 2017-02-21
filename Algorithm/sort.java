/*
 * Implementations for some popular sort algorithms
 */


/*
 *  大部分的排序算法都是使用 quick sort。**typical implement 算法结果并不稳定**
    Given an array with a normal distribution, Quicksort and Heapsort will both run in O(n log(n)). But Quicksort will execute faster because its constant factors are smaller than the constant factors for Heapsort. To put it simply,** partitioning is faster than maintaining the heap.**
    同时，partitioning也方便分布处理，易于 parallel
 */
public void quickSort(int[] A){
    if(A==null || A.length<=1)
        return;
    quickSortHelper(A, 0, A.length-1);
}

private void quickSortHelper(int[] A, int p, int q){
    if(p >= q)
        return;
    int i=p, j=q;
    int pivot = A[p];
    while(i <= j){
        while(A[i] < pivot) //cannot be <=, otherwise, the pivot won't change.
            i++;
        while(A[j] > pivot)
            j--;
        if(i <= j){         //这里判断条件是<=,主要是为了移动i,j,服务于下一次的递归
                            //否则对于诸如[1,2],会无限循环
            swap(A, i, j);
            i++;
            j--;
        }
    }
    if(p < j)
        quickSortHelper(A, p, j);
    if(i < q)
        quickSortHelper(A, i, q);
}

private void swap(int[] A, int i, int j){
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
