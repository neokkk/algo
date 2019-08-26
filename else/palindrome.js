function solution(text) {
    const textToArr = text.replace(/[^a-zA-Z]/g, '').toLowerCase().split('');

    while (textToArr.length > 1) {
        if (textToArr.shift() !== textToArr.pop()) return false;
    }

    return true;
}

console.log(solution("Madam, I'm Adam"));
console.log(solution("MaDDdam./ml,df Im"));