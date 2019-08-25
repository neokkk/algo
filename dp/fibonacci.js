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

const answer1 = solution1(10);
const answer2 = solution2(10);

console.log(answer1);
console.log(answer2);