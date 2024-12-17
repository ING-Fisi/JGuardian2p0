//******************************************************************************************************************//
#include "JGuardian.h"
#include "command.h"

using namespace std;
using namespace CPlusPlusLogging;

Logger* pLogger = NULL; // Create the object pointer for Logger Class

#define TIMER_CMD 3

//****************************************************************//
bool toggle = true;
typedef struct JGuardian_param
{
    bool RealTime_data;
    struct timeval tp;
    char id_dev[20];

    struct modules
    {
        char id_dev[20];
        char payload[50];
    }m;

}JGuardian_param;


JGuardian_param JGuardian_param_istance;


//*****************************************************************************//
MQTTAsync client;
MQTTAsync_connectOptions conn_opts;

#include "jwt/jwt_all.h"
using json = nlohmann::json;
volatile MQTTAsync_token deliveredtoken;

bool start_remote_test = false;


bool mqtt_connection(void);
//********************************************************************************//



std::vector<std::string> split(const std::string& s, char seperator)
{
    std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}
//**************************CURL *********************************//

typedef enum machine_type
{
    MOTOPOMPA_MB,
    MOTOPOMPA_RELE,
    ELETTROPOMPA_MB,
    ELETTROPOMPA_RELE,
    JOKEY,
    SPRINKLER,
}machine_type;

std::string response_string_modbus_MP;
std::string response_string_rele_MP;

std::string response_string_modbus_EP;
std::string response_string_rele_EP;

std::string response_string_JOKEY;

std::string response_string_SPRINKLER1;

CURL* curl_MP_GET_MODBUS;
CURL* curl_MP_GET_RELE_STATUS;
CURL* curl_MP_RESET_GPIO;
CURL* curl_MP_SET_START_ON;
CURL* curl_MP_SET_START_OFF;
CURL* curl_MP_SET_INIBIZIONE_ON;
CURL* curl_MP_SET_INIBIZIONE_OFF;
CURL* curl_MP_SET_STOP_ON;
CURL* curl_MP_SET_STOP_OFF;
CURL* curl_MP_SET_RESET_ON;
CURL* curl_MP_SET_RESET_OFF;

CURL* curl_EP_GET_MODBUS;
CURL* curl_EP_GET_RELE_STATUS;
CURL* curl_EP_RESET_GPIO;
CURL* curl_EP_SET_START_ON;
CURL* curl_EP_SET_START_OFF;
CURL* curl_EP_SET_INIBIZIONE_ON;
CURL* curl_EP_SET_INIBIZIONE_OFF;
CURL* curl_EP_SET_STOP_ON;
CURL* curl_EP_SET_STOP_OFF;
CURL* curl_EP_SET_RESET_ON;
CURL* curl_EP_SET_RESET_OFF;

CURL* curl_JOKEY_GET_RELE_STATUS;
CURL* curl_JOKEY_RESET_GPIO;
CURL* curl_JOKEY_SET_START_ON;
CURL* curl_JOKEY_SET_START_OFF;
CURL* curl_JOKEY_SET_INIBIZIONE_ON;
CURL* curl_JOKEY_SET_INIBIZIONE_OFF;

CURL* curl_SPRINKLER1_GET_RELE_STATUS;
CURL* curl_SPRINKLER1_RESET_GPIO;
CURL* curl_SPRINKLER1_SET_EV_ON;
CURL* curl_SPRINKLER1_SET_EV_OFF;
CURL* curl_SPRINKLER2_SET_EV_ON;
CURL* curl_SPRINKLER2_SET_EV_OFF;
CURL* curl_SPRINKLER3_SET_EV_ON;
CURL* curl_SPRINKLER3_SET_EV_OFF;
CURL* curl_SPRINKLER4_SET_EV_ON;
CURL* curl_SPRINKLER4_SET_EV_OFF;


bool send_curl_request(machine_type mt,CURL* curl_req)
{
    switch(mt)
    {
    case MOTOPOMPA_MB:

        if (curl_req) {
            response_string_modbus_MP.clear();
            CURLcode res = curl_easy_perform(curl_req);
            /* Check for errors */
            if(res != CURLE_OK)
            {
                printf("curl_easy_perform() MOTOPOMPA failed: %s\r\n",curl_easy_strerror(res));
                std::ostringstream ss;
                ss << endl;
                ss << "\t" << "curl_easy_perform() MOTOPOMPA failed " << curl_easy_strerror(res)<< endl;
                pLogger->error(ss);
            }

            return true;
        }

        break;
    case MOTOPOMPA_RELE:

        if (curl_req) {
            response_string_rele_MP.clear();
            CURLcode res = curl_easy_perform(curl_req);
            /* Check for errors */
            if(res != CURLE_OK)
            {
                printf("curl_easy_perform() MOTOPOMPA failed: %s\r\n",curl_easy_strerror(res));
                std::ostringstream ss;
                ss << endl;
                ss << "\t" << "curl_easy_perform() MOTOPOMPA failed " << curl_easy_strerror(res)<< endl;
                pLogger->error(ss);
            }

            return true;
        }

        break;
    case ELETTROPOMPA_MB:

        if (curl_req) {
            response_string_modbus_EP.clear();
            CURLcode res = curl_easy_perform(curl_req);
            /* Check for errors */
            if(res != CURLE_OK)
            {
                printf("curl_easy_perform() ELETTROPOMPA failed: %s\r\n",curl_easy_strerror(res));
                std::ostringstream ss;
                ss << endl;
                ss << "\t" << "curl_easy_perform() ELETTROPOMPA failed " << curl_easy_strerror(res)<< endl;
                pLogger->error(ss);
            }
            return true;
        }

        break;
    case ELETTROPOMPA_RELE:

        if (curl_req) {
            response_string_rele_EP.clear();
            CURLcode res = curl_easy_perform(curl_req);
            /* Check for errors */
            if(res != CURLE_OK)
            {
                printf("curl_easy_perform() ELETTROPOMPA failed: %s\r\n",curl_easy_strerror(res));
                std::ostringstream ss;
                ss << endl;
                ss << "\t" << "curl_easy_perform() ELETTROPOMPA failed " << curl_easy_strerror(res)<< endl;
                pLogger->error(ss);
            }
            return true;
        }

        break;

    case JOKEY:

        if (curl_req) {
            response_string_JOKEY.clear();
            CURLcode res = curl_easy_perform(curl_req);
            /* Check for errors */
            if(res != CURLE_OK)
            {
                printf("curl_easy_perform() JOKEY failed: %s\r\n",curl_easy_strerror(res));
                std::ostringstream ss;
                ss << endl;
                ss << "\t" << "curl_easy_perform() JOKEY failed " << curl_easy_strerror(res)<< endl;
                pLogger->error(ss);
            }
            return true;
        }

        break;

    case SPRINKLER:

        if (curl_req) {
            response_string_SPRINKLER1.clear();
            CURLcode res = curl_easy_perform(curl_req);
            /* Check for errors */
            if(res != CURLE_OK)
            {
                printf("curl_easy_perform() SPRINKLER1 failed: %s\r\n",curl_easy_strerror(res));
                std::ostringstream ss;
                ss << endl;
                ss << "\t" << "curl_easy_perform() SPRINKLER1 failed " << curl_easy_strerror(res)<< endl;
                pLogger->error(ss);
            }
            return true;
        }

        break;

    }

    return false;
}

//***************************RELE *******************************//

struct gpiod_chip *chip;
struct gpiod_line *line_rele0;
struct gpiod_line *line_rele1;

bool line_rele_camera_status = false;
bool line_rele_luci_status = false;

bool line_rele_start_ep_status = false;
bool line_rele_inib_ep_status = false;
bool line_rele_stop_ep_status = false;
bool line_rele_reset_ep_status = false;

bool line_rele_start_mp_status = false;
bool line_rele_inib_mp_status = false;
bool line_rele_stop_mp_status = false;
bool line_rele_reset_mp_status = false;

bool line_rele_start_jk_status = false;
bool line_rele_inib_jk_status = false;

bool line_rele_start_sp1_status = false;
bool line_rele_start_sp2_status = false;
bool line_rele_start_sp3_status = false;
bool line_rele_start_sp4_status = false;



#define PORT_LED "/dev/gpiochip5"
#define OFFSET_LED 0

#define PORT_RELE_NVR "/dev/gpiochip5"
#define OFFSET_RELE_NVR 5

#define PORT_RELE3 "/dev/gpiochip2"
#define OFFSET_RELE3 7

#define PORT_RELE_LUCI_REMOTE "/dev/gpiochip7"
#define OFFSET_RELE_LUCI_REMOTE 11


//*************************** ADC *********************************//
#include "Analog.h"
#define SENSORE_PRESSIONE_A_OFFSET 10479
#define SENSORE_PRESSIONE_B_OFFSET 10479


//0bar 10479 -> 9.2bar 34200
// 34200 - 10479 =

#define SENSORE_PRESSIONE_A_2_20m 19500
#define SENSORE_PRESSIONE_B_16BAR 59478


int sensore_pressione_a = 0;
int sensore_pressione_b = 0;
//***********************************************************************//


int messageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message) {
    printf("Message arrived\n");
    //printf("Topic: %s\n", topicName);

    char *messagePayload = (char*)malloc(message->payloadlen + 1);
    strncpy(messagePayload, (char*)message->payload, message->payloadlen);
    printf("message: %s\n", messagePayload);

    // json j = json::parse(messagePayload);

    messagePayload[message->payloadlen] = '\0';

    //    if(j["c"]=="2")
    //    {

    //    }

    //char cmd;
    //int command;
    //int ret = 0;
    //scanf(messagePayload,"{\"c\":\"%d\"}",&command);


    //  START SETTIMANNALE ////
    if(strcmp(messagePayload,REMOTE_START) == 0 )
    {
        gpio_write(PORT_RELE_LUCI_REMOTE, OFFSET_RELE_LUCI_REMOTE, 1);
        start_remote_test = true;
        line_rele_luci_status = true;

    }

    //  stop SETTIMANNALE ////

    if(strcmp(messagePayload,REMOTE_STOP) == 0 )
    {
        gpio_write(PORT_RELE_LUCI_REMOTE, OFFSET_RELE_LUCI_REMOTE, 0);
        start_remote_test = false;
        line_rele_luci_status = false;



        //********************** RESET RELE ***************************//
        send_curl_request(MOTOPOMPA_RELE,curl_MP_RESET_GPIO);
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_RESET_GPIO);
        send_curl_request(JOKEY,curl_JOKEY_RESET_GPIO);
        send_curl_request(SPRINKLER,curl_SPRINKLER1_RESET_GPIO);
        //**************************************************************//

        gpio_write(PORT_RELE_NVR, OFFSET_RELE_NVR, 0);

        line_rele_camera_status = false;

        //gpio_write(PORT_RELE1, OFFSET_RELE1, 0);

    }


    //********************************************************************************************************//
    if(strcmp(messagePayload,REMOTE_RELE_CAMERA_ON) == 0 )
    {
        printf("COMANDO ATTIVAZIONE RELE CAMERA\r\n");

        gpio_write(PORT_RELE_NVR, OFFSET_RELE_NVR, 1);

        line_rele_camera_status = true;

    }

    else if(strcmp(messagePayload,REMOTE_RELE_CAMERA_OFF) == 0 )
    {
        printf("COMANDO DISATTIVAZIONE RELE CAMERA\r\n");

        gpio_write(PORT_RELE_NVR, OFFSET_RELE_NVR, 0);

        line_rele_camera_status = false;
    }

    //************************************************************************************************//
    if(strcmp(messagePayload,REMOTE_RELE_LUCI_ON) == 0 )
    {
        printf("COMANDO ATTIVAZIONE RELE LUCI\r\n");

        gpio_write(PORT_RELE_LUCI_REMOTE, OFFSET_RELE_LUCI_REMOTE, 1);

        line_rele_luci_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_RELE_LUCI_OFF) == 0 )
    {
        printf("COMANDO DISATTIVAZIONE RELE LUCI\r\n");

        gpio_write(PORT_RELE_LUCI_REMOTE, OFFSET_RELE_LUCI_REMOTE, 0);

        line_rele_luci_status = false;
    }

    //**************************************************************************************************//
    if(strcmp(messagePayload,REMOTE_START_EP) == 0 )
    {
        printf("COMANDO curl_EP_SET_START_ON\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_START_ON);
        //line_rele_start_ep_status = true;

        sleep(TIMER_CMD);

        printf("COMANDO curl_EP_SET_START_OFF\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_START_OFF);
        //line_rele_start_ep_status = false;
    }

    if(strcmp(messagePayload,REMOTE_INIB_EP_ON) == 0 )
    {
        printf("COMANDO curl_EP_SET_INIBIZIONE_ON\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_INIBIZIONE_ON);
        //line_rele_inib_ep_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_INIB_EP_OFF) == 0 )
    {
        printf("COMANDO curl_EP_SET_INIBIZIONE_OFF\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_INIBIZIONE_OFF);
        //line_rele_inib_ep_status = false;
    }

    if(strcmp(messagePayload,REMOTE_STOP_EP) == 0 )
    {
        printf("COMANDO curl_EP_SET_STOP_ON\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_STOP_ON);
        //line_rele_stop_ep_status = true;

        sleep(TIMER_CMD);

        printf("COMANDO curl_EP_SET_STOP_OFF\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_STOP_OFF);
        //line_rele_stop_ep_status = false;
    }

    if(strcmp(messagePayload,REMOTE_RESET_EP) == 0 )
    {
        printf("COMANDO curl_EP_SET_RESET_ON\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_RESET_ON);
        //line_rele_reset_ep_status = true;

        sleep(TIMER_CMD);

        printf("COMANDO curl_EP_SET_RESET_OFF\r\n");
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_SET_RESET_OFF);
        //line_rele_reset_ep_status = false;
    }

    //*******************************************************************************************//
    if(strcmp(messagePayload,REMOTE_START_MP) == 0 )
    {
        printf("COMANDO curl_MP_SET_START_ON\r\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_START_ON);
        //line_rele_start_mp_status = true;

        sleep(TIMER_CMD);

        printf("COMANDO curl_MP_SET_START_OFF\r\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_START_OFF);
        //line_rele_start_mp_status = false;
    }

    if(strcmp(messagePayload,REMOTE_INIB_MP_ON) == 0 )
    {
        printf("COMANDO curl_MP_SET_INIBIZIONE_ON\r\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_INIBIZIONE_ON);
        //line_rele_inib_mp_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_INIB_MP_OFF) == 0 )
    {
        printf("COMANDO curl_MP_SET_INIBIZIONE_OFF\r\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_INIBIZIONE_OFF);
        //line_rele_inib_mp_status = false;
    }

    if(strcmp(messagePayload,REMOTE_STOP_MP) == 0 )
    {
        printf("COMANDO curl_MP_SET_STOP_ONr\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_STOP_ON);
        //line_rele_stop_mp_status = true;

        sleep(10);

        printf("COMANDO curl_MP_SET_STOP_OFF\r\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_STOP_OFF);
        //line_rele_stop_mp_status = false;
    }

    if(strcmp(messagePayload,REMOTE_RESET_MP) == 0 )
    {
        printf("COMANDO curl_EP_SET_STOP_ON\r\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_RESET_ON);
        //line_rele_reset_mp_status = true;

        sleep(TIMER_CMD);

        printf("COMANDO curl_EP_SET_STOP_OFF\r\n");
        send_curl_request(MOTOPOMPA_RELE,curl_MP_SET_RESET_OFF);
        //line_rele_reset_mp_status = false;
    }

    //************************************************************************************************//

    if(strcmp(messagePayload,REMOTE_START_JK) == 0 )
    {
        printf("COMANDO curl_JOKEY_SET_START_ON\r\n");
        send_curl_request(JOKEY,curl_JOKEY_SET_START_ON);
        //line_rele_start_jk_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_STOP_JK) == 0 )
    {
        printf("COMANDO curl_JOKEY_SET_START_OFF\r\n");
        send_curl_request(JOKEY,curl_JOKEY_SET_START_OFF);
        //line_rele_start_jk_status = false;

    }

    if(strcmp(messagePayload,REMOTE_INIB_JK_ON) == 0 )
    {
        printf("COMANDO curl_JOKEY_SET_INIBIZIONE_ON\r\n");
        send_curl_request(JOKEY,curl_JOKEY_SET_INIBIZIONE_ON);
        //line_rele_inib_jk_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_INIB_JK_OFF) == 0 )
    {
        printf("COMANDO curl_JOKEY_SET_INIBIZIONE_OFF\r\n");
        send_curl_request(JOKEY,curl_JOKEY_SET_INIBIZIONE_OFF);
        //line_rele_inib_jk_status = false;
    }
    //************************************************************************************************//


    if(strcmp(messagePayload,REMOTE_START_SP1) == 0 )
    {
        printf("COMANDO curl_SPRINKLER1_SET_EV_ON\r\n");
        send_curl_request(SPRINKLER,curl_SPRINKLER1_SET_EV_ON);
        //line_rele_start_sp_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_STOP_SP1) == 0 )
    {
        printf("COMANDO curl_SPRINKLER1_SET_EV_OFF\r\n");
        send_curl_request(SPRINKLER,curl_SPRINKLER1_SET_EV_OFF);
        //line_rele_start_sp_status = false;
    }

    if(strcmp(messagePayload,REMOTE_START_SP2) == 0 )
    {
        printf("COMANDO curl_SPRINKLER2_SET_EV_ON\r\n");
        send_curl_request(SPRINKLER,curl_SPRINKLER2_SET_EV_ON);
        //line_rele_start_sp_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_STOP_SP2) == 0 )
    {
        printf("COMANDO curl_SPRINKLER2_SET_EV_OFF\r\n");
        send_curl_request(SPRINKLER,curl_SPRINKLER2_SET_EV_OFF);
        //line_rele_start_sp_status = false;
    }

    if(strcmp(messagePayload,REMOTE_START_SP3) == 0 )
    {
        printf("COMANDO curl_SPRINKLER3_SET_EV_ON\r\n");
        send_curl_request(SPRINKLER,curl_SPRINKLER3_SET_EV_ON);
        //line_rele_start_sp_status = true;
    }

    else if(strcmp(messagePayload,REMOTE_STOP_SP3) == 0 )
    {
        printf("COMANDO curl_SPRINKLER3_SET_EV_OFF\r\n");
        send_curl_request(SPRINKLER,curl_SPRINKLER3_SET_EV_OFF);
        //line_rele_start_sp_status = false;
    }

    //    if(strcmp(messagePayload,REMOTE_START_SP4) == 0 )
    //    {
    //        printf("COMANDO curl_JOKEY_SET_START_ON\r\n");
    //        send_curl_request(JOKEY,curl_SPRINKLER4_SET_EV_ON);
    //        //line_rele_start_sp_status = true;
    //    }

    //    else if(strcmp(messagePayload,REMOTE_STOP_SP4) == 0 )
    //    {
    //        printf("COMANDO curl_JOKEY_SET_START_OFF\r\n");
    //        send_curl_request(JOKEY,curl_SPRINKLER4_SET_EV_OFF);
    //        //line_rele_start_sp_status = false;
    //    }


    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    free(messagePayload);

    return 1;
}



void connlost(void *context, char *cause)
{

    printf("Connection lost\r\n");
    std::ostringstream ss;
    ss << endl;
    ss << "\t" << "Connection lost";
    pLogger->error(ss);


    sleep(5);

    mqtt_connection();

}
void onDisconnect(void* context, MQTTAsync_successData* response)
{
    printf("Successful disconnection\r\n");
}
void onSend(void* context, MQTTAsync_successData* response)
{
    printf("CLIENT Message with token value %d delivery confirmed\n", response->token);
}
void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
    printf("CLIENT Connect failed, rc %d %s\r\n", response ? response->code : 0,response->message);

    std::ostringstream ss;
    ss << endl;
    ss << "\t" << "CLIENT Connect failed, rc " << response->code << response->message;
    pLogger->error(ss);

    sleep(5);

    mqtt_connection();

}


void onConnect(void* context, MQTTAsync_successData* response)
{
    printf("Successful connection CLIENT\n");
    std::ostringstream ss;
    ss << endl;
    ss << "\t" << "Successful connection CLIENT" ;
    pLogger->info(ss);

    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    int rc;

    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n", TOPIC_SUB, CLIENTID, QOS);
    opts.onSuccess = NULL;
    opts.onFailure = NULL;
    opts.context = client;
    if ((rc = MQTTAsync_subscribe(client, TOPIC_SUB, QOS, &opts)) != MQTTASYNC_SUCCESS)
    {
        printf("Failed to start subscribe, return code %d\r\n", rc);
        std::ostringstream ss;
        ss << endl;
        ss << "\t" << "Failed to start subscribe, return code" << rc;
        pLogger->error(ss);

    }

}

//*********************************************************************************************//

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}


bool mqtt_connection(void)
{
    RS256Validator signer(rsa_publ_key,rsa_priv_key);

    struct timeval tp;
    gettimeofday(&tp, NULL);

    // Create the json payload that expires 01/01/2017 @ 12:00am (UTC)
    json payload = {{"aud", "jguardian"}, {"iat", tp.tv_sec}, {"exp", tp.tv_sec + 3600}};

    // Let's encode the token to a string
    auto token_jwt = JWT::Encode(signer, payload);

    //***********************************************************************************//

    conn_opts = MQTTAsync_connectOptions_initializer;
    //MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
    MQTTAsync_SSLOptions ssl_opts = MQTTAsync_SSLOptions_initializer;


    int rc;
    rc = MQTTAsync_create(&client, ADDRESS_RT, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    rc = MQTTAsync_setCallbacks(client, NULL, connlost, messageArrived, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = onConnect;
    conn_opts.onFailure = onConnectFailure;
    conn_opts.context = client;
    conn_opts.ssl = &ssl_opts;
    conn_opts.username = "device";
    conn_opts.password = token_jwt.c_str();


    if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
        printf("Failed to start connect, return code %d\r\n", rc);
        std::ostringstream ss;
        ss << endl;
        ss << "\t" << "Failed to start connect, return code %d" << rc << endl;
        pLogger->error(ss);
        //exit(EXIT_FAILURE);

        return false;
    }


    return true ;

}


//****************************************************************************************//
#define FW_VERSION "FW VER 1.0.0 " __DATE__ " " __TIME__



int main(int argc, char* argv[])
{

    pLogger = Logger::getInstance();

    gpio_write(PORT_RELE_NVR, OFFSET_RELE_NVR, 0);
    gpio_write(PORT_RELE3, OFFSET_RELE3, 0);
    gpio_write(PORT_RELE_LUCI_REMOTE, OFFSET_RELE_LUCI_REMOTE, 0);

    gpio_write(PORT_LED, OFFSET_LED, 1);


    mqtt_connection();

    gpio_write(PORT_LED, OFFSET_LED, 1);
    usleep(50000);

    gpio_write(PORT_LED, OFFSET_LED, 0);
    usleep(50000);

    gpio_write(PORT_LED, OFFSET_LED, 1);
    usleep(50000);

    gpio_write(PORT_LED, OFFSET_LED, 0);
    usleep(50000);


    //********************************************************************************//

    printf("START JGUARDIAN 2p0");
    std::ostringstream ss;
    ss << endl;
    ss << "\t" << "Start JGuardian 2p0 " << FW_VERSION;
    pLogger->info(ss);

    //******************************MOTOPOMPA************************//

    std::string header_string_MP;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_MP_GET_MODBUS = curl_easy_init();
    if (curl_MP_GET_MODBUS) {
        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_URL, CURL_GETURI_MODBUS_MP);
        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_TIMEOUT_MS, 1000);


        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_WRITEDATA, &response_string_modbus_MP);
        curl_easy_setopt(curl_MP_GET_MODBUS, CURLOPT_HEADERDATA, &header_string_MP);
    }

    curl_MP_GET_RELE_STATUS = curl_easy_init();
    if (curl_MP_GET_RELE_STATUS) {
        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_URL, CURL_GETURI_RELE_MP);
        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_TIMEOUT_MS, 1000);


        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_WRITEDATA, &response_string_rele_MP);
        curl_easy_setopt(curl_MP_GET_RELE_STATUS, CURLOPT_HEADERDATA, &header_string_MP);
    }

    curl_MP_RESET_GPIO = curl_easy_init();
    if (curl_MP_RESET_GPIO) {
        curl_easy_setopt(curl_MP_RESET_GPIO, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_RESET_GPIO, CURLOPT_POSTFIELDS, RESET_GPIO);
    }

    curl_MP_SET_START_ON = curl_easy_init();
    if (curl_MP_SET_START_ON) {
        curl_easy_setopt(curl_MP_SET_START_ON, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_START_ON, CURLOPT_POSTFIELDS, SET_RELE1_ON);
    }

    curl_MP_SET_START_OFF = curl_easy_init();
    if (curl_MP_SET_START_OFF) {
        curl_easy_setopt(curl_MP_SET_START_OFF, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_START_OFF, CURLOPT_POSTFIELDS, SET_RELE1_OFF);
    }

    curl_MP_SET_INIBIZIONE_ON = curl_easy_init();
    if (curl_MP_SET_INIBIZIONE_ON) {
        curl_easy_setopt(curl_MP_SET_INIBIZIONE_ON, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_INIBIZIONE_ON, CURLOPT_POSTFIELDS, SET_RELE2_ON);
    }

    curl_MP_SET_INIBIZIONE_OFF = curl_easy_init();
    if (curl_MP_SET_INIBIZIONE_OFF) {
        curl_easy_setopt(curl_MP_SET_INIBIZIONE_OFF, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_INIBIZIONE_OFF, CURLOPT_POSTFIELDS, SET_RELE2_OFF);
    }

    curl_MP_SET_STOP_ON = curl_easy_init();
    if (curl_MP_SET_STOP_ON) {
        curl_easy_setopt(curl_MP_SET_STOP_ON, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_STOP_ON, CURLOPT_POSTFIELDS, SET_RELE3_ON);
    }

    curl_MP_SET_STOP_OFF = curl_easy_init();
    if (curl_MP_SET_STOP_OFF) {
        curl_easy_setopt(curl_MP_SET_STOP_OFF, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_STOP_OFF, CURLOPT_POSTFIELDS, SET_RELE3_OFF);
    }

    curl_MP_SET_RESET_ON = curl_easy_init();
    if (curl_MP_SET_RESET_ON) {
        curl_easy_setopt(curl_MP_SET_RESET_ON, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_RESET_ON, CURLOPT_POSTFIELDS, SET_RELE4_ON);
    }

    curl_MP_SET_RESET_OFF = curl_easy_init();
    if (curl_MP_SET_RESET_OFF) {
        curl_easy_setopt(curl_MP_SET_RESET_OFF, CURLOPT_URL, CURL_SETURI_MP);
        curl_easy_setopt(curl_MP_SET_RESET_OFF, CURLOPT_POSTFIELDS, SET_RELE4_OFF);
    }

    //******************************ELETTROPOMPA************************//


    std::string header_string_modbus_EP;

    curl_EP_GET_MODBUS = curl_easy_init();
    if (curl_EP_GET_MODBUS) {
        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_URL, CURL_GETURI_MODBUS_EP);
        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_TIMEOUT_MS, 1000);


        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_WRITEDATA, &response_string_modbus_EP);
        curl_easy_setopt(curl_EP_GET_MODBUS, CURLOPT_HEADERDATA, &header_string_modbus_EP);
    }

    std::string header_string_EP;

    curl_EP_GET_RELE_STATUS = curl_easy_init();
    if (curl_EP_GET_RELE_STATUS) {
        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_URL, CURL_GETURI_RELE_EP);
        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_TIMEOUT_MS, 1000);


        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_WRITEDATA, &response_string_rele_EP);
        curl_easy_setopt(curl_EP_GET_RELE_STATUS, CURLOPT_HEADERDATA, &header_string_EP);
    }

    curl_EP_RESET_GPIO = curl_easy_init();
    if (curl_EP_RESET_GPIO) {
        curl_easy_setopt(curl_EP_RESET_GPIO, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_RESET_GPIO, CURLOPT_POSTFIELDS, RESET_GPIO);
    }

    curl_EP_SET_START_ON = curl_easy_init();
    if (curl_EP_SET_START_ON) {
        curl_easy_setopt(curl_EP_SET_START_ON, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_START_ON, CURLOPT_POSTFIELDS, SET_RELE1_ON);
    }

    curl_EP_SET_START_OFF = curl_easy_init();
    if (curl_EP_SET_START_OFF) {
        curl_easy_setopt(curl_EP_SET_START_OFF, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_START_OFF, CURLOPT_POSTFIELDS, SET_RELE1_OFF);
    }

    curl_EP_SET_INIBIZIONE_ON = curl_easy_init();
    if (curl_EP_SET_INIBIZIONE_ON) {
        curl_easy_setopt(curl_EP_SET_INIBIZIONE_ON, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_INIBIZIONE_ON, CURLOPT_POSTFIELDS, SET_RELE2_ON);
    }

    curl_EP_SET_INIBIZIONE_OFF = curl_easy_init();
    if (curl_EP_SET_INIBIZIONE_OFF) {
        curl_easy_setopt(curl_EP_SET_INIBIZIONE_OFF, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_INIBIZIONE_OFF, CURLOPT_POSTFIELDS, SET_RELE2_OFF);
    }

    curl_EP_SET_STOP_ON = curl_easy_init();
    if (curl_EP_SET_STOP_ON) {
        curl_easy_setopt(curl_EP_SET_STOP_ON, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_STOP_ON, CURLOPT_POSTFIELDS, SET_RELE3_ON);
    }

    curl_EP_SET_STOP_OFF = curl_easy_init();
    if (curl_EP_SET_STOP_OFF) {
        curl_easy_setopt(curl_EP_SET_STOP_OFF, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_STOP_OFF, CURLOPT_POSTFIELDS, SET_RELE3_OFF);
    }

    curl_EP_SET_RESET_ON = curl_easy_init();
    if (curl_EP_SET_RESET_ON) {
        curl_easy_setopt(curl_EP_SET_RESET_ON, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_RESET_ON, CURLOPT_POSTFIELDS, SET_RELE4_ON);
    }

    curl_EP_SET_RESET_OFF = curl_easy_init();
    if (curl_EP_SET_RESET_OFF) {
        curl_easy_setopt(curl_EP_SET_RESET_OFF, CURLOPT_URL, CURL_SETURI_EP);
        curl_easy_setopt(curl_EP_SET_RESET_OFF, CURLOPT_POSTFIELDS, SET_RELE4_OFF);
    }


    //******************************JOKEY************************//

    std::string header_string_JOKEY;

    curl_JOKEY_GET_RELE_STATUS = curl_easy_init();
    if (curl_JOKEY_GET_RELE_STATUS) {
        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_URL, CURL_GETURI_RELE_JK);
        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_TIMEOUT_MS, 1000);


        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_WRITEDATA, &response_string_JOKEY);
        curl_easy_setopt(curl_JOKEY_GET_RELE_STATUS, CURLOPT_HEADERDATA, &header_string_JOKEY);
    }

    curl_JOKEY_RESET_GPIO = curl_easy_init();
    if (curl_JOKEY_RESET_GPIO) {
        curl_easy_setopt(curl_JOKEY_RESET_GPIO, CURLOPT_URL, CURL_SETURI_JK);
        curl_easy_setopt(curl_JOKEY_RESET_GPIO, CURLOPT_POSTFIELDS, RESET_GPIO);
    }

    curl_JOKEY_SET_START_ON = curl_easy_init();
    if (curl_JOKEY_SET_START_ON) {
        curl_easy_setopt(curl_JOKEY_SET_START_ON, CURLOPT_URL, CURL_SETURI_JK);
        curl_easy_setopt(curl_JOKEY_SET_START_ON, CURLOPT_POSTFIELDS, SET_RELE1_ON);
    }

    curl_JOKEY_SET_START_OFF = curl_easy_init();
    if (curl_JOKEY_SET_START_OFF) {
        curl_easy_setopt(curl_JOKEY_SET_START_OFF, CURLOPT_URL, CURL_SETURI_JK);
        curl_easy_setopt(curl_JOKEY_SET_START_OFF, CURLOPT_POSTFIELDS, SET_RELE1_OFF);
    }

    curl_JOKEY_SET_INIBIZIONE_ON = curl_easy_init();
    if (curl_JOKEY_SET_INIBIZIONE_ON) {
        curl_easy_setopt(curl_JOKEY_SET_INIBIZIONE_ON, CURLOPT_URL, CURL_SETURI_JK);
        curl_easy_setopt(curl_JOKEY_SET_INIBIZIONE_ON, CURLOPT_POSTFIELDS, SET_RELE2_ON);
    }

    curl_JOKEY_SET_INIBIZIONE_OFF = curl_easy_init();
    if (curl_JOKEY_SET_INIBIZIONE_OFF) {
        curl_easy_setopt(curl_JOKEY_SET_INIBIZIONE_OFF, CURLOPT_URL, CURL_SETURI_JK);
        curl_easy_setopt(curl_JOKEY_SET_INIBIZIONE_OFF, CURLOPT_POSTFIELDS, SET_RELE2_OFF);
    }

    //******************************SPRINKLER************************//

    std::string header_string_SPRINKLER1;

    curl_SPRINKLER1_GET_RELE_STATUS = curl_easy_init();
    if (curl_SPRINKLER1_GET_RELE_STATUS) {
        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_URL, CURL_GETURI_RELE_SP);
        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_TIMEOUT_MS, 1000);


        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_WRITEDATA, &response_string_SPRINKLER1);
        curl_easy_setopt(curl_SPRINKLER1_GET_RELE_STATUS, CURLOPT_HEADERDATA, &header_string_SPRINKLER1);
    }

    curl_SPRINKLER1_RESET_GPIO = curl_easy_init();
    if (curl_SPRINKLER1_RESET_GPIO) {
        curl_easy_setopt(curl_SPRINKLER1_RESET_GPIO, CURLOPT_URL, CURL_SETURI_SP);
        curl_easy_setopt(curl_SPRINKLER1_RESET_GPIO, CURLOPT_POSTFIELDS, RESET_GPIO);
    }

    curl_SPRINKLER1_SET_EV_ON = curl_easy_init();
    if (curl_SPRINKLER1_SET_EV_ON) {
        curl_easy_setopt(curl_SPRINKLER1_SET_EV_ON, CURLOPT_URL, CURL_SETURI_SP);
        curl_easy_setopt(curl_SPRINKLER1_SET_EV_ON, CURLOPT_POSTFIELDS, SET_RELE1_ON);
    }

    curl_SPRINKLER1_SET_EV_OFF = curl_easy_init();
    if (curl_SPRINKLER1_SET_EV_OFF) {
        curl_easy_setopt(curl_SPRINKLER1_SET_EV_OFF, CURLOPT_URL, CURL_SETURI_SP);
        curl_easy_setopt(curl_SPRINKLER1_SET_EV_OFF, CURLOPT_POSTFIELDS, SET_RELE1_OFF);
    }

    curl_SPRINKLER2_SET_EV_ON = curl_easy_init();
    if (curl_SPRINKLER2_SET_EV_ON) {
        curl_easy_setopt(curl_SPRINKLER2_SET_EV_ON, CURLOPT_URL, CURL_SETURI_SP);
        curl_easy_setopt(curl_SPRINKLER2_SET_EV_ON, CURLOPT_POSTFIELDS, SET_RELE2_ON);
    }

    curl_SPRINKLER2_SET_EV_OFF = curl_easy_init();
    if (curl_SPRINKLER2_SET_EV_OFF) {
        curl_easy_setopt(curl_SPRINKLER2_SET_EV_OFF, CURLOPT_URL, CURL_SETURI_SP);
        curl_easy_setopt(curl_SPRINKLER2_SET_EV_OFF, CURLOPT_POSTFIELDS, SET_RELE2_OFF);
    }


    curl_SPRINKLER3_SET_EV_ON = curl_easy_init();
    if (curl_SPRINKLER3_SET_EV_ON) {
        curl_easy_setopt(curl_SPRINKLER3_SET_EV_ON, CURLOPT_URL, CURL_SETURI_SP);
        curl_easy_setopt(curl_SPRINKLER3_SET_EV_ON, CURLOPT_POSTFIELDS, SET_RELE3_ON);
    }

    curl_SPRINKLER3_SET_EV_OFF = curl_easy_init();
    if (curl_SPRINKLER3_SET_EV_OFF) {
        curl_easy_setopt(curl_SPRINKLER3_SET_EV_OFF, CURLOPT_URL, CURL_SETURI_SP);
        curl_easy_setopt(curl_SPRINKLER3_SET_EV_OFF, CURLOPT_POSTFIELDS, SET_RELE3_OFF);
    }


    //********************** RESET RELE ***************************//
    send_curl_request(MOTOPOMPA_RELE,curl_MP_RESET_GPIO);
    send_curl_request(ELETTROPOMPA_RELE,curl_EP_RESET_GPIO);
    send_curl_request(JOKEY,curl_JOKEY_RESET_GPIO);
    send_curl_request(SPRINKLER,curl_SPRINKLER1_RESET_GPIO);

    sleep(3);

    //*************************************************************//

    char message_to_send[4000];// = (char*)malloc(sizeof(char) * payload_size);

    //	//****************************************************************//

    while(1)
    {
        send_curl_request(MOTOPOMPA_MB,curl_MP_GET_MODBUS);
        send_curl_request(MOTOPOMPA_RELE,curl_MP_GET_RELE_STATUS);

        send_curl_request(ELETTROPOMPA_MB,curl_EP_GET_MODBUS);
        send_curl_request(ELETTROPOMPA_RELE,curl_EP_GET_RELE_STATUS);

        send_curl_request(JOKEY,curl_JOKEY_GET_RELE_STATUS);

        send_curl_request(SPRINKLER,curl_SPRINKLER1_GET_RELE_STATUS);

        //*********************************************************//
        int index_reg = 0;

        //**************************************************************//
        //*************************** EP *******************************//
        //**************************************************************//

        uint16_t tab_reg_ep_16[5] = {0};
        int elettropompa_reg0[16] = {0};
        int elettropompa_reg1[16] = {0};
        int elettropompa_reg2 = 0;
        int elettropompa_reg3 = 0;
        int16_t elettropompa_reg4 = 0;
        int16_t elettropompa_reg5_1 = 0;
        int16_t elettropompa_reg5_2 = 0;

        std::vector<std::string> array_ep = split(response_string_modbus_EP,';');
        if(array_ep.size() > 1)
        {
            for(std::string var : array_ep)
            {
                if(!var.empty())
                {
                    tab_reg_ep_16[index_reg] = std::stoul(var,nullptr,0);
                    index_reg++;
                }
            }

            //**************** grub registri EP **********************//
            for(int ind = 0; ind < 16; ind++)
            {
                elettropompa_reg0[ind] = (int)(0x01 & (tab_reg_ep_16[0] >> ind));
                elettropompa_reg1[ind] = (int)(0x01 & (tab_reg_ep_16[1] >> ind));
            }
            elettropompa_reg2 = tab_reg_ep_16[2];
            elettropompa_reg3 = tab_reg_ep_16[3];
            elettropompa_reg4 = tab_reg_ep_16[4];
            elettropompa_reg5_1 = (int16_t)(tab_reg_ep_16[5] >> 8);
            elettropompa_reg5_2 = (int16_t)tab_reg_ep_16[5];
        }

        std::vector<std::string> array_ep_rele = split(response_string_rele_EP,',');

        if(array_ep_rele.size() == 4)
        {
            line_rele_start_ep_status = std::stoul(array_ep_rele[0],nullptr,0);
            line_rele_inib_ep_status = std::stoul(array_ep_rele[1],nullptr,0);
            line_rele_stop_ep_status = std::stoul(array_ep_rele[2],nullptr,0);
            line_rele_reset_ep_status = std::stoul(array_ep_rele[3],nullptr,0);
        }


        //**************************************************************//
        //*************************** MP *******************************//
        //**************************************************************//

        index_reg = 0;
        uint16_t tab_reg_mp_16[15] = {0};
        int motopompa_reg1[16] = {0};
        int motopompa_reg2[16] = {0};
        int motopompa_reg3[16] = {0};
        int motopompa_reg4 = 0;
        int motopompa_reg5 = 0;
        int motopompa_reg6 = 0;
        int motopompa_reg7 = 0;
        int motopompa_reg8 = 0;
        int motopompa_reg9 = 0;
        int motopompa_reg10 = 0;
        int motopompa_reg11 = 0;
        int motopompa_reg12 = 0;
        int motopompa_reg13 = {0};
        int motopompa_reg14_1 = {0};
        int motopompa_reg14_2 = {0};

        std::vector<std::string> array_mp = split(response_string_modbus_MP,';');

        if(array_mp.size() > 1)
        {

            for(std::string var : array_mp)
            {
                if(!var.empty())
                {
                    tab_reg_mp_16[index_reg] = std::stoul(var,nullptr,0);
                    index_reg++;
                }
            }

            //**************** grub registri MP **********************//
            for(int ind = 0; ind < 16;ind++)
            {
                motopompa_reg1[ind] = (int)(0x01 & (tab_reg_mp_16[1] >> ind));
                motopompa_reg2[ind] = (int)(0x01 & (tab_reg_mp_16[2] >> ind));
                motopompa_reg3[ind] = (int)(0x01 & (tab_reg_mp_16[3] >> ind));
                //motopompa_reg13[ind] = (int)(0x01 & (tab_reg_mp_16[13] >> ind));
                //motopompa_reg14[ind] = (int)(0x01 & (tab_reg_mp_16[14] >> ind));
            }

            motopompa_reg4 = tab_reg_mp_16[4];
            motopompa_reg5 = tab_reg_mp_16[5];
            motopompa_reg6 = tab_reg_mp_16[6];
            motopompa_reg7 = tab_reg_mp_16[7];
            motopompa_reg8 = tab_reg_mp_16[8];
            motopompa_reg9 = tab_reg_mp_16[9];
            motopompa_reg10 = tab_reg_mp_16[10];
            motopompa_reg11 = tab_reg_mp_16[11];
            motopompa_reg12 = tab_reg_mp_16[12];

            motopompa_reg13 = (uint8_t)(tab_reg_mp_16[13]);

            motopompa_reg14_1 = (int16_t)(tab_reg_mp_16[14] >> 8);
            motopompa_reg14_2 = (int16_t)tab_reg_mp_16[14];

        }


        std::vector<std::string> array_mp_rele = split(response_string_rele_MP,',');

        if(array_mp_rele.size() == 4)
        {
            line_rele_start_mp_status = std::stoul(array_mp_rele[0],nullptr,0);
            line_rele_inib_mp_status = std::stoul(array_mp_rele[1],nullptr,0);
            line_rele_stop_mp_status = std::stoul(array_mp_rele[2],nullptr,0);
            line_rele_reset_mp_status = std::stoul(array_mp_rele[3],nullptr,0);
        }


        //**************************************************************//
        //*************************** JK *******************************//
        //**************************************************************//

        std::vector<std::string> array_jk_rele = split(response_string_JOKEY,',');

        if(array_jk_rele.size() == 4)
        {
            line_rele_start_jk_status = std::stoul(array_jk_rele[0],nullptr,0);
            line_rele_inib_jk_status = std::stoul(array_jk_rele[1],nullptr,0);
        }


        //**************************************************************//
        //*************************** SP *******************************//
        //**************************************************************//

        std::vector<std::string> array_sp_rele = split(response_string_SPRINKLER1,',');

        if(array_sp_rele.size() == 4)
        {
            line_rele_start_sp1_status = std::stoul(array_sp_rele[0],nullptr,0);
            line_rele_start_sp2_status = std::stoul(array_sp_rele[1],nullptr,0);
            line_rele_start_sp3_status = std::stoul(array_sp_rele[2],nullptr,0);
            //line_rele_start_sp1_status = std::stoul(array_sp1_rele[0],nullptr,0);
        }

        //************************************************************************************//

        printf("\r\n MOTO_POMPA %s %s\r\n ELETTRO_POMPA %s %s\r\n JOKEY %s\r\n SPRINKLER1 %s\r\n",
               response_string_modbus_MP.c_str(),
               response_string_rele_MP.c_str(),
               response_string_modbus_EP.c_str(),
               response_string_rele_EP.c_str(),
               response_string_JOKEY.c_str(),
               response_string_SPRINKLER1.c_str()
               );


        int ad_value6_ch0=0;
        int ad_value13_ch0=0;
        int ad_value2_ch1=0;
        int ad_value6_ch1=0;

        read_ADvalue_row_ch0((char*)"in_voltage6_raw",&ad_value6_ch0);
        read_ADvalue_row_ch0((char*)"in_voltage13_raw",&ad_value13_ch0);
        read_ADvalue_row_ch1((char*)"in_voltage2_raw",&ad_value2_ch1);
        read_ADvalue_row_ch1((char*)"in_voltage6_raw",&ad_value6_ch1);





        sensore_pressione_b = (1000  * ad_value13_ch0) / SENSORE_PRESSIONE_A_2_20m;

        sensore_pressione_a = ( 1000 * ad_value2_ch1 ) /SENSORE_PRESSIONE_B_16BAR;

        //printf("\r\n ANALOG CHANNEL [%d][%d][%d][%d]\r\n",ad_value6_ch0,ad_value13_ch0,sensore_pressione_b,sensore_pressione_a);
        printf("\r\n ANALOG CHANNEL [%d][%d][%d][%d]\r\n",ad_value13_ch0,ad_value2_ch1,sensore_pressione_a,sensore_pressione_b);


        //        std::ostringstream ss;
        //        ss << "\t" << "MOTO_POMPA MODBUS" << response_string_modbus_MP;
        //        ss << "\t" << "MOTO_POMPA RELE" << response_string_rele_MP << endl;

        //        ss << "\t" << "ELETTRO_POMPA MODBUS" << response_string_modbus_EP;
        //        ss << "\t" << "ELETTRO_POMPA RELE" << response_string_rele_EP << endl;

        //        ss << "\t" << "JOKEY RELE" << response_string_JOKEY << endl;

        //        ss << "\t" << "SPRINKLER1 RELE" << response_string_SPRINKLER1 << endl;

        //        pLogger->info(ss);


        //****************************************************************************************************//

        MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

        gettimeofday(&JGuardian_param_istance.tp, NULL);

        json payload_msg;
        payload_msg["rt"] = true;
        payload_msg["u"] = DEVICE;
        payload_msg["ts"] = JGuardian_param_istance.tp.tv_sec;
        payload_msg["t"] = 30;
        payload_msg["m"] = {

                //************** MOTOPOMPA ***************//

        {{"m", "_1_1_0"}, {"v", motopompa_reg1[0]}},
        {{"m", "_1_1_1"}, {"v", motopompa_reg1[1]}},
        {{"m", "_1_1_2"}, {"v", motopompa_reg1[2]}},
        {{"m", "_1_1_3"}, {"v", motopompa_reg1[3]}},
        {{"m", "_1_1_4"}, {"v", motopompa_reg1[4]}},
        {{"m", "_1_1_5"}, {"v", motopompa_reg1[5]}},
        {{"m", "_1_1_6"}, {"v", motopompa_reg1[6]}},
        {{"m", "_1_1_7"}, {"v", motopompa_reg1[7]}},
        {{"m", "_1_1_8"}, {"v", motopompa_reg1[8]}},
        {{"m", "_1_1_9"}, {"v", motopompa_reg1[9]}},
        {{"m", "_1_1_10"}, {"v", motopompa_reg1[10]}},
        {{"m", "_1_1_11"}, {"v", motopompa_reg1[11]}},
        {{"m", "_1_1_12"}, {"v", motopompa_reg1[12]}},
        {{"m", "_1_1_13"}, {"v", motopompa_reg1[13]}},
        {{"m", "_1_1_14"}, {"v", motopompa_reg1[14]}},
        {{"m", "_1_1_15"}, {"v", motopompa_reg1[15]}},

        {{"m", "_1_2_0"}, {"v", motopompa_reg2[0]}},
        {{"m", "_1_2_1"}, {"v", motopompa_reg2[1]}},
        {{"m", "_1_2_2"}, {"v", motopompa_reg2[2]}},
        {{"m", "_1_2_3"}, {"v", motopompa_reg2[3]}},
        {{"m", "_1_2_4"}, {"v", motopompa_reg2[4]}},
        {{"m", "_1_2_5"}, {"v", motopompa_reg2[5]}},
        {{"m", "_1_2_6"}, {"v", motopompa_reg2[6]}},
        {{"m", "_1_2_7"}, {"v", motopompa_reg2[7]}},
        {{"m", "_1_2_8"}, {"v", motopompa_reg2[8]}},
        {{"m", "_1_2_9"}, {"v", motopompa_reg2[9]}},
        {{"m", "_1_2_10"}, {"v", motopompa_reg2[10]}},
        {{"m", "_1_2_11"}, {"v", motopompa_reg2[11]}},
        {{"m", "_1_2_12"}, {"v", motopompa_reg2[12]}},
        {{"m", "_1_2_13"}, {"v", motopompa_reg2[13]}},
        {{"m", "_1_2_14"}, {"v", motopompa_reg2[14]}},
        {{"m", "_1_2_15"}, {"v", motopompa_reg2[15]}},

        {{"m", "_1_3_0"}, {"v", motopompa_reg3[0]}},
        {{"m", "_1_3_1"}, {"v", motopompa_reg3[1]}},
        {{"m", "_1_3_2"}, {"v", motopompa_reg3[2]}},
        {{"m", "_1_3_3"}, {"v", motopompa_reg3[3]}},
        {{"m", "_1_3_4"}, {"v", motopompa_reg3[4]}},
        {{"m", "_1_3_5"}, {"v", motopompa_reg3[5]}},
        {{"m", "_1_3_6"}, {"v", motopompa_reg3[6]}},
        {{"m", "_1_3_7"}, {"v", motopompa_reg3[7]}},
        {{"m", "_1_3_8"}, {"v", motopompa_reg3[8]}},
        {{"m", "_1_3_9"}, {"v", motopompa_reg3[9]}},

        {{"m", "_1_3_10"}, {"v", motopompa_reg3[10]}},
        {{"m", "_1_3_11"}, {"v", motopompa_reg3[11]}},
        {{"m", "_1_3_12"}, {"v", motopompa_reg3[12]}},
        {{"m", "_1_3_13"}, {"v", motopompa_reg3[13]}},
        {{"m", "_1_3_14"}, {"v", motopompa_reg3[14]}},
        {{"m", "_1_3_15"}, {"v", motopompa_reg3[15]}},

        {{"m", "_1_4"}, {"v", motopompa_reg4}},

        {{"m", "_1_5"}, {"v", motopompa_reg5}},

        {{"m", "_1_6"}, {"v", motopompa_reg6}},

        {{"m", "_1_7"}, {"v", motopompa_reg7}},

        {{"m", "_1_8"}, {"v", motopompa_reg8}},

        {{"m", "_1_9"}, {"v", motopompa_reg9}},

        {{"m", "_1_10"}, {"v", motopompa_reg10}},

        {{"m", "_1_11"}, {"v", motopompa_reg11}},

        {{"m", "_1_12"}, {"v", motopompa_reg12}},

        {{"m", "_1_13"}, {"v", motopompa_reg13}},

        {{"m", "_1_14_1"}, {"v", motopompa_reg14_1}},

        {{"m", "_1_14_2"}, {"v", motopompa_reg14_2}},



        //************** ELETTROPOMPA ***************//

        {{"m", "_2_0_0"}, {"v", elettropompa_reg0[0]}},
        {{"m", "_2_0_1"}, {"v", elettropompa_reg0[1]}},
        {{"m", "_2_0_2"}, {"v", elettropompa_reg0[2]}},
        {{"m", "_2_0_3"}, {"v", elettropompa_reg0[3]}},
        {{"m", "_2_0_4"}, {"v", elettropompa_reg0[4]}},
        {{"m", "_2_0_5"}, {"v", elettropompa_reg0[5]}},
        {{"m", "_2_0_6"}, {"v", elettropompa_reg0[6]}},
        {{"m", "_2_0_7"}, {"v", elettropompa_reg0[7]}},
        {{"m", "_2_0_8"}, {"v", elettropompa_reg0[8]}},
        {{"m", "_2_0_9"}, {"v", elettropompa_reg0[9]}},
        {{"m", "_2_0_10"}, {"v", elettropompa_reg0[10]}},
        {{"m", "_2_0_11"}, {"v", elettropompa_reg0[11]}},
        {{"m", "_2_0_12"}, {"v", elettropompa_reg0[12]}},
        {{"m", "_2_0_13"}, {"v", elettropompa_reg0[13]}},
        {{"m", "_2_0_14"}, {"v", elettropompa_reg0[14]}},
        {{"m", "_2_0_15"}, {"v", elettropompa_reg0[15]}},

        {{"m", "_2_1_0"}, {"v", elettropompa_reg1[0]}},
        {{"m", "_2_1_1"}, {"v", elettropompa_reg1[1]}},
        {{"m", "_2_1_2"}, {"v", elettropompa_reg1[2]}},
        {{"m", "_2_1_3"}, {"v", elettropompa_reg1[3]}},
        {{"m", "_2_1_4"}, {"v", elettropompa_reg1[4]}},
        {{"m", "_2_1_5"}, {"v", elettropompa_reg1[5]}},
        {{"m", "_2_1_6"}, {"v", elettropompa_reg1[6]}},
        {{"m", "_2_1_7"}, {"v", elettropompa_reg1[7]}},
        {{"m", "_2_1_8"}, {"v", elettropompa_reg1[8]}},
        {{"m", "_2_1_9"}, {"v", elettropompa_reg1[9]}},
        {{"m", "_2_1_10"}, {"v", elettropompa_reg1[10]}},
        {{"m", "_2_1_11"}, {"v", elettropompa_reg1[11]}},
        {{"m", "_2_1_12"}, {"v", elettropompa_reg1[12]}},
        {{"m", "_2_1_13"}, {"v", elettropompa_reg1[13]}},
        {{"m", "_2_1_14"}, {"v", elettropompa_reg1[14]}},
        {{"m", "_2_1_15"}, {"v", elettropompa_reg1[15]}},

        {{"m", "_2_2"}, {"v", elettropompa_reg2}},

        {{"m", "_2_3"}, {"v", elettropompa_reg3}},

        {{"m", "_2_4"}, {"v", elettropompa_reg4}},

        {{"m", "_2_5_1"}, {"v", elettropompa_reg5_1}},

        {{"m", "_2_5_2"}, {"v", elettropompa_reg5_2}},

        //************************* STATO RELE ********************//

        {{"m", RELE_CAMERA_STATO}, {"v", line_rele_camera_status}},
        {{"m", RELE_LUCI_STATO}, {"v", line_rele_luci_status}},

        {{"m", RELE_START_EP_STATO}, {"v", line_rele_start_ep_status}},
        {{"m", RELE_INIB_EP_STATO}, {"v", line_rele_inib_ep_status}},
        {{"m", RELE_STOP_EP_STATO}, {"v", line_rele_stop_ep_status}},
        {{"m", RELE_RESET_EP_STATO}, {"v", line_rele_reset_ep_status}},

        {{"m", RELE_START_MP_STATO}, {"v", line_rele_start_mp_status}},
        {{"m", RELE_INIB_MP_STATO}, {"v", line_rele_inib_mp_status}},
        {{"m", RELE_STOP_MP_STATO}, {"v", line_rele_stop_mp_status}},
        {{"m", RELE_RESET_MP_STATO}, {"v", line_rele_reset_mp_status}},

        {{"m", RELE_START_JK_STATO}, {"v", line_rele_start_jk_status}},
        {{"m", RELE_INIB_JK_STATO}, {"v", line_rele_inib_jk_status}},

        {{"m", RELE_START_SP1_STATO}, {"v", line_rele_start_sp1_status}},
        {{"m", RELE_START_SP2_STATO}, {"v", line_rele_start_sp2_status}},
        {{"m", RELE_START_SP3_STATO}, {"v", line_rele_start_sp3_status}},
        //{{"m", RELE_START_SP4_STATO}, {"v", line_rele_start_sp4_status}},

        {{"m", LIVELLO_PRESSIONE1}, {"v", sensore_pressione_a}},
        {{"m", LIVELLO_PRESSIONE2}, {"v", sensore_pressione_b}}

    };


    int payload_size = strlen(payload_msg.dump().c_str());
    memset(message_to_send,0,4000);
    memcpy(message_to_send,payload_msg.dump().c_str(),payload_size);
    message_to_send[payload_size] = 0;

    //printf("\r\n %s \r\n", message_to_send); // @suppress("Method cannot be resolved")

    pubmsg.payload = (void*)message_to_send;//payload_char; // @suppress("Method cannot be resolved")
    pubmsg.payloadlen = payload_size;
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    deliveredtoken = 0;

    if((MQTTAsync_isConnected(client) == 1)&&(start_remote_test == true))
    {
        int rc;
        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        opts.onSuccess = onSend;
        opts.context = client;

        if ((rc = MQTTAsync_sendMessage(client, TOPIC_RT, &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
        {
            printf("Failed to start sendMessage, return code %d\n", rc);
            std::ostringstream ss;
            ss << endl;
            ss << "\t" << "Failed to start sendMessage, return code %d" << rc << endl;
            pLogger->error(ss);
        }

        sleep(1);//0.5s
    }
    else
    {
        sleep(10);
    }

    if(toggle)
    {
        gpio_write(PORT_LED, OFFSET_LED, 1);

        toggle = false;
    }
    else
    {
        gpio_write(PORT_LED, OFFSET_LED, 0);

        toggle = true;
    }



}

MQTTAsync_destroy(&client);

return false;

}

