#ifndef _DEFS_H_
#define _DEFS_H_

// Defs reader
class Defs 
{
private:
    static Defs* instance;
    
    Defs();
    Defs(const Defs&) = delete;
    Defs& operator=(const Defs&) = delete;
    ~Defs();
public:
    static Defs* getInstance();
    void read();
    void print();
};


#endif