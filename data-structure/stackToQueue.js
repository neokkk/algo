const Stack = require('./stack');

class StackToQueue {
    constructor() {
        this.s1 = new Stack();
        this.s2 = new Stack();
    }

    enqueue(data) {
        this.s1.push(data);
    }

    dequeue() {
        if (this.s1.arr.length < 2) {
            return this.s1.pop();
        }

        while (this.s1.arr.length > 1) {
            this.s2.push(this.s1.pop());
        }

        const dq = this.s1.pop();

        while (this.s2.arr.length) {
            this.s1.push(this.s2.pop());
        }

        return dq;
    }
}

const stq = new StackToQueue();

stq.enqueue('hello');
stq.enqueue('stack');
stq.enqueue('bye');
stq.enqueue('queue');
console.log(stq.dequeue());
console.log(stq.dequeue());
console.log(stq.dequeue());
console.log(stq.dequeue());