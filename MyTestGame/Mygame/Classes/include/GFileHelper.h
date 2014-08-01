#ifndef _G_FILE_HELPER
#define _G_FILE_HELPER
#include "cocos2d.h"
#include <string>
#include "include/sqlite3.h"
USING_NS_CC;
using namespace std;


class SkillModel
{
public:
	SkillModel(){};
	~SkillModel(){};
	bool IsBuy;
	int SkillLv;
	bool Unlock;
	string Introduction;
	string Norma;
	string Pressed;
	string light_skill;
};
class MYSkillModel
{
public:
	MYSkillModel(){};
	~MYSkillModel(){};
	int SkillNum;
	string Norma;
	string Pressed;
	string light_skill;
};
class GFileHelper
{
public:
	static GFileHelper* Singleton();
	///索引 0开始
	void UpdataModels(int lv);  //更新技能和快捷键
	void SetSkillModel(int lv); //更新技能
	int GetWeaponLv(int type);	//跟换武器
	SkillModel* GetSkillModel(int num);
	bool SaveSkillModel(SkillModel* model,int num);
	void SetMYSkillModel();
	MYSkillModel* GetMYSkillModel(int num);
	bool SaveMYSkillModel(MYSkillModel* model,int num);

	~GFileHelper();
	void CreateOrOpen();
	void CreateNewFile();
	//string getFileByName(string pFileName); 
	bool saveFile(char* pContent,string pFileName);  
	char** GetStringArray(const char* sql,int count); 
	void SetAddSkillPoints(int points);  //跟心技能点
	void SetWeaponLvUp(int index);
	static char* armsarray[6];
private:
	///sqlite
	sqlite3 *pDB;
	static char** arraysql;
	static int arraycout;
	static int loadRecord( void * para, int n_column, char ** column_value, char ** column_name );
	void CopyDbToWritablePath(const char* pFileName); //复制db
	void ConnectionDb(const char* pFileName);         //连接
	SkillModel *skill_model;						 //技能model
	MYSkillModel *my_skill_model;					//快捷键model
	static GFileHelper* _gFileHelper;
	CCDictionary *strings;
	GFileHelper();
	void Create();
	class CGarbo
	{  
	public:  
		~CGarbo()  
		{  
			if (GFileHelper::_gFileHelper)  
				delete GFileHelper::_gFileHelper;  
		}  
	};  
	static CGarbo Garbo;
};

#endif