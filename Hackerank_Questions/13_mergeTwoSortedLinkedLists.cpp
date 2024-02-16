SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2)
{
    if (head1==nullptr && head2==nullptr)
    {return nullptr;}
    
    if (head1!=nullptr && head2==nullptr)
    {return head1;}
    
    if (head1==nullptr && head2!=nullptr)
    {return head2;}
    
    if (head1->data <= head2->data)
    {head1->next=mergeLists(head1->next, head2);}
    
    else
    {
        SinglyLinkedListNode* temp=head2; //temp points to head2
        head2=head2->next; //head 2 ordinarily points to the next in the line
        
        temp->next=head1; // this is important as in the following line, where 'head1=temp', it needs to point back to the original head1linkedlist
        head1=temp; //right now, head 1 is actually pointing to in head2's list
        head1->next=mergeLists(head1->next, head2);        
    }
    
    return head1;
}