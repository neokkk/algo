class Stack {
    constructor(size) {
        this.arr = [];
        this.top = -1;

        if (size) this.size = size;
        else this.size = 1000000;
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

    clear() {
        this.arr = [];
    }

    isEmpty() {
        if (this.top < 0) return true;
        else return false;
    }
}

module.exports = Stack;