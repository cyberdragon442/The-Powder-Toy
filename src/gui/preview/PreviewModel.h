#ifndef PREVIEWMODEL_H_
#define PREVIEWMODEL_H_

#include <vector>
#include <iostream>
#include <pthread.h>
#undef GetUserName //God dammit microsoft!
#include "PreviewView.h"
#include "client/SaveInfo.h"
#include "gui/preview/Comment.h"
#include "gui/search/Thumbnail.h"

using namespace std;

struct SaveData
{
	unsigned char * data;
	int length;
};

class PreviewView;
class PreviewModel {
	bool doOpen;
	bool commentBoxEnabled;
	vector<PreviewView*> observers;
	SaveInfo * save;
	vector<char> saveDataBuffer;
	std::vector<SaveComment*> * saveComments;
	void notifySaveChanged();
	void notifySaveCommentsChanged();
	void notifyCommentsPageChanged();
	void notifyCommentBoxEnabledChanged();

	//Background retrieval
	int tSaveID;
	int tSaveDate;

	//
	bool commentsLoaded;
	int commentsTotal;
	int commentsPageNumber;

	bool updateSaveDataWorking;
	volatile bool updateSaveDataFinished;
	pthread_t updateSaveDataThread;
	static void * updateSaveDataTHelper(void * obj);
	static void updateSaveDataTDelete(void * arg);
	void * updateSaveDataT();

	bool updateSaveInfoWorking;
	volatile bool updateSaveInfoFinished;
	pthread_t updateSaveInfoThread;
	static void * updateSaveInfoTHelper(void * obj);
	static void updateSaveInfoTDelete(void * arg);
	void * updateSaveInfoT();

	bool updateSaveCommentsWorking;
	volatile bool updateSaveCommentsFinished;
	pthread_t updateSaveCommentsThread;
	static void * updateSaveCommentsTHelper(void * obj);
	static void updateSaveCommentsTDelete(void * arg);
	void * updateSaveCommentsT();
public:
	PreviewModel();
	SaveInfo * GetSave();
	std::vector<SaveComment*> * GetComments();

	bool GetCommentBoxEnabled();
	void SetCommentBoxEnabled(bool enabledState);

	bool GetCommentsLoaded();
	int GetCommentsPageNum();
	int GetCommentsPageCount();
	void UpdateComments(int pageNumber);

	void AddObserver(PreviewView * observer);
	void UpdateSave(int saveID, int saveDate);
	void SetFavourite(bool favourite);
	bool GetDoOpen();
	void SetDoOpen(bool doOpen);
	void Update();
	virtual ~PreviewModel();
};

#endif /* PREVIEWMODEL_H_ */
