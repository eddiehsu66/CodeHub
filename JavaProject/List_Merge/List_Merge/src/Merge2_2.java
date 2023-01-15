public class Merge2_2 {
    public static ListNode mergeKLists(ListNode[] lists) {
        if(null == lists || lists.length == 0) {
            return null;
        }
        //
        ListNode result = lists[0];
        // 从第二个开始遍历
        for(int i = 1; i < lists.length; i++) {
            ListNode node = lists[i];
            result = mergeTwoLists(result, node);
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
