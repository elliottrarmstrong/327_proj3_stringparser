/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include <vector>
#include "../327_proj3_test/includes/constants.h"
#include "../327_proj3_test/includes/StringParserClass.h"

using namespace std;
using namespace KP_StringParserClass;

const int SPACE = 256;

//TODO Fill in

//constructor
StringParserClass::StringParserClass(void){
	//never know when you're gonna have a huge char
	pStartTag = new char[SPACE];
	pEndTag = new char[SPACE];

	areTagsSet = false;

}

//destructor
StringParserClass::~StringParserClass(void){
	cleanup();
	areTagsSet = false;
}

//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::setTags(const char *pStart, const char *pEnd){
	if(pStart == NULL || pEnd == NULL)
		return ERROR_TAGS_NULL;

	//deep copy for pStartTag
	int slength = strlen(pStart);
	pStartTag = new char[slength+1];

	//deep copy for pEndTag
	int elength = strlen(pEnd);
	pEndTag = new char[elength+1];

	strncpy(pStartTag, pStart, slength);
	strncpy(pEndTag, pEnd, elength);

	int deleteMe = strlen(pStartTag);
	int deleteMe2 = strlen(pEndTag);

	areTagsSet = true;
	return SUCCESS;
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, vector<string> &myVector){
	if(!areTagsSet)
		return ERROR_TAGS_NULL;
	if(pDataToSearchThru == NULL)
		return ERROR_DATA_NULL;

	myVector.clear();

	int datalength = strlen(pDataToSearchThru);
	char *dataEnd = (pDataToSearchThru + datalength);

	//start of start tag
	char *ss = pDataToSearchThru;
	//end of start tag
	char *es = pDataToSearchThru + datalength;
	//start of end tag
	char *se = pDataToSearchThru;
	//end of end tag
	char *ee = pDataToSearchThru + datalength;

	while(findTag(pStartTag, ss, es) == SUCCESS){
		if(findTag(pEndTag, se, ee) == FAIL){
			return SUCCESS;
		}
		string data = "";
		while(es != se){
			data += *es;
			es++;
		}
		myVector.push_back(data);
		pDataToSearchThru == ee;
		datalength = strlen(pDataToSearchThru);
		ss = ee;
		es = ee + datalength;
		se = ee;
		ee = ee + datalength;
	}
	return SUCCESS;
}

void StringParserClass::cleanup(){
	if(pStartTag){
		delete[] pStartTag;
		pStartTag = 0;
	}
	if(pEndTag){
		delete[] pEndTag;
		pEndTag = 0;
	}
}

//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){
	if(pStart == NULL || pEnd == NULL)
		return ERROR_TAGS_NULL;
	int length = strlen(pTagToLookFor);

	while(pStart != pEnd){
		if(*pStart == *pTagToLookFor){
			if(strncmp(pStart, pTagToLookFor, length) == 0){
				pEnd = pStart + length;
				return SUCCESS;
			}
		}
		pStart++;
	}

	pEnd = 0;
	return FAIL;
}

