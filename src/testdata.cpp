#include "mesdata.h"
#include <stdlib.h>

int main()
{
	MesData m;
	m.SetMesId("001");
	m.SetUserId("yjx");
	m.SetLbmId("1001");
	m.SetValue("a", "1");
	m.SetValue("b", "1.109");
	m.SetValue("c", "hello");
	cout << m.GetParams() << endl;
	MesData n;
	n.SetParams("MesId:002,UserId:yyy,LbmId:1002,a:345,c:tututuy,D:caooo");
	cout<<n.GetParams()<<endl;
	MesData* p;
	p = (MesData*)malloc(sizeof(MesData));
	MesData* q = new MesData();
	p = q;
	delete q;
	p->SetLbmId("123456");
//	p->SetParams("MesId:002,UserId:yyy,LbmId:1002,a:345,c:tututuy,D:caooo");
	cout << p->GetParams()<<endl;
	free(q);
}
