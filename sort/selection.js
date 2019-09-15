const selectionSort = arr => {
    for (let i = 0; i < arr.length - 1; i++) {
        let minIndex = i;

        for (let j = i + 1; j < arr.length - 1; j++) {
            if (arr[minIndex] > arr[j]) {
                minIndex = j;
            }
        }

        let tmp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = tmp;
    }

    return arr;
}

console.log(selectionSort([5,1,7,4,6,3,2,8]));