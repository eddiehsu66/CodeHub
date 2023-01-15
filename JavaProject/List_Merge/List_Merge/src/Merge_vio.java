import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class Merge_vio {
    public static ListNode mergeKLists(ListNode[] lists) {
        if(null == lists || lists.length == 0) {
            return null;
        }
        // 查找操作比较少
        List<Integer> integerList = new LinkedList<>();
        for(ListNode listNode : lists) {
            integerList.addAll(getIntegerList(listNode));
        }
        // 排序
        System.out.println(integerList.size());
        Collections.sort(integerList);
        // 构建结果
        return buildHead(integerList);
    }

    private static List<Integer> getIntegerList(ListNode oneNode) {
        // 使用 linkedList，避免扩容
        List<Integer> resultList = new LinkedList<>();
        while (oneNode != null) {
            int value = oneNode.val;
            resultList.add(value);
            oneNode = oneNode.next;
        }
        return resultList;
    }

    private static ListNode buildHead(List<Integer> integers) {
        if(integers.size() == 0) {
            return null;
        }
        ListNode head = new ListNode(integers.get(0));
        ListNode temp = head;
        for(int i = 1; i < integers.size(); i++) {
            temp.next = new ListNode(integers.get(i));
            temp = temp.next;
        }
        return head;
    }
}
