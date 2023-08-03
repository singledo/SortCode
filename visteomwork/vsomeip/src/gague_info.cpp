#include "gague_info.hpp"
#include "ql-server.h"
#include <iostream>

using namespace std;

gague_info  g_gague_info;

bool gague_info::init (void)
{

    printf ("service id : 0x%x instance id 0x%x group id: 0x%x event id 0x%x \n", GAGUEINFO_SERVICE_ID, GAGUEINFO_SER_INSTANCE_ID, GAGUEINFO_EVT_GROUP_ID, GAGUEINFO_SER_EVENT);

    mApp = vsomeip::runtime::get()->create_application(GAGUEINFO_SERVICE_APP);

    printf("[%s],[%d]\n",__FUNCTION__,__LINE__);

    mApp->init ();

    mApp->register_state_handler(std::bind(&gague_info::on_state, this, std::placeholders::_1));

    /* for GagueInfo  */
    mApp->register_availability_handler(static_cast<vsomeip::service_t> (GAGUEINFO_SERVICE_ID),\
                                        static_cast<vsomeip::instance_t> (GAGUEINFO_SER_INSTANCE_ID),\
                                        std::bind(&gague_info::on_gagueinfo_availability, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    mApp->register_message_handler(static_cast<vsomeip::service_t> (GAGUEINFO_SERVICE_ID),\
                                   static_cast<vsomeip::instance_t> (GAGUEINFO_SER_INSTANCE_ID), \
                                   static_cast<vsomeip::method_t> (GAGUEINFO_SER_EVENT),\
                                   std::bind(&gague_info::on_event, this, std::placeholders::_1));

    mApp->request_service(static_cast<vsomeip::service_t> (GAGUEINFO_SERVICE_ID),\
                          static_cast<vsomeip::instance_t> (GAGUEINFO_SER_INSTANCE_ID));

    /*for OTA SINGLE*/
    mApp->register_availability_handler(static_cast<vsomeip::service_t> (OTA_SERVICE_ID),\
                                        static_cast<vsomeip::instance_t> (OTA_INSTANCE),\
                                        std::bind(&gague_info::on_ota_availability, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    mApp->register_message_handler(static_cast<vsomeip::service_t> (OTA_SERVICE_ID),\
                                   static_cast<vsomeip::instance_t> (OTA_INSTANCE), \
                                   static_cast<vsomeip::method_t> (OTA_SERVICE_EVENT),\
                                   std::bind(&gague_info::on_event, this, std::placeholders::_1));

    mApp->request_service(static_cast<vsomeip::service_t> (OTA_SERVICE_ID),\
                          static_cast<vsomeip::instance_t> (OTA_INSTANCE));



    this->timer.timer_start ();

    return true;
}


void gague_info::stop (void)
{

    mApp->unregister_message_handler(GAGUEINFO_SERVICE_ID, GAGUEINFO_SER_INSTANCE_ID, GAGUEINFO_SER_EVENT);
    mApp->clear_all_handler();
    mApp->stop();

    if(mReader.joinable())
    {
          mReader.join();
    }
}



void gague_info::start (void)
{
    std::set<vsomeip::eventgroup_t> its_groups;
    std::unique_lock<std::mutex> lock(m_mtx);

    mReader = std::thread([this]() { mApp->start(); });
    m_cnd.wait(lock);

    std::this_thread::sleep_for(std::chrono::milliseconds(SUBSCRIPTION_DELAY));

    its_groups.insert (GAGUEINFO_EVT_GROUP_ID);
    its_groups.insert (OTA_SERVICE_GROUP);

    mApp->request_event (static_cast<vsomeip::service_t> (GAGUEINFO_SERVICE_ID),\
                        static_cast<vsomeip::instance_t> (GAGUEINFO_SER_INSTANCE_ID), \
                        static_cast<vsomeip::method_t> (GAGUEINFO_SER_EVENT), its_groups, true);

    mApp->subscribe(static_cast<vsomeip::service_t> (GAGUEINFO_SERVICE_ID),\
                   static_cast<vsomeip::instance_t> (GAGUEINFO_SER_INSTANCE_ID), \
                   static_cast<vsomeip::instance_t> (GAGUEINFO_EVT_GROUP_ID));
    
    mApp->request_event (static_cast<vsomeip::service_t> (OTA_SERVICE_ID),\
                        static_cast<vsomeip::instance_t> (OTA_INSTANCE), \
                        static_cast<vsomeip::method_t> (OTA_SERVICE_EVENT), its_groups, true);

    mApp->subscribe(static_cast<vsomeip::service_t> (OTA_SERVICE_ID),\
                   static_cast<vsomeip::instance_t> (OTA_INSTANCE), \
                   static_cast<vsomeip::instance_t> (OTA_SERVICE_GROUP));

}

void gague_info::on_gagueinfo_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
{
    printf("[%s],[%d] [%s]\n",__FUNCTION__,__LINE__, \
           false==_is_available?"no available":"available");
    if (_is_available == true)
    {
        m_cnd.notify_all();
    } 
}

void gague_info::on_ota_availability (vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
{
    printf("[%s],[%d] [%s]\n",__FUNCTION__,__LINE__, \
           false==_is_available?"no available":"available");
}



bool gague_info::on_subscription(vsomeip::client_t _client, bool _subscribed)
{
    return true;
}

void gague_info::on_event(const std::shared_ptr<vsomeip::message> &_response)
{
    vsomeip::service_t service_id  = 0;  
    vsomeip::method_t  method_id   = 0;
    vsomeip::length_t  payload_len = 0;
    gagueInfo_t        *p_gagueInfo = NULL;
    int                i = 0;
    std::stringstream its_message;


    std::shared_ptr<vsomeip::payload> _payload ;

    service_id = _response->get_service();
    method_id  = _response->get_method ();

    cout << "service id"  <<  service_id  << "method  id " << method_id << endl;

    if (GAGUEINFO_SERVICE_ID == service_id)
    {
        _payload = _response->get_payload ();
        payload_len = _payload->get_length ();

        cout << "payload len" << payload_len  << endl;

        if (payload_len > 0)
        {
            its_message  << "payload data:[ " ;
            for (i=0; i<payload_len; i++)
            {
                its_message  << std::hex << "-" << (int)_payload->get_data()[i];
            }
            its_message << "]";

            cout << its_message.str() << endl;
        }
    }
    else if (OTA_SERVICE_ID == service_id) 
    {
        _payload = _response->get_payload ();
        payload_len = _payload->get_length ();

        cout << "payload len" << payload_len  << endl;

        if (payload_len > 0)
        {
            its_message  << "payload data:[ " ;
            for (i=0; i<payload_len; i++)
            {
                its_message  << std::hex << "-" << (int)_payload->get_data()[i];
            }
            its_message << "]";

            cout << its_message.str() << endl;
        }
    }
    else
    {
    }
}

void  gague_info::on_state (vsomeip::state_type_e state)
{
    if (vsomeip::state_type_e::ST_REGISTERED == state)
    {
        cout << "ST_REGISTERED" << endl;
    }
    else if (vsomeip::state_type_e::ST_DEREGISTERED == state)
    {
        cout << "ST_DEREGISTERED" << endl;
    }
}

