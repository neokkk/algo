function lcs (strA, strB) {
    const arr = Array(strA.length + 1).fill(0).map(v => Array(strB.length + 1).fill(0));

    for (let i = 1; i <= strA.length; i++) { // length of LCS
        for (let j = 1; j <= strB.length; j++) {
            if (strA.slice(i - 1, i) === strB.slice(j - 1, j)) {
                arr[i][j] = arr[i - 1][j - 1] + 1;
            } else {
                arr[i][j] = Math.max(arr[i][j - 1], arr[i - 1][j]);
            }
        }
    }

    const result = [];

    let k = 1,
        str = '';

    for (let i = 1; i <= strA.length; i++) { // find LCS
        for (let j = 1; j <= strB.length; j++) {
            if (arr[i][j] === k) {
                result.push(i);

                k++;
                j++;
            }
        }
    }

    result.forEach(v => str += strA.slice(v - 1, v));

    return str;
}