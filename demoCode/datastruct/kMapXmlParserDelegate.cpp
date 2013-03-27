//
//  kMapXmlParserDelegate.cpp
//
//  Created by kael on 12/26/12.
//
//

#include "kMapXmlParserDelegate.h"
#include "kCommonStruct.h"
using namespace rapidxml;
using namespace std;
#include<string>
void kMapXmlParserDelegate::toStruct(const rapidxml::xml_document<>& doc,void* pdata)
{
    xml_node<> *root = doc.first_node("map");
    string attrid;
    kMapStruct* kms = (kMapStruct*)pdata;
    K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrid, root, "id");
    kms->mid = atoi(attrid.c_str());
    
    string attrname;
    K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrname, root, "name");
    kms->name = attrname;
    
    string attrix;
    K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrix, root, "initX");
    kms->initx = atoi(attrix.c_str());
    
    string attriy;
    K_GET_RAPIDXML_ATTRIBUTE_VALUE(attriy, root, "initY");
    kms->inity = atoi(attriy.c_str());
    
    string attrwa;
    K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrwa, root, "walkArr");
    kms->walkArr = attrwa;
    
    string attrcolumn;
    K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrcolumn, root, "column");
    kms->column = atoi(attrcolumn.c_str());
    
    xml_node<>* childnode = root->first_node();
    while (childnode) {
        if (strcmp(childnode->name(),"npc") == 0) {
            kNpcStruct npc;
            string attrnid;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrnid, childnode, "id");
            npc.id =atoi(attrnid.c_str());
            
            string attrnname;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrnname, childnode, "name");
            npc.name = attrnname;
            
            string attrnic;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrnic, childnode, "icon");
            npc.icon = attrnic;
            
            string attrnfa;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrnfa, childnode, "face");
            npc.face = attrnfa;
            
            string attrnd;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrnd, childnode, "dialog");
            npc.dialogure = attrnd;
            
            string attrnx;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrnx, childnode, "x");
            npc.x = atoi(attrnx.c_str());
            
            string attrny;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrny, childnode, "y");
            npc.y = atoi(attrny.c_str());
            
            kms->npclist[npc.id] = npc;
        }
        else if(strcmp(childnode->name(),"cfb") == 0)
        {
            string attrfx;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrfx, childnode, "x");
            kms->normal.x =atoi(attrfx.c_str());
            
            string attrfy;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrfy, childnode, "y");
            kms->normal.y =atoi(attrfy.c_str());
            
            string attrfl;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrfl, childnode, "fbList");
            kms->normal.fbList = attrfl.c_str();
        }
        else if(strcmp(childnode->name(),"hfb") == 0)
        {
            string attrfx;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrfx, childnode, "x");
            kms->hero.x =atoi(attrfx.c_str());
            
            string attrfy;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrfy, childnode, "y");
            kms->hero.y =atoi(attrfy.c_str());
            
            string attrfl;
            K_GET_RAPIDXML_ATTRIBUTE_VALUE(attrfl, childnode, "fbList");
            kms->hero.fbList = attrfl.c_str();
        }
        childnode = childnode->next_sibling();
    }
}