function jumpingOnClouds(arr) {
    let currentIndex = 0, count = 0;

    while (currentIndex < arr.length - 1) {
        arr[currentIndex + 2] === 0 ? currentIndex += 2 : currentIndex += 1;

        count++;
    }

    return count;
}