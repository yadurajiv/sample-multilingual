/* Copyright 2017 Yadu Rajiv */

#include "GameResources.h"

GameResources* GameResources::_pInstance = nullptr;

// creates and returns a pointer to the only instance of the app
GameResources* GameResources::getInstance() {
    if (!_pInstance) {   // Only allow one instance of class to be generated.
        _pInstance = new GameResources;
        srand(time(NULL));
    }

	return _pInstance;
}

void GameResources::loadFonts() {

    // json file containing strings for multiple languages
    std::string filename = "ui/fonts.json";
    std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename));
    gameFonts.Parse(data.c_str());

}

void GameResources::loadStrings(std::string defaultLangauge) {

    // json file containing strings for multiple languages
    std::string filename = "ui/strings/" + defaultLangauge + ".json";
    std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename));
    gameStrings.Parse(data.c_str());

    settingsUILanguage = defaultLangauge;

}

std::string GameResources::getFont(std::string langauge, std::string key) {

    if (langauge.length() <= 0) {
        langauge = settingsUILanguage;
    }

    // our json was not parsed correctly, return fallback default font
    if (!gameFonts.IsObject()) {
        return "ui/fonts/en.ttf";
    }

    const rapidjson::Value& v = gameFonts[langauge.c_str()];
    if (v.HasMember(key.c_str())) {
        return v[key.c_str()].GetString();
    } else {
        // our key is missing, try "regular" as key if it is valid
        if (v.HasMember("regular")) {
            return v["regular"].GetString();
        } else {
            // our key is missing, return an error string
            return "ui/fonts/en.ttf";
        }
    }

    return std::string();
}

std::string GameResources::getUIString(std::string key, std::string langauge) {

    if (langauge.length() <= 0) {
        langauge = settingsUILanguage;
    }

    // our json was not parsed correctly, return an error string
    if (!gameStrings.IsObject()) {
        return "ERR_STR_DOC_" + langauge;
    }

    const rapidjson::Value& v = gameStrings[langauge.c_str()];
    if (v.HasMember(key.c_str())) {
        return v[key.c_str()].GetString();
    } else {
        // our key is missing, return an error string
        return "ERR_STR_MISS_" + langauge + "_" + key;
    }
}

std::string GameResources::getUIString(std::string key) {
    return getUIString(key, settingsUILanguage);
}