const mergeSort = arr => {
    if (arr.length < 2) return arr;

    let half = Math.floor(arr.length / 2);
    let left = arr.slice(0, half);
    let right = arr.slice(half, arr.length);

    return merge(mergeSort(left), mergeSort(right));
}

const merge = (left, right) => {
    const result = [];

    while (left.length && right.length) {
        if (left[0] < right[0]) {
            result.push(left.shift());
        } else {
            result.push(right.shift());
        }
    }

    while (left.length) result.push(left.shift());
    while (right.length) result.push(right.shift());

    return result;
}

console.log(mergeSort([5,1,7,4,6,3,2,8]));