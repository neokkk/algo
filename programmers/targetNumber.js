function solution(numbers, target) {
    let count = 0;

    function plusOrMinus(target, sum, numbers, index) {
        if (index === numbers.length) {
            if (sum === target) count++;
    
            return;
        } else {        
            plusOrMinus(target, sum + numbers[index], numbers, index + 1);
            plusOrMinus(target, sum - numbers[index], numbers, index + 1);
        }
    }

    plusOrMinus(target, 0, numbers, 0);
    
    return count;
}

