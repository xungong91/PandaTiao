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
	///���� 0��ʼ
	void UpdataModels(int lv);  //���¼��ܺͿ�ݼ�
	void SetSkillModel(int lv); //���¼���
	int GetWeaponLv(int type);	//��������
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
	void SetAddSkillPoints(int points);  //���ļ��ܵ�
	void SetWeaponLvUp(int index);
	static char* armsarray[6];
private:
	///sqlite
	sqlite3 *pDB;
	static char** arraysql;
	static int arraycout;
	static int loadRecord( void * para, int n_column, char ** column_value, char ** column_name );
	void CopyDbToWritablePath(const char* pFileName); //����db
	void ConnectionDb(const char* pFileName);         //����
	SkillModel *skill_model;						 //����model
	MYSkillModel *my_skill_model;					//��ݼ�model
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