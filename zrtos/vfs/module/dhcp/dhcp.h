/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_DHCP_H
#define ZRTOS_VFS_MODULE_DHCP_H
#ifdef __cplusplus
extern "C" {
#endif

#include <zrtos/types.h>

#define ZRTOS_VFS_MODULE_DHCP__FLAGSBROADCAST	0x8000

/* UDP port numbers for DHCP */
#define	ZRTOS_VFS_MODULE_DHCP__SERVER_PORT	67	/* from server to client */
#define ZRTOS_VFS_MODULE_DHCP__CLIENT_PORT	68	/* from client to server */

#define ZRTOS_VFS_MODULE_DHCP__HTYPE10MB		1
#define ZRTOS_VFS_MODULE_DHCP__HTYPE100MB		2

#define ZRTOS_VFS_MODULE_DHCP__HLENETHERNET	6
#define ZRTOS_VFS_MODULE_DHCP__HOPS		0
#define ZRTOS_VFS_MODULE_DHCP__SECS		0

#define ZRTOS_VFS_MODULE_DHCP__MAGIC_COOKIE		0x63825363
#define ZRTOS_VFS_MODULE_DHCP__MAX_DHCP_OPT	16

#define ZRTOS_VFS_MODULE_DHCP__HOST_NAME "WIZnet"
#define ZRTOS_VFS_MODULE_DHCP__DEFAULT_LEASE	(900) //default lease time in seconds

//DHCP state machine
typedef enum{
	 ZRTOS_VFS_MODULE_DHCP_STATE__START     = 0
	,ZRTOS_VFS_MODULE_DHCP_STATE__DISCOVER  = 1
	,ZRTOS_VFS_MODULE_DHCP_STATE__REQUEST   = 2
	,ZRTOS_VFS_MODULE_DHCP_STATE__LEASED    = 3
	,ZRTOS_VFS_MODULE_DHCP_STATE__REREQUEST = 4
	,ZRTOS_VFS_MODULE_DHCP_STATE__RELEASE   = 5
}zrtos_vfs_module_dhcp_state_t;

/* DHCP message OP code */
typedef enum{
	 ZRTOS_VFS_MODULE_DHCP_MESSAGE_OP__BOOTREQUEST = 1
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_OP__BOOTREPLY   = 2
}zrtos_vfs_module_dhcp_message_op_t;

/* DHCP message type */
typedef enum{
	 ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__DISCOVER = 1
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__OFFER    = 2
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__REQUEST  = 3
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__DECLINE  = 4
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__ACK      = 5
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__NAK      = 6
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__RELEASE  = 7
	,ZRTOS_VFS_MODULE_DHCP_MESSAGE_TYPE__INFORM   = 8
}zrtos_vfs_module_dhcp_message_type_t;

typedef enum{
	 ZRTOS_VFS_MODULE_DHCP_ERROR__NONE = 0
	,ZRTOS_VFS_MODULE_DHCP_ERROR__RENEW_FAIL    = 1
	,ZRTOS_VFS_MODULE_DHCP_ERROR__RENEW_OK  = 2
	,ZRTOS_VFS_MODULE_DHCP_ERROR__REBIND_FAIL  = 3
	,ZRTOS_VFS_MODULE_DHCP_ERROR__REBIND_OK      = 4
}zrtos_vfs_module_dhcp_error_t;
/*
#define DHCP_CHECK_NONE         (0)
#define DHCP_CHECK_RENEW_FAIL   (1)
#define DHCP_CHECK_RENEW_OK     (2)
#define DHCP_CHECK_REBIND_FAIL  (3)
#define DHCP_CHECK_REBIND_OK    (4)
*/
typedef enum{
	 ZRTOS_VFS_MODULE_DHCP_OPTION__padOption		=	0
	,ZRTOS_VFS_MODULE_DHCP_OPTION__subnetMask		=	1
	,ZRTOS_VFS_MODULE_DHCP_OPTION__timerOffset		=	2
	,ZRTOS_VFS_MODULE_DHCP_OPTION__routersOnSubnet		=	3
	,ZRTOS_VFS_MODULE_DHCP_OPTION__/* timeServer		=	4
	,ZRTOS_VFS_MODULE_DHCP_OPTION__nameServer		=	5,*/
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dns			=	6
	,ZRTOS_VFS_MODULE_DHCP_OPTION__/*logServer		=	7
	,ZRTOS_VFS_MODULE_DHCP_OPTION__cookieServer		=	8
	,ZRTOS_VFS_MODULE_DHCP_OPTION__lprServer		=	9
	,ZRTOS_VFS_MODULE_DHCP_OPTION__impressServer		=	10
	,ZRTOS_VFS_MODULE_DHCP_OPTION__resourceLocationServer	=	11,*/
	,ZRTOS_VFS_MODULE_DHCP_OPTION__hostName		=	12
	,ZRTOS_VFS_MODULE_DHCP_OPTION__/*bootFileSize		=	13
	,ZRTOS_VFS_MODULE_DHCP_OPTION__meritDumpFile		=	14,*/
	,ZRTOS_VFS_MODULE_DHCP_OPTION__domainName		=	15
	,ZRTOS_VFS_MODULE_DHCP_OPTION__/*swapServer		=	16
	,ZRTOS_VFS_MODULE_DHCP_OPTION__rootPath		=	17
	,ZRTOS_VFS_MODULE_DHCP_OPTION__extentionsPath		=	18
	,ZRTOS_VFS_MODULE_DHCP_OPTION__IPforwarding		=	19
	,ZRTOS_VFS_MODULE_DHCP_OPTION__nonLocalSourceRouting	=	20
	,ZRTOS_VFS_MODULE_DHCP_OPTION__policyFilter		=	21
	,ZRTOS_VFS_MODULE_DHCP_OPTION__maxDgramReasmSize	=	22
	,ZRTOS_VFS_MODULE_DHCP_OPTION__defaultIPTTL		=	23
	,ZRTOS_VFS_MODULE_DHCP_OPTION__pathMTUagingTimeout	=	24
	,ZRTOS_VFS_MODULE_DHCP_OPTION__pathMTUplateauTable	=	25
	,ZRTOS_VFS_MODULE_DHCP_OPTION__ifMTU			=	26
	,ZRTOS_VFS_MODULE_DHCP_OPTION__allSubnetsLocal		=	27
	,ZRTOS_VFS_MODULE_DHCP_OPTION__broadcastAddr		=	28
	,ZRTOS_VFS_MODULE_DHCP_OPTION__performMaskDiscovery	=	29
	,ZRTOS_VFS_MODULE_DHCP_OPTION__maskSupplier		=	30
	,ZRTOS_VFS_MODULE_DHCP_OPTION__performRouterDiscovery	=	31
	,ZRTOS_VFS_MODULE_DHCP_OPTION__routerSolicitationAddr	=	32
	,ZRTOS_VFS_MODULE_DHCP_OPTION__staticRoute		=	33
	,ZRTOS_VFS_MODULE_DHCP_OPTION__trailerEncapsulation	=	34
	,ZRTOS_VFS_MODULE_DHCP_OPTION__arpCacheTimeout		=	35
	,ZRTOS_VFS_MODULE_DHCP_OPTION__ethernetEncapsulation	=	36
	,ZRTOS_VFS_MODULE_DHCP_OPTION__tcpDefaultTTL		=	37
	,ZRTOS_VFS_MODULE_DHCP_OPTION__tcpKeepaliveInterval	=	38
	,ZRTOS_VFS_MODULE_DHCP_OPTION__tcpKeepaliveGarbage	=	39
	,ZRTOS_VFS_MODULE_DHCP_OPTION__nisDomainName		=	40
	,ZRTOS_VFS_MODULE_DHCP_OPTION__nisServers		=	41
	,ZRTOS_VFS_MODULE_DHCP_OPTION__ntpServers		=	42
	,ZRTOS_VFS_MODULE_DHCP_OPTION__vendorSpecificInfo	=	43
	,ZRTOS_VFS_MODULE_DHCP_OPTION__netBIOSnameServer	=	44
	,ZRTOS_VFS_MODULE_DHCP_OPTION__netBIOSdgramDistServer	=	45
	,ZRTOS_VFS_MODULE_DHCP_OPTION__netBIOSnodeType		=	46
	,ZRTOS_VFS_MODULE_DHCP_OPTION__netBIOSscope		=	47
	,ZRTOS_VFS_MODULE_DHCP_OPTION__xFontServer		=	48
	,ZRTOS_VFS_MODULE_DHCP_OPTION__xDisplayManager		=	49,*/
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpRequestedIPaddr	=	50
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpIPaddrLeaseTime	=	51
	,ZRTOS_VFS_MODULE_DHCP_OPTION__/*dhcpOptionOverload	=	52,*/
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpMessageType		=	53
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpServerIdentifier	=	54
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpParamRequest	=	55
	,ZRTOS_VFS_MODULE_DHCP_OPTION__/*dhcpMsg			=	56
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpMaxMsgSize		=	57,*/
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpT1value		=	58
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpT2value		=	59
	,ZRTOS_VFS_MODULE_DHCP_OPTION__/*dhcpClassIdentifier	=	60,*/
	,ZRTOS_VFS_MODULE_DHCP_OPTION__dhcpClientIdentifier	=	61
	,ZRTOS_VFS_MODULE_DHCP_OPTION__endOption		=	255
}zrtos_vfs_module_dhcp_option_t;

typedef struct /*_RIP_MSG_FIXED*/{
	uint8_t  op; 
	uint8_t  htype; 
	uint8_t  hlen;
	uint8_t  hops;
	uint32_t xid;
	uint16_t secs;
	uint16_t flags;
	uint8_t  ciaddr[4];
	uint8_t  yiaddr[4];
	uint8_t  siaddr[4];
	uint8_t  giaddr[4];
	uint8_t  chaddr[6];
}zrtos_vfs_module_dhcp_rip_message_t;

typedef struct{
	zrtos_vfs_module_network_ip_t ip;
	zrtos_vfs_module_network_subnet_mask_t subnet_mask;
	zrtos_vfs_module_network_ip_t gateway;
	zrtos_vfs_module_network_ip_t dns_server;
	zrtos_vfs_module_dhcp_state_t state;
}zrtos_vfs_module_dhcp_inode_t;

int DhcpClass::beginWithDHCP(uint8_t *mac, unsigned long timeout, unsigned long responseTimeout)
{
    _dhcpLeaseTime=0;
    _dhcpT1=0;
    _dhcpT2=0;
    _lastCheck=0;
    _timeout = timeout;
    _responseTimeout = responseTimeout;

    // zero out _dhcpMacAddr
    memset(_dhcpMacAddr, 0, 6); 
    reset_DHCP_lease();

    memcpy((void*)_dhcpMacAddr, (void*)mac, 6);
    _dhcp_state = STATE_DHCP_START;
    return request_DHCP_lease();
}

void DhcpClass::reset_DHCP_lease(){
    // zero out _dhcpSubnetMask, _dhcpGatewayIp, _dhcpLocalIp, _dhcpDhcpServerIp, _dhcpDnsServerIp
    memset(_dhcpLocalIp, 0, 20);
}

//return:0 on error, 1 if request is sent and response is received
int DhcpClass::request_DHCP_lease(){
    uint8_t messageType = 0;
  
    // Pick an initial transaction ID
    _dhcpTransactionId = random(1UL, 2000UL);
    _dhcpInitialTransactionId = _dhcpTransactionId;

    _dhcpUdpSocket.stop();
    if (_dhcpUdpSocket.begin(DHCP_CLIENT_PORT) == 0)
    {
      // Couldn't get a socket
      return 0;
    }
    
    presend_DHCP();
    
    int result = 0;
    
    unsigned long startTime = millis();
    
    while(_dhcp_state != STATE_DHCP_LEASED)
    {
        if(_dhcp_state == STATE_DHCP_START)
        {
            _dhcpTransactionId++;
            
            send_DHCP_MESSAGE(DHCP_DISCOVER, ((millis() - startTime) / 1000));
            _dhcp_state = STATE_DHCP_DISCOVER;
        }
        else if(_dhcp_state == STATE_DHCP_REREQUEST){
            _dhcpTransactionId++;
            send_DHCP_MESSAGE(DHCP_REQUEST, ((millis() - startTime)/1000));
            _dhcp_state = STATE_DHCP_REQUEST;
        }
        else if(_dhcp_state == STATE_DHCP_DISCOVER)
        {
            uint32_t respId;
            messageType = parseDHCPResponse(_responseTimeout, respId);
            if(messageType == DHCP_OFFER)
            {
                // We'll use the transaction ID that the offer came with,
                // rather than the one we were up to
                _dhcpTransactionId = respId;
                send_DHCP_MESSAGE(DHCP_REQUEST, ((millis() - startTime) / 1000));
                _dhcp_state = STATE_DHCP_REQUEST;
            }
        }
        else if(_dhcp_state == STATE_DHCP_REQUEST)
        {
            uint32_t respId;
            messageType = parseDHCPResponse(_responseTimeout, respId);
            if(messageType == DHCP_ACK)
            {
                _dhcp_state = STATE_DHCP_LEASED;
                result = 1;
                //use default lease time if we didn't get it
                if(_dhcpLeaseTime == 0){
                    _dhcpLeaseTime = DEFAULT_LEASE;
                }
                //calculate T1 & T2 if we didn't get it
                if(_dhcpT1 == 0){
                    //T1 should be 50% of _dhcpLeaseTime
                    _dhcpT1 = _dhcpLeaseTime >> 1;
                }
                if(_dhcpT2 == 0){
                    //T2 should be 87.5% (7/8ths) of _dhcpLeaseTime
                    _dhcpT2 = _dhcpT1 << 1;
                }
                _renewInSec = _dhcpT1;
                _rebindInSec = _dhcpT2;
            }
            else if(messageType == DHCP_NAK)
                _dhcp_state = STATE_DHCP_START;
        }
        
        if(messageType == 255)
        {
            messageType = 0;
            _dhcp_state = STATE_DHCP_START;
        }
        
        if(result != 1 && ((millis() - startTime) > _timeout))
            break;
    }
    
    // We're done with the socket now
    _dhcpUdpSocket.stop();
    _dhcpTransactionId++;

    return result;
}

void DhcpClass::presend_DHCP()
{
}

void DhcpClass::send_DHCP_MESSAGE(uint8_t messageType, uint16_t secondsElapsed)
{
    uint8_t buffer[32];
    memset(buffer, 0, 32);
    IPAddress dest_addr( 255, 255, 255, 255 ); // Broadcast address

    if (-1 == _dhcpUdpSocket.beginPacket(dest_addr, DHCP_SERVER_PORT))
    {
        // FIXME Need to return errors
        return;
    }

    buffer[0] = DHCP_BOOTREQUEST;   // op
    buffer[1] = DHCP_HTYPE10MB;     // htype
    buffer[2] = DHCP_HLENETHERNET;  // hlen
    buffer[3] = DHCP_HOPS;          // hops

    // xid
    unsigned long xid = htonl(_dhcpTransactionId);
    memcpy(buffer + 4, &(xid), 4);

    // 8, 9 - seconds elapsed
    buffer[8] = ((secondsElapsed & 0xff00) >> 8);
    buffer[9] = (secondsElapsed & 0x00ff);

    // flags
    unsigned short flags = htons(DHCP_FLAGSBROADCAST);
    memcpy(buffer + 10, &(flags), 2);

    // ciaddr: already zeroed
    // yiaddr: already zeroed
    // siaddr: already zeroed
    // giaddr: already zeroed

    //put data in W5100 transmit buffer
    _dhcpUdpSocket.write(buffer, 28);

    memset(buffer, 0, 32); // clear local buffer

    memcpy(buffer, _dhcpMacAddr, 6); // chaddr

    //put data in W5100 transmit buffer
    _dhcpUdpSocket.write(buffer, 16);

    memset(buffer, 0, 32); // clear local buffer

    // leave zeroed out for sname && file
    // put in W5100 transmit buffer x 6 (192 bytes)
  
    for(int i = 0; i < 6; i++) {
        _dhcpUdpSocket.write(buffer, 32);
    }
  
    // OPT - Magic Cookie
    buffer[0] = (uint8_t)((MAGIC_COOKIE >> 24)& 0xFF);
    buffer[1] = (uint8_t)((MAGIC_COOKIE >> 16)& 0xFF);
    buffer[2] = (uint8_t)((MAGIC_COOKIE >> 8)& 0xFF);
    buffer[3] = (uint8_t)(MAGIC_COOKIE& 0xFF);

    // OPT - message type
    buffer[4] = dhcpMessageType;
    buffer[5] = 0x01;
    buffer[6] = messageType; //DHCP_REQUEST;

    // OPT - client identifier
    buffer[7] = dhcpClientIdentifier;
    buffer[8] = 0x07;
    buffer[9] = 0x01;
    memcpy(buffer + 10, _dhcpMacAddr, 6);

    // OPT - host name
    buffer[16] = hostName;
    buffer[17] = strlen(HOST_NAME) + 6; // length of hostname + last 3 bytes of mac address
    strcpy((char*)&(buffer[18]), HOST_NAME);

    printByte((char*)&(buffer[24]), _dhcpMacAddr[3]);
    printByte((char*)&(buffer[26]), _dhcpMacAddr[4]);
    printByte((char*)&(buffer[28]), _dhcpMacAddr[5]);

    //put data in W5100 transmit buffer
    _dhcpUdpSocket.write(buffer, 30);

    if(messageType == DHCP_REQUEST)
    {
        buffer[0] = dhcpRequestedIPaddr;
        buffer[1] = 0x04;
        buffer[2] = _dhcpLocalIp[0];
        buffer[3] = _dhcpLocalIp[1];
        buffer[4] = _dhcpLocalIp[2];
        buffer[5] = _dhcpLocalIp[3];

        buffer[6] = dhcpServerIdentifier;
        buffer[7] = 0x04;
        buffer[8] = _dhcpDhcpServerIp[0];
        buffer[9] = _dhcpDhcpServerIp[1];
        buffer[10] = _dhcpDhcpServerIp[2];
        buffer[11] = _dhcpDhcpServerIp[3];

        //put data in W5100 transmit buffer
        _dhcpUdpSocket.write(buffer, 12);
    }
    
    buffer[0] = dhcpParamRequest;
    buffer[1] = 0x06;
    buffer[2] = subnetMask;
    buffer[3] = routersOnSubnet;
    buffer[4] = dns;
    buffer[5] = domainName;
    buffer[6] = dhcpT1value;
    buffer[7] = dhcpT2value;
    buffer[8] = endOption;
    
    //put data in W5100 transmit buffer
    _dhcpUdpSocket.write(buffer, 9);

    _dhcpUdpSocket.endPacket();
}

uint8_t DhcpClass::parseDHCPResponse(unsigned long responseTimeout, uint32_t& transactionId)
{
    uint8_t type = 0;
    uint8_t opt_len = 0;
     
    unsigned long startTime = millis();

    while(_dhcpUdpSocket.parsePacket() <= 0)
    {
        if((millis() - startTime) > responseTimeout)
        {
            return 255;
        }
        delay(50);
    }
    // start reading in the packet
    RIP_MSG_FIXED fixedMsg;
    _dhcpUdpSocket.read((uint8_t*)&fixedMsg, sizeof(RIP_MSG_FIXED));
  
    if(fixedMsg.op == DHCP_BOOTREPLY && _dhcpUdpSocket.remotePort() == DHCP_SERVER_PORT)
    {
        transactionId = ntohl(fixedMsg.xid);
        if(memcmp(fixedMsg.chaddr, _dhcpMacAddr, 6) != 0 || (transactionId < _dhcpInitialTransactionId) || (transactionId > _dhcpTransactionId))
        {
            // Need to read the rest of the packet here regardless
            _dhcpUdpSocket.flush();
            return 0;
        }

        memcpy(_dhcpLocalIp, fixedMsg.yiaddr, 4);

        // Skip to the option part
        // Doing this a byte at a time so we don't have to put a big buffer
        // on the stack (as we don't have lots of memory lying around)
        for (int i =0; i < (240 - (int)sizeof(RIP_MSG_FIXED)); i++)
        {
            _dhcpUdpSocket.read(); // we don't care about the returned byte
        }

        while (_dhcpUdpSocket.available() > 0) 
        {
            switch (_dhcpUdpSocket.read()) 
            {
                case endOption :
                    break;
                    
                case padOption :
                    break;
                
                case dhcpMessageType :
                    opt_len = _dhcpUdpSocket.read();
                    type = _dhcpUdpSocket.read();
                    break;
                
                case subnetMask :
                    opt_len = _dhcpUdpSocket.read();
                    _dhcpUdpSocket.read(_dhcpSubnetMask, 4);
                    break;
                
                case routersOnSubnet :
                    opt_len = _dhcpUdpSocket.read();
                    _dhcpUdpSocket.read(_dhcpGatewayIp, 4);
                    for (int i = 0; i < opt_len-4; i++)
                    {
                        _dhcpUdpSocket.read();
                    }
                    break;
                
                case dns :
                    opt_len = _dhcpUdpSocket.read();
                    _dhcpUdpSocket.read(_dhcpDnsServerIp, 4);
                    for (int i = 0; i < opt_len-4; i++)
                    {
                        _dhcpUdpSocket.read();
                    }
                    break;
                
                case dhcpServerIdentifier :
                    opt_len = _dhcpUdpSocket.read();
                    if( *((uint32_t*)_dhcpDhcpServerIp) == 0 || 
                        IPAddress(_dhcpDhcpServerIp) == _dhcpUdpSocket.remoteIP() )
                    {
                        _dhcpUdpSocket.read(_dhcpDhcpServerIp, sizeof(_dhcpDhcpServerIp));
                    }
                    else
                    {
                        // Skip over the rest of this option
                        while (opt_len--)
                        {
                            _dhcpUdpSocket.read();
                        }
                    }
                    break;

                case dhcpT1value : 
                    opt_len = _dhcpUdpSocket.read();
                    _dhcpUdpSocket.read((uint8_t*)&_dhcpT1, sizeof(_dhcpT1));
                    _dhcpT1 = ntohl(_dhcpT1);
                    break;

                case dhcpT2value : 
                    opt_len = _dhcpUdpSocket.read();
                    _dhcpUdpSocket.read((uint8_t*)&_dhcpT2, sizeof(_dhcpT2));
                    _dhcpT2 = ntohl(_dhcpT2);
                    break;

                case dhcpIPaddrLeaseTime :
                    opt_len = _dhcpUdpSocket.read();
                    _dhcpUdpSocket.read((uint8_t*)&_dhcpLeaseTime, sizeof(_dhcpLeaseTime));
                    _dhcpLeaseTime = ntohl(_dhcpLeaseTime);
                    _renewInSec = _dhcpLeaseTime;
                    break;

                default :
                    opt_len = _dhcpUdpSocket.read();
                    // Skip over the rest of this option
                    while (opt_len--)
                    {
                        _dhcpUdpSocket.read();
                    }
                    break;
            }
        }
    }

    // Need to skip to end of the packet regardless here
    _dhcpUdpSocket.flush();

    return type;
}


/*
    returns:
    0/DHCP_CHECK_NONE: nothing happened
    1/DHCP_CHECK_RENEW_FAIL: renew failed
    2/DHCP_CHECK_RENEW_OK: renew success
    3/DHCP_CHECK_REBIND_FAIL: rebind fail
    4/DHCP_CHECK_REBIND_OK: rebind success
*/
int DhcpClass::checkLease(){
    //this uses a signed / unsigned trick to deal with millis overflow
    unsigned long now = millis();
    signed long snow = (long)now;
    int rc=DHCP_CHECK_NONE;
    if (_lastCheck != 0){
        signed long factor;
        //calc how many ms past the timeout we are
        factor = snow - (long)_secTimeout;
        //if on or passed the timeout, reduce the counters
        if ( factor >= 0 ){
            //next timeout should be now plus 1000 ms minus parts of second in factor
            _secTimeout = snow + 1000 - factor % 1000;
            //how many seconds late are we, minimum 1
            factor = factor / 1000 +1;
            
            //reduce the counters by that mouch
            //if we can assume that the cycle time (factor) is fairly constant
            //and if the remainder is less than cycle time * 2 
            //do it early instead of late
            if(_renewInSec < factor*2 )
                _renewInSec = 0;
            else
                _renewInSec -= factor;
            
            if(_rebindInSec < factor*2 )
                _rebindInSec = 0;
            else
                _rebindInSec -= factor;
        }

        //if we have a lease but should renew, do it
        if (_dhcp_state == STATE_DHCP_LEASED && _renewInSec <=0){
            _dhcp_state = STATE_DHCP_REREQUEST;
            rc = 1 + request_DHCP_lease();
        }

        //if we have a lease or is renewing but should bind, do it
        if( (_dhcp_state == STATE_DHCP_LEASED || _dhcp_state == STATE_DHCP_START) && _rebindInSec <=0){
            //this should basically restart completely
            _dhcp_state = STATE_DHCP_START;
            reset_DHCP_lease();
            rc = 3 + request_DHCP_lease();
        }
    }
    else{
        _secTimeout = snow + 1000;
    }

    _lastCheck = now;
    return rc;
}

#ifdef __cplusplus
}
#endif
#endif
