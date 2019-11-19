class Stack {
    constructor(size) {
        this.arr = [];
        this.top = -1;
        this.size = size ? size : 1000000;
    }

    push(data) {
        if (this.size === this.arr.length) return;

        this.top++;
        this.arr[this.top] = data;

        console.log(this.arr);
    }

    pop() {
        if (this.top < 0) return;

        const popped = this.arr.splice(this.top);
        this.top--;

        console.log(this.arr);

        return popped;
    }
}

const stack = new Stack(5);

stack.push('hello');
stack.push('annyeong');
stack.push('konnichiwa');
stack.push('ni hao');
stack.push('buon giorno');
stack.push('bonsoir');
stack.pop();
stack.pop();

class Queue {
    constructor(size) {
        this.arr = [];
        this.size = size;
    }

    enqueue(data) {
        if (this.size === this.arr.length) return;

        
    }
}