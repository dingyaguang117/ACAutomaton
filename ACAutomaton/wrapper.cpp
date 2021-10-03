#include <Python.h>
#include "_ACAutomaton.h"
/****** wrap for python ********/

// for python3 use PyCapsule_GetPointer instead of PyCObject_AsVoidPtr
// ref: http://www.speedupcode.com/c-class-in-python3/

#if PY_MAJOR_VERSION >= 3
    #define PyCObject_FromVoidPtr(pointer, destructor) \
     (PyCapsule_New(pointer, "ACAutomaton", destructor))
    #define PyCObject_AsVoidPtr(capsule) \
     (PyCapsule_GetPointer(capsule, "ACAutomaton"))
#endif


#if PY_MAJOR_VERSION < 3
    static void ACAutomaton_Delete(void *ptr)
    {
        ACAutomaton * pAC = static_cast<ACAutomaton *>(ptr);
        delete pAC;
    }
#else
    static void ACAutomaton_Delete(PyObject *ptr)
    {
        ACAutomaton * pAC = static_cast<ACAutomaton *>(PyCapsule_GetPointer(ptr, "ACAutomaton"));
        delete pAC;
    }
#endif 


static PyObject* ACAutomaton_new(PyObject *self, PyObject* args)
{
    ACAutomaton *pAC = new ACAutomaton();
    return PyCObject_FromVoidPtr(pAC, ACAutomaton_Delete);
}

static PyObject* ACAutomaton_insert(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    const char* str;
    int ok = PyArg_ParseTuple(args, "Os", &ac, &str);
    if(!ok) return NULL;
    //printf("insert: %s\n", str);
    ACAutomaton *acautomaton = static_cast<ACAutomaton *>(PyCObject_AsVoidPtr(ac));
    acautomaton->insert(str);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* ACAutomaton_build(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    int ok = PyArg_ParseTuple(args, "O", &ac);
    if(!ok) return NULL;
    ACAutomaton *acautomaton = static_cast<ACAutomaton *>(PyCObject_AsVoidPtr(ac));
    acautomaton->build();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* ACAutomaton_matchOne(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    const char* str;
    std::queue<Result> results;
    int ok = PyArg_ParseTuple(args, "Os", &ac, &str);
    if(!ok) return NULL;
    ACAutomaton *acautomaton = static_cast<ACAutomaton *>(PyCObject_AsVoidPtr(ac));
    acautomaton->match(str, false, results);
    if(results.empty())
    {
        return Py_BuildValue("is", -1, 0);
    }
    Result result = results.front();
    return Py_BuildValue("ls", result.position, result.word);
}

static PyObject* ACAutomaton_matchAll(PyObject *self, PyObject* args)
{
    PyObject *ac = 0;
    const char* str;
    std::queue<Result> results;
    int ok = PyArg_ParseTuple(args, "Os", &ac, &str);
    if(!ok) return NULL;
    ACAutomaton *acautomaton = static_cast<ACAutomaton *>(PyCObject_AsVoidPtr(ac));
    acautomaton->match(str, true, results);
    PyObject* pList = PyList_New(results.size());
    unsigned long i = 0;
    while(!results.empty())
    {
        Result result = results.front();
        results.pop();
        PyList_SetItem(pList, i++, Py_BuildValue("ls", result.position, result.word));
    }
    return pList;
}

static PyMethodDef Methods[] =
{
     { "new", ACAutomaton_new, METH_NOARGS, "create a ACAutomaton Object" },
     { "insert", ACAutomaton_insert, METH_VARARGS, "insert string" },
     { "build", ACAutomaton_build, METH_VARARGS, "build" },
     { "matchOne", ACAutomaton_matchOne, METH_VARARGS, "matchOne" },
     { "matchAll", ACAutomaton_matchAll, METH_VARARGS, "matchAll" },
     { NULL, NULL, 0, NULL }
};



#if PY_MAJOR_VERSION < 3
    PyMODINIT_FUNC init_ACAutomaton(void)
    {
        Py_InitModule( "_ACAutomaton", Methods);
    }
#else
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "_ACAutomaton", /* m_name */
        NULL,      /* m_doc */
        -1,                  /* m_size */
        Methods,             /* m_methods */
        NULL,                /* m_reload */
        NULL,                /* m_traverse */
        NULL,                /* m_clear */
        NULL,                /* m_free */
    };

    PyMODINIT_FUNC PyInit__ACAutomaton(void)
    {
        PyObject *m = PyModule_Create(&moduledef);
        return m;
    }
#endif