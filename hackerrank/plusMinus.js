function plusMinus(arr) {
    const posit = arr.filter(v => v > 0).length,
          negot = arr.filter(v => v < 0).length,
          zero = arr.filter(v => v === 0).length;

    calcPartion(posit, arr.length);
    calcPartion(negot, arr.length);
    calcPartion(zero, arr.length);
}

function calcPartion(part, all) {
    const sliced = (part / all).toFixed(6);

    console.log(sliced);
    return sliced;
}