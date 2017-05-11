/*

Copyright 2017 Yadu Rajiv 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

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

void GameResources::loadStrings(std::string defaultLangauge) {

    // json file containing strings for multiple languages
    std::string filename = "ui/strings.json";
    std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename));
    gameStrings.Parse(data.c_str());

    settingsUILanguage = defaultLangauge;
}

std::string GameResources::getUIString(const std::string key, const std::string langauge) {

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