function solution(arr, weight) {
    const hashTable = {};

    for (let i = 0; i < arr.length; i++) {
        let current = arr[i];
        let interval = weight - current;
    
        if (hashTable[current] !== undefined) return [i, interval];
        else hashTable[current] = i;
    }

    return -1;
}

console.log(solution([1,2,3,4,5], 9));