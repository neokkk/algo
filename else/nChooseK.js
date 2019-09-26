// a + b + c ... (k개) = n이 되는 해의 수
function solution(n, k) {
    if (k === 0) return 0;
    if (k === 1) return 1;

    let count = 0;

    for (let i = 0; i <= k; i++) {
        count += solution(n - i, k - 1);
    }

    return count;
}