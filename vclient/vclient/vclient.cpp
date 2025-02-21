/*
* vclient.cpp
*
*  Created on: Feb 17, 2017
*      Author: NI
*/

#ifdef _WIN32
#include "stdafx.h"
#endif

#include "RDBHandler.hh"
#include "vclient.h"
//include <stdbool.h>
#include <stdio.h>
#include <string.h>




using namespace Framework;

void parseRDBMessage(RDB_MSG_t* msg, bool & isImage);
void parseRDBMessageEntry(const double & simTime, const unsigned int & simFrame, RDB_MSG_ENTRY_HDR_t* entryHdr);
void handleRDBitem(const double & simTime, const unsigned int & simFrame, RDB_OBJECT_STATE_t & item, bool isExtended);
void handleRDBitem(const double & simTime, const unsigned int & simFrame, RDB_IMAGE_t & item);
//void sendTrigger( int & sendSocket, const double & simTime, const unsigned int & simFrame );





bool							isImage = false;
double							simTime;
int								simFrame;

/*ID = 34 #########################################################*/
RDB_TRAJECTORY_t				*ReceiveTrajectoryArray;
std::vector<int>				ReceiveTrajectoryIDs;
std::vector<std::vector<RDB_POINT_t>> ReceiveTrajectoryPoints;
int								ReceiveTrajectoryNoElements;
/*ID = 6 ##########################################################*/                      
RDB_LANE_INFO_t					*ReceiveLaneInfoArray;	
std::vector<int>				ReceiveLaneInfoIDs;
int								ReceiveLaneInfoNoElements;
/*ID = 10 ##########################################################*/
RDB_VEHICLE_SYSTEMS_t			*ReceiveVehicleSystemsArray;
std::vector<int>				ReceiveVehicleSystemsIDs;
int								ReceiveVehicleSystemsNoElements;
/*ID = 11 ##########################################################*/
RDB_VEHICLE_SETUP_t				*ReceiveVehicleSetupArray;
std::vector<int>				ReceiveVehicleSetupIDs;
int								ReceiveVehicleSetupNoElements;
/*ID = 16 ##########################################################*/
RDB_SENSOR_STATE_t				*ReceiveSensorStateArray;
std::vector<int>				ReceiveSensorStateIDs;
int								ReceiveSensorStateNoElements;
/*ID = 17 ##########################################################*/
RDB_SENSOR_OBJECT_t				*ReceiveSensorObjectArray;
std::vector<int>				ReceiveSensorObjectIDs;
int								ReceiveSensorObjectNoElements;
/*ID = 5 ##########################################################*/
RDB_ROAD_POS_t					*ReceiveRoadPosArray;
std::vector<int>				ReceiveRoadPosIDs;
int								ReceiveRoadPosNoElements;
/*##########################################################*/
RDB_ROAD_STATE_t				*ReceiveRoadStateArray;
std::vector<int>				ReceiveRoadStateIDs;
int								ReceiveRoadStateNoElements;
/*##########################################################*/
RDB_OBJECT_STATE_t				*ReceiveObjectStateArray;
std::vector<int>				ReceiveObjectStateIDs;
int								ReceiveObjectStateNoElements;
/*##########################################################*/
RDB_WHEEL_t						*ReceiveWheelArray;
std::vector<int>				ReceiveWheelIDs;
std::vector<int>				ReceivePlayerWheelIDs;
int								ReceiveWheelNoElements;
/*##########################################################*/
RDB_ENGINE_t					*ReceiveEngineArray;
std::vector<int>				ReceiveEngineIDs;
int								ReceiveEngineNoElements;
/*##########################################################*/
RDB_DRIVER_PERCEPTION_t			*ReceiveDriverPerceptionArray;
std::vector<int>				ReceiveDriverPerceptionIDs;
int								ReceiveDriverPerceptionNoElements;
/*##########################################################*/
RDB_DRIVER_CTRL_t				*ReceiveDriverCtrlArray;
std::vector<int>				ReceiveDriverCtrlIDs;
int								ReceiveDriverCtrlNoElements;
/*##########################################################*/
RDB_OBJECT_STATE_t				*SendObjectStateArray;
int								*SendObjectStateIDs;
int								SendObjectStateNoElements;
/*##########################################################*/
RDB_DRIVER_CTRL_t				*SendDriverCtrlArray;
int								*SendDriverCtrlIDs;
int								SendDriverCtrlNoElements;
/*##########################################################*/
RDB_ENGINE_t					*SendEngineArray;
int								*SendEngineIDs;
int								SendEngineNoElements;
/*##########################################################*/
RDB_VEHICLE_SYSTEMS_t			*SendVehicleSystemsArray;
int								*SendVehicleSystemsIDs;
int								SendVehicleSystemsNoElements;
/*##########################################################*/
RDB_VEHICLE_SETUP_t				*SendVehicleSetupArray;
int								*SendVehicleSetupIDs;
int								SendVehicleSetupNoElements;
/*##########################################################*/
RDB_WHEEL_t						*SendWheelArray;
int								*SendWheelIDs;
int								SendWheelNoElements;
/*##########################################################*/
RDB_DRIVETRAIN_t				*SendDrivetrainArray;
int								*SendDrivetrainIDs;
int								SendDrivetrainNoElements;
/*##########################################################*/
RDB_LIGHT_SOURCE_t				*SendLigthSourceArray;
int								*SendLightSourcelIDs;
int								SendLightSourceNoElements;
/*##########################################################*/
RDB_SYNC_t						*SendSyncArray;
int								*SendSyncIDs;
int								SendSyncNoElements;
/*##########################################################*/
RDB_TRIGGER_t					*SendTriggerArray;
int								*SendTriggerIDs;
int								SendTriggerNoElements;
/*##########################################################*/
RDB_TRAFFIC_LIGHT_t				*SendTrafficLigthArray;
int								*SendTrafficLigthIDs;
int								SendTrafficLightNoElements;




Framework::RDBHandler myHandler;



void InitReceiveRDB(int pkID, const int noElements, int IDs[], int WheelIDs[])
{
	switch (pkID)
	{
	
	case 5:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveRoadPosIDs.push_back(IDs[i]);
		}
		ReceiveRoadPosNoElements = noElements;
		ReceiveRoadPosArray = (RDB_ROAD_POS_t*)malloc(sizeof(RDB_ROAD_POS_t)*noElements);
		break;

	case 6:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveLaneInfoIDs.push_back(IDs[i]);
		}
		ReceiveLaneInfoNoElements = noElements;
		ReceiveLaneInfoArray = (RDB_LANE_INFO_t*)malloc(sizeof(RDB_LANE_INFO_t)*noElements);
		break;
		
	case 9:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveObjectStateIDs.push_back(IDs[i]);
		}	
		ReceiveObjectStateNoElements = noElements;
		ReceiveObjectStateArray = (RDB_OBJECT_STATE_t*)malloc(sizeof(RDB_OBJECT_STATE_t)*noElements);
		break;

	case 10:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveVehicleSystemsIDs.push_back(IDs[i]);
		}
		ReceiveVehicleSystemsNoElements = noElements;
		ReceiveVehicleSystemsArray = (RDB_VEHICLE_SYSTEMS_t*)malloc(sizeof(RDB_VEHICLE_SYSTEMS_t)*noElements);
		break;

	case 11:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveVehicleSetupIDs.push_back(IDs[i]);
		}
		ReceiveVehicleSetupNoElements = noElements;
		ReceiveVehicleSetupArray = (RDB_VEHICLE_SETUP_t*)malloc(sizeof(RDB_VEHICLE_SETUP_t)*noElements);
		break;

	case 12:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveEngineIDs.push_back(IDs[i]);
		}
		ReceiveEngineNoElements = noElements;
		ReceiveEngineArray = (RDB_ENGINE_t*)malloc(sizeof(RDB_ENGINE_t)*noElements);
		break;

	case 14:
		for (int i = 0; i < noElements; i++)
		{
			ReceivePlayerWheelIDs.push_back(IDs[i]);
			ReceiveWheelIDs.push_back(WheelIDs[i]);
		}
		ReceiveWheelNoElements = noElements;
		ReceiveWheelArray = (RDB_WHEEL_t*)malloc(sizeof(RDB_WHEEL_t)*noElements);
		break;
		
	case 16:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveSensorStateIDs.push_back(IDs[i]);
		}
		ReceiveSensorStateNoElements = noElements;
		ReceiveSensorStateArray = (RDB_SENSOR_STATE_t*)malloc(sizeof(RDB_SENSOR_STATE_t)*noElements);
		break;

	case 17:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveSensorObjectIDs.push_back(IDs[i]);
		}
		ReceiveSensorObjectNoElements = noElements;
		ReceiveSensorObjectArray = (RDB_SENSOR_OBJECT_t*)malloc(sizeof(RDB_SENSOR_OBJECT_t)*noElements);
		break;

	case 21:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveRoadStateIDs.push_back(IDs[i]);
		}
		ReceiveRoadStateNoElements = noElements;
		ReceiveRoadStateArray = (RDB_ROAD_STATE_t*)malloc(sizeof(RDB_ROAD_STATE_t)*noElements);
		break;

	case 26:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveDriverCtrlIDs.push_back(IDs[i]);
		}
		ReceiveDriverCtrlNoElements = noElements;
		ReceiveDriverCtrlArray = (RDB_DRIVER_CTRL_t*)malloc(sizeof(RDB_DRIVER_CTRL_t)*noElements);
		break;

	case 29:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveDriverPerceptionIDs.push_back(IDs[i]);
		}
		ReceiveDriverPerceptionNoElements = noElements;
		ReceiveDriverPerceptionArray = (RDB_DRIVER_PERCEPTION_t*)malloc(sizeof(RDB_DRIVER_PERCEPTION_t)*noElements);
		break;

	case 34:
		for (int i = 0; i < noElements; i++)
		{
			ReceiveTrajectoryIDs.push_back(IDs[i]);
			ReceiveTrajectoryPoints.push_back(std::vector<RDB_POINT_t>());
		}
		ReceiveTrajectoryNoElements = noElements;
		ReceiveTrajectoryArray = (RDB_TRAJECTORY_t*)malloc(sizeof(RDB_TRAJECTORY_t)*noElements);
		break;

	default:
		return;
		break;
	}

}

void InitSendRDB(int pkID, const int noElements, int IDs[])
{
	switch (pkID)
	{
	case 9:
		SendObjectStateIDs = IDs;
		SendObjectStateNoElements = noElements;
		SendObjectStateArray = (RDB_OBJECT_STATE_t*)malloc(sizeof(RDB_OBJECT_STATE_t)*noElements);
		break;
	
	case 10:
		SendVehicleSystemsIDs = IDs;
		SendVehicleSystemsNoElements = noElements;
		SendVehicleSystemsArray = (RDB_VEHICLE_SYSTEMS_t*)malloc(sizeof(RDB_VEHICLE_SYSTEMS_t)*noElements);
		break;

	case 11:
		SendVehicleSetupIDs = IDs;
		SendVehicleSetupNoElements = noElements;
		SendVehicleSetupArray = (RDB_VEHICLE_SETUP_t*)malloc(sizeof(RDB_VEHICLE_SETUP_t)*noElements);
		break;
	
	case 12:
		SendEngineIDs = IDs;
		SendEngineNoElements = noElements;
		SendEngineArray = (RDB_ENGINE_t*)malloc(sizeof(RDB_ENGINE_t)*noElements);
		break;

	case 13:
		SendDrivetrainIDs = IDs;
		SendDrivetrainNoElements = noElements;
		SendDrivetrainArray = (RDB_DRIVETRAIN_t*)malloc(sizeof(RDB_DRIVETRAIN_t)*noElements);
		break;
	
	case 14:
		SendWheelIDs = IDs;
		SendWheelNoElements = noElements;
		SendWheelArray = (RDB_WHEEL_t*)malloc(sizeof(RDB_WHEEL_t)*noElements);
		break;
	
	case 23:
		SendLightSourcelIDs = IDs;
		SendLightSourceNoElements = noElements;
		SendLigthSourceArray = (RDB_LIGHT_SOURCE_t*)malloc(sizeof(RDB_LIGHT_SOURCE_t)*noElements);
		break;

	case 25:
		SendTriggerIDs = IDs;
		SendTriggerNoElements = noElements;
		SendTriggerArray = (RDB_TRIGGER_t*)malloc(sizeof(RDB_TRIGGER_t)*noElements);
		break;

	case 26:
		SendDriverCtrlIDs = IDs;
		SendDriverCtrlNoElements = noElements;
		SendDriverCtrlArray = (RDB_DRIVER_CTRL_t*)malloc(sizeof(RDB_DRIVER_CTRL_t)*noElements);
		break;

	case 27:
		SendTrafficLigthIDs = IDs;
		SendTrafficLightNoElements = noElements;
		SendTrafficLigthArray = (RDB_TRAFFIC_LIGHT_t*)malloc(sizeof(RDB_TRAFFIC_LIGHT_t)*noElements);
		break;

	case 28:
		SendSyncIDs = IDs;
		SendSyncNoElements = noElements;
		SendSyncArray = (RDB_SYNC_t*)malloc(sizeof(RDB_SYNC_t)*noElements);
		break;

	default:
		return;
		break;
	}

}

void clear()
{
	ReceiveLaneInfoIDs.clear();
	ReceiveVehicleSystemsIDs.clear();
	ReceiveVehicleSetupIDs.clear();
	ReceiveSensorStateIDs.clear();
	ReceiveSensorObjectIDs.clear();
	ReceiveRoadPosIDs.clear();
	ReceiveRoadStateIDs.clear();
	ReceiveObjectStateIDs.clear();
	ReceiveWheelIDs.clear();
	ReceivePlayerWheelIDs.clear();
	ReceiveEngineIDs.clear();
	ReceiveDriverPerceptionIDs.clear();
	ReceiveDriverCtrlIDs.clear();
	ReceiveTrajectoryIDs.clear();
	ReceiveTrajectoryPoints.clear();

	//free(ReceiveObjectStateArray);
	//free(ReceiveObjectStateIDs);
	//ReceiveObjectStateNoElements = 0;

	//free(SendObjectStateArray);
	//free(SendObjectStateIDs);
	//SendObjectStateNoElements = 0;
}

void ReceiveRDBMessage(int pkID, uint8_t *Item[], int id, int wheelid1
	
{
	int x = 0;
	switch (pkID)
	{
	case 5:
		while ((x < ReceiveRoadPosNoElements) && (id != ReceiveRoadPosArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveRoadPosNoElements) {
			memcpy(Item, &ReceiveRoadPosArray[x], sizeof(RDB_ROAD_POS_t));
		}
		break;
		
	case 6:
		while ((x < ReceiveLaneInfoNoElements) && (id != ReceiveLaneInfoArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveLaneInfoNoElements) {
			memcpy(Item, &ReceiveLaneInfoArray[x], sizeof(RDB_LANE_INFO_t));
		}
		break;
	
	case 9:
		while ((x < ReceiveObjectStateNoElements) && (id != ReceiveObjectStateArray[x].base.id)) {
			x++;
		}
		if (x < ReceiveObjectStateNoElements) {
			memcpy(Item, &ReceiveObjectStateArray[x], sizeof(RDB_OBJECT_STATE_t));
		}
		break;

	case 10:
		while ((x < ReceiveVehicleSystemsNoElements) && (id != ReceiveVehicleSystemsArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveVehicleSystemsNoElements) {
			memcpy(Item, &ReceiveVehicleSystemsArray[x], sizeof(RDB_VEHICLE_SYSTEMS_t));
		}
		break;

	case 11:
		while ((x < ReceiveVehicleSetupNoElements) && (id != ReceiveVehicleSetupArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveVehicleSetupNoElements) {
			memcpy(Item, &ReceiveVehicleSetupArray[x], sizeof(RDB_VEHICLE_SETUP_t));
		}
		break;

	case 12:
		while ((x < ReceiveEngineNoElements) && (id != ReceiveEngineArray[x].base.playerId)) {
			x++;
		}
		if (x < ReceiveEngineNoElements) {
			memcpy(Item, &ReceiveEngineArray[x], sizeof(RDB_ENGINE_t));
		}
		break;

	case 14:
		while ((x < ReceiveWheelNoElements)) {
			if ((id == ReceiveWheelArray[x].base.playerId) && (wheelid == ReceiveWheelArray[x].base.id))
				break;
			x++;
		}
		if (x < ReceiveWheelNoElements) {
			memcpy(Item, &ReceiveWheelArray[x], sizeof(RDB_WHEEL_t));
		}
		break;

	case 16:
		while ((x < ReceiveSensorStateNoElements) && (id != ReceiveSensorStateArray[x].id)) {
			x++;
		}
		if (x < ReceiveSensorStateNoElements) {
			memcpy(Item, &ReceiveSensorStateArray[x], sizeof(RDB_SENSOR_STATE_t));
		}
		break;

	case 17:
		while ((x < ReceiveSensorObjectNoElements) && (id != ReceiveSensorObjectArray[x].id)) {
			x++;
		}
		if (x < ReceiveSensorObjectNoElements) {
			memcpy(Item, &ReceiveSensorObjectArray[x], sizeof(RDB_SENSOR_OBJECT_t));
		}
		break;

	case 21:
		while ((x < ReceiveRoadStateNoElements) && (id != ReceiveRoadStateArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveRoadStateNoElements) {
			memcpy(Item, &ReceiveRoadStateArray[x], sizeof(RDB_ROAD_STATE_t));
		}
		break;

	case 26:
		while ((x < ReceiveDriverCtrlNoElements) && (id != ReceiveDriverCtrlArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveDriverCtrlNoElements) {
			memcpy(Item, &ReceiveDriverCtrlArray[x], sizeof(RDB_DRIVER_CTRL_t));
		}
		break;

	case 29:
		while ((x < ReceiveDriverPerceptionNoElements) && (id != ReceiveDriverPerceptionArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveDriverPerceptionNoElements) {
			memcpy(Item, &ReceiveDriverPerceptionArray[x], sizeof(RDB_DRIVER_CTRL_t));
		}
		break;

	case 34:
		while ((x < ReceiveTrajectoryNoElements) && (id != ReceiveTrajectoryArray[x].playerId)) {
			x++;
		}
		if (x < ReceiveTrajectoryNoElements) {
			memcpy(Item, &ReceiveTrajectoryArray[x], sizeof(RDB_TRAJECTORY_t));
			// 处理RDB_POINT_t数据
			size_t offset = sizeof(RDB_TRAJECTORY_t);
			for (int j = 0; j < ReceiveTrajectoryArray[x].noDataPoints; j++) 
			{
				// 每次复制一个RDB_POINT_t数据
				memcpy(Item + offset, &ReceiveTrajectoryPoints[x][j], sizeof(RDB_POINT_t));
				offset += sizeof(RDB_POINT_t);
			}
		}
		break;
		
	default:
		return;
		break;
	}


}

int InitNewRDBMessage()
{
	// start a new message
	myHandler.initMsg();

	// begin with an SOF identifier
	myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_START_OF_FRAME);

	return myHandler.getMsgTotalSize();
}

int ComposeRDBMessage(int pkID, int ElementIter, uint8_t *DataIn)
{
	switch (pkID)
	{
	case 9:		
		SendObjectStateArray[ElementIter] = *((RDB_OBJECT_STATE_t*)DataIn);
		if (ElementIter >= SendObjectStateNoElements - 1)
		{
			// add extended package for the object state
			RDB_OBJECT_STATE_t *objState = (RDB_OBJECT_STATE_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_OBJECT_STATE, SendObjectStateNoElements, true);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendObjectStateArray, (sizeof(RDB_OBJECT_STATE_t)*SendObjectStateNoElements));
		}
		break;

	case 10:
		SendVehicleSystemsArray[ElementIter] = *((RDB_VEHICLE_SYSTEMS_t*)DataIn);
		if (ElementIter >= SendVehicleSystemsNoElements - 1)
		{
			// add extended package for the object state
			RDB_VEHICLE_SYSTEMS_t *objState = (RDB_VEHICLE_SYSTEMS_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_VEHICLE_SYSTEMS, SendVehicleSystemsNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendVehicleSystemsArray, (sizeof(RDB_VEHICLE_SYSTEMS_t)*SendVehicleSystemsNoElements));
		}
		break;

	case 11:
		SendVehicleSetupArray[ElementIter] = *((RDB_VEHICLE_SETUP_t*)DataIn);
		if (ElementIter >= SendVehicleSetupNoElements - 1)
		{
			// add extended package for the object state
			RDB_VEHICLE_SETUP_t *objState = (RDB_VEHICLE_SETUP_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_VEHICLE_SETUP, SendVehicleSetupNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendVehicleSetupArray, (sizeof(RDB_VEHICLE_SETUP_t)*SendVehicleSetupNoElements));
		}
		break;

	case 12:
		SendEngineArray[ElementIter] = *((RDB_ENGINE_t*)DataIn);
		if (ElementIter >= SendEngineNoElements - 1)
		{
			// add extended package for the object state
			RDB_ENGINE_t *objState = (RDB_ENGINE_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_ENGINE, SendEngineNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendEngineArray, (sizeof(RDB_ENGINE_t)*SendEngineNoElements));
		}
		break;

	case 13:
		SendDrivetrainArray[ElementIter] = *((RDB_DRIVETRAIN_t*)DataIn);
		if (ElementIter >= SendDrivetrainNoElements - 1)
		{
			// add extended package for the object state
			RDB_DRIVETRAIN_t *objState = (RDB_DRIVETRAIN_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_DRIVETRAIN, SendDrivetrainNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendDrivetrainArray, (sizeof(RDB_DRIVETRAIN_t)*SendDrivetrainNoElements));
		}
		break;

	case 14:
		SendWheelArray[ElementIter] = *((RDB_WHEEL_t*)DataIn);
		if (ElementIter >= SendWheelNoElements - 1)
		{
			// add extended package for the object state
			RDB_WHEEL_t *objState = (RDB_WHEEL_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_WHEEL, SendWheelNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendWheelArray, (sizeof(RDB_WHEEL_t)*SendWheelNoElements));
		}
		break;

	case 23:
		SendLigthSourceArray[ElementIter] = *((RDB_LIGHT_SOURCE_t*)DataIn);
		if (ElementIter >= SendLightSourceNoElements - 1)
		{
			// add extended package for the object state
			RDB_LIGHT_SOURCE_t *objState = (RDB_LIGHT_SOURCE_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_LIGHT_SOURCE, SendLightSourceNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendLigthSourceArray, (sizeof(RDB_LIGHT_SOURCE_t)*SendLightSourceNoElements));
		}
		break;

	case 25:
		SendTriggerArray[ElementIter] = *((RDB_TRIGGER_t*)DataIn);
		if (ElementIter >= SendTriggerNoElements - 1)
		{
			// add extended package for the object state
			RDB_TRIGGER_t *objState = (RDB_TRIGGER_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_TRIGGER, SendTriggerNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendTriggerArray, (sizeof(RDB_TRIGGER_t)*SendTriggerNoElements));
		}
		break;

	case 26:
		SendDriverCtrlArray[ElementIter] = *((RDB_DRIVER_CTRL_t*)DataIn);
		if (ElementIter >= SendDriverCtrlNoElements - 1)
		{
			// add extended package for the object state
			RDB_DRIVER_CTRL_t *objState = (RDB_DRIVER_CTRL_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_DRIVER_CTRL, SendDriverCtrlNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendDriverCtrlArray, (sizeof(RDB_DRIVER_CTRL_t)*SendDriverCtrlNoElements));
		}
		break;

	case 27:
		SendTrafficLigthArray[ElementIter] = *((RDB_TRAFFIC_LIGHT_t*)DataIn);
		if (ElementIter >= SendTrafficLightNoElements - 1)
		{
			// add extended package for the object state
			RDB_TRAFFIC_LIGHT_t *objState = (RDB_TRAFFIC_LIGHT_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_TRAFFIC_LIGHT, SendTrafficLightNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendTrafficLigthArray, (sizeof(RDB_TRAFFIC_LIGHT_t)*SendTrafficLightNoElements));
		}
		break;

	case 28:
		SendSyncArray[ElementIter] = *((RDB_SYNC_t*)DataIn);
		if (ElementIter >= SendSyncNoElements - 1)
		{
			// add extended package for the object state
			RDB_SYNC_t *objState = (RDB_SYNC_t*)myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_SYNC, SendSyncNoElements, false);
			// copy contents of internally held object state to output structure
			memcpy(objState, SendSyncArray, (sizeof(RDB_SYNC_t)*SendSyncNoElements));
		}
		break;

	default:
		return myHandler.getMsgTotalSize();
		break;
	}
	return myHandler.getMsgTotalSize();
}

int SizeRDBMessage()
{
	// terminate with an EOF identifier
	myHandler.addPackage(simTime, simFrame, RDB_PKG_ID_END_OF_FRAME);
	return myHandler.getMsgTotalSize();
}

int SendRDBMessage(int size, uint8_t *Item[])
{

	memcpy(Item, (const char*)(myHandler.getMsg()), myHandler.getMsgTotalSize());
	return myHandler.getMsgTotalSize();

}

void parseRDBMessage(RDB_MSG_t* msg, bool & isImage)
{
	uint8_t *valid = 0;
	
	if (!msg)
		return;

	if (!msg->hdr.dataSize)
		return;

	RDB_MSG_ENTRY_HDR_t* entry = (RDB_MSG_ENTRY_HDR_t*)(((char*)msg) + msg->hdr.headerSize);
	uint32_t remainingBytes = msg->hdr.dataSize;

	simTime = msg->hdr.simTime;
	simFrame = msg->hdr.frameNo;

	while (remainingBytes)
	{
		parseRDBMessageEntry(msg->hdr.simTime, msg->hdr.frameNo, entry);

		isImage |= (entry->pkgId == RDB_PKG_ID_IMAGE);

		remainingBytes -= (entry->headerSize + entry->dataSize);

		if (remainingBytes)
			entry = (RDB_MSG_ENTRY_HDR_t*)((((char*)entry) + entry->headerSize + entry->dataSize));
	}
	
}

void parseRDBMessageEntry(const double & simTime, const unsigned int & simFrame, RDB_MSG_ENTRY_HDR_t* entryHdr)
{
	if (!entryHdr)
		return;

	int noElements = entryHdr->elementSize ? (entryHdr->dataSize / entryHdr->elementSize) : 0;

	/*if (!noElements)  // some elements require special treatment
	{
		switch (entryHdr->pkgId)
		{
		case RDB_PKG_ID_START_OF_FRAME:
			fprintf(stderr, "void parseRDBMessageEntry: got start of frame\n");
			break;

		case RDB_PKG_ID_END_OF_FRAME:
			fprintf(stderr, "void parseRDBMessageEntry: got end of frame\n");
			break;

		default:
			return;
			break;
		}
		return;
		}*/			//Don't print on Console due to Performance

	unsigned char ident = 6;
	char*         dataPtr = (char*)entryHdr;

	dataPtr += entryHdr->headerSize;

	int i = 0;
	int x = 0;

	while (noElements--)
	{
		bool printedMsg = true;

		switch (entryHdr->pkgId)
		{
			/*
			case RDB_PKG_ID_COORD_SYSTEM:
			print( *( ( RDB_COORD_SYSTEM_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_COORD:
			print( *( ( RDB_COORD_t* ) dataPtr ), ident );
			break;
			*/

			case RDB_PKG_ID_ROAD_POS:
				//Search starts from the zero location
				x = 0;
				RDB_ROAD_POS_t roadpos;
				memcpy(&roadpos, ((RDB_ROAD_POS_t*)dataPtr), sizeof(RDB_ROAD_POS_t));
				while ((x < ReceiveRoadPosNoElements) && (roadpos.playerId != ReceiveRoadPosIDs[x])) {
					x++;
				}

				//If i < ReceiveRoadPosNoElement then Match found
				if (x < ReceiveRoadPosNoElements) {
					ReceiveRoadPosArray[i] = *((RDB_ROAD_POS_t*)dataPtr);
					i++;
				}
			break;
			
			case RDB_PKG_ID_LANE_INFO:
				//Search starts from the zero location
				x = 0;
				RDB_LANE_INFO_t laneinfo;
				memcpy(&laneinfo, ((RDB_LANE_INFO_t*)dataPtr), sizeof(RDB_LANE_INFO_t));
				while ((x < ReceiveLaneInfoNoElements) && (laneinfo.playerId != ReceiveLaneInfoIDs[x])) {
					x++;
				}

				//If i < ReceiveRoadPosNoElement then Match found
				if (x < ReceiveLaneInfoNoElements) {
					ReceiveLaneInfoArray[i] = *((RDB_LANE_INFO_t*)dataPtr);
					i++;
				}
			/*
			case RDB_PKG_ID_LANE_INFO:
			print( *( ( RDB_LANE_INFO_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_ROADMARK:
			print( *( ( RDB_ROADMARK_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_OBJECT_CFG:
			Customizing Data Streams
			break;
			*/
			case RDB_PKG_ID_OBJECT_STATE:			
				//Search starts from the zero location
				x = 0;
				RDB_OBJECT_STATE_t objectstate;

				memcpy(&objectstate, ((RDB_OBJECT_STATE_t*)dataPtr), sizeof(RDB_OBJECT_STATE_t));
				//while ((x < ReceiveObjectStateNoElements)) {
				//	int test = ReceiveObjectStateIDs[x];

				//	if (objectstate.base.id == test)
				//		break;

				//	x++;
				//}

				while ((x < ReceiveObjectStateNoElements) && (objectstate.base.id != ReceiveObjectStateIDs[x])) {
					x++;
				}

				//If i < ObjectStateNoElements then Match found
				if (x < ReceiveObjectStateNoElements) {
					ReceiveObjectStateArray[i] = *((RDB_OBJECT_STATE_t*)dataPtr);
					i++;
				}
			break;

			case RDB_PKG_ID_VEHICLE_SYSTEMS:
				//Search starts from the zero location
				x = 0;
				RDB_VEHICLE_SYSTEMS_t vehiclesystems;
				memcpy(&vehiclesystems, ((RDB_VEHICLE_SYSTEMS_t*)dataPtr), sizeof(RDB_VEHICLE_SYSTEMS_t));
				while ((x < ReceiveVehicleSystemsNoElements) && (vehiclesystems.playerId != ReceiveVehicleSystemsIDs[x])) {
					x++;
				}

				//If i < ObjectStateNoElements then Match found
				if (x < ReceiveVehicleSetupNoElements) {
					ReceiveVehicleSystemsArray[i] = *((RDB_VEHICLE_SYSTEMS_t*)dataPtr);
					i++;
				}
			break;

			case RDB_PKG_ID_VEHICLE_SETUP:
				//Search starts from the zero location
				x = 0;
				RDB_VEHICLE_SETUP_t vehiclesetup;
				memcpy(&vehiclesetup, ((RDB_VEHICLE_SETUP_t*)dataPtr), sizeof(RDB_VEHICLE_SETUP_t));
				while ((x < ReceiveVehicleSetupNoElements) && (vehiclesetup.playerId != ReceiveVehicleSetupIDs[x])) {
					x++;
				}

				//If i < ObjectStateNoElements then Match found
				if (x < ReceiveVehicleSetupNoElements) {
					ReceiveVehicleSetupArray[i] = *((RDB_VEHICLE_SETUP_t*)dataPtr);
					i++;
				}
			break;


			case RDB_PKG_ID_ENGINE:
			//Search starts from the zero location
			x = 0;
			RDB_ENGINE_t engine;
			memcpy(&engine, ((RDB_ENGINE_t*)dataPtr), sizeof(RDB_ENGINE_t));
			while ((x < ReceiveEngineNoElements) && (engine.base.playerId != ReceiveEngineIDs[x])) {
				x++;
			}

			//If i < ObjectStateNoElements then Match found
			if (x < ReceiveEngineNoElements) {
				ReceiveEngineArray[i] = *((RDB_ENGINE_t*)dataPtr);
				i++;
			}
			break;

			/*
			case RDB_PKG_ID_DRIVETRAIN:
			print( *( ( RDB_DRIVETRAIN_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident );
			break; */

			case RDB_PKG_ID_WHEEL:
			//Search starts from the zero location
			if (i >= ReceiveWheelNoElements)
				break;

			x = 0;
			RDB_WHEEL_t wheel;
			memcpy(&wheel, ((RDB_WHEEL_t*)dataPtr), sizeof(RDB_WHEEL_t));
			while (x < ReceiveWheelNoElements) 
			{
				if ((wheel.base.playerId == ReceivePlayerWheelIDs[x]) && (wheel.base.id == ReceiveWheelIDs[x]))
					break;				
				x++;
			}

			//If i < ObjectStateNoElements then Match found
			if (x < ReceiveWheelNoElements) {
				ReceiveWheelArray[i] = *((RDB_WHEEL_t*)dataPtr);
				i++;
			}
			break;

			/*
			case RDB_PKG_ID_PED_ANIMATION:
			print( *( ( RDB_PED_ANIMATION_t* ) dataPtr ), ident );
			break;*/

			//case RDB_PKG_ID_SENSOR_STATE:
			////Search starts from the zero location
			//x = 0;
			//RDB_SENSOR_STATE_t sensorstate;
			//memcpy(&sensorstate, ((RDB_SENSOR_STATE_t*)dataPtr), sizeof(RDB_SENSOR_STATE_t));
			//while ((x < ReceiveSensorStateNoElements) && (sensorstate.id != ReceiveSensorStateIDs[x])) {
			//	x++;
			//}

			////If i < ObjectStateNoElements then Match found
			//if (x < ReceiveSensorStateNoElements) {
			//	ReceiveSensorStateArray[i] = *((RDB_SENSOR_STATE_t*)dataPtr);
			//	i++;
			//}
			//break;

			//case RDB_PKG_ID_SENSOR_OBJECT:
			////Search starts from the zero location
			//x = 0;
			//RDB_SENSOR_OBJECT_t sensorobject;
			//memcpy(&sensorobject, ((RDB_SENSOR_OBJECT_t*)dataPtr), sizeof(RDB_SENSOR_OBJECT_t));
			//while ((x < ReceiveSensorObjectNoElements) && (sensorobject.id != ReceiveSensorObjectIDs[x])) {
			//	x++;
			//}

			////If i < ObjectStateNoElements then Match found
			//if (x < ReceiveSensorObjectNoElements) {
			//	ReceiveSensorObjectArray[i] = *((RDB_SENSOR_OBJECT_t*)dataPtr);
			//	i++;
			//}
			//break;
			
#/*
			case RDB_PKG_ID_CAMERA:
			print( *( ( RDB_CAMERA_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_CONTACT_POINT:
			print( *( ( RDB_CONTACT_POINT_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_TRAFFIC_SIGN:
			print( *( ( RDB_TRAFFIC_SIGN_t* ) dataPtr ), ident );
			break;*/

			case RDB_PKG_ID_ROAD_STATE:
			//Search starts from the zero location
			x = 0;
			RDB_ROAD_STATE_t roadstate;
			memcpy(&roadstate, ((RDB_ROAD_STATE_t*)dataPtr), sizeof(RDB_ROAD_STATE_t));
			while ((x < ReceiveRoadStateNoElements) && (roadstate.playerId != ReceiveRoadStateIDs[x])) {
				x++;
			}

			//If i < ObjectStateNoElements then Match found
			if (x < ReceiveRoadStateNoElements) {
				ReceiveRoadStateArray[i] = *((RDB_ROAD_STATE_t*)dataPtr);
				i++;
			}
			break;

			/*
			case RDB_PKG_ID_IMAGE:
			case RDB_PKG_ID_LIGHT_MAP:
			handleRDBitem( simTime, simFrame, *( ( RDB_IMAGE_t* ) dataPtr ) );
			break;

			case RDB_PKG_ID_LIGHT_SOURCE:
			print( *( ( RDB_LIGHT_SOURCE_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident );
			break;

			case RDB_PKG_ID_ENVIRONMENT:
			print( *( ( RDB_ENVIRONMENT_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_TRIGGER:
			print( *( ( RDB_TRIGGER_t* ) dataPtr ), ident );
			break; */

			case RDB_PKG_ID_DRIVER_CTRL:
				//Search starts from the zero location
				x = 0;
				RDB_DRIVER_CTRL_t driverCtrl;
				memcpy(&driverCtrl, ((RDB_DRIVER_CTRL_t*)dataPtr), sizeof(RDB_DRIVER_CTRL_t));
				while ((x < ReceiveDriverCtrlNoElements) && (driverCtrl.playerId != ReceiveDriverCtrlIDs[x])) {
					x++;
				}

				//If i < ObjectStateNoElements then Match found
				if (x < ReceiveDriverCtrlNoElements) {
					ReceiveDriverCtrlArray[i] = *((RDB_DRIVER_CTRL_t*)dataPtr);
					i++;
				}	
			break;

			/*
			case RDB_PKG_ID_TRAFFIC_LIGHT:
			print( *( ( RDB_TRAFFIC_LIGHT_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident );
			break;
			*/	

			case RDB_PKG_ID_SYNC:
				
			break;

			
			case RDB_PKG_ID_DRIVER_PERCEPTION:
			//Search starts from the zero location
			x = 0;
			RDB_DRIVER_PERCEPTION_t driverPerception;
			memcpy(&driverPerception, ((RDB_DRIVER_PERCEPTION_t*)dataPtr), sizeof(RDB_DRIVER_PERCEPTION_t));
			while ((x < ReceiveDriverPerceptionNoElements) && (driverPerception.playerId != ReceiveDriverPerceptionIDs[x])) {
				x++;
			}

			//If i < ObjectStateNoElements then Match found
			if (x < ReceiveDriverPerceptionNoElements) {
				ReceiveDriverPerceptionArray[i] = *((RDB_DRIVER_PERCEPTION_t*)dataPtr);
				i++;
			}
			break;
			
			
			/*
			case RDB_PKG_ID_TONE_MAPPING:
			print( *( ( RDB_FUNCTION_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_ROAD_QUERY:
			print( *( ( RDB_ROAD_QUERY_t* ) dataPtr ), ident );
			break;
			*/

			case RDB_PKG_ID_TRAJECTORY:
			//Search starts from the zero location
			x = 0;
			RDB_TRAJECTORY_t trajectory;
			memcpy(&trajectory, ((RDB_TRAJECTORY_t*)dataPtr), sizeof(RDB_TRAJECTORY_t));
			while ((x < ReceiveTrajectoryNoElements) && (trajectory.playerId != ReceiveTrajectoryIDs[x])) {
				x++;
			}
			
			//If i < ObjectStateNoElements then Match found
			if (x < ReceiveTrajectoryNoElements) {
				ReceiveTrajectoryArray[i] = *((RDB_TRAJECTORY_t*)dataPtr);
				ReceiveTrajectoryPoints[i].resize(trajectory.noDataPoints);
				memcpy(ReceiveTrajectoryPoints[i].data(), dataPtr + sizeof(RDB_TRAJECTORY_t), trajectory.noDataPoints * sizeof(RDB_POINT_t));
				i++;
			}
			break;

			/*
			case RDB_PKG_ID_DYN_2_STEER:
			print( *( ( RDB_DYN_2_STEER_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_STEER_2_DYN:
			print( *( ( RDB_STEER_2_DYN_t* ) dataPtr ), ident );
			break;

			case RDB_PKG_ID_PROXY:
			print( *( ( RDB_PROXY_t* ) dataPtr ), ident );
			break;
			*/
			
			default:
			printedMsg = false;
			break;
		}
		dataPtr += entryHdr->elementSize;

		/*        if ( noElements && printedMsg )
		fprintf( stderr, "\n" );
		*/
	}
}

void handleRDBitem(const double & simTime, const unsigned int & simFrame, RDB_OBJECT_STATE_t & item, bool isExtended)
{
	fprintf( stderr, "handleRDBitem: handling object state\n" );
	fprintf( stderr, "    simTime = %.3lf, simFrame = %ld\n", simTime, simFrame );
	fprintf( stderr, "    object = %s, id = %d\n", item.base.name, item.base.id );
	fprintf( stderr, "    position = %.3lf / %.3lf / %.3lf\n", item.base.pos.x, item.base.pos.y, item.base.pos.z );

	if ( isExtended )
	  fprintf( stderr, "    speed = %.3lf / %.3lf / %.3lf\n", item.ext.speed.x, item.ext.speed.y, item.ext.speed.z );
}

void handleRDBitem(const double & simTime, const unsigned int & simFrame, RDB_IMAGE_t & item)
{
	fprintf(stderr, "handleRDBitem: handling image data\n");
	fprintf(stderr, "    simTime = %.3lf, simFrame = %ld\n", simTime, simFrame);
	fprintf(stderr, "    id = %d, width = %d, height = %d\n", item.id, item.width, item.height);
	fprintf(stderr, "    pixelSize = %d, pixelFormat = %d, imgSize = %d\n", item.pixelSize, item.pixelFormat, item.imgSize);

	// write image to file
	unsigned char* imgData = (unsigned char*)(&item);
	imgData += sizeof(RDB_IMAGE_t);

	/* here could be a routine to process the image data, e.g.
	processImgData( item.width, item.height, item.pixelSize, item.pixelFormat, item.imgSize, imgData, simFrame );
	*/
}

/*
void sendTrigger( int & sendSocket, const double & simTime, const unsigned int & simFrame )
{
Framework::RDBHandler myHandler;

myHandler.initMsg();

RDB_TRIGGER_t *myTrigger = ( RDB_TRIGGER_t* ) myHandler.addPackage( simTime, simFrame, RDB_PKG_ID_TRIGGER );

if ( !myTrigger )
return;

myTrigger->frameNo = simFrame + 1;
myTrigger->deltaT  = 0.043;

int retVal = send( sendSocket, ( const char* ) ( myHandler.getMsg() ), myHandler.getMsgTotalSize(), 0 );

if ( !retVal )
fprintf( stderr, "sendTrigger: could not send trigger\n" );

}*/


unsigned int  bytesInBuffer = 0;
size_t        bufferSize = sizeof(RDB_MSG_HDR_t);
unsigned int  count = 0;
unsigned char *pData = (unsigned char*)calloc(1, bufferSize);


void msgparse(unsigned char* szBuffer, int ret, uint8_t *valid, double *simTime, int *simFrame)
{

	*valid = 0;
	
	// do we have to grow the buffer??
	if ((bytesInBuffer + ret) > bufferSize)
	{
		pData = (unsigned char*)realloc(pData, bytesInBuffer + ret);
		bufferSize = bytesInBuffer + ret;
	}

	memcpy(pData + bytesInBuffer, szBuffer, ret);
	bytesInBuffer += ret;

	// already complete messagae?
	if (bytesInBuffer >= sizeof(RDB_MSG_HDR_t))
	{
		RDB_MSG_HDR_t* hdr = (RDB_MSG_HDR_t*)pData;

		// is this message containing the valid magic number?
		if (hdr->magicNo != RDB_MAGIC_NO)
		{
			printf("message receiving is out of sync; discarding data");
			bytesInBuffer = 0;
			*valid = 0;
		}

		// handle all messages in the buffer before proceeding
		while (bytesInBuffer >= (hdr->headerSize + hdr->dataSize))
		{
			unsigned int msgSize = hdr->headerSize + hdr->dataSize;
			bool         isImage = false;
			
			*simTime = hdr->simTime;
			*simFrame = hdr->frameNo;

			// now parse the message
			parseRDBMessage((RDB_MSG_t*)pData, isImage);

			// remove message from queue
			memmove(pData, pData + msgSize, bytesInBuffer - msgSize);
			bytesInBuffer -= msgSize;
			*valid = 1;
		}
	}
}
