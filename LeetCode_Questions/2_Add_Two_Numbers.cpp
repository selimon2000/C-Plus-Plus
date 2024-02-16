/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *returnListNode = new ListNode();
        ListNode *head=returnListNode;
        int data;
        int carry_over = 0;

        bool virgin_flag=true;


        while ((l1 != NULL || l2 != NULL) || carry_over>0)
        {
            data = 0;
            if (l1 != NULL)
            {
                data += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL)
            {
                data += l2->val;
                l2 = l2->next;
            }

            data += carry_over;
            carry_over = data / 10;
            data %= 10;
            cout << "Data: " << data << endl;

            if(virgin_flag==false)
           {
            ListNode *newNode = new ListNode();
            returnListNode->next = newNode;
            returnListNode = returnListNode->next;
           }

            returnListNode->val = data;
            virgin_flag=false;
        }

        return head;
    }
};