class Node {
    constructor(data) {
        this.data = data;
        this.left;
        this.right;
    }
}

class Tree {
    constructor() {
        this.count = 0;
        this.root;
    }

    insert(data) {
        const node = new Node(data);

        if (this.count === 0) {
            this.root = node;
        } else {
            this._insert(this.root, node);
        }

        this.count++;
    }

    find(data) {
        if (!this.root) return null;
        else return this._find(data, this.root);
    }

    display() {
        if (!this.root) return null;
        else this._display(this.root);
    }

    remove(data) {
        const node = this._remove(this.root, data);

        if (node) {
            this.root = node;
            this.count--;
        }
    }

    /* recursion */
    _insert(root, node) { 
        if (!root) return node;
        if (node.data < root.data) {
            root.left = this._insert(root.left, node);
            return root;
        } else {
            root.right = this._insert(root.right, node);
            return root;
        }
        return root;
    }

    _find(data, node) {
        if (node) { // node가 있으면
            if (data < node.data) {
                return this._find(data, node.left);
            } else if (data > node.data) {
                return this._find(data, node.right);
            } else {
                return node;
            }
        } else { // 없으면
            return null;
        }
    }

    _display(root) {
        console.log(root.data);

        this._display(root.left);
        this._display(root.right);
    }

    _remove(root, data) {
        let newRoot, exchange, tmp;

        if (!root) return false;
        if (data < root.data) {
            root.left = this._remove(root.left, data);
        } else if (data > root.data) {
            root.right = this._remove(root.right, data);
        } else { // root를 삭제
            if (!root.left) {
                newRoot = root.right;
                return newRoot;
            } else if (!root.right) {
                newRoot = root.left;
                return newRoot;
            } else {
                exchange = root.left;

                while (exchange.right) exchange = exchange.right;
                // right가 있는 node까지 내려간 후 root와 교환 후 제거
                tmp = root.data;
                root.data = exchange.data;
                exchange.data = tmp;

                root.left = this._remove(root.left, exchange.data);
            }
        }
    }
}

const tree = new Tree();

tree.insert(10);
tree.insert(5);
tree.insert(3);
tree.insert(30);
tree.insert(15);
tree.display();