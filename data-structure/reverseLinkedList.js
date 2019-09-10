export function reverseLinkedList(rll) {
    let currentNode = rll.head;
    let prev;

    while (currentNode) {
        let tmp = currentNode.next;
        currentNode.next = prev;
        prev = currentNode;

        if (!tmp) { // head
            break;
        }

        currentNode = tmp;
    }

    return rll;
}