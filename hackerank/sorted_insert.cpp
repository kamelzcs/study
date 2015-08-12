/*
    Insert Node in a doubly sorted linked list 
    After each insertion, the list should be sorted
   Node is defined as
   struct Node
   {
     int data;
     Node *next;
     Node *prev
   }
*/
Node* SortedInsert(Node *head,int data)
{
    // Complete this function
   // Do not write the main method. 
   Node* to_add = new Node();
   to_add->data = data;
   to_add->next = to_add->prev = NULL;
   if(!head){
       return to_add;
   }
   if(data <= head->data){
       to_add->prev = head->prev;
       to_add->next = head;
       head->prev = to_add;
       return to_add;
   }
   Node *current = head;
   while(current->next){
       if(data <= current->next->data){
           to_add->prev = current;
           to_add->next = current->next;
           current->next->prev = to_add;
           current->next = to_add;
           return head;
       }
       current = current->next;
   }
   to_add->prev = current;
   to_add->next = current->next;
   current->next = to_add;
   return head;
}
