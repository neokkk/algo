const mergeSort = arr => {
    if (arr.length < 2) return arr;

    const middleIndex = Math.floor(arr.length / 2);

    const left = arr.slice(0, middleIndex);
    const right = arr.slice(middleIndex, arr.length);

    return merge(mergeSort(left), mergeSort(right));
}

const merge = (left, right) => {
    const merged = [];

    while (left.length && right.length) {
        if (left[0] < right[0]) {
            merged.push(left.shift());
        } else {
            merged.push(right.shift());
        }
    }

    while (left.length) merged.push(left.shift());
    while (right.length) merged.push(right.shift());

    return merged;
}

console.log(mergeSort([5,1,7,4,6,3,2,8]));