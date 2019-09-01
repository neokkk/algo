function ex(n) {
    let count = 0;

    for (let i = 0; i < n; i * 2) {
        count++;
    }

    return count;
}

console.log(ex(100000000));