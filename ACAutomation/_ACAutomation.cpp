#include <iostream>
#include <queue>
#include <Python.h>


using namespace std;

const int KIND = 16;


struct Node{
	Node *fail;
	Node *next[KIND];
	const char *word;
	bool end;

	Node()
	{
		fail = NULL;
		word = NULL;
		end = false;
		memset(next, 0, sizeof(next));
	}
};

struct Result
{
    int position;
    const char *word;
};


class ACAutomation
{
    private:
    Node *root;
    queue<Node*> q;

    public :
    ACAutomation()
    {
        this->root = new Node();
    }


    void insert(const char *str)
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
        //TODO： str可能被释放
        p->word = str;
    }


    void build(){
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


    Result matchOne(const char *str)
    {
        Result result={-1, NULL};
        Node *p = this->root;
        int i = 0;
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
                    result.position = i;
                    result.word = p->word;
                    return result;
                }
            }
            i++;
        }
        return result;
    }
        
};

/****** wrap for python ********/

static void ACAutomation_Delete(void *ptr)
{
    //TODO delete the tree
    ACAutomation * pAC = static_cast<ACAutomation *>(ptr);
    delete pAC;
}

static PyObject* ACAutomation_new(PyObject *self, PyObject* args)
{
    ACAutomation *pAC = new ACAutomation();
    return PyCObject_FromVoidPtr(pAC, ACAutomation_Delete);
}

static PyObject* ACAutomation_insert(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    const char* str;
    int ok = PyArg_ParseTuple(args, "Os", &ac, &str);
    if(!ok) return NULL;
    ACAutomation *acautomation = static_cast<ACAutomation *>(PyCObject_AsVoidPtr(ac));
    acautomation->insert(str);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* ACAutomation_build(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    int ok = PyArg_ParseTuple(args, "O", &ac);
    if(!ok) return NULL;
    ACAutomation *acautomation = static_cast<ACAutomation *>(PyCObject_AsVoidPtr(ac));
    acautomation->build();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* ACAutomation_matchOne(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    const char* str;
    int ok = PyArg_ParseTuple(args, "Os", &ac, &str);
    if(!ok) return NULL;
    ACAutomation *acautomation = static_cast<ACAutomation *>(PyCObject_AsVoidPtr(ac));
    Result result = acautomation->matchOne(str);
    return Py_BuildValue("is", result.position, result.word);
}

static PyMethodDef Methods[] =
{
     { "new", ACAutomation_new, METH_NOARGS, "create a ACAutomation Object" },
     { "insert", ACAutomation_insert, METH_VARARGS, "insert string" },
     { "build", ACAutomation_build, METH_VARARGS, "build" },
     { "matchOne", ACAutomation_matchOne, METH_VARARGS, "matchOne" },
     { NULL, NULL, 0, NULL }
};


PyMODINIT_FUNC init_ACAutomation(void)
{
     //PyObject *m = Py_InitModule( "_ACAutomation", Methods);
     Py_InitModule( "_ACAutomation", Methods);
}

int main()
{
    ACAutomation ac;
    ac.insert("1111");
    ac.insert("丁亚光");
    ac.build();
    //cout<< ac.matchOne("丁亚光不错~")<<endl;
    //cout<< ac.matchOne("113333") <<endl;
}
