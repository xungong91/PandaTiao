#ifndef _G_SHOP_LAYER_H_
#define _G_SHOP_LAYER_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GDialogLayer.h"
#include <string>

USING_NS_CC_EXT;
USING_NS_CC;
using namespace std;

class GShopDelegate {
public:
	virtual void onShopCloseActivated(CCLayer* layer){};
};
class GSkillModel
{
public:
	GSkillModel();
	~GSkillModel();
	bool IsBuy;
	int Price;
	//true为没锁
	bool Unlock;
	string Introduction;
private:
};
class GShopLayer:public CCLayer,public GDialogDelegate
{
public:
	static GShopLayer* Singleton();
	~GShopLayer();
	GShopDelegate *_delegate;
	void ButtonClick(CCObject* sender);
	void SkillbuttonEvent(CCObject *pSender);
	void ButtonTouchEvent( CCObject *pSender, TouchEventType type );
	void BuyTouchEvent( CCObject *pSender, TouchEventType type );

	void WeaponbuttonEvent(CCObject *pSender);
	void WeaponTouchEvent( CCObject *pSender, TouchEventType type );
	void WeaponBuyTouchEvent( CCObject *pSender, TouchEventType type );

	void SetDialog(GShopDelegate* _delegate);
	virtual void onOkActivated(const char* sender,CCLayer* layer);;
	virtual void onCancelActivated(const char* sender,CCLayer* layer);;
private:
	static GShopLayer* _m_Shop;
	UILayer *m_uILayer;
	CREATE_FUNC(GShopLayer);
	bool init();
	GShopLayer();
	CCDictionary *strings;
	CCArray* array_uibutton;
	CCArray* array_weapon;
	//GSkillModel* model;
	//UILabel* skill_LabelPiece;
	UITextButton* skill_Buy;
	UILabel* Lv_Label;
	//UILabel* Gold_Label;
	UILabel* points;
	int skillpoints;           
	void Setskillpoints_Label();
	UITextArea* skill_TextArea;
	int SelectButtonNum;		//选择的技能
	void SetGDialog(const char* data);
	void SetSkillButton(int num);
	int SelectWeaponNum;		//选择的武器
	void updataGold_Label();   //更新金钱
	void updataWeaponButton(CCObject* image);
	int updataWeapon(CCObject* image);
	class CGarbo
	{
	public:
		~CGarbo()
		{
			CC_SAFE_RELEASE(GShopLayer::_m_Shop);
		}
	};
	static CGarbo garbo;
};

#endif