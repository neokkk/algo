function countPrimeNumber(n) {
    if (n < 2) return 0;
    if (n < 4) return n - 1;

    const sqrt = Math.ceil(Math.sqrt(n));

    let bucket = Array(n).fill().map((v, i) => i + 1);
    let i = 2;

    while (i <= sqrt) {
        bucket = bucket.map(v => v % i === 0 ? 0 : v);
        i++;
    }

    console.log(bucket);
    return bucket.filter(v => v !== 0 && v !== 1).length + 2;
}

console.log(countPrimeNumber(10));
console.log(countPrimeNumber(1));
console.log(countPrimeNumber(3));