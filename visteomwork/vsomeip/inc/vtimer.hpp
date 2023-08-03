#ifndef _vtimer_hpp
#define _vtimer_hpp

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>  
#include <signal.h>  
#include <time.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h> 

#ifdef __cplusplus
           }
#endif

#include <thread>
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <list>

#define TIMER_DEBUG

using namespace std;

#define GNSS_TIMER_SINGLE (SIGUSR1)
#define FUNC_MAX          (10)

typedef enum 
{
    _TIMER_START = 0,
    _TIMER_STOP,
    _TIMER_VAL,
    _TIMER_UNVAL
}TIMER_ST;

typedef void *(*cb_func) (void );

class vtimer 
{
public:
    vtimer (int sec, int nsec) ;
    vtimer () ;
    bool timer_start ();
#ifdef TIMER_DEBUG
    void p_timer (void);
#endif
    static void timer_sig_handler (int nsig);
    bool timer_stop (void);
    bool timer_add_cb (cb_func func);

private:
    TIMER_ST timer_st;
    int      time_sec ;
    int      time_nsec;
    pid_t    pid ;
    std::thread  mTimer;
    void timer_loop(void);

    cb_func  up_func[FUNC_MAX];
    int      func_num;
    std::mutex  timer_mtx;

    int tt;
};


#endif

