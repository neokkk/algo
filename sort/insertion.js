const insertionSort = arr => {
    for (let i = 1; i < arr.length; i++) {
        let selected = arr[i];

        for (let j = i - 1; j >= 0; j--) {
            if (arr[j] > selected) {
                arr[j + 1] = arr[j];
                arr[j] = selected;
            }
        }
    }

    return arr;
}

console.log(insertionSort([5,1,7,4,6,3,2,8]));