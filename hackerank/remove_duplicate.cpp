/*
  Remove all duplicate elements from a sorted linked list
  Node is defined as 
  struct Node
  {
     int data;
     struct Node *next;
  }
*/
Node* RemoveDuplicates(Node *head)
{
  // This is a "method-only" submission. 
  // You only need to complete this method. 
  if(!head || !head->next){
      return head;
  }
  Node* current=head, *next=head->next;
  while(1){
      if(!current){
          break;
      }
      next=current->next;
      while(next && next->data == current->data){
          next = next->next;
      }
      current->next = next;
      current = next;
  }
  return head;
}
