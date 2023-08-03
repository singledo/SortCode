#ifndef _gague_info_hpp
#define _gague_info_hpp

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vsomeip/vsomeip.hpp>
#include <vsomeip/enumeration_types.hpp>
#include <iomanip>
#include  <sstream>

#include "vtimer.hpp"

#define GAGUEINFO_SERVICE_APP  "gagueInfoClient"
#define GAGUEINFO_SERVICE_ID       (0x36)
#define GAGUEINFO_SER_INSTANCE_ID  1
#define GAGUEINFO_SER_EVENT        (0x8001)
#define GAGUEINFO_EVT_GROUP_ID     (0x4444)
#define SUBSCRIPTION_DELAY         100

#define OTA_SERVICE_ID       (0x73)
#define OTA_INSTANCE         (0x01)
#define OTA_SERVICE_EVENT    (0x8001)
#define OTA_SERVICE_GROUP    (0x4444)

typedef enum EGaugeUnit_t 
{
    EGaugeUnit_Mph = 0,
    EGaugeUnit_Kmph ,
    EGaugeUnit_Centigrade ,
    EGaugeUnit_Farenheit ,
    EGaugeUnit_Psi ,
    EGaugeUnit_Pa ,
    EGaugeUnit_Bar ,
    EGaugeUnit_Last
};

#pragma pack(1)
struct gagueInfo 
{
    unsigned char  id;
    unsigned short position;
    signed int digitalDataa;
    EGaugeUnit_t unit;
    unsigned short dynData;
};
typedef struct gagueInfo  gagueInfo_t;
#pragma pack()


class gague_info
{
private:
    std::shared_ptr<vsomeip::application> mApp;
    std::thread mReader; 
    mutable std::mutex m_mtx;       
    std::condition_variable m_cnd;  

    /*fot timer */
    vtimer  timer;

public:
    gague_info(): m_mtx(), m_cnd() {};
    virtual  ~gague_info () {};
    void event_handler(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);

    bool init (void);
    void start (void);
    void stop();


    void on_event(const std::shared_ptr<vsomeip::message> &_response);
    bool on_subscription(vsomeip::client_t _client, bool _subscribed);
    void on_state (vsomeip::state_type_e state);
    void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);

    void on_gagueinfo_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);
    void on_ota_availability (vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);
};


extern gague_info  g_gague_info;

#endif
