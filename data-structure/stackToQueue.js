const Stack = require('./stack');

const stack1 = new Stack(), stack2 = new Stack();

stack1.push('hello');
stack1.push('stack');
stack1.push('hello');
stack1.push('queue');

// while (stack1.arr.length) {
//     stack2.push(stack1.pop());
// }

// while (stack2.arr.length) {
//     console.log(stack2.pop());
// }

class StackToQueue {
    constructor() {
        this.s1 = new Stack();
        this.s2 = new Stack();
    }

    enqueue(data) {
        this.s1.push(data);

        console.log(this.s1.arr);
    }

    dequeue() {
        if (this.s1.arr.length) {
            if (this.s1.arr.length === 1) return this.s1.pop();
            
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
}

const stq = new StackToQueue();

stq.enqueue('hello');
stq.enqueue('stack');
stq.enqueue('hello');
stq.enqueue('queue');
console.log(stq.dequeue());
console.log(stq.dequeue());
console.log(stq.dequeue());
console.log(stq.dequeue());
console.log(stq.dequeue());