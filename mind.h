#ifndef MIND_H
#define MIND_H
#include <appmanager.h>

class Mind
{
public:
    static Mind *getMind();

    void start();

private:
    Mind();
    Mind(const Mind& root) = delete;
    Mind& operator=(const Mind&) = delete;
    ~Mind();

    static Mind *_mind;

    AppManager *appMgr;
};

#endif // MIND_H
