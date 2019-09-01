function heapify (arr, idx) {
    let left = 2 * idx + 1;
    let right = 2 * idx + 2;
    let max = idx;

    if (left < arr.length && arr[left] > arr[max]) max = left;
    if (right < arr.length && arr[right] > arr[max]) max = right;

    if (max !== idx) {
        swap(arr, idx, max);
        heapify(arr, max);
    }
}

function swap (arr, idxA, idxB) {
    let tmp = arr[idxA];
    arr[idxA] = arr[idxB];
    arr[idxB] = tmp;
}

const heapSort = arr => {
    const half = Math.floor(arr.length / 2);

    for (let i = half; i >= 0; i--) { // max heap 만들기
        heapify(arr, i);
    }
}

console.log(heapSort([5,1,7,4,6,3,2,8]));