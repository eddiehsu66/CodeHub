public class Merge_divide {
    public static ListNode mergeKLists(ListNode[] lists) {
        final int length = lists.length;
        if (lists.length == 0) {
            return null;
        }
        if (lists.length == 1) {
            return lists[0];
        }
        // 递归获取两个节点
        int mid = (length) / 2;
        ListNode one = mergeKLists(subArray(lists, 0, mid));
        ListNode two = mergeKLists(subArray(lists, mid, length));
        // 合并最后2个节点
        return mergeTwoLists(one, two);
    }

    private static ListNode[] subArray(ListNode[] listNodes, int start, int end) {
        int size = end - start;
        ListNode[] result = new ListNode[size];
        int index = 0;
        for (int i = start; i < end; i++) {
            result[index++] = listNodes[i];
        }
        return result;
    }
    public static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if(l1 == null) {
            return l2;
        }
        if(l2 == null) {
            return l1;
        }
        // 临时变量
        ListNode newNode = new ListNode(0);
        // 新增的头指针
        ListNode head = newNode;
        // 循环处理
        while (l1 != null && l2 != null) {
            int valOne = l1.val;
            int valTwo = l2.val;
            // 插入小的元素节点
            if(valOne <= valTwo) {
                newNode.next = l1;
                l1 = l1.next;
            } else {
                newNode.next = l2;
                l2 = l2.next;
            }
            // 变换 newNode
            newNode = newNode.next;
        }
        // 如果长度不一样
        if(l1 != null) {
            newNode.next = l1;
        }
        if(l2 != null) {
            newNode.next = l2;
        }
        return head.next;
    }
}
