class Node {
    constructor(data) {
        this.data = data;
        this.left;
        this.right;
    }
}

class BinarySearchTree {
    constructor() {
        this.root;
        this.count = 0;
    }

    insert(data) {
        const node = new Node(data);

        if (this.count === 0) this.root = node;
        else this._insert(this.root, node);
        
        this.count++;
    }

    _insert(root, node) {
        if (root.data > node.data) {
            root.left = this._insert(root.left, node);

            return root;
        }

        if (root.data < node.data) {
            root.right = this._insert(root.right, node);

            return root;
        }

        return root;
    }

    remove(data) {
        if (this.count === 0) return null;

        this.root = this._remove(this.root, data);
        this.count--;
    } 

    _remove(root, data) {
        let exchange;

        if (root.data > data) root.left = this._remove(root.left, data);
        if (root.data < data) root.right = this._remove(root.right, data);
        if (root.data === data) {
            if (!root.left) return root.right;
            else if (!root.right) return root.left;
            else {
                exchange = root.left;

                while (exchange.right) {
                    exchange = exchange.right;
                }

                let tmp = root.data;
                root.data = exchange.data;
                exchange.data = tmp;

                root.left = this._remove(root.left, exchange.data);
            }
        }
    }
}

const bst = new BinarySearchTree();

bst.insert(15);
bst.insert(1);
bst.insert(11);
bst.insert(7);

console.log(bst);