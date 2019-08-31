const partition = (arr, left, right, pivotIndex) => {
    const pivot = arr[pivotIndex];

    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;

        if (left <= right) {
            let tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;

            left++;
            right--;
        }
    }

    let tmp = arr[left];
    arr[left] = arr[pivotIndex];
    arr[pivotIndex] = tmp;

    return left;
}

const quickSort = (arr, left, right) => {
    if (!left) left = 0;
    if (!right) right = arr.length - 1;

    let pivotIndex = right;

    pivotIndex = partition(arr, left, right - 1, pivotIndex);

    if (left < pivotIndex - 1) quickSort(arr, left, pivotIndex - 1);
    if (right > pivotIndex + 1) quickSort(arr, pivotIndex + 1, right);

    return arr;
}

console.log(quickSort([5,1,7,4,6,3,2,8]));