function solution(num) {
    const repeated = Array(num).fill('A').map((v, i) => i % 2 === 1 ? 'B' : v).join('');
    console.log(repeated);

    return repeated;
}

solution(4);
solution(0);
solution(11);