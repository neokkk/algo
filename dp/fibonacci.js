/* recursion */
const solution1 = function(num) {
    if (num < 2) return num;
    else return solution1(num - 1) + solution1(num - 2);
}

/* memoization */
const solution2 = (function() {
    const save = [];

    const fbnc = function(num) {
        if (num < 2) return num;
        else {
            let saved1 = save[num - 1] || fbnc(num - 1),
                saved2 = save[num - 2] || fbnc(num - 2);
            
            let result = saved1 + saved2;

            save[num] = result;

            return result;
        }
    }

    return fbnc;
})();

/* array */
const solution3 = function(n) {
    const arr = [1, 1];
    
    let i = 0;
    
    while (i <= n - 2) {
        arr[i + 2] = arr[i + 1] + arr[i];
        i++;
    };
    
    return arr[n - 1];
}

console.time();
solution1(10);
console.timeEnd();
// 0.564ms

console.time();
solution2(10);
console.timeEnd();
// 0.123ms

console.time();
solution3(10);
console.timeEnd();
// 0.164ms