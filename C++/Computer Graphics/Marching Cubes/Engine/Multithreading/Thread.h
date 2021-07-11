/*
Thread.h
Written by Matthew Fisher

A thread is a single unit of code execution
*/

struct Thread
{
public:
    Thread();
    ~Thread();
    
    __forceinline bool Active()
    {
        return (_Handle != NULL);
    }
    void CloseThread();
    
    void Begin(LPTHREAD_START_ROUTINE StartFunction, void *Context);

private:
    HANDLE _Handle;
};
