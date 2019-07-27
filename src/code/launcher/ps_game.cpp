//
// Created by screemer on 2/12/19.
//

#include "ps_game.h"
#include "../util.h"
#include "../engine/inifile.h"
#include "../gui/gui.h"
#include <fstream>
using namespace std;

//*******************************
// PsGame::isCleanExit
//*******************************
bool PsGame::isCleanExit() {
    if (!foreign) {
        string filenamefile = ssFolder + "filename.txt";
        return DirEntry::exists(filenamefile);
    } else
    {
        return true;
    }
}

//*******************************
// PsGame::setMemCard
//*******************************
void PsGame::setMemCard(string name) {
    if (!foreign) {
        this->memcard = name;
        Inifile *ini = new Inifile();
        ini->load(this->folder + "/Game.ini");
        ini->values["memcard"] = name;
        ini->save(this->folder + "/Game.ini");
        shared_ptr<Gui> gui(Gui::getInstance());
        gui->db->updateMemcard(this->gameId, name);
    }
}

//*******************************
// PsGame::removeResumePoint
//*******************************
void PsGame::removeResumePoint(int slot) {
     if (!foreign) {
         string filenamefile = ssFolder + "filename.txt.res";
         string filenamepoint = ssFolder + "filename." + to_string(slot) + ".txt.res";
         if (DirEntry::exists(filenamepoint)) {
             filenamefile = filenamepoint;
         }
         if (DirEntry::exists(filenamefile)) {
             ifstream is(filenamefile.c_str());
             if (is.is_open()) {

                 std::string line;
                 std::getline(is, line);
                 std::getline(is, line);

                 string ssfile = ssFolder + "sstates/" + line + ".00" + to_string(slot) + ".res";
                 remove(ssfile.c_str());
                 // last line is our filename
                 if (slot == 0) {
                     string slot0img = ssFolder + "screenshots/" + line + ".png.res";
                     remove(slot0img.c_str());

                 } else {
                     string slotnimg = ssFolder + "screenshots/" + line + "." + to_string(slot) + ".png.res";
                     remove(slotnimg.c_str());
                 }
                 is.close();
             }
         }
     }
}

//*******************************
// PsGame::isResumeSlotActive
//*******************************
bool PsGame::isResumeSlotActive(int slot) {
    if (!foreign) {
        string filenamefile = ssFolder + "filename.txt.res";
        string filenamepoint = ssFolder + "filename." + to_string(slot) + ".txt.res";
        if (DirEntry::exists(filenamepoint)) {
            filenamefile = filenamepoint;
        }
        if (DirEntry::exists(filenamefile)) {
            ifstream is(filenamefile.c_str());
            if (is.is_open()) {

                std::string line;
                std::getline(is, line);
                std::getline(is, line);

                // last line is our filename
                if (slot == 0) {
                    string slot0img = ssFolder + "screenshots/" + line + ".png.res";
                    if (DirEntry::exists(slot0img)) {
                        return true;
                    }
                } else {
                    string slotnimg = ssFolder + "screenshots/" + line + "." + to_string(slot) + ".png.res";
                    if (DirEntry::exists(slotnimg)) {
                        return true;
                    }
                }
                is.close();
            }
        }
    }
    return false;
}

//*******************************
// PsGame::storeResumePicture
//*******************************
void PsGame::storeResumePicture(int slot) {
    if (!foreign) {
        string filenamefile = ssFolder + "filename.txt.res";
        string filenamepoint = ssFolder + "filename." + to_string(slot) + ".txt.res";
        if (DirEntry::exists(filenamepoint)) {
            filenamefile = filenamepoint;
        }
        if (DirEntry::exists(filenamefile)) {
            ifstream is(filenamefile.c_str());
            if (is.is_open()) {

                std::string line;
                std::getline(is, line);
                std::getline(is, line);

                string inputImg = ssFolder + "screenshots/" + line + ".png";
                if (!DirEntry::exists(inputImg)) {
                    return;
                }
                string slotImg;
                // last line is our filename
                if (slot == 0) {
                    slotImg = ssFolder + "screenshots/" + line + ".png.res";

                } else {
                    slotImg = ssFolder + "screenshots/" + line + "." + to_string(slot) + ".png.res";
                }
                is.close();

                remove(slotImg.c_str());
                DirEntry::copy(inputImg, slotImg);
                remove(inputImg.c_str());
            }
        }
    }
}

//*******************************
// PsGame::findResumePicture
//*******************************
string PsGame::findResumePicture(int slot) {
    if (!foreign) {
        string filenamefile = ssFolder + "filename.txt.res";
        string filenamepoint = ssFolder + "filename." + to_string(slot) + ".txt.res";
        if (DirEntry::exists(filenamepoint)) {
            filenamefile = filenamepoint;
        }
        if (DirEntry::exists(filenamefile)) {
            ifstream is(filenamefile.c_str());
            if (is.is_open()) {

                std::string line;
                std::getline(is, line);
                std::getline(is, line);

                // last line is our filename
                if (slot == 0) {
                    string slot0img = ssFolder + "screenshots/" + line + ".png.res";
                    if (DirEntry::exists(slot0img)) {
                        return slot0img;
                    }
                } else {
                    string slotnimg = ssFolder + "screenshots/" + line + "." + to_string(slot) + ".png.res";
                    if (DirEntry::exists(slotnimg)) {
                        return slotnimg;
                    }
                }
                is.close();
            }
        }
    }
    return "";
}


//*******************************
// PsGame::findResumePicture
//*******************************
string PsGame::findResumePicture() {
    // try to do it in silly Sony way
    if (!foreign) {
        string filenamefile = ssFolder + "filename.txt.res";
        for (int i = 0; i < 4; i++) {
            string filenamepoint = ssFolder + "filename." + to_string(i) + ".txt.res";
            if (DirEntry::exists(filenamepoint)) {
                filenamefile = filenamepoint;
                break;
            }
        }
        if (DirEntry::exists(filenamefile)) {
            ifstream is(filenamefile.c_str());
            if (is.is_open()) {

                std::string line;
                std::getline(is, line);
                std::getline(is, line);

                // last line is our filename
                string pngfile = ssFolder + "screenshots/" + line + ".png.res";
                if (DirEntry::exists(pngfile)) {
                    return pngfile;
                }
                is.close();
            }
        }
    }
    return "";
}