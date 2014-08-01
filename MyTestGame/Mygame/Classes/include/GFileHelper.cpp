#include "GFileHelper.h"
#include <fstream>
//#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//#include <android/log.h>
//#define  LOG_TAG    "TestGame"
//#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
//#endif

const char* Normalpng[5]={"attack_skill.png","paoxiao.png","paiji.png","nailuo.png","duyao.png"};
const char* Pressedpng[5]={"attack_skill1.png","paoxiao1.png","paiji1.png","nailuo1.png","duyao1.png"};
const char* Disabledpng="lock.png";
const char* light_skill="light_skill.png";
const char* pFileName="GameConfig.db";
//const char* pFileName="fps_images.png";
const string _isbuy="Skill_";
const string _SkillLv="Skill_Lv_";
const string _unlock="Skill_Unlock_";
const string _introduction="Hero_Skill_Introduction";
const string _Skill_Button="Skill_Button";
const string _Weapon="Weapon_";
const string data_select;
int GFileHelper::arraycout=0;
char** GFileHelper::arraysql=NULL;
char* GFileHelper::armsarray[6]={"arms1.png","arms2.png","arms3.png","arms4.png","arms5.png","arms6.png"};

int GFileHelper::loadRecord( void * para, int n_column, char ** column_value, char ** column_name )
{
	arraysql=new char*[arraycout];
	int i= 0;
	while (i<arraycout)
	{
		int columncout=strlen(column_value[i]);
		arraysql[i]=new char[columncout+1];
		strcpy(arraysql[i],column_value[i]);
		i++;
	}
	return 0; 
}

char** GFileHelper::GetStringArray(const char* sql,int count )
{
	arraycout=count;
	char * errMsg = NULL;
	int result;//sqlite3_exec返回值 
	result = sqlite3_exec( pDB, sql ,loadRecord, NULL, &errMsg ); 
	delete errMsg;
	if (result!=SQLITE_OK)
	{
		return NULL;
	}
	return arraysql;
}

GFileHelper::GFileHelper()
{
	strings = CCDictionary::createWithContentsOfFile("GameLanguage/SimplifiedChinese.xml"); 
	strings->retain();
	skill_model=new SkillModel[5];
	my_skill_model=new MYSkillModel[4];
	int lv= CCUserDefault::sharedUserDefault()->getIntegerForKey("My_Lv");
	UpdataModels(lv);  //读取技能model
	stringstream ss;
	ss<<CCFileUtils::sharedFileUtils()->getWritablePath()<<pFileName;
	string s=ss.str();
	if (!CCFileUtils::sharedFileUtils()->isFileExist(s.c_str()))
	{
		CopyDbToWritablePath(pFileName);
	}
	ConnectionDb(pFileName);
	//#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	//	LOGD("YOU Login This");
	//#endif
}

GFileHelper::~GFileHelper()
{
	_gFileHelper=NULL;
	CC_SAFE_DELETE(strings);
	CC_SAFE_DELETE_ARRAY(skill_model);
	CC_SAFE_DELETE_ARRAY(my_skill_model);
	//关闭数据库 
	sqlite3_close(pDB); 
}
GFileHelper::CGarbo GFileHelper::Garbo;

bool GFileHelper::saveFile( char* pContent,string pFileName )
{
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;  
	CCLOG("wanna save file path = %s",path.c_str());  

	//创建一个文件指针  
	//路径、模式  
	FILE* file = fopen(path.c_str(), "w");  
	if (file) {  
		fputs(pContent, file);  
		fclose(file); 
		return true;
	}  
	else  
		CCLOG("save file error.");  

	return false;  
}
GFileHelper* GFileHelper::_gFileHelper=NULL;
GFileHelper* GFileHelper::Singleton()
{
	if (_gFileHelper==NULL)
	{
		_gFileHelper=new GFileHelper();
	}
	return _gFileHelper;
}
void GFileHelper::CreateOrOpen()
{
	bool isExist= CCUserDefault::sharedUserDefault()->getBoolForKey("IsFile");
	if (!isExist)
	{
		Create();
	}
}

void GFileHelper::CreateNewFile()
{
	Create();
}
void GFileHelper::Create()
{
	//sqlite3_close(pDB); 
	CopyDbToWritablePath(pFileName);
	ConnectionDb(pFileName);

	CCUserDefault::sharedUserDefault()->setBoolForKey("IsFile", true);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Chapter", 1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Lv", 1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Exp", 1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_SkillPoints", 1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("MY_Gold", 1500);
	///技能等级
	CCUserDefault::sharedUserDefault()->setBoolForKey("Skill_1", true);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Lv_1",1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Unlock_1",1);
	CCUserDefault::sharedUserDefault()->setBoolForKey("Skill_2", false);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Lv_2",0);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Unlock_2",1);
	CCUserDefault::sharedUserDefault()->setBoolForKey("Skill_3", false);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Lv_3",0);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Unlock_3",2);
	CCUserDefault::sharedUserDefault()->setBoolForKey("Skill_4", false);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Lv_4",0);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Unlock_4",4);
	CCUserDefault::sharedUserDefault()->setBoolForKey("Skill_5", false);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Lv_5",0);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Unlock_5",9);
	///武器
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Weapon",1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Weapon_1",1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Weapon_2",1);
	///技能栏
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Button1",1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Button2",0);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Button3",0);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Skill_Button4",0);
	CCUserDefault::sharedUserDefault()->flush();
	UpdataModels(1);
}
int GFileHelper::GetWeaponLv( int type )
{
	ostringstream oss;
	oss<<_Weapon<<type;
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(oss.str().c_str());
}
void GFileHelper::SetWeaponLvUp( int index )
{
	string s;
	ostringstream oss;
	oss<<_Weapon<<index+1;
	s=oss.str();
	int lv=CCUserDefault::sharedUserDefault()->getIntegerForKey(s.c_str());
	CCUserDefault::sharedUserDefault()->setIntegerForKey(s.c_str(),lv+1);
}
void GFileHelper::SetAddSkillPoints( int points )
{
	int data=CCUserDefault::sharedUserDefault()->getIntegerForKey("My_SkillPoints");
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_SkillPoints",data+points);
}

void GFileHelper::SetSkillModel(int lv)
{
	for (int i=1;i<=5;i++)
	{ 
		SkillModel *model=&skill_model[i-1];
		string c;
		ostringstream oss;
		oss<<i;
		c=oss.str();
		model->IsBuy=CCUserDefault::sharedUserDefault()->getBoolForKey((_isbuy+c).c_str());
		model->SkillLv=CCUserDefault::sharedUserDefault()->getIntegerForKey((_SkillLv+c).c_str());
		model->Unlock=CCUserDefault::sharedUserDefault()->getIntegerForKey((_unlock+c).c_str())<=lv?false:true;
		model->light_skill=light_skill;
		CCString* str=(CCString*)strings->objectForKey(_introduction+c);
		model->Introduction=str->m_sString;
		if (model->Unlock)
		{
			model->Norma=Disabledpng;
			model->Pressed=Disabledpng;
		}
		else if (model->IsBuy)
		{
			model->Norma=Normalpng[i-1];
			model->Pressed=Pressedpng[i-1];
		}
		else if (!model->IsBuy)
		{
			model->Norma=Pressedpng[i-1];
			model->Pressed=Pressedpng[i-1];
		}
	}
}
SkillModel* GFileHelper::GetSkillModel( int num )
{
	return &skill_model[num];
}
bool GFileHelper::SaveSkillModel( SkillModel* model,int num )
{
	skill_model[num]=*model;
	string c;
	ostringstream oss;
	oss<<num+1;
	c=oss.str();
	CCUserDefault::sharedUserDefault()->setBoolForKey((_isbuy+c).c_str(),model->IsBuy);
	CCUserDefault::sharedUserDefault()->setIntegerForKey((_SkillLv+c).c_str(),model->SkillLv);
	if (model->Unlock)
	{
		model->Norma=Disabledpng;
		model->Pressed=Disabledpng;
	}
	else if (model->IsBuy)
	{
		model->Norma=Normalpng[num];
		model->Pressed=Pressedpng[num];
	}
	else if (!model->IsBuy)
	{
		model->Norma=Pressedpng[num];
		model->Pressed=Pressedpng[num];
	}
	return true;
}

void GFileHelper::SetMYSkillModel()
{
	for (int i=1;i<=4;i++)
	{ 
		MYSkillModel *model=&my_skill_model[i-1];
		string c;
		ostringstream oss;
		oss<<i;
		c=oss.str();
		model->SkillNum=CCUserDefault::sharedUserDefault()->getIntegerForKey((_Skill_Button+c).c_str());
		model->light_skill=light_skill;
		if (model->SkillNum!=0)
		{
			SkillModel* skillmodel= GetSkillModel(model->SkillNum-1);
			model->Norma=skillmodel->Norma;
			model->Pressed=skillmodel->Pressed;
		}
	}
}

MYSkillModel* GFileHelper::GetMYSkillModel( int num )
{
	return &my_skill_model[num];
}

bool GFileHelper::SaveMYSkillModel( MYSkillModel *model,int num )
{
	my_skill_model[num]=*model;
	string c;
	ostringstream oss;
	oss<<num+1;
	c=oss.str();
	CCUserDefault::sharedUserDefault()->setIntegerForKey((_Skill_Button+c).c_str(),model->SkillNum);
	if (model->SkillNum!=0)
	{
		SkillModel* skillmodel= GetSkillModel(model->SkillNum-1);
		model->Norma=skillmodel->Norma;
		model->Pressed=skillmodel->Pressed;
	}
	return true;
}

void GFileHelper::UpdataModels(int lv)
{
	SetSkillModel(lv);
	SetMYSkillModel();
}

void GFileHelper::CopyDbToWritablePath( const char* pFileName )
{
	//#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	//	LOGD("New Game");
	//#endif
	string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName);
	int b=CCFileUtils::sharedFileUtils()->isFileExist(strPath);
	if (b>0)
	{
		string destPath = CCFileUtils::sharedFileUtils()->getWritablePath();
		destPath += pFileName;
#if (CC_TARGET_PLATFORM!=CC_PLATFORM_ANDROID)
		ifstream is(strPath.c_str(),ios::binary);
		ofstream os(destPath.c_str(),ios::binary);
		os << is.rdbuf(); 
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		unsigned long len=0;
		unsigned char* data =NULL;
		data = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(),"r",&len);
		FILE *pFp=fopen(destPath.c_str(),"w+");
		fwrite(data,sizeof(char),len,pFp);
		fclose(pFp);
		delete []data;
		data=NULL;
#endif
	}
}

void GFileHelper::ConnectionDb( const char* pFileName )
{
	pDB = NULL;
	char * errMsg = NULL;
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	//打开一个数据库，如果该数据库不存在，则创建一个数据库文件 
	stringstream ss;
	ss<<CCFileUtils::sharedFileUtils()->getWritablePath()<<pFileName;
	string s=ss.str();
	#if (CC_TARGET_PLATFORM!=CC_PLATFORM_ANDROID)
		result = sqlite3_open("GameConfig.db", &pDB); 
	#endif
	#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		result = sqlite3_open(s.c_str(), &pDB); 
	#endif
	if( result != SQLITE_OK ) 
	{
		CCLog( "打开数据库失败，错误码:%d ，错误原因:%s\n" , result, errMsg ); 
	}
}