#ifndef  __NONCOPYABLE_H__
#define __NONCOPYABLE_H__


class Noncopyable
{
protected:
    Noncopyable(){}
    ~Noncopyable(){}


    Noncopyable(const Noncopyable&) = delete;
    Noncopyable&operator=(const Noncopyable&)=delete;
};



#endif