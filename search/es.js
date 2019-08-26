function solution(num) {
    const numToArr = ('' + num).split('').map(v => Number(v));
    console.log('numToArr : ', numToArr);
    selection(numToArr, 0);    
}

function selection(arr, startIndex) {
    const returnArr = [];

    if (startIndex === arr.length) {
        console.log('returnArr : ', returnArr);
        return returnArr.join('');
    } else {
        for (let i in arr) {
            let currentIndex = startIndex + i > arr.length - 1 ? startIndex + i - 5 : startIndex + i;
            
            returnArr.push(arr[currentIndex]);
        }

        startIndex++;
        selection(arr, startIndex);
    }
}

solution(3479);