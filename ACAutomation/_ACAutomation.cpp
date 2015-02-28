#include "_ACAutomation.h"
#include <iostream>

using namespace std;



ACAutomation::ACAutomation()
{
    this->root = new Node();
}

void freeNode(Node *node)
{
    for(int i=0; i<KIND; ++i)
    {
        if(node->next[i] != NULL)
        {
            freeNode(node->next[i]);
        }
    }
    delete node->word;
    delete node;
}

ACAutomation::~ACAutomation()
{
    freeNode(this->root);
}

void ACAutomation::insert(const char *str)
{
    Node *p = this->root;
    int i = 0;
    while(str[i])
    {
        //KIND=16, 所以一个字节分成2个4字节
        unsigned short chr = str[i];
        for(int j=0; j<2; ++j)
        {
            int index = chr % 16;
            chr /= 16;
            if (p->next[index] == NULL)
                p->next[index] = new Node();
            p = p->next[index];
        }
        i++;
    }
    p->end = true;
    p->word = strdup(str);
}


void ACAutomation::build(){
    this->root->fail = NULL;
    this->q.push(this->root);
    while(!this->q.empty())
    {
        Node *parent = this->q.front();
        this->q.pop();
        for(int i=0; i<KIND; ++i)
        {
            Node *child =parent->next[i];
            if (child == NULL) continue;
            if (parent == this->root){
                child->fail = this->root;
            }
            else{
                Node *failp = parent->fail;
                while(failp != NULL)
                {
                    if(failp->next[i] != NULL)
                    {
                        child->fail = failp->next[i];
                        break;
                    }
                    failp = failp->fail;
                }
                if(failp == NULL) child->fail=this->root;
            }
            this->q.push(child);
        }
    }

}


void ACAutomation::match(const char *str, bool multi, queue<Result> &ret)
{
    Node *p = this->root;
    unsigned long i = 0;
    while(str[i])
    {
        //KIND=16, 所以一个字节分成2个4字节
        unsigned short chr = str[i];
        for(int j=0; j<2; ++j){
            int index = chr % 16;
            chr /= 16;
            while(p->next[index] == NULL && p != this->root)
                p = p->fail;
            if(p->next[index] == NULL)
                p=this->root;
            else
                p=p->next[index];
            if(p->end)
            {
                Result result = {i- strlen(p->word) + 1, p->word};
                ret.push(result);
                if(!multi) return;
            }
        }
        i++;
    }
}


int main()
{
    ACAutomation ac;
    ac.insert("11");
    ac.insert("22");
    ac.build();
    queue<Result> results;
    ac.match("1111111111", true, results);
    ac.~ACAutomation();
    cout<<results.size()<<endl;
}
