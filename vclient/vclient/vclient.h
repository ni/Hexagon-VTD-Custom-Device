/*
* vclient.h
*
*  Created on: Feb 17, 2017
*      Author: NI
*/

//#ifdef VCLIENT_EXPORTS
#ifdef _WIN32
#define VCLIENT_API __declspec(dllexport)
#elif __linux__
#define VCLIENT_API __attribute__((visibility("default")))
#endif //_WIN32 & __linux__
//#else
//#define VCLIENT_API __declspec(dllimport)
//#endif //VCLIENT_EXPORTS

#ifndef VCLIENT_H_
#define VCLIENT_H_

#ifdef __cplusplus
extern "C" {

#else

#endif

	VCLIENT_API void InitReceiveRDB(int pkID, const int noElements, int IDs[], int WheelIDs[]);
	VCLIENT_API void InitSendRDB(int pkID, const int noElements, int IDs[]);
	VCLIENT_API void parseRDBMessage(RDB_MSG_t* msg, bool & isImage);
	VCLIENT_API void ReceiveRDBMessage(int pkID, uint8_t *Item[], int id, int wheelid, uint8_t *Data[]);
	VCLIENT_API int  InitNewRDBMessage();
	VCLIENT_API int  ComposeRDBMessage(int pkID, int ElementIter, uint8_t *DataIn);
	VCLIENT_API	int  SendRDBMessage(int size, uint8_t *Item[]);
	VCLIENT_API int  SizeRDBMessage();
	VCLIENT_API void clear();
	VCLIENT_API void msgparse(unsigned char* szBuffer, int ret, uint8_t *valid, double *simTime, int *simFrame);

#ifdef __cplusplus
}
#endif




#endif /* VCLIENT_H_ */

