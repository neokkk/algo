function solution(number, k) {
    const result = [];
    
    let numToArr;
    
    for (let i = 0; i < number.length - k + 1; i++) {
        numToArr = Array.from(number);
        numToArr.splice(i, k);
        
        result.push(Number(numToArr.join('')));
        console.log(result);
    }
    
    return '' + Math.max.apply(null, result);
}