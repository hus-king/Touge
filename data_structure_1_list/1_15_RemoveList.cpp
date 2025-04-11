#include "def.h"
#include "my.h"
status RemoveList(LISTS &Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName) == 0) {
            for (int j = i; j < Lists.length - 1; j++) {
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}
int main() {
	LISTS Lists;
   int n,e;
   char name[30];
   Lists.length=0;
	scanf("%d", &n);
	while(n--)
   {
    	scanf("%s",name);
   		AddList(Lists,name);
      scanf("%d",&e);
      while (e)
      {
      		ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
      		scanf("%d",&e);
      }
   }
   scanf("%s",name);
   if (RemoveList(Lists,name)==OK)
	   for(n=0;n<Lists.length;n++)
   		{
   			printf("%s ",Lists.elem[n].name);
   			ListTraverse(Lists.elem[n].L);
        	putchar('\n');
   		}
   else printf("删除失败");
return 1;
}