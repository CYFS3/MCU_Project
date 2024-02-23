#ifndef _USER_H__
#define _USER_H__

#define USERNAMEMAX 20
#define USERPHONEMAX 20
#define USERNUM 20
typedef struct{
	int ID;
	char Name[USERNAMEMAX];
	char Phone[USERPHONEMAX];
	
}User;

extern User user[USERNUM];
extern unsigned int UserNum;

void Init_User(void);
void Save_user_falsh(void);
void Add_User(void);
void Get_user_uaer(int id);

#endif
