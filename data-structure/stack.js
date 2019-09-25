class Stack {
    constructor(size) {
        this.arr = [];
        this.top = -1;
        this.size = size;
    }

    push(data) {
        if (this.arr.length === this.size) {
            console.log('This is stack overflow!');
            return;
        }

        this.top++;
        this.arr[this.top] = data;
    }

    pop() {
        if (this.top < 0) {
            console.log('This is stack underflow...');
            return;
        }

        const popped = this.arr.splice(this.top)[0];
        this.top--;

        return popped;
    }

    peek() {
        return this.arr[this.top];
    }
}

const stack = new Stack(3);

stack.push('h');
stack.push('e');
stack.push('l');
stack.push('l');
stack.push('o');

console.log(stack.pop());
console.log(stack.pop());
console.log(stack.peek());