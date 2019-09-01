class Node {
    constructor(data) {
        this.data = data;
        this.left;
        this.right;
    }
}

class Bst {
    constructor() {
        this.root;
    }

    insert(data) {
        const node = new Node(data);

        if (!this.root) {
            this.root = node;
        } else {
            this._insert(this.root, node);
        }
    }

    _insert(root, node) {
        if (node.data < root.data) {
            root.left = this._insert(root.left, node);
        }

        if (node.data > root.data) {
            root.right = this._insert(root.right, node);
        }

        return root;
    }

    remove(data) {
        if (!this.root) return null;

        this.root = this._remove(this.root, data);
    }

    _remove(root, data) {
        let exchange;

        if (data < root.data) {
            root.left = this._remove(root.left, data);
        } else if (data > root.data) {
            root.right = this._remove(root.right, data);
        } else {
            if (!root.left) return root.right;
            if (!root.right) return root.left;

            exchange = root.left;

            while (exchange.right) exchange = exchange.right;

            let tmp = root.data;
            root.data = exchange.data;
            exchange.data = tmp;

            root.left = this._remove(root.left, exchange.data);
        }
    }
}

const bst = new Bst();

bst.insert(5);
bst.insert(9);