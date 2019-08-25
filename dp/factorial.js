/* recursion */
const solution1 = function(num) {
    if (num === 0) return 1; 
    else return num * solution1(num - 1);
}

/* memoization */
const solution2 = (function() {
    const save = [];
    const fact = function(num) {
        if (num === 0) return 1;
        else {
            let saved = save[num - 1] || fact(num - 1);
            let result = num * saved;

            save[num] = result;

            return result;
        }
    }

    return fact;
})();

const answer1 = solution1(10);
const answer2 = solution2(10);

console.log(answer1);
console.log(answer2);