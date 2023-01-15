import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class Merge_queue {
    public static ListNode mergeKLists(ListNode[] lists) {
        if(null == lists || lists.length == 0) {
            return null;
        }
        PriorityQueue<ListNode> queue = new PriorityQueue<>(lists.length, new Comparator<ListNode>() {
            @Override
            public int compare(ListNode o1, ListNode o2) {
                return o1.val - o2.val;
            }
        });
        // 循环添加元素
        for(ListNode listNode : lists) {
            if(listNode != null) {
                queue.offer(listNode);
            }
        }
        // 依次弹出
        return buildHead(queue);
    }
    /**
     * 构建头节点
     * @param queue 列表
     * @return 结果
     * @since v2
     */
    private static ListNode buildHead(Queue<ListNode> queue) {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;
        while (!queue.isEmpty()) {
            tail.next = queue.poll();
            tail = tail.next;
            // 这里类似于将 queue 层层剥开放入 queue 中
            if(tail.next != null) {
                queue.add(tail.next);
            }
        }
        return dummy.next;
    }
}
