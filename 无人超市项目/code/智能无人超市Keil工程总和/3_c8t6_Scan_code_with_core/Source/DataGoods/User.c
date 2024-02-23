#include "User.h"
#include "config.h"
User user[USERNUM];
unsigned int UserNum=0;;
	
void Init_User(void)
{
	W25QXX_Read((u8*)&UserNum,1024-4,4);
	if(UserNum<'\xff')
	for(int i=0;i<UserNum;i++)
	{
		W25QXX_Read((u8*)(user+i),1024+i*44,44);
	}else
	{
		UserNum=0;
	}
	
}
void Save_user_falsh(void)
{
	user[0].ID=1;
	sprintf(user[0].Name,"%s","吴艺彬");
	sprintf(user[0].Phone,"%s","123456");
	UserNum=1;
//	W25QXX_Write((u8*)&UserNum,1024-4,4);
//	for(int i=0;i<UserNum;i++)
//	{
//		W25QXX_Write((u8*)(user+i),1024+i*44,44);
//	}
}
void Add_User(void)
{
	UserNum++;
}
void Get_user_uaer(int id)
{
	
}

