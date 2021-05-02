/*
 * RtosTool.cpp
 *
 *  Created on: 1 maj 2021
 *      Author: Igor
 */

#include <RtosTool.h>

RtosTool::RtosTool() {
	// TODO Auto-generated constructor stub

}

template<class MsgClass>
void RtosTool::registerQueue(uint8_t queueSize) {

	QueuePools queuePools;
	const osPoolDef_t os_pool_defx = { queueSize, sizeof(MsgClass), NULL };
	queuePools.mpool = osPoolCreate(&os_pool_defx);

	const osMessageQDef_t os_messageQ_defx ={ queueSize, sizeof(MsgClass), NULL, NULL };
	queuePools.msgBox = osMessageCreate(&os_messageQ_defx, NULL);

	BaseRtosMsg::MsgType msgtype = MsgClass::getMsgType();

	queuesData.insert(std::pair<BaseRtosMsg::MsgType, QueuePools>(msgtype, queuePools));


}




template<typename MsgClass>
void RtosTool::insertData(MsgClass& data) {
	//check type and :
	// 1. create pointer to specific struct
	// 2. cast "data" to that pointer
	// 3. osMessagePut

//	  T_MEAS    *mptr;
//	   mptr = osPoolAlloc(mpool)
}
template<typename MsgClass>
MsgClass* RtosTool::pop(BaseRtosMsg::MsgType type) {
}
