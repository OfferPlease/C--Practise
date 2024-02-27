#include<iostream>
#include<vector>
// write a function to delete all even values in a linked list
// upon return, the original list should only contains odd value
// a list containing even value is returned
struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
}; 
typedef ListNode* node;

void printList(node list);
node makeList(std::vector<int> & nums);
node solution(node* list);

int main(){
    std::vector<int> vect{1,2,3,4,5};
    node list = makeList(vect);
    node even = solution(&list);
    printList(list);
    printList(even);
    return 0;
}

void printList(node list){
    std::cout<<"list is:"<<std::endl;
    
    while(list!=nullptr){
        std::cout << list->val <<" ";
    }

    std::cout<<std::endl;
}

node makeList(std::vector<int> & nums){
    node dummy = new ListNode();
    node p = dummy;
    for(int i=0; i<nums.size(); i++){
        p->next = new ListNode(nums[i]);
        p = p->next;
    }
    return dummy->next;
}

node solution(node* list){
    node evenHead = new ListNode(0);
    node oddHead = new ListNode(0);
    node pe = evenHead;
    node po = oddHead;
    node head = *list;
    while(head!=nullptr){
        if(head->val % 2 == 0){
            pe->next = head;
            pe = pe->next;
        }
        else{
            po->next = head;
            po = po->next;
        }
        head = head->next;
    }
    po->next = nullptr;
    pe->next = nullptr;
    *list = oddHead->next;
    return evenHead->next;

}