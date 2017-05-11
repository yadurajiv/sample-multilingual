/* Copyright 2017 Yadu Rajiv */

#ifndef __GAMERESOURCES_H__
#define __GAMERESOURCES_H__

#include <cocos2d.h>
#include <json\rapidjson.h>
#include <json\document.h>
#include <string>

class GameResources
{
public:

	static GameResources* getInstance();

    void loadFonts();

    void loadStrings(std::string defaultLangauge = "en");

    std::string getFont(std::string langauge = "", std::string key = "regular");

    std::string getUIString(std::string key, std::string langauge);

    std::string getUIString(std::string key);

    rapidjson::Document gameStrings;

    rapidjson::Document gameFonts;

    std::string settingsUILanguage;

private:
	GameResources() {};  // Private so that it can  not be called

	GameResources(GameResources const&) {};             // copy constructor is private
	GameResources& operator=(GameResources const&) {};  // assignment operator is private

	static GameResources* _pInstance;

};

#endif // __GAMERESOURCES_H__