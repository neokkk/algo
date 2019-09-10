class MinHeap {
    constructor() {
        this.arr = [];
    }

    insert(data) {
        const last = this.arr.length;

        this.arr[last] = data;
        this._heapUp(last);
    }

    _heapUp(index) {
        if (index) {
            let parent = parseInt((index - 1) / 2);

            if (this.arr[index] < this.arr[parent]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[parent];
                this.arr[parent] = tmp;

                this._heapUp(parent);
            }
        }
    }

    delete() {
        if (this.arr.length === 0) return null;

        const del = this.arr[0];

        this.arr[0] = this.arr.pop();
        this._heapDown(0);

        return del;
    }

    _heapDown(index) {
        let left, right, smallIndex;

        if (index * 2 + 1 < this.arr.length) {
            left = this.arr[index * 2 + 1];

            if (index * 2 + 2 < this.arr.length - 1) {
                right = this.arr[index * 2 + 2];
            }

            if (left < right) smallIndex = index * 2 + 1;
            else smallIndex = index * 2 + 2;

            if (this.arr[index] > this.arr[smallIndex]) {
                let tmp = this.arr[index];
                this.arr[index] = this.arr[smallIndex];
                this.arr[smallIndex] = tmp;

                this._heapDown(smallIndex);
            }
        }
    }
}

const mh = new MinHeap();

mh.insert(1);
mh.insert(4);
mh.insert(11);
mh.insert(3);
mh.insert(8);
mh.insert(5);
console.log(mh.arr);
mh.delete();
console.log(mh.arr);