class Vertex {
    constructor(data) {
        this.data = data;
        this.next = null;
        this.arc = null;
    }
}

class Arc {
    constructor(data, destination) {
        this.data =  data;
        this.destination = destination;
        this.nextArc = null;
    }
}

class Graph {
    constructor() {
        this.count = 0;
        this.first = null;
    }

    insertVertex(data) {
        const vertex = new Vertex(data);

        let last = this.first;

        if (last) { // 기존 값이 있으면
            while (last.next !== null) {
                last = last.next;
            }

            last.next = vertex; // 마지막에 삽입
        } else { // 없으면
            this.first = vertex;
        }

        this.count++;
    }

    deleteVertex(data) {
        let vertex = this.first;
        let prev = null;

        while (vertex.data !== data) { // 찾을 때 까지 반복
            prev = vertex;
            vertex = vertex.next;
        }
        
        if (!vertex) return false;
        if (!vertex.arc) return false;

        if (prev) { // 이전 값이 있으면
            prev.next = vertex.next;
        } else { // 없으면
            this.first = vertex.next;
        }

        this.count--;
    }

    insertArc(data, fromV, toV) {
        let from  = this.first;
        let to = this.first;

        while (from !== null) {
            if (from.data === fromV) break;

            from = from.next;
        }

        while (to && to.data !== toV) {
            to = to.next;
        }

        if (!from || !to) return false;

        const arc = new Arc(data, to);

        let fromLast = from.arc;

        if (fromLast) {
            while (fromLast.nextArc !== null) {
                fromLast = fromLast.nextArc;
            }

            fromLast.nextArc = arc;
        } else {
            from.arc = arc;
        }
    }

    deleteArc(fromV, toV) {
        let from = this.first;

        while (from !== null) {
            if (from.data === fromV) break;

            from = from.next;
        }

        if (!from) return false;

        let fromArc = from.arc;
        let preArc;

        while (fromArc !== null) {
            if (toV === fromArc.destination.data) break;

            preArc = fromArc;
            fromArc = fromArc.next;
        }

        if (!fromArc) return false;
        if (preArc) {
            preArc.nextArc = fromArc.nextArc;
        } else {
            from.arc = fromArc.nextArc;
        }
    }
}

const graph = new Graph();

graph.insertVertex('A');
graph.insertVertex('B');
graph.insertVertex('C');
graph.insertArc(1, 'A', 'B');
graph.insertArc(1, 'A', 'C');

console.dir(graph);