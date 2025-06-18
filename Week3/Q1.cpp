Node* FirstNode(Node* head)
{
  Node* fast = head;
  Node* slow = head;
  bool isLoop = false;
  while (fast!=nullptr && fast->next!=nullptr)
  {
    fast = fast->next->next;
    slow = slow->next;
    if (fast==slow)
    {
      isLoop = true;
      break;
    }
  }
  if (isLoop==false) return nullptr;
  slow=head;
  while(fast!=slow)
  {
    fast = fast->next;
    slow = slow->next;
  }
  return fast;
}