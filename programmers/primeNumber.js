function solution(n) {
    if (n === 1) return false;
    if (n === 2) return true;
    
    const sqrt = Math.ceil(Math.sqrt(n));
    
    for (let i = 3; i <= n; i++) {
        for (let j = 2; j <= sqrt; j++) {
            if (i % j === 0) return false;
            
            return true;
        }
    }
}

// 에라토스테네스의 체
function solution2(n) {
    let bucket = Array(n - 1).fill(0).map((v, i) => i + 2);
    let i = 2;
    
    const sqrt = parseInt(Math.sqrt(n));

    while (i <= sqrt) {
        bucket = bucket.map(val => i !== val && val % i === 0 ? 0 : val);
        
        i++;
    }
    
    return bucket.filter(v => v !== 0).length;
}

solution2(100);