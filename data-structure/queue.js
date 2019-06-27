class Queue {
    constructor() {
        this._arr = [];
        this.front;
        this.back;
    }

    enqueue(data) {
        this._arr.push(data);
    }

    dequeue() {
        if (this._arr.length < 0) {
            console.log('This is Stack Underflow!');
            return
        }

        this._arr.shift();
    }

    front() {
        return this._arr[this.front];
    }

    back() {
        return this._arr[this.back];
    }

    clear() {
        this._arr = [];
    }
}

const queue = new Queue();

queue.enqueue(1);
queue.enqueue(2);
queue.enqueue(3);
queue.enqueue(4);
queue.dequeue();
queue.dequeue();

console.log(queue);