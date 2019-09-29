function sockMerchant(n, arr) {
    const set = new Set(ar);
    const obj = {};

    set.forEach(v => obj[v] = 0);
    arr.forEach(v => obj[v] += 1);

    return Object.values(obj).map(v => parseInt(v / 2)).reduce((prev, cur) => prev += cur);
}