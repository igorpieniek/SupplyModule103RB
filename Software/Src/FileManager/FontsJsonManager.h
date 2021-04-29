/*
 * FontsJsonManager.h
 *
 *  Created on: 20 lut 2021
 *      Author: danie
 */
#include <vector>
#include <cardSD.h>
#include <ArduinoJson-v6.15.2.h>
#include <JsonManager.h>

#ifndef SRC_FILEMANAGER_FONTSJSONMANAGER_H_
#define SRC_FILEMANAGER_FONTSJSONMANAGER_H_

using namespace std;

class FontsJsonManager {
public:
	FontsJsonManager(JsonManager const&) = delete;
	void operator=(JsonManager const&) = delete;
	virtual ~FontsJsonManager();
	static FontsJsonManager& getInstance(){
		static FontsJsonManager instance;
		return instance;
	}

	typedef enum {JSON_OK, JSON_READ_ERR, JSON_SD_ERR, JSON_KEY_ERR, NO_FONT_ERROR} Json_FontsStatus;

	Json_FontsStatus getJsonFontsStatus();
	void findFontToCreate(uint8_t width, uint8_t height);
	void findFontToCreate(string name);
	string getPath(uint8_t width, uint8_t height);
	uint8_t getWidth(uint8_t width, uint8_t height);
	uint8_t getHeight(uint8_t width, uint8_t height);
	string getName(uint8_t width, uint8_t height);
	string getPath(string name);
	uint8_t getWidth(string name);
	uint8_t getHeight(string name);
	string getName(string name);

private:
	FontsJsonManager();
	struct FontsSettings{
		std::string font;
		uint8_t height;
		uint8_t width;
		string path;
	};
	FontsSettings actualFontSettings;
	vector<FontsSettings> fontsSettings;
	Json_FontsStatus json_fonts_status;
};

#endif /* SRC_FILEMANAGER_FONTSJSONMANAGER_H_ */
