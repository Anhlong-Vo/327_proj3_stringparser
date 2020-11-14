/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include <strings.h>
#include <cstring>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace KP_StringParserClass;

StringParserClass::StringParserClass():pStartTag(0),pEndTag(0),areTagsSet(false){

}
StringParserClass::~StringParserClass() {
	cleanup();
}

int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == 0 || pEnd == 0) {
		return ERROR_TAGS_NULL;
	}

	pStartTag = strdup(pStart);

	pEndTag = strdup(pEnd);

	areTagsSet = true;

	return SUCCESS;
}

int StringParserClass::getDataBetweenTags(char* pDataToSearchThru, std::vector<std::string> &myVector) {

	myVector.clear();

	if (!areTagsSet) {
		return ERROR_TAGS_NULL;
	}
	if (pDataToSearchThru == 0) {
		return ERROR_DATA_NULL;
	}

	bool areAllTagsFound = false;
	while (!areAllTagsFound) {
		std::string s;
		char* pEnd = (pStartTag + strlen(pStartTag) -1);
		char* pStart = 0;
		char* pNonceStart = 0;
		char* pNonceEnd = 0;
		int iret = findTag(pStartTag, pDataToSearchThru, pEnd);

		if (iret == SUCCESS) {
			pNonceStart = pEnd;
			pStart = pNonceStart;
			int iret = findTag(pEndTag, pStart, pEnd);
			if (iret == FAIL) {
				break;
			}
		}
		else {
			break;
		}

		pNonceEnd = pStart;
		s.assign(pNonceStart, pNonceEnd - (pNonceStart));
		pDataToSearchThru = pStart + strlen(pEndTag);
		myVector.push_back(s);
		iret = findTag(pStartTag, pDataToSearchThru, pEnd);
		if (iret != SUCCESS) {
			areAllTagsFound = true;
		}
	}
	return SUCCESS;
}

void StringParserClass::cleanup() {
	delete pStartTag;
	delete pEndTag;
	areTagsSet = false;
}

int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
	if (!areTagsSet) {
		return ERROR_TAGS_NULL;
	}
	pEnd = 0;

	int ilen = strlen(pStart);
	int lenTag = strlen(pTagToLookFor);
	for (int i = 0; i< ilen; i++) {
		if (*(pStart) == *(pTagToLookFor)) {
			if (strncmp(pStart, pTagToLookFor, lenTag) == 0) {
				pEnd = pStart + lenTag;
				return SUCCESS;
			}
		}
		pStart++;
	}
	return FAIL;
}
