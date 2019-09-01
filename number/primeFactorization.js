function solution(n) {
    const answer = [];
    
    let p = 2;

    while (n !== 1) {
        if (n % p === 0) {
            answer.push(p);
            n = n / p;
        } else {
            p++;
        }
    }

    console.log(answer);
    return [...new Set(answer)];
}

console.log(solution(100));
console.log(solution(11));
console.log(solution(1203));