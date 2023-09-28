const Queue = require('./queue');

class QueueToStack {
    constructor() {
        this.q1 = new Queue();
        this.q2 = new Queue();
    }

    push(data) {
        if (this.q1.arr.length || (!this.q1.arr.length && !this.q2.arr.length)) {
            this.q1.enqueue(data);
        } else {
            this.q2.enqueue(data);
        }
    }

    pop() {
        if (this.q1.arr.length) {
            if (this.q1.arr.length < 2) {
                return this.q1.dequeue();
            }

            while (this.q1.arr.length > 1) {
                this.q2.enqueue(this.q1.dequeue());
            }

            return this.q1.dequeue();
        } else {
            if (this.q2.arr.length < 2) {
                return this.q2.dequeue();
            }

            while (this.q2.arr.length > 1) {
                this.q1.enqueue(this.q2.dequeue());
            }

            return this.q2.dequeue();
        }
    }
}

const qts = new QueueToStack();

qts.push('hello');
qts.push('queue');
qts.push('bye');
qts.push('stack');
console.log(qts.pop());
console.log(qts.pop());
console.log(qts.pop());
console.log(qts.pop());
console.log(qts.pop());