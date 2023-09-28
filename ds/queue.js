class Queue {
    constructor(size) {
        this.arr = [];

        if (size) this.size = size;
        else this.size = 1000000;
    }

    enqueue(data) {
        if (this.arr.length === this.size) {
            console.log('This is Queue Overflow!');
            return;
        }

        this.arr.push(data);
    }

    dequeue() {
        if (this.arr.length < 0) {
            console.log('This is Queue Underflow!');
            return;
        }

        return this.arr.shift();
    }

    clear() {
        this.arr = [];
    }
}

module.exports = Queue;
