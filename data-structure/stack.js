class Stack {
    constructor() {
        this._arr = [];
        this.top = -1;
    }

    push (data) {
        this.top++;
        this._arr.push(data);
    }

    pop () {
        if (this.top <= -1) {
            console.log('This is Stack underflow!');
            return null;
        } else {
            const popped = this._arr[this.top];

            this._arr.splice(this.top);
            this.top--;

            return popped; 
        } 
    }

    peek () {
        return this.arr[this.top];
    }

    clear() {
        this._arr = [];
        this.top = -1;
    }
}

const stack = new Stack();

stack.push(1);
stack.push(2);
stack.push(3);

stack.pop();
stack.pop();

stack.push(4);
stack.push(5);
stack.push(6);
stack.peek();


console.log(stack);