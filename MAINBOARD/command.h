#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "MQTTAsync.h"
#include <iostream>
#include <curl/curl.h>
//#include <string>


//*******************************************************************************************//

#define CURL_GETURI_MODBUS_MP "http://10.100.0.66/get_modbus"
#define CURL_GETURI_RELE_MP "http://10.100.0.66/get_rele_status"
#define CURL_SETURI_MP "http://10.100.0.66/set_rele"

#define CURL_GETURI_MODBUS_EP "http://10.100.0.77/get_modbus"
#define CURL_GETURI_RELE_EP "http://10.100.0.77/get_rele_status"
#define CURL_SETURI_EP "http://10.100.0.77/set_rele"

#define CURL_GETURI_RELE_JK "http://10.100.0.88/get_rele_status"
#define CURL_SETURI_JK "http://10.100.0.88/set_rele"

#define CURL_GETURI_RELE_SP "http://10.100.0.91/get_rele_status"
#define CURL_SETURI_SP "http://10.100.0.91/set_rele"
//#define CURL_GETURI_RELE_SP2 "http://10.100.0.92/get_rele_status"
//#define CURL_SETURI_SP2 "http://10.100.0.92/set_rele"
//#define CURL_GETURI_RELE_SP3 "http://10.100.0.93/get_rele_status"
//#define CURL_SETURI_SP3 "http://10.100.0.93/set_rele"
//#define CURL_GETURI_RELE_SP4 "http://10.100.0.94/get_rele_status"
//#define CURL_SETURI_SP4 "http://10.100.0.94/set_rele"

#define RESET_GPIO "RELE[0][0]"
#define SET_RELE1_ON "RELE[1][1]"
#define SET_RELE1_OFF "RELE[1][0]"
#define SET_RELE2_ON "RELE[2][1]"
#define SET_RELE2_OFF "RELE[2][0]"
#define SET_RELE3_ON "RELE[3][1]"
#define SET_RELE3_OFF "RELE[3][0]"
#define SET_RELE4_ON "RELE[4][1]"
#define SET_RELE4_OFF "RELE[4][0]"





//***********************************************************************************************//

#ifdef OBISP

#define DEVICE "obisp"


#define ADDRESS_RT  "mqtt://mqtt.datasmart.cloud:1883"
#define CLIENTID    "projects/jguardian/locations/europe-west1/registries/j-guardian-v1/devices/Device-obisp"
#define TOPIC_RT    "/application/jguardian/devices/Device-obisp/events"
#define TOPIC_SUB   "/application/jguardian/devices/Device-obisp/commands/#"
#define QOS         1
#define TIMEOUT    200000L


#define REMOTE_START "{\"c\":\"start\"}"
#define REMOTE_STOP "{\"c\":\"stop\"}"

#define REMOTE_RELE_CAMERA_ON "{\"c\":\"2\",\"m\":\"obisp_rele_camera\",\"v\":\"1\"}"
#define REMOTE_RELE_CAMERA_OFF "{\"c\":\"2\",\"m\":\"obisp_rele_camera\",\"v\":\"0\"}"
#define REMOTE_RELE_LUCI_ON "{\"c\":\"2\",\"m\":\"obisp_rele_luci\",\"v\":\"1\"}"
#define REMOTE_RELE_LUCI_OFF "{\"c\":\"2\",\"m\":\"obisp_rele_luci\",\"v\":\"0\"}"

#define REMOTE_START_EP "{\"c\":\"2\",\"m\":\"obisp_start_ep\",\"v\":\"1\"}"
#define REMOTE_INIB_EP_ON "{\"c\":\"2\",\"m\":\"obisp_inib_ep\",\"v\":\"1\"}"
#define REMOTE_INIB_EP_OFF "{\"c\":\"2\",\"m\":\"obisp_inib_ep\",\"v\":\"0\"}"
#define REMOTE_STOP_EP "{\"c\":\"2\",\"m\":\"obisp_stop_ep\",\"v\":\"1\"}"
#define REMOTE_RESET_EP "{\"c\":\"2\",\"m\":\"obisp_reset_ep\",\"v\":\"1\"}"

#define REMOTE_START_MP "{\"c\":\"2\",\"m\":\"obisp_start_mp\",\"v\":\"1\"}"
#define REMOTE_INIB_MP_ON "{\"c\":\"2\",\"m\":\"obisp_inib_mp\",\"v\":\"1\"}"
#define REMOTE_INIB_MP_OFF "{\"c\":\"2\",\"m\":\"obisp_inib_mp\",\"v\":\"0\"}"
#define REMOTE_STOP_MP "{\"c\":\"2\",\"m\":\"obisp_stop_mp\",\"v\":\"1\"}"
#define REMOTE_RESET_MP "{\"c\":\"2\",\"m\":\"obisp_reset_mp\",\"v\":\"1\"}"

#define REMOTE_START_JK "{\"c\":\"2\",\"m\":\"obisp_start_jk\",\"v\":\"1\"}"
#define REMOTE_STOP_JK "{\"c\":\"2\",\"m\":\"obisp_start_jk\",\"v\":\"0\"}"
#define REMOTE_INIB_JK_ON "{\"c\":\"2\",\"m\":\"obisp_inib_jk\",\"v\":\"1\"}"
#define REMOTE_INIB_JK_OFF "{\"c\":\"2\",\"m\":\"obisp_inib_jk\",\"v\":\"0\"}"

#define REMOTE_START_SP1 "{\"c\":\"2\",\"m\":\"obisp_ev_spk1\",\"v\":\"1\"}"
#define REMOTE_STOP_SP1 "{\"c\":\"2\",\"m\":\"obisp_ev_spk1\",\"v\":\"0\"}"

#define REMOTE_START_SP2 "{\"c\":\"2\",\"m\":\"obisp_ev_spk2\",\"v\":\"1\"}"
#define REMOTE_STOP_SP2 "{\"c\":\"2\",\"m\":\"obisp_ev_spk2\",\"v\":\"0\"}"

#define REMOTE_START_SP3 "{\"c\":\"2\",\"m\":\"obisp_ev_spk3\",\"v\":\"1\"}"
#define REMOTE_STOP_SP3 "{\"c\":\"2\",\"m\":\"obisp_ev_spk3\",\"v\":\"0\"}"

#define REMOTE_START_SP4 "{\"c\":\"2\",\"m\":\"obisp_ev_spk4\",\"v\":\"1\"}"
#define REMOTE_STOP_SP4 "{\"c\":\"2\",\"m\":\"obisp_ev_spk4\",\"v\":\"0\"}"


//********************************STATI RELE*******************************************//

#define RELE_CAMERA_STATO "obisp_rele_camera"
#define RELE_LUCI_STATO "obisp_rele_luci"

#define RELE_START_EP_STATO "obisp_start_ep"
#define RELE_STOP_EP_STATO "obisp_stop_ep"
#define RELE_INIB_EP_STATO "obisp_inib_ep"
#define RELE_RESET_EP_STATO "obisp_reset_ep"

#define RELE_START_MP_STATO "obisp_start_mp"
#define RELE_STOP_MP_STATO "obisp_stop_mp"
#define RELE_INIB_MP_STATO "obisp_inib_mp"
#define RELE_RESET_MP_STATO "obisp_reset_mp"

#define RELE_START_JK_STATO "obisp_start_jk"
#define RELE_INIB_JK_STATO "obisp_inib_jk"

#define RELE_START_SP1_STATO "obisp_ev_spk1"
#define RELE_START_SP2_STATO "obisp_ev_spk2"
#define RELE_START_SP3_STATO "obisp_ev_spk3"
#define RELE_START_SP4_STATO "obisp_ev_spk4"


#define LIVELLO_PRESSIONE1 "obisp_pressione2"
#define LIVELLO_PRESSIONE2 "obisp_livello"

//************************************************************************************************//

#endif


#ifdef DEV3

#define DEVICE "testdev3"


#define ADDRESS_RT  "mqtt://mqtt.datasmart.cloud:1883"
#define CLIENTID    "projects/jguardian/locations/europe-west1/registries/j-guardian-v1/devices/Device-testdev3"
#define TOPIC_RT    "/application/jguardian/devices/Device-testdev3/events"
#define TOPIC_SUB   "/application/jguardian/devices/Device-testdev3/commands/#"
#define QOS         1
#define TIMEOUT    200000L


#define REMOTE_START "{\"c\":\"start\"}"
#define REMOTE_STOP "{\"c\":\"stop\"}"

#define REMOTE_RELE_CAMERA_ON "{\"c\":\"2\",\"m\":\"testdev3_rele_camera\",\"v\":\"1\"}"
#define REMOTE_RELE_CAMERA_OFF "{\"c\":\"2\",\"m\":\"testdev3_rele_camera\",\"v\":\"0\"}"
#define REMOTE_RELE_LUCI_ON "{\"c\":\"2\",\"m\":\"testdev3_rele_luci\",\"v\":\"1\"}"
#define REMOTE_RELE_LUCI_OFF "{\"c\":\"2\",\"m\":\"testdev3_rele_luci\",\"v\":\"0\"}"

#define REMOTE_START_EP "{\"c\":\"2\",\"m\":\"testdev3_start_ep\",\"v\":\"1\"}"
#define REMOTE_INIB_EP_ON "{\"c\":\"2\",\"m\":\"testdev3_inib_ep\",\"v\":\"1\"}"
#define REMOTE_INIB_EP_OFF "{\"c\":\"2\",\"m\":\"testdev3_inib_ep\",\"v\":\"0\"}"
#define REMOTE_STOP_EP "{\"c\":\"2\",\"m\":\"testdev3_stop_ep\",\"v\":\"1\"}"
#define REMOTE_RESET_EP "{\"c\":\"2\",\"m\":\"testdev3_reset_ep\",\"v\":\"1\"}"

#define REMOTE_START_MP "{\"c\":\"2\",\"m\":\"testdev3_start_mp\",\"v\":\"1\"}"
#define REMOTE_INIB_MP_ON "{\"c\":\"2\",\"m\":\"testdev3_inib_mp\",\"v\":\"1\"}"
#define REMOTE_INIB_MP_OFF "{\"c\":\"2\",\"m\":\"testdev3_inib_mp\",\"v\":\"0\"}"
#define REMOTE_STOP_MP "{\"c\":\"2\",\"m\":\"testdev3_stop_mp\",\"v\":\"1\"}"
#define REMOTE_RESET_MP "{\"c\":\"2\",\"m\":\"testdev3_reset_mp\",\"v\":\"1\"}"

#define REMOTE_START_JK "{\"c\":\"2\",\"m\":\"testdev3_start_jk\",\"v\":\"1\"}"
#define REMOTE_STOP_JK "{\"c\":\"2\",\"m\":\"testdev3_start_jk\",\"v\":\"0\"}"
#define REMOTE_INIB_JK_ON "{\"c\":\"2\",\"m\":\"testdev3_inib_jk\",\"v\":\"1\"}"
#define REMOTE_INIB_JK_OFF "{\"c\":\"2\",\"m\":\"testdev3_inib_jk\",\"v\":\"0\"}"

#define REMOTE_START_SP "{\"c\":\"2\",\"m\":\"testdev3_ev_spk\",\"v\":\"1\"}"
#define REMOTE_STOP_SP "{\"c\":\"2\",\"m\":\"testdev3_ev_spk\",\"v\":\"0\"}"


//********************************STATI RELE*******************************************//

#define RELE_CAMERA_STATO "testdev3_rele_camera"
#define RELE_LUCI_STATO "testdev3_rele_luci"

#define RELE_START_EP_STATO "testdev3_start_ep"
#define RELE_STOP_EP_STATO "testdev3_stop_ep"
#define RELE_INIB_EP_STATO "testdev3_inib_ep"
#define RELE_RESET_EP_STATO "testdev3_reset_ep"

#define RELE_START_MP_STATO "testdev3_start_mp"
#define RELE_STOP_MP_STATO "testdev3_stop_mp"
#define RELE_INIB_MP_STATO "testdev3_inib_mp"
#define RELE_RESET_MP_STATO "testdev3_reset_mp"

#define RELE_START_JK_STATO "testdev3_start_jk"
#define RELE_INIB_JK_STATO "testdev3_inib_jk"

#define RELE_START_SP_STATO "testdev3_ev_spk"


#define LIVELLO_PRESSIONE1 "testdev3_pressione2"
#define LIVELLO_PRESSIONE2 "testdev3_livello"

//************************************************************************************************//

#endif

#ifdef DEV4

#define DEVICE "testdev4"


#define ADDRESS_RT  "mqtt://mqtt.datasmart.cloud:1883"
#define CLIENTID    "projects/jguardian/locations/europe-west1/registries/j-guardian-v1/devices/Device-testdev4"
#define TOPIC_RT    "/application/jguardian/devices/Device-testdev4/events"
#define TOPIC_SUB   "/application/jguardian/devices/Device-testdev4/commands/#"
#define QOS         1
#define TIMEOUT    200000L


#define REMOTE_START "{\"c\":\"start\"}"
#define REMOTE_STOP "{\"c\":\"stop\"}"

#define REMOTE_RELE_CAMERA_ON "{\"c\":\"2\",\"m\":\"testdev4_rele_camera\",\"v\":\"1\"}"
#define REMOTE_RELE_CAMERA_OFF "{\"c\":\"2\",\"m\":\"testdev4_rele_camera\",\"v\":\"0\"}"
#define REMOTE_RELE_LUCI_ON "{\"c\":\"2\",\"m\":\"testdev4_rele_luci\",\"v\":\"1\"}"
#define REMOTE_RELE_LUCI_OFF "{\"c\":\"2\",\"m\":\"testdev4_rele_luci\",\"v\":\"0\"}"

#define REMOTE_START_EP "{\"c\":\"2\",\"m\":\"testdev4_start_ep\",\"v\":\"1\"}"
#define REMOTE_INIB_EP_ON "{\"c\":\"2\",\"m\":\"testdev4_inib_ep\",\"v\":\"1\"}"
#define REMOTE_INIB_EP_OFF "{\"c\":\"2\",\"m\":\"testdev4_inib_ep\",\"v\":\"0\"}"
#define REMOTE_STOP_EP "{\"c\":\"2\",\"m\":\"testdev4_stop_ep\",\"v\":\"1\"}"
#define REMOTE_RESET_EP "{\"c\":\"2\",\"m\":\"testdev4_reset_ep\",\"v\":\"1\"}"

#define REMOTE_START_MP "{\"c\":\"2\",\"m\":\"testdev4_start_mp\",\"v\":\"1\"}"
#define REMOTE_INIB_MP_ON "{\"c\":\"2\",\"m\":\"testdev4_inib_mp\",\"v\":\"1\"}"
#define REMOTE_INIB_MP_OFF "{\"c\":\"2\",\"m\":\"testdev4_inib_mp\",\"v\":\"0\"}"
#define REMOTE_STOP_MP "{\"c\":\"2\",\"m\":\"testdev4_stop_mp\",\"v\":\"1\"}"
#define REMOTE_RESET_MP "{\"c\":\"2\",\"m\":\"testdev4_reset_mp\",\"v\":\"1\"}"

#define REMOTE_START_JK "{\"c\":\"2\",\"m\":\"testdev4_start_jk\",\"v\":\"1\"}"
#define REMOTE_STOP_JK "{\"c\":\"2\",\"m\":\"testdev4_start_jk\",\"v\":\"0\"}"
#define REMOTE_INIB_JK_ON "{\"c\":\"2\",\"m\":\"testdev4_inib_jk\",\"v\":\"1\"}"
#define REMOTE_INIB_JK_OFF "{\"c\":\"2\",\"m\":\"testdev4_inib_jk\",\"v\":\"0\"}"

#define REMOTE_START_SP1 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk1\",\"v\":\"1\"}"
#define REMOTE_STOP_SP1 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk1\",\"v\":\"0\"}"

#define REMOTE_START_SP2 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk2\",\"v\":\"1\"}"
#define REMOTE_STOP_SP2 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk2\",\"v\":\"0\"}"

#define REMOTE_START_SP3 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk3\",\"v\":\"1\"}"
#define REMOTE_STOP_SP3 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk3\",\"v\":\"0\"}"

#define REMOTE_START_SP4 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk4\",\"v\":\"1\"}"
#define REMOTE_STOP_SP4 "{\"c\":\"2\",\"m\":\"testdev4_ev_spk4\",\"v\":\"0\"}"


//********************************STATI RELE*******************************************//

#define RELE_CAMERA_STATO "testdev4_rele_camera"
#define RELE_LUCI_STATO "testdev4_rele_luci"

#define RELE_START_EP_STATO "testdev4_start_ep"
#define RELE_STOP_EP_STATO "testdev4_stop_ep"
#define RELE_INIB_EP_STATO "testdev4_inib_ep"
#define RELE_RESET_EP_STATO "testdev4_reset_ep"

#define RELE_START_MP_STATO "testdev4_start_mp"
#define RELE_STOP_MP_STATO "testdev4_stop_mp"
#define RELE_INIB_MP_STATO "testdev4_inib_mp"
#define RELE_RESET_MP_STATO "testdev4_reset_mp"

#define RELE_START_JK_STATO "testdev4_start_jk"
#define RELE_INIB_JK_STATO "testdev4_inib_jk"

#define RELE_START_SP1_STATO "testdev4_ev_spk1"
#define RELE_START_SP2_STATO "testdev4_ev_spk2"
#define RELE_START_SP3_STATO "testdev4_ev_spk3"
#define RELE_START_SP4_STATO "testdev4_ev_spk4"


#define LIVELLO_PRESSIONE1 "testdev4_pressione2"
#define LIVELLO_PRESSIONE2 "testdev4_livello"

#endif
//************************************************************************************************//







#endif // COMMAND_H
