const quickSort = arr => {
    if (arr.length === 0) return [];

    let pivot = arr[0];

    const left = [];
    const right = [];

    for (let i = 1; i < arr.length; i++) {
        if (arr[i] < pivot) left.push(arr[i]);
        else right.push(arr[i]);
    }

    return quickSort(left).concat(pivot, quickSort(right));
}

console.log(quickSort([5,1,7,4,6,3,2,8]));