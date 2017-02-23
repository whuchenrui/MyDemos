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


/*
 *  一般来讲 Quick Sort的速度还是要快一点,最优为O(nlog2)，而且Merge Sort 还会使用额外的空间。另外就是MergeSort是稳定的排序。而快速排序是不稳定的。如果不允许使用递归，那么quick sort又不是一个好的选择了。
    关于Java中排序的实现
 */
void mergeSort(int A[])
{
    if (A==null || A.length<=1)
        return;
    int[] tmp = new int[A.length];
    mergeSort(A, 0, A.length-1, tmp);
}

void mergeSort(int a[], int p, int q, int[] tmp)
{
    if (p < q)
    {
        int mid = p + (q-p) / 2;
        mergeSort(a, p, mid, tmp);     //左边有序
        mergeSort(a, mid + 1, q, tmp); //右边有序
        mergeArray(a, p, mid, q, tmp); //再将二个有序数列合并
    }
}

//将有二个有序数列a[first...mid]和a[mid...last]合并。  
void mergeArray(int a[], int p, int mid, int q, int tmp[])
{
    int i = p, j = mid + 1;
    int k = 0;

    while (i <= mid && j <= q)
        {
            if (a[i] <= a[j])
                tmp[k++] = a[i++];
            else
                tmp[k++] = a[j++];
        }
    
    while (i <= mid)
            tmp[k++] = a[i++];
    
    while (j <= q)
            tmp[k++] = a[j++];
    
    for (i = 0; i < k; i++)
            a[p + i] = tmp[i];
}

