#include "vtimer.hpp"

vtimer *p_gEntry = NULL;

#ifdef TIMER_DEBUG

void vtimer::p_timer (void)
{
    time_t timep;
    struct tm *p;
    struct timeval tv;
    long long n_ms = 0;

    gettimeofday(&tv,NULL);
    n_ms =  tv.tv_usec / 1000;
    time(&timep);
    p = gmtime(&timep);
    printf("time: %d-%d-%d %d:%d:%d:%ld \n", 1900 + p->tm_year, 1 + p->tm_mon,\
           p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec, n_ms);

}
#endif


vtimer::vtimer (int sec, int nsec) 
{
    struct sigaction act,oldact;

    memset (this->up_func, 0 , sizeof(this->up_func));
    this->func_num = 0;

    this->timer_st = _TIMER_STOP;

    this->time_sec  = sec;
    this->time_nsec = nsec;
    this->pid       = pthread_self();
    p_gEntry = this;

    act.sa_handler  = this->timer_sig_handler;
    act.sa_flags = 0;
    sigaction(GNSS_TIMER_SINGLE, &act, &oldact);

}

vtimer::vtimer () 
{
    struct sigaction act,oldact;
    memset (this->up_func, 0 , sizeof(this->up_func));
    this->func_num = 0;
   
    this->timer_st = _TIMER_STOP;

    this->time_sec  = 0;
    this->time_nsec = 100;
    this->pid       = getpid();
    p_gEntry = this;

    act.sa_handler  = timer_sig_handler;
    act.sa_flags    = 0;

    sigaction (GNSS_TIMER_SINGLE,&act,&oldact);
}


void vtimer::timer_sig_handler (int nsig)
{
    //p_gEntry->p_timer ();
    int i = 0;
    p_gEntry->timer_mtx.lock() ;  
    for (i=0; i<p_gEntry->func_num; i++)
    {
        p_gEntry->up_func[i]();
    }
    p_gEntry->timer_mtx.unlock() ;  
}


bool vtimer::timer_add_cb (cb_func func)
{
    timer_mtx.lock() ;  

    if (this->func_num < FUNC_MAX)
    {
        up_func[this->func_num] = func;
        this->func_num += 1;

        timer_mtx.unlock() ;  
        return true;
    }
    else
    {
        timer_mtx.unlock() ;  
        return false;
    }
}

void vtimer::timer_loop (void)
{
    struct timeval delay_time;;

    while (_TIMER_START == timer_st)
    {
        delay_time.tv_sec  = this->time_sec;
        delay_time.tv_usec = this->time_nsec * 1000;
        select(0, NULL, NULL, NULL, &delay_time);    
        kill (this->pid, GNSS_TIMER_SINGLE);
    }
}

bool vtimer::timer_start ()
{
    this->timer_st = _TIMER_START;

    mTimer = std::thread ([this](){
                          this->timer_loop();
                          });
    return true;
}

bool vtimer::timer_stop (void)
{
    this->timer_st = _TIMER_STOP;
    mTimer.join ();
    return true;
}

